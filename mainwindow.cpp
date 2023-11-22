#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    isSetup=false;
    if(!isSetup)
    {
        MAX_LABELS=32;
        MAX_SUBLABELS=32;
        labeltext=new QString[MAX_LABELS];
        sublabeltext=new QString*[MAX_LABELS];
        labels=new LabelGroup*[MAX_LABELS];
        sublabels=new LabelGroup**[MAX_LABELS];
        for(int i=0;i<MAX_LABELS;i++)
        {
            sublabeltext[i]=new QString[MAX_SUBLABELS];
            sublabels[i]=new LabelGroup*[MAX_SUBLABELS];
        }
        statictics=new int[MAX_LABELS];
        sub_statictics=new int*[MAX_LABELS];
        for(int i=0;i<MAX_LABELS;i++)
            sub_statictics[i]=new int[MAX_SUBLABELS];
        for(int i=0;i<MAX_LABELS;i++)
        {
            statictics[i]=0;
            for(int j=0;j<MAX_SUBLABELS;j++)
            {
                sub_statictics[i][j]=0;
            }
        }
    }
    ct=new changeTime();
    begin=420;
    end=1410;
    up=85;
    down=686;
    height=601;
    offset=0;
    table_title="ʱ���";
    label_count=0;
    sublabel_count=0;
    setplace();
    setLabel();
    win_addevent=new AddEvent();
    win_ch=new ChangeHeight();
    win_at=new AddTitle();
    win_cf=new CreateFile();
    connect(ct,SIGNAL(OK(QTime,QTime)),this,SLOT(resetplace(QTime,QTime)));
    connect(win_addevent,SIGNAL(OK(EventData*)),this,SLOT(addevent(EventData*)));
    connect(win_ch,SIGNAL(OK(int)),this,SLOT(changeHeight(int)));
    connect(win_at,SIGNAL(OK(QString)),this,SLOT(addtitle(QString)));
    connect(win_cf,SIGNAL(OK(int*)),this,SLOT(createfile(int*)));
    ui->setupUi(this);
    isSetup=true;
}

void MainWindow::setLabel()
{
    if(label_count>0)
    {
        for(int i=0;i<MAX_LABELS;i++)
            delete labels[i];
        for(int i=0;i<MAX_LABELS;i++)
            for(int j=0;j<MAX_SUBLABELS;j++)
                delete sublabels[i][j];
        label_count=0;
        sublabel_count=0;
    }
    for(int i=0;i<MAX_LABELS;i++)
        labels[i]=new LabelGroup(this);
    for(int i=0;i<MAX_LABELS;i++)
        for(int j=0;j<MAX_SUBLABELS;j++)
            sublabels[i][j]=new LabelGroup(this);
    loadLabels();
    for(int i=0;i<MAX_LABELS;i++)
    {
        if(labeltext[i].length()>=1)
            labels[i]->setText(labeltext[i]+"��");
    }
    for(int i=0;i<MAX_LABELS;i++)
    {
        for(int j=0;j<MAX_SUBLABELS;j++)
        {
            if(sublabeltext[i][j].length()>=1)
                sublabels[i][j]->setText("��"+sublabeltext[i][j]+"��");
        }
    }
    //�������ñ�ǩλ��
    countLabels();
    double labelsize=642/(label_count+sublabel_count*0.85);
    if(labelsize>28)
        labelsize=28;
    double sublabelsize=labelsize*0.85;
    double y=56;
    for(int i=0;i<MAX_LABELS;i++)
    {
        if(!labels[i]->isempty())
        {
            labels[i]->setSize(int(labelsize));
            labels[i]->setPlace(1030,int(y));
            labels[i]->show();
            y+=labelsize;
        }
        else
            labels[i]->hide();
        for(int j=0;j<MAX_SUBLABELS;j++)
        {
            if(!sublabels[i][j]->isempty())
            {
                sublabels[i][j]->setSize(int(sublabelsize));
                sublabels[i][j]->setPlace(1050,int(y));
                sublabels[i][j]->show();
                y+=sublabelsize;
            }
            else
                sublabels[i][j]->hide();
        }
    }
}
void MainWindow::countLabels()
{
    label_count=0;
    sublabel_count=0;
    for(int i=0;i<MAX_LABELS;i++)
    {
        if(!labels[i]->isempty())
            label_count++;
    }
    for(int i=0;i<MAX_LABELS;i++)
    {
        for(int j=0;j<MAX_SUBLABELS;j++)
        {
            if(!sublabels[i][j]->isempty())
                sublabel_count++;
        }
    }
}
MainWindow::~MainWindow()
{
    delete ui;
    delete[] labeltext;
    for(int i=0;i<MAX_LABELS;i++)
        delete[] sublabeltext[i];
    delete[] sublabeltext;
}

