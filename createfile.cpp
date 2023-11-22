#include "createfile.h"
#include "ui_createfile.h"

CreateFile::CreateFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateFile)
{
    ui->setupUi(this);
}

CreateFile::~CreateFile()
{
    delete ui;
}

void CreateFile::on_Button_OK_clicked()
{
    int *create=new int[8+MAX_LABELS*MAX_SUBLABELS];
    for(int i=0;i<8+MAX_LABELS*MAX_SUBLABELS;i++)
        create[i]=0;
    create[0]=ui->Week->isChecked();
    create[1]=ui->Day1->isChecked();
    create[2]=ui->Day2->isChecked();
    create[3]=ui->Day3->isChecked();
    create[4]=ui->Day4->isChecked();
    create[5]=ui->Day5->isChecked();
    create[6]=ui->Day6->isChecked();
    create[7]=ui->Day7->isChecked();
    if(ui->R_Study->isChecked())
    {
        for(int i=8;i<8+MAX_SUBLABELS;i++)
            create[i]=1;
        create[8+MAX_LABELS*3]=1;
        create[8+MAX_LABELS*3+1]=1;
    }
    if(ui->R_StudyPE->isChecked())
    {
        for(int i=8;i<8+MAX_SUBLABELS;i++)
            create[i]=1;
        create[8+MAX_LABELS*2+3]=1;
        create[8+MAX_LABELS*3]=1;
        create[8+MAX_LABELS*3+1]=1;
    }
    if(ui->R_All->isChecked())
    {
        for(int i=8;i<8+MAX_LABELS*MAX_SUBLABELS;i++)
            create[i]=1;
    }
    emit OK(create);
    clear_all();
    close();
}

void CreateFile::clear_all()
{
    ui->Week->setChecked(false);
    ui->Day1->setChecked(false);
    ui->Day2->setChecked(false);
    ui->Day3->setChecked(false);
    ui->Day4->setChecked(false);
    ui->Day5->setChecked(false);
    ui->Day6->setChecked(false);
    ui->Day7->setChecked(false);
    ui->R_Study->setChecked(false);
    ui->R_StudyPE->setChecked(false);
    ui->R_All->setChecked(false);
}

void CreateFile::on_Button_Cancel_clicked()
{
    clear_all();
    close();
}
