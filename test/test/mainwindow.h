#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

class TCPInterface :public QObject
{
    Q_OBJECT
public:
    explicit TCPInterface(QObject *parent = Q_NULLPTR);
//    TCPInterface();

    virtual ~TCPInterface() {}
    void readData();
    QTcpSocket *socket = nullptr;
    QString publicIP;
    int publicPort;

public slots:
    void readyReadData();
signals:
};

#endif // MAINWINDOW_H
