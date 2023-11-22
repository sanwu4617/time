#include "IOclass.h"
void drawRectangle(QImage& image,QColor color,int x1,int y1,int width,int height,int cheek)
{
    for(int i=x1;i<x1+width;i++)
    {
        for(int j=y1;j<y1+height;j++)
        {
            image.setPixelColor(i,j,color);
        }
    }
    if(cheek>0)
    {
        drawRectangle(image,Qt::red,x1,y1,width,cheek,0);
        drawRectangle(image,Qt::red,x1,y1,cheek,height,0);
        drawRectangle(image,Qt::red,x1+width-cheek,y1,cheek,height,0);
        drawRectangle(image,Qt::red,x1,y1+height-cheek,width,cheek,0);
    }
}
void writeWord(QImage& image,QColor color,int x1,int y1,int width,int height,int size,QString str,QFont font,bool isBold,int align)
{
    QPainter painter(&image); //为这个QImage构造一个QPainter
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);  //设置画刷的组合模式CompositionMode_SourceOut这个模式为目标图像在上。
    QPen pen = painter.pen();
    pen.setColor(color);
    font.setBold(isBold);
    font.setPixelSize(size);//改变字体大小
    painter.setPen(pen);
    painter.setFont(font);
    painter.drawText(x1,y1,width,height,align,str);
}
void setWhite(QImage& image,int x,int y)
{
    for(int i=0;i<x;i++)
    {
        for(int j=0;j<y;j++)
        {
            image.setPixelColor(i,j,Qt::white);
        }
    }
}
void writeWordTime(QImage& image,int x1,int y1,int height,int size,int time,QFont font,int mode)
{
    switch(mode)
    {
    case 0:
        if(time>=60)
        {
            writeWord(image,QColor(Qt::red),x1,y1,size*1.2,height,size,QString::number(time/60),font,false,Qt::AlignHCenter);
            writeWord(image,QColor(Qt::black),x1+size*1.2,y1,size*1.2,height,size,"时",font,false,Qt::AlignHCenter);
            x1+=size*2.4;
        }
        writeWord(image,QColor(Qt::red),x1,y1,size*1.2,height,size,QString::number(time%60),font,false,Qt::AlignHCenter);
        writeWord(image,QColor(Qt::black),x1+size*1.2,y1,size,height,size,"分",font,false,Qt::AlignHCenter);
        break;
    }
}
QStringList toStringList(QString s,int width,int align)
{
    QStringList strlist;
    QString temp;
    int strlength=s.length();
    int realwidth=width*2;
    int reallength=0;
    int begin=0,n=0;
    bool first=true;
    if(strlength==0)
        return strlist;
    for(int i=0;i<strlength;i++)
    {
        reallength+=s[i].unicode()<128? 1 : 2 ;
        n++;
        if(s[i]=='\\')
        {
            s[i]=' ';
            reallength=realwidth;    //表示将本行终止
        }
        if((reallength+1)/2==realwidth/2||i==strlength-1)
        {
            QString qtemp="";
            if(!first)
                for(int k=0;k<align;k++)
                    qtemp+=" ";
            if(i==strlength-1 && s.mid(begin,n).length()==0)
                break;
            if(ismark(s[i+1]))   //标点放在行末
            {
                n++;
                i++;
            }
            if(n>=1)
                strlist.append(qtemp+s.mid(begin,n));   //添加6个空格进行对齐
            begin+=n;
            n=0;
            reallength=align;
            first=false;
        }
    }
    return strlist;
}
bool ismark(QChar c)
{
    QChar mark[4]={65292,12290,12289,65307};
    for(int i=0;i<4;i++)
    {
        if(c==mark[i])
            return true;
    }
    return false;
}
QString getQStringTime(int time)
{
    QString qtime;
    int hour=time/60;
    int minute=time%60;
    if(minute<10)
        qtime=QString::number(hour)+":0"+QString::number(minute);
    else
        qtime=QString::number(hour)+":"+QString::number(minute);
    return qtime;
}
QString getQStringTime(int begin,int end)
{
    return getQStringTime(begin)+"~"+getQStringTime(end);
}
using namespace std;
void loadLabels()
{
    ifstream fin("labels.ini");
    if(!fin)
        return;
    while(!fin.eof())
    {
        char c[256]={0};
        fin.getline(c,256);
        if(c[0]=='L')
        {
            int label_num=c[5]*10+c[6]-528;
            if(label_num>=0 && label_num<MAX_LABELS)
            {
                labeltext[label_num]=QString::fromUtf8(c+8);
            }
        }
        if(c[0]=='S')
        {
            int label_num=c[8]*10+c[9]-528;
            int sublabel_num=c[10]*10+c[11]-528;
            if(label_num>=0 && label_num<MAX_LABELS && sublabel_num>=0 && sublabel_num<MAX_SUBLABELS)
            {
                sublabeltext[label_num][sublabel_num]=QString::fromUtf8(c+13);
            }
        }

    }
}
