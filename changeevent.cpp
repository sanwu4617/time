#include "changeevent.h"
#include "ui_changeevent.h"

ChangeEvent::ChangeEvent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeEvent)
{
    ui->setupUi(this);
}

ChangeEvent::~ChangeEvent()
{
    delete ui;
}

void ChangeEvent::setData(Event* event0)
{
    clear_all();
    event=event0;
    QTime qbegin(event->begin/60,event->begin-60*(event->begin/60));
    QTime qend(event->end/60,event->end-60*(event->end/60));
    ui->line_name->setText(event->str);
    ui->timeEdit->setTime(qbegin);
    ui->timeEdit_2->setTime(qend);
    ui->line_weekday->setText(QString::number(event->weekday));
    QString &ed=event->describe;
    if(ed.size()>0)
    {
        QChar describe_last=ed[ed.size()-1];
        if(describe_last.unicode()>=10000 && describe_last.unicode()<=10100)
        {
            ui->textEdit->setText(ed.left(ed.size()-1));
            ui->Score->setText(QString::number(describe_last.unicode()-10000));
        }
        else
            ui->textEdit->setText(ed);
    }
    else
    {
        ui->textEdit->clear();
        ui->Score->clear();
    }
    ui->comboBox->setCurrentIndex(event->type);
    setsubtype(event->type);
    ui->comboBox_2->setCurrentIndex(event->subtype);
}

void ChangeEvent::setsubtype(int index)
{
    ui->comboBox_2->clear();
    for(int i=0;i<MAX_SUBLABELS;i++)
    {
        if(index<0)
            break;
        if(sublabeltext[index][i].length()>=1)
            ui->comboBox_2->addItem(sublabeltext[index][i]);
    }
}

void ChangeEvent::on_pushButton_clicked()
{
    QString str=ui->line_name->text();
    int begin=ui->timeEdit->time().hour()*60+ui->timeEdit->time().minute();
    int end=ui->timeEdit_2->time().hour()*60+ui->timeEdit_2->time().minute();
    int weekday=ui->line_weekday->text().toInt();
    if(weekday<=0 ||weekday>=8)
        return;
    int type=ui->comboBox->currentIndex();
    int subtype=ui->comboBox_2->currentIndex();
    QString describe=ui->textEdit->toPlainText().replace('\n','\\');
    if(ui->Score->text()!="")
        describe+=QChar(ui->Score->text().toInt()+10000);
    event->change(str,begin,end,weekday,type,subtype,describe);
    emit close_signal();
    clear_all();
    close();
}

void ChangeEvent::on_pushButton_3_clicked()
{
    event->change("",0,0,0,0,0,"");
    emit close_signal();
    clear_all();
    close();
}

void ChangeEvent::on_pushButton_2_clicked()
{
    clear_all();
    close();
}

void ChangeEvent::on_comboBox_currentIndexChanged(int index)
{
    setsubtype(index);
    ui->comboBox_2->setCurrentIndex(0);
}

void ChangeEvent::clear_all()
{
    ui->line_name->clear();
    ui->line_weekday->clear();
    ui->textEdit->clear();
    ui->timeEdit->setTime(QTime::fromMSecsSinceStartOfDay(0));
    ui->timeEdit_2->setTime(QTime::fromMSecsSinceStartOfDay(0));
    ui->comboBox->clear();
    ui->comboBox_2->clear();
    ui->Score->clear();
    for(int i=0;i<MAX_LABELS;i++)
    {
        if(labeltext[i].length()>=1)
            ui->comboBox->addItem(labeltext[i]);
    }
    ui->comboBox->setCurrentIndex(0);
}
