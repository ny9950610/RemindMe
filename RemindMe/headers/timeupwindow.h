#ifndef TIMEUPWINDOW_H
#define TIMEUPWINDOW_H

#include <QDialog>
#include <QString>


namespace Ui { class TimeUpWindow ; }

class TimeUpWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TimeUpWindow( QString, QWidget *parent = nullptr ) ;
    ~TimeUpWindow() ;

signals:
    void timeUp() ;

private slots:
    void on_okButton_clicked() ;

private:
    Ui::TimeUpWindow *ui ;
};

#endif // TIMEUPWINDOW_H
