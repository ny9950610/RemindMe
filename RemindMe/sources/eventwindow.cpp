#include "headers/eventwindow.h"
#include "ui_eventwindow.h"
#include <qdebug.h>


EventWindow::EventWindow( QString windowName, QWidget *parent ) : QDialog( parent ), ui( new Ui::EventWindow ) {
    ui->setupUi( this ) ;
    setWindowTitle( windowName ) ;

    QString hour, min ;
    bool isAM = true ;
    setTime( hour, min, isAM, QTime::currentTime() ) ;

    ui->hrText->setText( hour ) ;
    ui->minText->setText( min ) ;
    if ( isAM ) ui->comboBox->setCurrentIndex( 0 ) ;
    else ui->comboBox->setCurrentIndex( 1 ) ;
}

EventWindow::EventWindow( QString windowName, QString description, QTime time, QWidget *parent ) : QDialog( parent ), ui( new Ui::EventWindow ) {
    ui->setupUi( this ) ;
    setWindowTitle( windowName ) ;
    ui->description->setText( description ) ;

    QString hour, min ;
    bool isAM = true ;
    setTime( hour, min, isAM, time ) ;

    ui->hrText->setText( hour ) ;
    ui->minText->setText( min ) ;
    if ( isAM ) ui->comboBox->setCurrentIndex( 0 ) ;
    else ui->comboBox->setCurrentIndex( 1 ) ;
}

EventWindow::~EventWindow() {
    delete ui;
}

/* 按下confirmButton後 將資料回傳到mainWindow 並關閉addEventWindow */
void EventWindow::on_confirmButton_clicked() {
    QTime time ;
    // 使用指定時間設定時間
    if ( ui->tabWidget->currentIndex() == 0 ) {
        bool isAM ;
        if ( ui->comboBox->currentText() == "上午" ) isAM = true ;
        else isAM = false ;

        time = getTime_t1( ui->hrText->text(), ui->minText->text(), isAM ) ;
        if ( time.isNull() ) qDebug() << "error" ;
        qDebug() << "getTime_t1" << time ;
    }
    // 使用剩餘時間設定時間
    else {
        time = getTime_t2( ui->hrText2->text(), ui->minText2->text() ) ;
        if ( time.isNull() ) qDebug() << "error" ;
        qDebug() << "getTime_t2" << time ;
    }

    if ( time.isValid() ) {
        emit sendData( ui->description->toPlainText(), time ) ;
        close() ;
    }
    else {
        ui->errorLabel->setText( "Error! 再試一次" ) ;
    }
}

/* 按下cancelButton後 直接關閉addEventWindow */
void EventWindow::on_cancelButton_clicked() {
    close() ;
}

/* 取得目前時間並把型別轉換成int */
void EventWindow::setTime( QString &hour, QString &min, bool &isAM, QTime time ) {
    //把24小時制換算成12小時制
    if ( time.hour() <= 12 ) {
        hour = QString::number( time.hour() ) ;
        isAM = true ;
    }
    else {
        hour = QString::number( time.hour() - 12 ) ;
        isAM = false ;
    }

    min = QString::number( time.minute() ) ;
    qDebug() << "setTime" << isAM << hour << min ;
}

/* 根據指定時間設定事件 */
QTime EventWindow::getTime_t1( QString hour, QString min, bool isAM ) {
    if ( isAM ) {
        qDebug() << hour.toInt() << min.toInt() ;
        return QTime( hour.toInt(), min.toInt() ) ;
    }
    else {
        qDebug() << hour.toInt()+12 << min.toInt() ;
        return QTime( hour.toInt()+12, min.toInt() ) ;
    }
}

/* 根據剩餘時間勝定事件 */
QTime EventWindow::getTime_t2( QString hour, QString min ) {
    if ( hour.toInt() >= 24 || min.toInt() >= 60 ) {
        return QTime( -1, -1 ) ;
    }

    int finalHr = ( QTime::currentTime().hour() + hour.toInt() ) % 24 ;
    int finalMin = ( QTime::currentTime().minute() + min.toInt() ) % 60 ;

    if ( ( QTime::currentTime().minute() + min.toInt() ) / 60 == 1 ) finalHr ++ ;

    qDebug() << finalHr << finalMin ;
    return QTime( finalHr, finalMin ) ;

}
