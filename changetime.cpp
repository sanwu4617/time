#include "changetime.h"
#include "ui_changetime.h"

changeTime::changeTime(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changeTime)
{
    ui->setupUi(this);
}

changeTime::~changeTime()
{
    delete ui;
}

void changeTime::on_pushButton_2_clicked()
{
    close();
    //this->deleteLater();
}

void changeTime::on_pushButton_clicked()
{
    emit OK(ui->Begin->time(),ui->End->time());
    close();
}