void MainWindow::addtitle(QString s)
{
    table_title=s;
}
void MainWindow::changeHeight(int h)
{
    height=h;
    clearTimelist();
    setplace();
}
void MainWindow::on_action_2_triggered()
{
    ct->show();
}
void MainWindow::clearTimelist()
{
    while(timelist.length()>0)
    {
        timelist.front()->deleteLater();
        timelist.pop_front();
    }
}
void MainWindow::resetplace(QTime begin1,QTime end1)
{
    clearTimelist();
    begin=begin1.hour()*60+begin1.minute();
    end=end1.hour()*60+end1.minute();
    //ui->label_8->setText(QString::number(begin));
    setplace();
}
void MainWindow::setplace()
{
    //�������ð�ťλ��
    if(end<begin)
        end+=1440;
    for(int i=(begin-1)/60+1;i*60<end;i++)
    {
        double temp=i*60-begin;
        temp/=end-begin;
        int y=up+temp*height-offset;
        int j;
        if(i>=24)
            j=i-24;
        else
            j=i;
        QLabel* time=new QLabel(QString::number(j)+":00",this);
        time->setFixedSize(120,12);
        time->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
        time->move(32,y);
        timelist.append(time);
        if(y>=up&&y<=down)
            time->show();
        else
            time->hide();
    }
    QList<Event*> temp;
    //��������ʱ��ͳ��
    for(int i=0;i<MAX_LABELS;i++)
    {
        statictics[i]=0;
        for(int j=0;j<MAX_SUBLABELS;j++)
        {
            sub_statictics[i][j]=0;
        }
    }
    while(eventlist.length()>0)
    {
        if(eventlist.front()->str!="")
        {
            eventlist.front()->setPlace(begin,end,up,down,height,offset);
            statictics[eventlist.front()->type]+=eventlist.front()->getDuration();
            sub_statictics[eventlist.front()->type][eventlist.front()->subtype]+=eventlist.front()->getDuration();
            temp.push_front(eventlist.front());
        }
        else
        {
            eventlist.front()->deleteLater();
        }
        eventlist.pop_front();
    }
    eventlist=temp;
    //��������ʱ��ͳ��
    if(isSetup)
    {
        for(int i=0;i<MAX_LABELS;i++)
            labels[i]->setTime(statictics[i]);
        for(int i=0;i<MAX_LABELS;i++)
            for(int j=0;j<MAX_SUBLABELS;j++)
                sublabels[i][j]->setTime(sub_statictics[i][j]);
    }
}

void MainWindow::changeevent(Event* event)
{
    win_ce=new ChangeEvent();
    win_ce->setData(event);
    win_ce->show();
    connect(win_ce,SIGNAL(close_signal()),this,SLOT(setplace()));
}
void MainWindow::on_pushButton_clicked()
{
    win_addevent->show();
    win_addevent->clear_all();
}
void MainWindow::addevent(EventData* eventdata)
{
    Event* event=new Event(eventdata,this);
    this->eventlist.append(event);
    setplace();
    connect(event,SIGNAL(theSignal(Event*)),this,SLOT(changeevent(Event*)));
}

void MainWindow::on_verticalScrollBar_sliderReleased()
{
    offset=(height-(down-up))*ui->verticalScrollBar->value()/100;
    clearTimelist();
    setplace();
}

