#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myserverfile.h"

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
    void on_CopyButton_clicked();

    void on_StartServerButton_clicked();

public slots:
    void fillactiveusers(QString dom, QString ho, QString na, int po);
    void fillchatarea(QString);
    void removeuser(QString);


private:
    Ui::MainWindow *ui;
    Network server;
    int row_amount;
};

#endif // MAINWINDOW_H
