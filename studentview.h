#ifndef STUDENTVIEW_H
#define STUDENTVIEW_H

#include <QWidget>
#include <QDialog>
#include <QMainWindow>
#include <QPushButton>
#include<QMessageBox>
#include <QSqlTableModel>
#include<QtSql/QSqlDatabase>
#include<QDebug>
#include <QTcpSocket>
#include <QByteArray>
#include"studentlogin.h"
QT_BEGIN_NAMESPACE
namespace Ui { class StudentView; }
QT_END_NAMESPACE

class StudentView : public QWidget
{
    Q_OBJECT

public:
    StudentView(QWidget *parent = nullptr);
    ~StudentView();


private:
    Ui::StudentView *ui;
    QSqlTableModel *model;

    QTcpSocket* server;
private slots:
    void on_ReturnwinBtn_clicked();//返回

public slots:
    void slotReadyRead(QByteArray);//读
   void slotSendInfo();//发送查询信息
    void slotSendPass();//发送修改密码信息
   void slotSendPic();



};


#endif // STUDENTVIEW_H
