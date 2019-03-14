#include "clientservice.h"
#include "socketreaderwriter.h"
#include "servicemessage.h"
#include "usermessage.h"
#include <QThread>
#include "WinSock2.h"

ClientService::ClientService(int clsock, char *name, int pperiod, QObject *parent)
{
    client_socket = clsock;
    strcpy(username, name);
    pollingperiod = pperiod;
}

ClientService::~ClientService()
{

}


void ClientService::UserService()
{
    char temp_buf[1000];
    memset(temp_buf, 0, 1000);
    if(Socketreaderwriter::read(client_socket, temp_buf, 1000) >= 0){
        QString Buf(temp_buf);
        if(Buf == ServiceMessage::DisconnectMessage()){
            Message::AddToFront(Buf, username);
            emit disconnect(Buf);
            emit finish(QThread::currentThread());
        }
        else{

            emit sentMessageClient(Buf);
        }
    }

}

void ClientService::ReleaseSocket()
{
    if(shutdown(client_socket ,SD_BOTH) == -1)
        qDebug() << "Can\'t shutdown the socket!";
    closesocket(client_socket);
}
