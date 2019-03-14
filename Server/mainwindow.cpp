#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QClipboard>
#include <QThread>

#include "socketreaderwriter.h"
#include "myserverfile.h"
#include "servicemessage.h"
#include "usermessage.h"
#include "networkthread.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->usertable->setColumnCount(4);
    ui->usertable->setRowCount(1);
    ui->usertable->setHorizontalHeaderLabels(QStringList() << "Domain" << "Host" << "Name" << "Pooling time");
    ui->usertable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->usertable->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_CopyButton_clicked()
{
    QApplication::clipboard()->setText(ui->input_port->text());
}

void MainWindow::on_StartServerButton_clicked()
{
    //To DO:
    server.SetConnectionPort(ui->input_port->text().toInt());

    NetworkThread* N = new NetworkThread(server);
    connect(N, SIGNAL(finished()), N, SLOT(deleteLater()));
    N->start();

    connect(&server, SIGNAL(sentData(QString, QString, QString, int)), this, SLOT(fillactiveusers(QString, QString, QString, int)));
    connect(&server, SIGNAL(sentMessage(QString)), this, SLOT(fillchatarea(QString))/*, Qt::DirectConnection*/);
    connect(&server, SIGNAL(disconnect(QString)), this, SLOT(removeuser(QString)));

    ui->StartServerButton->setDisabled(true);
}

void MainWindow::fillactiveusers(QString dom, QString ho, QString na, int po)
{
    //add items to table
    row_amount = ui->usertable->rowCount();
    ui->usertable->setItem(row_amount - 1, 0, new QTableWidgetItem(dom));
    ui->usertable->setItem(row_amount - 1, 1, new QTableWidgetItem(ho));
    ui->usertable->setItem(row_amount - 1, 2, new QTableWidgetItem(na));
    ui->usertable->setItem(row_amount - 1, 3, new QTableWidgetItem(QString::number(po)));
    ui->usertable->setRowCount(row_amount + 1);

}


void MainWindow::fillchatarea(QString text)
{

    ui->chatarea->append(text);
}

void MainWindow::removeuser(QString str)
{
    QString name = Message::GetUserNameFromString(str);
    QTableWidgetItem* itm = ui->usertable->findItems(name,Qt::MatchContains).first();
    ui->usertable->removeRow(itm->row());
}

