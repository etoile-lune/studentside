#include "studentlogin.h"
#include "ui_studentlogin.h"
#include "studentwindow.h"
#include <QSqlTableModel>
#include<QtSql/QSqlDatabase>
#include<QDebug>
#include<QMessageBox>
#include <QtSql>
#include <QHostAddress>
#include<QMessageBox>
// StudentLogin::StudentLogin(QWidget *parent)
//     : QWidget(parent)
//     , ui(new Ui::StudentLogin)
// {
//     ui->setupUi(this);
//     server = SocketManager::instance().socket();
//     connect(&SocketManager::instance(),&SocketManager::loginSuccess,this,&StudentLogin::slotReadyRead);//建立槽函数的连接
//     connect(ui->LoginButton,&QPushButton::clicked,this,&StudentLogin::slotSendId);//登录

// }


// StudentLogin::~StudentLogin()
// {
//     //disconnect(&SocketManager::instance(),&SocketManager::loginSuccess,this,&StudentLogin::slotReadyRead);//断开槽函数的连接
//     delete ui;
// }
#include "studentlogin.h"

StudentLogin::StudentLogin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StudentLogin)
{
    ui->setupUi(this);

    this->setFixedSize(800,600);

    QPixmap backgroundImage(":/picture/6.JPG");

    backgroundImage = backgroundImage.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, backgroundImage);

    this->setAutoFillBackground(true);

    this->setPalette(palette);
    server = SocketManager::instance().socket();
    connect(&SocketManager::instance(), &SocketManager::loginSuccess, this, &StudentLogin::slotReadyRead); // 建立槽函数的连接
    connect(ui->LoginButton, &QPushButton::clicked, this, &StudentLogin::slotSendId); // 登录
}

StudentLogin::~StudentLogin()
{
    delete ui;
}

StudentLogin& StudentLogin::instance()
{
    static StudentLogin instance; // 静态局部变量确保只被创建一次
    return instance;
}
void StudentLogin::slotReadyRead(QByteArray array){


    qDebug()<<array<<"www";
    if (array == "Login:ok"){//登陆成功
            StudentWindow *stuwin=new StudentWindow;
            stuwin->show();
            this->close();
            //QMessageBox::information(this,"消息","登录成功！",QMessageBox::Ok);
        }
    else if (array =="Login:invalid"){
        QString dlgTitle="error";
        QString strInfo="账号或密码错误!";
        QMessageBox::critical(this,dlgTitle,strInfo);
    }
}
void StudentLogin::slotSendId(){
    if(ui->UserNameLineEdit->text()!=""&& ui->PasswordLineEdit->text()!=""){
        QString id = ui->UserNameLineEdit->text();
        QString password = ui->PasswordLineEdit->text();

        QString data = "ID:" + id + " " + password ;//添加标识符
        server->write(data.toUtf8());
        qDebug()<<server->state();
        ui->UserNameLineEdit->clear();
        ui->PasswordLineEdit->clear();
    }else{
    if(ui->UserNameLineEdit->text()==""){
        QString dlgTitle="error";
        QString strInfo="请输入账号!";
        QMessageBox::critical(this,dlgTitle,strInfo);
    }
    else{
        QString dlgTitle="error";
        QString strInfo="请输入密码!";
        QMessageBox::critical(this,dlgTitle,strInfo);
    }
    }
}



