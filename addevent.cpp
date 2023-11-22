#include "addevent.h"
#include "ui_addevent.h"

AddEvent::AddEvent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEvent)
{
    ui->setupUi(this);
}

AddEvent::~AddEvent()
{
    delete ui;
}

void AddEvent::on_pushButton_2_clicked()
{
    clear_all();
    close();
}

void AddEvent::on_pushButton_clicked()
{
    int begin=ui->timeEdit->time().hour()*60+ui->timeEdit->time().minute();
    int end=ui->timeEdit_2->time().hour()*60+ui->timeEdit_2->time().minute();
    int weekday=ui->lineEdit_2->text().toInt();
    QString describe=ui->textEdit->toPlainText().replace('\n','\\');
    if(ui->Score->text()!="")
        describe+=QChar(ui->Score->text().toInt()+10000);
    if(weekday<=0 ||weekday>=8)
        return;
    EventData* eventdata=new EventData(ui->lineEdit->text(),describe,begin,end,weekday,
                                       ui->comboBox->currentIndex(),ui->comboBox_2->currentIndex());
    emit(OK(eventdata));
    clear_all();
    close();
}

void AddEvent::on_comboBox_currentIndexChanged(int index)
{
    ui->comboBox_2->clear();
    for(int i=0;i<MAX_SUBLABELS;i++)
    {
        if(index<0)
            break;
        if(sublabeltext[index][i].length()>=1)
            ui->comboBox_2->addItem(sublabeltext[index][i]);
    }
    ui->comboBox_2->setCurrentIndex(0);
}

void AddEvent::clear_all()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->textEdit->clear();
    ui->timeEdit->setTime(QTime::fromMSecsSinceStartOfDay(0));
    ui->timeEdit_2->setTime(QTime::fromMSecsSinceStartOfDay(0));
    ui->comboBox->clear();
    ui->comboBox_2->clear();
    for(int i=0;i<MAX_LABELS;i++)
    {
        if(labeltext[i].length()>=1)
            ui->comboBox->addItem(labeltext[i]);
    }
    ui->comboBox->setCurrentIndex(0);
    ui->Score->clear();
}
