#include "Event.h"
LabelGroup::LabelGroup(QWidget* parent)
{
    label[0].setText("");
    label[1].setText("0");
    label[2].setText("时");
    label[3].setText("0");
    label[4].setText("分");
    label[1].setAlignment(Qt::AlignCenter);
    label[2].setAlignment(Qt::AlignCenter);
    label[3].setAlignment(Qt::AlignCenter);
    label[4].setAlignment(Qt::AlignCenter);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::red);
    label[1].setPalette(pa);
    label[3].setPalette(pa);
    for(int i=0;i<5;i++)
        label[i].setParent(parent);
    x=0;
    y=0;
    size=0;
}
void LabelGroup::setText(QString text)
{
    label[0].setText(text);
}
void LabelGroup::setSize(int size0)
{
    size=size0;
    int label_height=int(size*0.9);
    int label_width[3]={0};
    int word_size=int(size*0.45);
    label_width[0]=label[0].text().length()*word_size*4;
    label_width[1]=int(size*1.8);
    label_width[2]=size;

    QFont ft("黑体",word_size,50);
    label[0].setFixedSize(label_width[0],label_height);
    label[1].setFixedSize(label_width[1],label_height);
    label[2].setFixedSize(label_width[2],label_height);
    label[3].setFixedSize(label_width[1],label_height);
    label[4].setFixedSize(label_width[2],label_height);
    for(int i=0;i<5;i++)
        label[i].setFont(ft);
}
void LabelGroup::setPlace(int x0, int y0)
{
    x=x0;
    y=y0;
    int title_len=int(label[0].text().length()*size*0.68);
    label[0].move(x,y);
    label[1].move(x+int(title_len),y);
    label[2].move(x+int(title_len+size*1.3),y);
    label[3].move(x+int(title_len+size*2.0),y);
    label[4].move(x+int(title_len+size*3.3),y);
}
void LabelGroup::setTime(int time)
{
    label[1].setText(QString::number(time/60));
    label[3].setText(QString::number(time%60));
}
void LabelGroup::show()
{
    for(int i=0;i<5;i++)
        label[i].show();
}
void LabelGroup::hide()
{
    for(int i=0;i<5;i++)
        label[i].hide();
}
bool LabelGroup::isempty()
{
    if(label[0].text().length()<1)
        return true;
    return false;
}
void LabelGroup::WriteImage(QImage& image,int x0,int y0)
{
    int ws=size*1.5;
    QFont font("黑体",ws,50);
    writeWord(image,Qt::black,x0,y0,ws*8,ws,ws,label[0].text(),font,false,Qt::AlignLeft);
    writeWord(image,Qt::red,int(x0+ws*0.6),y0+ws*1.3,int(ws*1.8),ws,ws,label[1].text(),font,false,Qt::AlignCenter);
    writeWord(image,Qt::black,int(x0+ws*2.4),y0+ws*1.3,ws,ws,ws,label[2].text(),font,false,Qt::AlignCenter);
    writeWord(image,Qt::red,int(x0+ws*3.4),y0+ws*1.3,int(ws*1.8),ws,ws,label[3].text(),font,false,Qt::AlignCenter);
    writeWord(image,Qt::black,int(x0+ws*5.2),y0+ws*1.3,ws,ws,ws,label[4].text(),font,false,Qt::AlignCenter);
}
