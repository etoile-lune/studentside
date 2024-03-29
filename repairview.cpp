#include "repairview.h"
#include "ui_repairview.h"
#include "studentwindow.h"
#include "studentlogin.h"
#include <QSqlTableModel>
#include <QTableView>
#include<QtSql/QSqlDatabase>
#include<QDebug>
#include<QMessageBox>
#include <QtSql>
#include <QHostAddress>
#include<QMessageBox>
#include <QStandardItemModel>  // 包含QStandardItemModel的头文件
#include <QStringList>
#include <QStandardItem>
RepairView::RepairView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RepairView)
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
    connect(&SocketManager::instance() ,&SocketManager::repairResult,this,&RepairView::slotReadyRead);
    connect(ui->DornumviewBtn,&QPushButton::clicked,this,&RepairView::slotSendNumView);
}


RepairView::~RepairView()
{
    delete ui;
}

void RepairView::slotSendNumView(){
    if(ui->DorNumLineEdit->text()!=""){
    QString dornum = ui->DorNumLineEdit->text();
    QString data = "DOR:" + dornum ;//数据类型标识
    server->write(data.toUtf8());
    }
    else{
        QString dlgTitle="error";
        QString strInfo="请输入完整信息!";
        QMessageBox::critical(this,dlgTitle,strInfo);
    }


}
void RepairView::slotReadyRead(QByteArray array){

    QString tmp = QString::fromUtf8(array);
     QString result = tmp.mid(13);
    if (result == "RepairResult,No records found") {
        QMessageBox::critical(this, "Query Failed", "No records found for the specified query.");
        return;
    }

    // 处理来自服务端的查询结果
    // 将结果显示在QTableView上
    QStandardItemModel *model = new QStandardItemModel();
    QStringList headers = {"Num", "RepairType","Fault","Phone", "RepairTime","State"};
    model->setHorizontalHeaderLabels(headers);//列标题
    qDebug()<<result;
    QStringList records = result.split("$");//分隔符
    model->removeRows(0, model->rowCount()); // 清除之前的数据
    int row = 0;
    foreach (const QString &record, records) {// 遍历每条记录，分割字段并添加到model中
        QStringList fields = record.split(",");

        if (fields.size() ==6 ) {
            for (int column = 0; column < 6; ++column) {
                model->setItem(row, column, new QStandardItem(fields.at(column)));
            }
            row++;
        }
    }

    // 将model设置给QTableView
    ui->tableView->setModel(model);
}

void RepairView::on_ReturnwinBtn_clicked()
{
    StudentWindow *windowwin=new StudentWindow;
    windowwin->show();
    delete this;
}
