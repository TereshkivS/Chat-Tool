#include "myclient.h"
#include <QDebug>
#include "WinSock2.h"
#include "socketreaderwriter.h"

MyClient::MyClient(QObject *parent)
{


}

MyClient::~MyClient()
{
    //DiscSocket();
}

int MyClient::CreateConnectSocket(int port, const char *addr)
{
    /*to prevent 10093 socket error*/
    int iResult;
    WSADATA wsaData;
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);

    struct hostent *hostp;
    struct sockaddr_in serveraddr;

    if ((connectsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        qDebug() << "Socket createion falied";
        return -1;
    }

    memset(&serveraddr, 0, sizeof(serveraddr));

    serveraddr.sin_family = AF_INET;

    //hostp = gethostbyname(machine);
    //memcpy(&serveraddr.sin_addr, hostp->h_addr, hostp->h_length);
    serveraddr.sin_addr.s_addr = inet_addr(addr);
    serveraddr.sin_port = htons(port);

    if(::connect(connectsocket, (struct sockaddr *)&serveraddr, sizeof serveraddr) < 0)
    {
        closesocket(connectsocket);
        qDebug("Cannot connect to server");
        return -3;
    }
    qDebug() << "Create socket !!";

    return connectsocket;
}

int MyClient::getExistingSocket()
{
    return connectsocket;
}

void MyClient::DiscSocket()
{

//    char msgp[] = "#disconnect";
//    int bufmes = strlen(msgp);
//    Socketreaderwriter::write(connectsocket, msgp, bufmes);
//    if(-1 == shutdown(connectsocket, SD_BOTH)){
//        qDebug() << "Cannot shutdown socket";
//    }
//    closesocket(connectsocket);

}

void MyClient::connected()
{
    qDebug() << "Connected ";
}

void MyClient::disconnected()
{
    qDebug() << "Disconnected ";
}
