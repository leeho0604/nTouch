#include "dialog.h"
#include "ui_dialog.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <iostream>
#include <QPixmap>
#include <QMessageBox>
QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
QSqlRecord rec;
int nameCol;
int pwCol;
int stateCol;

using namespace std;
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QPixmap innotium_logo(":/resources/image/Innotium.png");
    int w = ui->labelPic->width();
    int h = ui->labelPic->height();
    ui->labelPic->setPixmap(innotium_logo.scaled(w,h,Qt::KeepAspectRatio));

    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("dlrudgh12!@");
    db.setDatabaseName("leeho");
    if(!db.open()){
        cout<<"database not connect"<<endl;
        exit(2);
    }
    else{
        cout<<"database connect"<<endl;;
    }
    /*
    QSqlQuery q("SELECT * FROM UserInfo");
    rec=q.record();
    nameCol=rec.indexOf("name");
    pwCol=rec.indexOf("pw");
    stateCol=rec.indexOf("status");
    while(q.next()){
        qDebug()<<q.value(nameCol).toString();
        qDebug()<<q.value(pwCol).toString();
        qDebug()<<q.value(stateCol).toInt();
    }
    */
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_loginButton_clicked()
{
    QString ID = ui->lineEdit_ID->text();
    QString password = ui->lineEdit_password->text();
    QSqlQuery q("SELECT * FROM UserInfo WHERE name='"+ID+"'");
    rec=q.record();
    nameCol=rec.indexOf("name");
    pwCol=rec.indexOf("pw");
    stateCol=rec.indexOf("status");
    while(q.next()){
        if(password.compare(q.value(pwCol).toString())==0){
            //MainWindow mainWindow;
            //mainWindow.setModal(true);
            //mainWindow.exec();
            mainwindow = new MainWindow(this);
            mainwindow->show();
            hide();
        }
        else{
            QMessageBox::critical(this,"입력 오류","아이디 또는 비밀번호가 일치하지 않습니다");
        }
    }
}
