#include "changeheight.h"
#include "ui_changeheight.h"

ChangeHeight::ChangeHeight(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeHeight)
{
    ui->setupUi(this);
}

ChangeHeight::~ChangeHeight()
{
    delete ui;
}

void ChangeHeight::on_pushButton_2_clicked()
{
    close();
}

void ChangeHeight::on_pushButton_clicked()
{
    emit(OK(ui->lineEdit->text().toInt()));
    close();
}
