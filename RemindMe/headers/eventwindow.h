#ifndef EVENTWINDOW_H
#define EVENTWINDOW_H

#include <QDialog>
#include <headers/eventInfo.h>

namespace Ui { class EventWindow ; }

class EventWindow : public QDialog
{
    Q_OBJECT

public:
    EventWindow( QWidget *parent = nullptr ) ;

    EventWindow( QString, QTime, QWidget *parent = nullptr ) ;

    ~EventWindow() ;

signals:
    void sendData( QString, QTime ) ;

private slots:
    void on_confirmButton_clicked() ;

    void on_cancelButton_clicked() ;

private:
    Ui::EventWindow *ui ;
};

#endif // EVENTWINDOW_H
