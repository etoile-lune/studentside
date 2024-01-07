
#ifndef STUDENTLOGIN_H
#define STUDENTLOGIN_H

#include <QWidget>
#include <QDialog>
#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QTcpSocket>
#include <QByteArray>
#include "SocketManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class StudentLogin; }
QT_END_NAMESPACE

class StudentLogin : public QWidget
{
    Q_OBJECT

public:
    static StudentLogin& instance(); // 静态方法用于获取实例

private:
    StudentLogin(QWidget *parent = nullptr); // 构造函数设为私有
    ~StudentLogin(); // 析构函数设为私有

    Ui::StudentLogin *ui;
    QSqlTableModel *model;
    QTcpSocket* server;

public slots:
    void slotReadyRead(QByteArray); // 读
    void slotSendId(); // 发

};
#endif // STUDENTLOGIN_H
