#include "headers/timeupwindow.h"
#include "ui_timeupwindow.h"

TimeUpWindow::TimeUpWindow( QString str, QWidget *parent ) : QDialog( parent ), ui( new Ui::TimeUpWindow ) {
    ui->setupUi( this );
    ui->label->setText( str ) ;
}

TimeUpWindow::~TimeUpWindow()
{
    delete ui;
}

void TimeUpWindow::on_okButton_clicked()
{
    emit timeUp() ;
    close() ;
}