void MainWindow::on_pushButton_2_clicked()
{
    QImage image(2479,3508,QImage::Format_RGB32);
    QImage describe(2479,3508,QImage::Format_RGB32);
    QColor white(255,255,255);
    QColor gray(128,128,128);
    QColor red(255,0,0);
    QColor lightgray(224,224,224);
    QColor lightred(255,192,192);
    QColor lightpink(255,128,255);
    QColor lightorange(255,192,128);
    QColor lightyellow(255,255,128);
    QColor lightpurple(192,128,255);
    QColor lightblue(128,128,255);
    QColor lightgreen(128,255,128);
    QColor black(0,0,0);
    QFont font1("�����п�");
    QFont font2("����");
    QFont font3("����");
    QStringList deslist;
    const int dataHeight=2463;
    //�������ص�Ԥ��Ϊ��ɫ
    setWhite(image,2479,3508);
    setWhite(describe,2479,3508);
    //��������ͼƬ����
    if(record_type==0)
    {
        writeWord(image,black,0,142,2479,142,100,table_title,font1,true);
        writeWord(describe,black,0,142,2479,142,100,table_title+"˵��",font1,true);
    }
    else
    {
        writeWord(image,black,0,142,2479,142,100,table_title+"ʱ�䰲�ż�¼",font1,true);
        writeWord(describe,black,0,142,2479,142,100,table_title+"����",font1,true);
    }
    //�������ñ�����
    writeWord(image,black,180,298,194,89,55,"ʱ��",font1,false);
    writeWord(image,black,380,298,194,89,55,"����һ",font1,false);
    writeWord(image,black,580,298,194,89,55,"���ڶ�",font1,false);
    writeWord(image,black,780,298,194,89,55,"������",font1,false);
    writeWord(image,black,980,298,194,89,55,"������",font1,false);
    writeWord(image,black,1180,298,194,89,55,"������",font1,false);
    writeWord(image,black,1380,298,194,89,55,"������",font1,false);
    writeWord(image,black,1580,298,194,89,55,"������",font1,false);
    //�������ʱ��
    if((begin%60)*dataHeight/(end-begin)>40)
    {
        writeWord(image,black,180,393,194,40,40,getQStringTime(begin),font2,false);
    }
    for(int i=(begin-1)/60+1;i<=end/60;i++)
    {
        int y=(i*60-begin)*dataHeight/(end-begin)+393;
        //�����ʱ����
        if(y<393+dataHeight-10)
            drawRectangle(image,lightgray,180,y,1600,4);
        //���ʱ��
        if(y<393+dataHeight-40)
            writeWord(image,black,180,y,194,40,40,QString::number(i)+":00",font2,false);
    }
    //��������¼�����
    QList<Event*> temp;
    eventsort();
    int descount=1;
    bool isdes=false;
    while(eventlist.length()>0)
    {
        int event_begin=eventlist.front()->begin;
        int event_end=eventlist.front()->end;
        int rect_up=(event_begin-begin)*dataHeight/(end-begin)+393;
        int rect_height=(event_end-event_begin)*dataHeight/(end-begin);
        int rect_left=(eventlist.front()->weekday)*200+180;
        QColor color;
        QString event_time=getQStringTime(event_begin)+"~"+getQStringTime(event_end);
        QString event_str=eventlist.front()->str;
        QString event_des=eventlist.front()->describe;
        //���Ʊ���
        int type=eventlist.front()->type*MAX_SUBLABELS+eventlist.front()->subtype;
        int cheek=0;
        int color_type=0;
        if(type<=4)
            color_type=0;
        else if(type<=6)
            color_type=1;
        else if(type<=9)
            color_type=2;
        else if(type<=10)
            color_type=3;
        else if(type<=11)
            color_type=4;
        else if(type<=63)
            color_type=5;
        else if(type<=95)
            color_type=6;
        else
            color_type=7;
        switch(color_type)
        {
        case 0:
            color=lightred;
            cheek=4;
            break;
        case 1:
            color=lightorange;
            break;
        case 2:
            color=lightpink;
            break;
        case 3:
            color=lightyellow;
            break;
        case 4:
            color=lightgreen;
            break;
        case 5:
            color=lightpurple;
            break;
        case 6:
            color=lightpink;
            break;
        case 7:
            color=lightgray;
            break;
        default:
            color=lightgray;
        }
        drawRectangle(image,color,rect_left,rect_up,194,rect_height,cheek);
        //д������
        QStringList strlist;
        if(event_end-event_begin<25)   //����������25��������ʱֻ��ʾʱ��
        {
            event_str+='('+QString::number(event_end-event_begin)+')';
            strlist.append(event_str);
        }
        else
        {
            strlist=toStringList(event_str,6);
            strlist.append(event_time);
        }
        if(event_des.length()>0)
        {
            QChar c=event_des[event_des.length()-1];
            if(c.unicode()>=10000 && c.unicode()<=10100)
                event_des=event_des.left(event_des.length()-1);
        }
        if(event_des.length()>1)
        {
            if(record_type==0)
                strlist.append("˵��"+QString::number(descount));
            else
                strlist.append("����"+QString::number(descount));
            descount++;
            isdes=true;
            if(type==0)   //��ʾΪ�γ̣�ͬʱ����ͬ���γ�
            {
                for(int i=0;i<eventlist.length();i++)
                {
                    if(eventlist.at(i)->str==event_str)
                        eventlist.at(i)->index_mark=descount-1;
                }
            }
        }
        else if(eventlist.front()->index_mark!=0)
        {
            if(record_type==0)
                strlist.append("˵��"+QString::number(eventlist.front()->index_mark));
            else
                strlist.append("����"+QString::number(eventlist.front()->index_mark));
            eventlist.front()->index_mark=0;
            isdes=true;
        }
        int strlistlen=strlist.length();
        int fontsize;
        if(rect_height>30*strlistlen)
            fontsize=30;
        else
            fontsize=rect_height/strlistlen;
        //��¼˵����Ϣ
        if(event_des.length()>0)   //-1��Ϊǰ���Ѿ������������
        {
            if(record_type==0)
                deslist.append(toStringList("˵��"+QString::number(descount-1)+"��"+event_des,42));
            else
                deslist.append(toStringList("����"+QString::number(descount-1)+"��"+event_des,42));
        }
        for(int i=0;i<strlistlen;i++)
        {
            QColor color_temp;
            if(isdes && i==strlistlen-1)
            {
                color_temp=red;
                isdes=false;
            }
            else
                color_temp=black;
            writeWord(image,color_temp,rect_left,rect_up+(rect_height-fontsize*(strlistlen-2*i))/2,194,fontsize,fontsize,strlist.front(),font2,true);
            strlist.pop_front();
        }
        temp.push_front(eventlist.front());
        eventlist.pop_front();
    }
    eventlist=temp;
    //�����������ߣ����������غϵ��ߣ�
    drawRectangle(image,gray,174,292,1606,6);
    drawRectangle(image,gray,174,387,1606,6);
    drawRectangle(image,gray,174,393+dataHeight,1606,6);
    for(int i=0;i<9;i++)
        drawRectangle(image,gray,174+200*i,292,6,107+dataHeight);
    //д��ע�Ͳ���
    if(record_type==0)
    {
        writeWord(image,black,174,413+dataHeight,250,45,45,"ע��",font2,true,Qt::AlignLeft);
        QString note11="�������񣺢��Ű���������ҵ��Ԥ��12h��";
        QString note12="          ���Ű�������ҵ��Ԥ��8h��";
        QString note2="          ��ë�����ģ�Ԥ��2h��";
        QString note31="�����������������Գ�";
        QString note32="����Ҫ�󣺢�ÿ����鲻����1h���������۲�����30min";
        QString note33="          ��������������ÿ�찲��25min���ң������ϰ��������ÿ��30min����";
        QString note4="          �۽���ʱ�������22:00��֮�󲻰�������";
        QString note5="          ��ÿ��������Ҫ���ˡ���¼ʱ�����";
        writeWord(image,black,264,413+dataHeight,2000,45,45,note11,font2,true,Qt::AlignLeft);
        writeWord(image,black,264,468+dataHeight,2000,45,45,note12,font2,true,Qt::AlignLeft);
        writeWord(image,black,264,523+dataHeight,2000,45,45,note2,font2,true,Qt::AlignLeft);
        writeWord(image,black,264,578+dataHeight,2000,45,45,note31,font2,true,Qt::AlignLeft);
        writeWord(image,black,264,633+dataHeight,2000,45,45,note32,font2,true,Qt::AlignLeft);
        writeWord(image,black,264,688+dataHeight,2000,45,45,note33,font2,true,Qt::AlignLeft);
        writeWord(image,black,264,743+dataHeight,2000,45,45,note4,font2,true,Qt::AlignLeft);
        writeWord(image,black,264,798+dataHeight,2000,45,45,note5,font2,true,Qt::AlignLeft);
    }
    //for(int i=700+dataHeight;i<3360;i+=88)
    //    drawRectangle(image,gray,254,i,2048,4);
    //д��ͳ����Ϣ
    countLabels();
    double labelsize=2500/(label_count+sublabel_count*0.85);
    double sublabelsize=labelsize*0.85;
    double y=363;
    for(int i=0;i<MAX_LABELS;i++)
    {
        if(!labels[i]->isempty())
        {
            labels[i]->WriteImage(image,1835,int(y));
            y+=labelsize;
        }
        for(int j=0;j<MAX_SUBLABELS;j++)
        {
            if(!sublabels[i][j]->isempty())
            {
                sublabels[i][j]->WriteImage(image,1870,int(y));
                y+=sublabelsize;
            }
        }
    }
    int des_count=deslist.length();
    for(int i=0;i<des_count;i++)
    {
        writeWord(describe,black,190,298+60*i,2100,50,50,deslist.front(),font3,false,Qt::AlignLeft);
        deslist.pop_front();
    }
    image.save("ʱ���.png","png",0);
    describe.save("˵��.png","png",0);
}



