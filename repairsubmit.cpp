#include "repairsubmit.h"
#include "studentwindow.h"
#include "ui_repairsubmit.h"
#include <QSqlTableModel>
#include<QtSql/QSqlDatabase>
#include<QDebug>
#include<QMessageBox>
#include <QtSql>
#include <QDateTime>
RepairSubmit::RepairSubmit(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RepairSubmit)
{
    ui->setupUi(this);
    server = SocketManager::instance().socket();
    connect(&SocketManager::instance(),&SocketManager::repairSubmitSuccess,this,&RepairSubmit::slotReadyRead);//接收消息
    connect(ui->SubmitBtn,&QPushButton::clicked,this,&RepairSubmit::slotSendNum);//提交

}

RepairSubmit::~RepairSubmit()
{
    delete ui;
}



void RepairSubmit::on_WindowBtn_clicked()//返回
{
    StudentWindow *windowwin=new StudentWindow;
    windowwin->show();
    delete this;
}


void RepairSubmit::slotReadyRead(QByteArray array){
    qDebug()<<array;
    if (array == "RepairSubmit:insertsuccess"){
        QString dlgTitle="success";
        QString strInfo="提交成功!";
        QMessageBox::information(this,dlgTitle,strInfo);
        StudentWindow *stuwin=new StudentWindow;
        stuwin->show();
        this->close();
    }
    else if (array =="RepairSubmit:invalid"){
        QString dlgTitle="error";
        QString strInfo="提交失败!";
        QMessageBox::critical(this,dlgTitle,strInfo);
        RepairSubmit *stulogwin=new RepairSubmit;
        stulogwin->show();
        this->close();
    }
}

void RepairSubmit::slotSendNum(){
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString repairtime = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");
    QString repairtype = ui->comboBox->currentText();
    QString num = ui->RepairNum->text();
    QString phone = ui->Repairphone->text();
    QString fault = ui->RepairFault->toPlainText();

    if(num!="" &&phone != "" && fault!=""){

    QString data = "NUM:" + num + "$"  + repairtype + "$" + fault + "$" + phone + "$"  + repairtime ; // 在数据前面添加"NUM:"作为数据类型标识
    server->write(data.toUtf8());

    ui->RepairNum->clear();
    ui->Repairphone->clear();
    ui->RepairFault->clear();
    }
    else{
        QString dlgTitle="error";
        QString strInfo="请输入完整信息!";
        QMessageBox::critical(this,dlgTitle,strInfo);
    }
}
