#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myclient.h"
#include "servicemessage.h"
#include "usermessage.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_ConnectButton_clicked();

    void on_SendButton_clicked();

    void setSendButtonEnable();

    void fillCharArea(QString);

signals:
    void send(QByteArray);


private:
    Ui::MainWindow *ui;
    MyClient client;
    ServiceMessage SM;
    UserMessage UM;

};

#endif // MAINWINDOW_H
