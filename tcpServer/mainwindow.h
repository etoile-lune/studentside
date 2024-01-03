#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
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
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool connectdatabase(const QString &dbName);
public slots:
    void newConnection();
    void readyRead();
    void clientDisconnected();

private:
    QTcpServer* m_server;
    QTcpSocket* m_client;
    QSqlTableModel *model;
    QString m_receivedId;//保存id
private:
    Ui::MainWindow *ui;

    QLabel* m_imageLabel;  // 用于显示图片的QLabel
};
#endif // MAINWINDOW_H
