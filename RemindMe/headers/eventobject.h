#ifndef EVENTOBJECT_H
#define EVENTOBJECT_H

#include <QObject>


class EventObject : public QObject
{
    Q_OBJECT
public:
    explicit EventObject( QObject *parent = 0 ) ;
    /*
    多寫一個.h檔的原因 參考下面網址
    https://blog.csdn.net/muyuyuzhong/article/details/8736069
    */
};

#endif // EVENTOBJECT_H
