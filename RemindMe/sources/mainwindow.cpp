#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include "headers/eventwindow.h"
#include <qdebug.h>


MainWindow::MainWindow( QWidget *parent ) : QMainWindow( parent ) , ui( new Ui::MainWindow ) {
    ui->setupUi( this ) ;

    // 設定trayIcon
    trayIcon = new QSystemTrayIcon( this ) ;
    trayIcon->setIcon( QIcon(":/images/icon.png") ) ;
    trayIcon->setToolTip( "RemindMe" ) ;
    trayIcon->show() ;
    connect(trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::iconActivated );

    // 設定trayIconMenu的quitAction
    quitAction = new QAction( "關閉", this ) ;
    connect(quitAction, SIGNAL( triggered() ), qApp, SLOT( quit() ) ) ;

    trayIconMenu = new QMenu( this ) ;
    trayIconMenu->addAction( quitAction ) ;
    trayIcon->setContextMenu( trayIconMenu ) ;
}

MainWindow::~MainWindow() {
    delete ui ;
}

/* 決定user跟trayIcon互動後會有甚麼反應 */
void MainWindow::iconActivated( QSystemTrayIcon::ActivationReason reason ) {
    switch (reason) {
        // 雙擊後使mainwindow顯現
        case QSystemTrayIcon::DoubleClick:
            this->show() ;
            break;
        default:
            break;
    }
}

/* 按下addEventButton後 跳出addEventWindow */
void MainWindow::on_addEvent_clicked() {
    EventWindow *window = new EventWindow( "新增事件" ) ;
    connect( window, SIGNAL( sendData( QString, QTime ) ), this, SLOT( createEvent( QString, QTime ) ) ) ; // 當window關閉 回傳eventInfo並createEvent
    window->exec() ;
}

/* 按下changeEventButton後 更改目前選擇event的內容 */
void MainWindow::on_changeEvent_clicked() {
    if ( currentEvent != -1 ) {
        EventWindow *window = new EventWindow( "更改事件", eventList[currentEvent]->description, eventList[currentEvent]->time ) ;
        connect( window, SIGNAL( sendData( QString, QTime ) ), this, SLOT( modifyEvent( QString, QTime ) ) ) ; // 當window關閉 回傳eventInfo並createEvent
        window->exec() ;
     }
}

/* 按下changeEventButton後 刪除目前選擇的event */
void MainWindow::on_deleteEvent_clicked() {
    deleteEvent( currentEvent ) ;
}

/* 根據回傳的eventInfo建立event */
void MainWindow::createEvent( QString description, QTime time ) {
    // 將目前的hashValue記下
    int i = hashValue ;
    hashValue ++ ;

    // 建立eventButton
    QPushButton *eventButton = new QPushButton( description ) ;
    connect( eventButton, &QPushButton::clicked, this, [this,i]() { showData( i ) ; } ) ; // 按下eventButton後 在label中顯示eventInfo

    // 建立event
    EventInfo *event = new EventInfo( description, time, eventButton ) ;
    connect( event, &EventInfo::eventEnd, this, [this,i]() { deleteEvent( i ) ; } ) ;

    // 將data存入eventList
    eventList[i] = event ;

    // 在layout中放入新按鈕 將更新過的layout放入buttons中 再將更新過的buttons放入scrollArea中
    layout->addWidget( eventButton ) ;
    buttons->setLayout( layout ) ;
    ui->scrollArea->setWidget( buttons ) ;

    showData( i ) ;
}

/* 根據回傳的eventInfo更改event */
void MainWindow::modifyEvent( QString description, QTime time ) {
    eventList[currentEvent]->description = description ;
    eventList[currentEvent]->time = time ;
    eventList[currentEvent]->button->setText( description ) ;

    showData( currentEvent ) ;
}

/* 刪除currentEvent */
void MainWindow::deleteEvent( int i ) {
    if ( i != -1 ) {
        eventList[i]->button->close() ;
        delete eventList[i] ;
     }

    showData( -1 ) ;
}

/* 根據按鈕的index在label中顯示對應的eventInfo */
void MainWindow::showData( int i ) {
    currentEvent = i ;
    if ( i == -1 ) {
        ui->description->setText( "說明" ) ;
        ui->time->setText( "時間" ) ;
    }
    else {
        ui->description->setText( "說明 " + eventList[i]->description ) ;
        ui->time->setText( "時間 " + eventList[i]->time.toString( "HH:mm" ) ) ;
    }
}
