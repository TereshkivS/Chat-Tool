#ifndef MYSERVERFILE_H
#define MYSERVERFILE_H

#include <QObject>
#include "clientservice.h"
#include "usermessage.h"
#include "servicemessage.h"

class Network : public QObject {
    Q_OBJECT
public:
    Network(QObject * parent = 0);
    ~Network();


    int CreateListenSocket(int port);
    int Accept(int listensock);
    void SetConnectionPort(int);

public slots:
    void CreateNetworkConnections();
    int ShutDownSockets();
    void SendMessageToAllClients(QString);
    void StopThread(QThread *);



signals:
    void sentData(QString dom, QString ho, QString nam, int po);
    void sentMessage(QString);
    void disconnect(QString);



private:
    int server_socket;
    int client_socket;
    QList<QThread* > threadPool;
    QList<int> sockets;
    char buf[1000];
    int port;

    UserMessage UM;
    ServiceMessage SM;


};

#endif // MYSERVERFILE_H
