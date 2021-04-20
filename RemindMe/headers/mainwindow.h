#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <qmap.h>
#include <headers/eventInfo.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow ; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget *parent = nullptr ) ;

    ~MainWindow() ;

    QMap<int,EventInfo*> eventList ; // 用來儲存所有eventInfo
    int hashValue = 0 ;              // 用來設定每個hash的keyValue
    int currentEvent = -1 ;          // 用來判斷目前顯示的event 值為event的hashValue
    QWidget *buttons = new QWidget() ;
    QLayout *layout = new QVBoxLayout() ;

private slots:
    void on_addEvent_clicked() ;

    void on_changeEvent_clicked() ;

    void on_deleteEvent_clicked() ;

    void createEvent( QString, QTime ) ;

    void modifyEvent( QString, QTime ) ;

    void deleteEvent() ;

    void showData( int ) ;

private:
    Ui::MainWindow *ui ;
};
#endif // MAINWINDOW_H
