#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "socketreaderwriter.h"
#include "service.h"
#include "servicemessage.h"

#include <QTimer>
#include <QThread>
#include <QHostInfo>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->input_host->setPlaceholderText("127.0.0.1");

}

MainWindow::~MainWindow()
{
    int socket = client.getExistingSocket();
    char buf[100];
    strcpy(buf, SM.DisconnectMessage().toStdString().c_str());
    int buflen = strlen(buf);
    Socketreaderwriter::write(socket, buf, buflen);
    if(-1 == shutdown(socket, SD_BOTH)){
        qDebug() << "Cannot shutdown socket";
    }
    closesocket(socket);
    delete ui;
}

void MainWindow::on_ConnectButton_clicked()
{
    int socket;
    char buf[1000];

    SM.SetName(ui->input_username->text());
    SM.SetHost(QHostInfo::localHostName());
    SM.SetDomain(QHostInfo::localDomainName());
    SM.SetPoolingPeriod(ui->input_period->text().toInt());
    UM.SetSenderName(ui->input_username->text());


    if(ui->input_host->text().isEmpty())
        ui->input_host->setText("127.0.0.1");
    client.CreateConnectSocket(ui->input_port->text().toInt(),
                               ui->input_host->text().toStdString().c_str());

    socket = client.getExistingSocket();
    if(socket > 0)
        ui->ConnectButton->setDisabled(true);
    else {
        qDebug() << "Cannot connect socket ";
        return;
    }

    strcpy(buf, SM.FormMessage(SM.GetName(),
                               SM.GetHost(),
                               SM.GetDomain(),
                               SM.GetPoolingPeriod()).toStdString().c_str());

    int buflen = strlen(buf);
    Socketreaderwriter::write(socket, buf, buflen);

    //create thread responsible for reading data from the server
    QThread* readingthread = new QThread;
    Service* service = new Service(socket);
    QTimer * timer = new QTimer(0);
    timer->setInterval(SM.GetPoolingPeriod());
    service->moveToThread(readingthread);
    timer->moveToThread(readingthread);
    connect(readingthread, SIGNAL(started()), timer, SLOT(start()));
    connect(timer, SIGNAL(timeout()), service, SLOT(ReadingMessages()));
    connect(readingthread, SIGNAL(finished()), timer, SLOT(stop()));       // ???
    readingthread->start();
    connect(service, SIGNAL(recieveMessage(QString)), this, SLOT(fillCharArea(QString)));


}

void MainWindow::on_SendButton_clicked()
{
    char buf[1500];
    memset(buf, 0, 1500);
    if(!ui->anoncheckbox->isChecked()){
        UM.FormMessage(UM.GetSenderName(), ui->input_message->toPlainText());

        strcpy(buf, UM.GetBuffer().toStdString().c_str());
        int lenbuf = strlen(buf);

        if(Socketreaderwriter::write(client.getExistingSocket(), buf, lenbuf) < 0)
            qDebug() << "Cannot send message ";

//        Socketreaderwriter::sendmessagetoserver(ui->input_message->toPlainText(),
//                                                ui->input_username->text(),
//                                                client.getExistingSocket(),
//                                                SendState::NOT_ANON_MES);
    }
    else{
        UM.FormMessage("Anonymous", ui->input_message->toPlainText());

        strcpy(buf, UM.GetBuffer().toStdString().c_str());
        int lenbuf = strlen(buf);

        if(Socketreaderwriter::write(client.getExistingSocket(), buf, lenbuf) < 0)
            qDebug() << "Cannot send message ";


//        Socketreaderwriter::sendmessagetoserver(ui->input_message->toPlainText(),
//                                                ui->input_username->text(),
//                                                client.getExistingSocket(),
//                                                SendState::ANON_MES);
    }

    ui->input_message->clear();

}

void MainWindow::setSendButtonEnable()
{
    ui->SendButton->setEnabled(true);
}

void MainWindow::fillCharArea(QString str)
{
    ui->chatarea->append(str);
}
