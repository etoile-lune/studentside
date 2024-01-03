#include "studentview.h"
#include "studentwindow.h"
#include "ui_studentview.h"
#include <QSqlTableModel>
#include<QtSql/QSqlDatabase>
#include<QDebug>
#include<QMessageBox>
#include <QtSql>
#include <QFileDialog>
StudentView::StudentView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StudentView)
{
    ui->setupUi(this);
    server = new QTcpSocket(this);
    server->connectToHost(QHostAddress("127.0.0.1"),8000);
    connect(server ,&QTcpSocket::readyRead,this,&StudentView::slotReadyRead);
   // connect(ui->StuInfoBtn,&QPushButton::clicked,this,&StudentView::slotSendInfo);//请求查看信息
    connect(ui->PasswordBtn,&QPushButton::clicked,this,&StudentView::slotSendPass);//修改密码
    connect(ui->addpictureBtn,&QPushButton::clicked,this,&StudentView::slotSendPic);
    slotSendInfo();
}

StudentView::~StudentView()
{
    delete ui;
}





void StudentView::on_ReturnwinBtn_clicked()
{
    StudentWindow *windowwin=new StudentWindow;
    windowwin->show();
    delete this;
}


void StudentView::slotReadyRead(){

    QString array = server->readAll();
    if (array.startsWith("ID:")){//查看信息
       //qDebug()<<array;
       QStringList dataList = array.split(", ");
       foreach(QString item, dataList) {
           qDebug() << item;
       }
       ui->idlabel->setText(dataList[0]);
       ui->namelabel->setText(dataList[1]);
       ui->sexlabel->setText(dataList[2]);
       ui->agelabel->setText(dataList[3]);
       ui->majorlabel->setText(dataList[4]);
       ui->classlabel->setText(dataList[5]);
       ui->phonelabel->setText(dataList[6]);
       ui->roomlabel->setText(dataList[7]);
       ui->bedlabel->setText(dataList[8]);


        QByteArray imageData = QByteArray::fromBase64(dataList[9].mid(9).toUtf8());
        qDebug()<<imageData;

        // 创建QImage并加载图片数据
        QImage image;
        image.loadFromData(imageData);
        QSize newSize(100, 100);  // 新的大小
        image = image.scaled(newSize, Qt::KeepAspectRatio);

        //将缩放后的图像设置到QLabel中
        ui->label->setPixmap(QPixmap::fromImage(image));
        ui->label->setScaledContents(true);

        }




    else if(array=="passwordsuccess"){//修改成功
        QString dlgTitle="success";
        QString strInfo="修改成功!";
        QMessageBox::information(this,dlgTitle,strInfo);
    }
    else if (array =="passwordfail"){
        QString dlgTitle="error";
        QString strInfo="修改失败!";
        QMessageBox::critical(this,dlgTitle,strInfo);
    }



}

void StudentView::slotSendPass(){
    QString password = ui->PasswordlineEdit->text();
    if(ui->PasswordlineEdit->text()!=""){
        QString password = ui->PasswordlineEdit->text();
        QString data = "PASS:" + password;
        server->write(data.toUtf8());

        ui->PasswordlineEdit->clear();
    }
    else{
        QString dlgTitle="error";
        QString strInfo="请输入密码!";
        QMessageBox::critical(this,dlgTitle,strInfo);   
    }
}

void StudentView::slotSendInfo(){

    QString data = "Infoview" ;
    server->write(data.toUtf8());

}

void StudentView::slotSendPic(){
    //ui->label->clear();
    QString fileName = QFileDialog::getOpenFileName(this, "Select Image", QDir::homePath(), "Images (*.png *.jpg)");
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray imageData = file.readAll();
        qDebug()<<imageData;


        QString data = "PIC:";
        server->write(data.toUtf8()+imageData);

        file.close();
    }
    slotSendInfo();
}

