#include "Event.h"
Event::Event(QString str0,int begin0,int end0,int weekday0,int type0,int subtype0,QWidget* parent0,QString describe0)
{
    str=str0;
    begin=begin0;
    end=end0;
    weekday=weekday0;
    type=type0;
    subtype=subtype0;
    describe=describe0;
    Interface_operation(parent0);
    index_mark=0;
}
Event::Event(EventData* ed,QWidget* parent0)
{
    str=ed->str;
    begin=ed->begin;
    end=ed->end;
    weekday=ed->weekday;
    type=ed->type;
    subtype=ed->subtype;
    describe=ed->describe;
    Interface_operation(parent0);
    index_mark=0;
}
Event::Event(QWidget* parent0)
{
    str="";
    begin=0;
    end=0;
    weekday=0;
    type=0;
    subtype=0;
    describe="";
    Interface_operation(parent0);
    index_mark=0;
}
void Event::Interface_operation(QWidget* parent0)
{
    parent=parent0;
    button=new QPushButton(parent);
    button->setText(str);
    button->hide();
    connect(button,SIGNAL(clicked(bool)),this,SLOT(theSlot()));
}
Event::~Event()
{
    this->button->deleteLater();
    this->parent=nullptr;
}

void Event::setPlace(int date_begin,int date_end,int up,int down,int height,int offset)
{
    int diff1=begin-date_begin;
    int diff2=date_end-date_begin;
    int diff3=end-date_begin;
    double prop1=double(diff1)/diff2;
    double prop2=double(diff3)/diff2;
    int button_up=up+prop1*height-offset;
    int button_down=up+prop2*height-offset;
    button->setFixedSize(123,button_down-button_up);
    button->move(30+weekday*120,button_up);
    if(button_up>=up&&button_down<=down)
        button->show();
    else
        button->hide();

}
int Event::getDuration()
{
    return end-begin;
}
void Event::theSlot()
{
    emit theSignal(this);
}
void Event::change(QString str0,int begin0,int end0,int weekday0,int type0,int subtype0,QString describe0)
{
    str=str0;
    begin=begin0;
    end=end0;
    weekday=weekday0;
    type=type0;
    subtype=subtype0;
    describe=describe0;
    button->setText(str);
}

using namespace std;
void Event::save(ofstream& fout)
{
    fout<<str.toStdString()<<endl;
    fout<<describe.toStdString()<<endl;
    fout<<begin<<endl;
    fout<<end<<endl;
    fout<<weekday<<endl;
    fout<<type<<endl;
    fout<<subtype<<endl;
    fout<<"END EVENT"<<endl;
}
void Event::load(ifstream& fin,int& flag)
{
    str=getQString(fin,flag);
    describe=getQString(fin,flag);
    begin=getNumber(fin,flag);
    end=getNumber(fin,flag);
    weekday=getNumber(fin,flag);
    type=getNumber(fin,flag);
    subtype=getNumber(fin,flag);
    QString endflag=getQString(fin,flag,true);
    if(flag==1)
        return;
    if(endflag=="END EVENT")
    {
        button->setText(str);
        return;
    }
    else
        str="Error!";
}
EventData Event::toEventData()
{
    return EventData(str,describe,begin,end,weekday,type,subtype);
}
bool operator < (EventData a,EventData b)
{
    if(a.weekday*1440+a.begin<b.weekday*1440+b.begin)
        return true;
    return false;
}

int getNumber(ifstream& fin,int& flag)
{
    char temp[11]={0};
    if(flag!=0)
        return 0;
    fin.getline(temp,11);
    if(fin.eof())
    {
        flag=1;
        return 0;
    }
    if(strcmp(temp,"END EVENT"))
        return QString::fromUtf8(temp).toInt();
    else
    {
        flag=2;
        return 0;
    }


}
QString getQString(ifstream& fin,int& flag,bool isend)
{
    char temp[1024]={0};
    if(flag==1 || (flag==2 && !isend))
        return "";
    if(flag==2 && isend)
        return "END EVENT";
    fin.getline(temp,1024);
    if(fin.eof())
    {
        flag=1;
        return "";
    }
    if(isend)
    {
        if(strcmp(temp,"END EVENT"))
            return getQString(fin,flag,true);
        if(!strcmp(temp,"END EVENT"))
            return "END EVENT";
    }
    if(strcmp(temp,"END EVENT"))
        return QString::fromUtf8(temp);
    else
    {
        flag=2;
        return "";
    }
}
EventData::EventData(QString str0,QString describe0,int begin0,int end0,int weekday0,int type0,int subtype0)
{
    str=str0;
    describe=describe0;
    begin=begin0;
    end=end0;
    weekday=weekday0;
    type=type0;
    subtype=subtype0;
}
EventData::EventData()
{
    str="";
    describe="";
    begin=0;
    end=0;
    weekday=0;
    type=0;
    subtype=0;
}
int EventData::getDuration()
{
    return end-begin;
}

int record_type;
int MAX_LABELS=32;
int MAX_SUBLABELS=32;
QString *labeltext;
QString **sublabeltext;

