#include "service.h"
#include "socketreaderwriter.h"
#include <QThread>
#include "WinSock2.h"


Service::Service(int sock, QObject *parent)
{
    client_socket = sock;
}

Service::~Service()
{

}

void Service::ReadingMessages()
{
    char temp_buf[1000];
    memset(temp_buf, 0, 1000);
    if(Socketreaderwriter::read(client_socket, temp_buf, 1000) >= 0){
        QString Buf(temp_buf);
        if(Buf.at(0) == '#')
            ;//set into setting
        else{

            emit recieveMessage(Buf);
        }
    }
}

