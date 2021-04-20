#include "headers/eventwindow.h"
#include "ui_eventwindow.h"
#include <qdebug.h>

EventWindow::EventWindow( QWidget *parent ) : QDialog( parent ), ui( new Ui::EventWindow ) {
    ui->setupUi( this ) ;
    ui->time->setTime( QTime::currentTime() ) ;
}

EventWindow::EventWindow( QString description, QTime time, QWidget *parent ) : QDialog( parent ), ui( new Ui::EventWindow ) {
    ui->setupUi( this ) ;
    ui->description->setText( description ) ;
    ui->time->setTime( time ) ;
}

EventWindow::~EventWindow() {
    delete ui;
}

/* 按下confirmButton後 將資料回傳到mainWindow 並關閉addEventWindow */
void EventWindow::on_confirmButton_clicked() {
    emit sendData( ui->description->toPlainText(), ui->time->time() ) ;
    close() ;
}

/* 按下cancelButton後 直接關閉addEventWindow */
void EventWindow::on_cancelButton_clicked() {
    close() ;
}
