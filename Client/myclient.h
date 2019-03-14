#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <QObject>
#include "myclient.h"

class MyClient : public QObject{
    Q_OBJECT

public:
    MyClient(QObject* parent = 0);
    ~MyClient();

    int CreateConnectSocket(int port, const char * addr);
    int getExistingSocket();

public slots:
    void DiscSocket();


private slots:
    void connected();
    void disconnected();




private:
    int connectsocket;
};

#endif // MYCLIENT_H
