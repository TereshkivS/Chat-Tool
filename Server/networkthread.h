#ifndef NETWORKTHREAD_H
#define NETWORKTHREAD_H
#include "myserverfile.h"
#include <QThread>

class NetworkThread : public QThread{
    Q_OBJECT
public:
    NetworkThread(Network & n) : _n(n)
    {

    }

public:
    void run() override{
        _n.CreateNetworkConnections();
    }


private:
    Network& _n;

};


#endif // NETWORKTHREAD_H