void MainWindow::eventsort()
{
    int eventlength=eventlist.length();
    for(int i=0;i<eventlength;i++)
    {
        for(int j=0;j<eventlength-i-1;j++)
        {
            int a=eventlist.at(j)->weekday*10000+eventlist.at(j)->begin;
            int b=eventlist.at(j+1)->weekday*10000+eventlist.at(j+1)->begin;
            if(a>b)
                eventlist.swap(j,j+1);
        }
    }
}
void MainWindow::on_Save_clicked()
{
    std::ofstream fout(ui->lineEdit->text().toLatin1());
    fout<<begin<<std::endl<<end<<std::endl;
    fout<<table_title.toStdString()<<std::endl;
    fout<<record_type<<std::endl;
    fout<<ui->dateEdit->dateTime().toTime_t()<<std::endl;
    QList<Event*> temp;
    while(eventlist.length()>0)
    {
        eventlist.front()->save(fout);
        temp.push_front(eventlist.front());
        eventlist.pop_front();
    }
    eventlist=temp;
    fout.close();
}

void MainWindow::on_Load_clicked()
{
    std::ifstream fin(ui->lineEdit->text().toLatin1());
    if(!fin)
        return;
    char temp_begin[8],temp_end[8],temp_str[64],temp_type[8],temp_date[12];
    fin.getline(temp_begin,8);
    fin.getline(temp_end,8);
    fin.getline(temp_str,64);
    fin.getline(temp_type,8);
    fin.getline(temp_date,12);
    begin=QString::fromUtf8(temp_begin).toInt();
    end=QString::fromUtf8(temp_end).toInt();
    record_type=QString::fromUtf8(temp_type).toInt();
    int date=QString::fromUtf8(temp_date).toInt();
    table_title=QString::fromUtf8(temp_str);
    ui->dateEdit->setDate(QDateTime::fromTime_t(date).date());
    QList<Event*> temp;
    int flag=0;
    while(!fin.eof())
    {
        flag=0;
        Event* event=new Event(this);
        event->load(fin,flag);
        if(flag==1)
            break;
        temp.push_front(event);
        connect(event,SIGNAL(theSignal(Event*)),this,SLOT(changeevent(Event*)));
    }
    eventlist=temp;
    clearTimelist();
    setplace();
    fin.close();
    setRecordType();
}

