#include "addtitle.h"
#include "ui_addtitle.h"

AddTitle::AddTitle(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTitle)
{
    ui->setupUi(this);
}

AddTitle::~AddTitle()
{
    delete ui;
}

void AddTitle::on_pushButton_clicked()
{
    emit OK(ui->lineEdit->text());
    ui->lineEdit->clear();
    close();
}

void AddTitle::on_pushButton_2_clicked()
{
    close();
}
