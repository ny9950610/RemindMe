#ifndef EVENTINFO_H
#define EVENTINFO_H

#include <headers/eventobject.h>
#include <qpushbutton.h>
#include <QString>
#include <QTime>
#include <QMediaPlayer>


class EventInfo : public EventObject {
    Q_OBJECT

public:
    EventInfo( QString, QTime , QPushButton* ) ;

    QPushButton *button ; // 指向按鈕的指標 用來更改按鈕的資訊
    QString description ;
    QTime time ;
    int timer ;
    QMediaPlayer *sound ;

    virtual void timerEvent( QTimerEvent *Event ) ;

signals:
    void eventEnd() ;

private slots:
    void callDeleteEvent() ;
};

#endif // EVENTINFO_H