void MainWindow::on_action_triggered()
{
    win_ch->show();
}

void MainWindow::on_action_3_triggered()
{
    win_at->show();
}

void MainWindow::on_type_record_clicked()
{
    record_type=1;
    setRecordType();
}

void MainWindow::on_type_plan_clicked()
{
    record_type=0;
    setRecordType();
}
void MainWindow::setRecordType()
{
    if(record_type==0)
    {
        ui->type_plan->setChecked(true);
        ui->type_record->setChecked(false);
    }
    if(record_type==1)
    {
        ui->type_plan->setChecked(false);
        ui->type_record->setChecked(true);
    }
    setLabel();
    setplace();
}

void MainWindow::on_Create_clicked()
{
    win_cf->show();
}

void MainWindow::createfile(int* create)
{
    QString weekday[7]={ui->dateEdit->date().toString("yyyyMMdd")+" ����һ",
                        ui->dateEdit->date().addDays(1).toString("yyyyMMdd")+" ���ڶ�",
                        ui->dateEdit->date().addDays(2).toString("yyyyMMdd")+" ������",
                        ui->dateEdit->date().addDays(3).toString("yyyyMMdd")+" ������",
                        ui->dateEdit->date().addDays(4).toString("yyyyMMdd")+" ������",
                        ui->dateEdit->date().addDays(5).toString("yyyyMMdd")+" ������",
                        ui->dateEdit->date().addDays(6).toString("yyyyMMdd")+" ������"};
    QString week=ui->dateEdit->date().toString("yyyyMMdd")+"~"+ui->dateEdit->date().addDays(6).toString("yyyyMMdd")+"��";
    int ***sta_time;    //����ά�ȣ����ڼ����������
    bool **switch_class;
    double_new(switch_class,MAX_LABELS,MAX_SUBLABELS);
    multi_new(sta_time,8,MAX_LABELS,MAX_SUBLABELS);
    QVector<Event*> temp0=eventlist.toVector();
    QVector<EventData> temp;
    QStringList sta_list[8];
    QImage *image[8];
    QFont font1("�����п�");
    QFont font2("����");
    QFont font3("����");
    for(int i=0;i<MAX_LABELS;i++)
    {
        for(int j=0;j<MAX_SUBLABELS;j++)
        {
            switch_class[i][j]=create[i*MAX_SUBLABELS+8+j];
        }
    }
    for(int i=0;i<8;i++)
    {
        if(create[i]==0)
            continue;
        image[i]=new QImage(2479,3508,QImage::Format_RGB32);
        setWhite(*image[i],2479,3508);
    }
    for(int i=0;i<temp0.size();i++)
    {
        temp.append(temp0[i]->toEventData());
    }
    std::sort(temp.begin(),temp.end());
    for(int i=0;i<temp.size();i++)
    {
        //ʹ�����ü򻯱���
        int &w=temp[i].weekday;
        int &t=temp[i].type;
        int &s=temp[i].subtype;
        int &b=temp[i].begin;
        int &e=temp[i].end;
        int dur=e-b;
        QString &d=temp[i].describe;
        QString &str=temp[i].str;
        //�жϱ���Ŀ�ǲ�����Ҫ������
        if(!switch_class[t][s])
            continue;
        QStringList day_event;
        QStringList week_event;
        QString class_text=labeltext[t];
        if(s>=0)
            class_text+=" "+sublabeltext[t][s];
        //��ȡ���Ч��
        int ds=d.size();
        int score=-1;
        if(ds>0)
        {
            if(d[ds-1].unicode()>=10000 && d[ds-1].unicode()<=10100)
            {
                score=d[ds-1].unicode()-10000;
                d=d.left(ds-1);
            }
        }
        week_event.append("��Ŀ��"+str);
        week_event.append("���"+class_text);
        week_event.append("ʱ�䣺"+weekday[w-1]+getQStringTime(b,e));
        if(score>=0)
        {
            week_event.append("���Ч����"+QString::number(score)+"��");
            dur=dur*score/100;
        }
        day_event.append(week_event);
        week_event.append("END");
        if(d.length()>1)
        {
            day_event.append("���ݣ�"+d);
        }
        day_event.append("END");

        sta_time[0][t][s]+=dur;
        sta_time[w][t][s]+=dur;
        sta_list[0].append(week_event);
        sta_list[w].append(day_event);
    }
    for(int i=0;i<8;i++)
    {
        if(create[i]==0)   //δѡ�б���
            continue;
        QString title;
        if(i==0)
            title=week;
        else
            title=weekday[i-1];
        if(record_type==0)
            title+=" �ƻ�";
        if(record_type==1)
            title+=" ��¼";
        writeWord(*image[i],QColor(Qt::black),0,150,2479,100,80,title,font1,true,Qt::AlignCenter);
        QStringList temp_list;
        while(!sta_list[i].isEmpty())
        {
            temp_list.append(toStringList(sta_list[i].front(),32,6));
            sta_list[i].pop_front();
        }
        int y=300;
        int row_height=0;
        if(i>0)
        {
            row_height=3400/temp_list.size();
            if(row_height>70)
                row_height=70;
        }
        else
        {
            row_height=6800/temp_list.size();
            if(row_height>35)
                row_height=35;
        }
        while(!temp_list.isEmpty())
        {
            QString &st=temp_list.front();
            if(i==0)
            {
                if(st=="END")
                    y+=row_height*0.4;
                else
                {
                    if(y<3300)
                        writeWord(*image[i],QColor(Qt::black),200,y,1000,50,25,st,font2,false,Qt::AlignLeft);
                    else
                        writeWord(*image[i],QColor(Qt::black),1015,y-3000,1000,50,25,st,font2,false,Qt::AlignLeft);
                    y+=row_height;
                }
            }
            else
            {
                if(st=="END")
                    y+=row_height*0.4;
                else
                {
                    writeWord(*image[i],QColor(Qt::black),175,y,2179,70,50,st,font2,false,Qt::AlignLeft);
                    y+=row_height;
                }
            }
            temp_list.pop_front();
        }
        //�������ͳ����Ϣ
        int sum_time=arraysum(sta_time[i],MAX_LABELS,MAX_SUBLABELS);
        y=370;
        drawRectangle(*image[i],Qt::black,1810,300,3,3025);
        QString time_text;
        if(record_type==0)
            time_text="ʱ��ͳ�ƣ�";
        else
            time_text="��Чʱ��ͳ�ƣ�";
        writeWord(*image[i],QColor(Qt::black),1830,y-70,2179,70,50,time_text,font3,true,Qt::AlignLeft);
        for(int j=0;j<MAX_LABELS;j++)
        {
            int sum_j=arraysum(sta_time[i][j],MAX_SUBLABELS);
            if(sum_j<=0)
                continue;
            writeWord(*image[i],QColor(Qt::black),1830,y,2179,70,50,labeltext[j]+"��",font3,false,Qt::AlignLeft);
            int x=50*labeltext[j].length()+1890;
            writeWordTime(*image[i],x,y,70,50,sum_j,font3);
            y+=70;
            for(int k=0;k<MAX_SUBLABELS;k++)
            {
                if(sta_time[i][j][k]>0)
                {
                    writeWord(*image[i],QColor(Qt::black),1830,y,2179,70,50,"��"+sublabeltext[j][k]+"��",font3,false,Qt::AlignLeft);
                    x=50*sublabeltext[j][k].length()+1940;
                    writeWordTime(*image[i],x,y,70,50,sta_time[i][j][k],font3);
                    y+=70;
                }
            }
        }
        writeWord(*image[i],QColor(Qt::black),1830,y,2179,70,50,"��ʱ�䣺",font3,false,Qt::AlignLeft);
        writeWordTime(*image[i],2040,y,70,50,sum_time,font3);
        QString filename;
        if(i==0)
            filename=week;
        else
            filename=weekday[i-1];
        if(record_type==0)
            filename+="�ƻ�";
        if(record_type==1)
            filename+="��¼";
        filename+=".png";
        image[i]->save(filename,"png",0);
    }
}
