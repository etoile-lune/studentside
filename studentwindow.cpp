#include "studentwindow.h"
#include "ui_studentwindow.h"
#include "studentlogin.h"
#include"repairsubmit.h"
#include"repairview.h"
#include"studentview.h"
#include <QSqlTableModel>
#include<QtSql/QSqlDatabase>
#include<QDebug>
#include<QMessageBox>
#include <QtSql>
#include <QHostAddress>
#include<QMessageBox>
StudentWindow::StudentWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StudentWindow)
{

    ui->setupUi(this);
    this->setFixedSize(800,600);

    QPixmap backgroundImage(":/picture/6.JPG");
    backgroundImage = backgroundImage.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, backgroundImage);

    this->setAutoFillBackground(true);

    this->setPalette(palette);
}

StudentWindow::~StudentWindow()
{
    delete ui;
}





void StudentWindow::on_ReturnLoginBtn_clicked() // 返回
{
    StudentLogin::instance().show(); // 通过单例模式获取StudentLogin实例并显示
    this->close(); // 关闭当前窗口
}

void StudentWindow::on_RepairBtn_clicked()//报修
{
    RepairSubmit *repSubWin=new RepairSubmit;
    repSubWin->show();
    this->close();
}

void StudentWindow::on_RepairInfoBtn_clicked()//修理信息
{
    RepairView *repViewWin=new RepairView;
    repViewWin->show();
    this->close();
}


void StudentWindow::on_ViewInfoBtn_clicked()//学生信息
{
    StudentView *stuViewWin=new StudentView;
    stuViewWin->show();
    this->close();
}




