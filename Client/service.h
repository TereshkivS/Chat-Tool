#ifndef SERVICE_H
#define SERVICE_H

#include <QObject>
#include <QTimer>

class Service : public QObject {
    Q_OBJECT
public:
    Service(int sock, QObject * parent = 0);
    ~Service();




public slots:
    void ReadingMessages();

signals:
    void recieveMessage(QString);



private:
    int client_socket;
    int pollingperiod;

};

#endif // SERVICE_H
