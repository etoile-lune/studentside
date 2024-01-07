#include "socketmanager.h"


void SocketManager::connectServe(){

    server.connectToHost(QHostAddress("127.0.0.1"),8000);

}

void SocketManager::readyRead(){
    QByteArray array=server.readAll();
    qDebug()<<array;
    if(array.startsWith("RepairSubmit")){
        emit(repairSubmitSuccess(array));//报修提交信号
    }else if(array.startsWith("Login")){
        emit(loginSuccess(array));//登录成功信号
    }else if(array.startsWith("RepairResult")){
        emit(repairResult(array));//发送报修结果信号
    }else if(array.startsWith("ID")){
        emit(studentInfo(array));//个人信息返回信号
    }else if(array.startsWith("password")){
        emit(passwordModify(array));
    }else if(array.startsWith("Picture")){
        emit(pictureModify());
    }
}

