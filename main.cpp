// #include "studentlogin.h"

// #include <QApplication>

// int main(int argc, char *argv[])
// {
//     QApplication a(argc, argv);
//     StudentLogin w;
//     w.show();
//     return a.exec();
// }
#include "studentlogin.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StudentLogin::instance().show(); // 通过静态方法获取实例并显示
    return a.exec();
}
