#ifndef EVENTWINDOW_H
#define EVENTWINDOW_H

#include <QDialog>
#include <QString>
#include <headers/eventInfo.h>


namespace Ui { class EventWindow ; }

class EventWindow : public QDialog
{
    Q_OBJECT

public:
    EventWindow( QString, QWidget *parent = nullptr ) ;

    EventWindow( QString, QString, QTime, QWidget *parent = nullptr ) ;

    ~EventWindow() ;

signals:
    void sendData( QString, QTime ) ;

private slots:
    void on_confirmButton_clicked() ;

    void on_cancelButton_clicked() ;

private:
    Ui::EventWindow *ui ;

    void setTime( QString&, QString&, bool&, QTime ) ;
    QTime getTime_t1( QString, QString, bool ) ;
    QTime getTime_t2( QString, QString ) ;
};

#endif // EVENTWINDOW_H
