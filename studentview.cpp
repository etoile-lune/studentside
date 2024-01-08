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

    this->setFixedSize(800,600);

    QPixmap backgroundImage(":/picture/6.JPG");
    backgroundImage = backgroundImage.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, backgroundImage);

    this->setAutoFillBackground(true);

    this->setPalette(palette);
    server=SocketManager::instance().socket();
    connect(&SocketManager::instance(),&SocketManager::studentInfo,this,&StudentView::slotReadyRead);
    connect(&SocketManager::instance(),&SocketManager::passwordModify,this,&StudentView::slotReadyRead);
    connect(&SocketManager::instance(),&SocketManager::pictureModify,this,&StudentView::slotSendInfo);
    connect(ui->PasswordBtn,&QPushButton::clicked,this,&StudentView::slotSendPass);//修改密码
    connect(ui->addpictureBtn,&QPushButton::clicked,this,&StudentView::slotSendPic);//发送图片
    slotSendInfo();
}

StudentView::~StudentView()
{
    //disconnect(server,&QTcpSocket::readyRead,this,&StudentView::slotReadyRead);

    delete ui;
}





void StudentView::on_ReturnwinBtn_clicked()
{
    StudentWindow *windowwin=new StudentWindow;
    windowwin->show();
    delete this;
}

//从服务端到来的个人信息、修改成功、修改失败
void StudentView::slotReadyRead(QByteArray array){

    QString tmp_array=QString::fromUtf8(array);//转化为字符串类型
    qDebug()<<array;
    if (array.startsWith("ID: ")){//查看信息

       QStringList dataList = tmp_array.split(", ");
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
        //qDebug()<<imageData;

        // 创建QImage并加载图片数据
        QImage image;
        image.loadFromData(imageData);
        //QSize newSize(100, 100);  // 新的大小
        //image = image.scaled(newSize, Qt::KeepAspectRatio);

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

//修改密码按钮
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

//添加图片按钮
void StudentView::slotSendPic(){
    //ui->label->clear();
    QString fileName = QFileDialog::getOpenFileName(this, "Select Image", QDir::homePath(), "Images (*.png *.jpg)");
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray imageData = file.readAll();
        QImage originalImage;
        originalImage.loadFromData(imageData);

        QSize newSize(800, 600); // 指定新的大小
        QImage scaledImage = originalImage.scaled(newSize, Qt::KeepAspectRatio); // 压缩图片到指定大小，保持原始图片的宽高比

        QByteArray compressedData;
        QBuffer buffer(&compressedData);
        buffer.open(QIODevice::WriteOnly);
        scaledImage.save(&buffer, "JPEG", 50);
        buffer.close();

        QString data = "PIC:";
        server->write(data.toUtf8()+compressedData);

        file.close();
    }
    //slotSendInfo();
}

