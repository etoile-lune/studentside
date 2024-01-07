#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H

#include <QObject>
#include<QTcpSocket>
#include<QDebug>
#include <QByteArray>
#include<QtSql/QSqlDatabase>
#include <QTcpServer>
class SocketManager : public QObject
{
    Q_OBJECT

public:
    static SocketManager& instance() {
        static SocketManager _instance;
        return _instance;

    }

    QTcpSocket* socket() { return &server; }
    //连接服务器
    void connectServe();

signals:
    void repairSubmitSuccess(QByteArray);//报修提交成功信号
    void loginSuccess(QByteArray);//登录成功信号
    void repairResult(QByteArray);//报修结果返回信号
    void studentInfo(QByteArray);//个人信息返回信号
    void passwordModify(QByteArray);//密码修改信号
    void pictureModify();//图片修改信号
public slots:
    void readyRead();
private:
    SocketManager() {
        connectServe();
        connect(&server,&QTcpSocket::readyRead,this,&SocketManager::readyRead);//建立连接
    } // 私有构造函数
    QTcpSocket server;

signals:
};

#endif // SOCKETMANAGER_H
