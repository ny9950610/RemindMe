#include "headers/eventInfo.h"
#include "headers/timeupwindow.h"
#include <qdebug.h>
#include <QCoreApplication>

EventInfo::EventInfo( QString description , QTime time, QPushButton *button ) {
    // 根據參數設定資料
    this->description = description ;
    this->time = time ;
    this->button = button ;

    // 開啟timer 每秒觸發timerEvent
    timer = startTimer( 1000 ) ;
}

void EventInfo::timerEvent( QTimerEvent *event ) {
    // 取得現在時間
    QTime nowTime( QTime::currentTime() );

    // 時間到時 跳出timeupwindow
    if ( nowTime.hour() == time.hour() && nowTime.minute() == time.minute() ) {
        TimeUpWindow *window = new TimeUpWindow( description ) ;
        connect( window, SIGNAL( timeUp() ), this, SLOT( callDeleteEvent() ) ) ;

        // 加入音效
        sound = new QMediaPlayer() ;
        sound->setMedia( QUrl( "qrc:/sounds/sound.mp3" ) ) ;
        sound->play();

        window->exec() ;
    }
}

/* 觸發mainwindow中的deleteEvent() */
void EventInfo::callDeleteEvent() {
    emit eventEnd() ;
}
