#ifndef EVENT_H
#define EVENT_H
#include <QObject>
#include <QPushButton>
#include <QLabel>
#include "IOclass.h"
#include "Templates.h"

struct EventData{
    QString str;
    QString describe;
    int begin;
    int end;
    int weekday;
    int type;
    int subtype;
    EventData();
    EventData(QString str0,QString describe0,int begin0,int end0,int weekday0,int type0,int subtype0);
    friend bool operator < (EventData a,EventData b);
    int getDuration();
};
class Event:public QObject{
    Q_OBJECT

public:
    Event(QWidget* parent);
    Event(EventData* ed,QWidget* parent);
    Event(QString str0,int begin0,int end0,int weekday,int type,int subtype,QWidget* parent,QString describe0="");
    ~Event();
    void setDescribe(QString des);
    void setPlace(int date_begin,int date_end,int up,int down,int height,int offset);
    void change(QString str0,int begin0,int end0,int weekday,int type,int subtype,QString describe0="");
    void save(std::ofstream&);
    void load(std::ifstream&,int& flag);
    EventData toEventData();
    int getDuration();
    friend class MainWindow;
    friend class ChangeEvent;
signals:
    void theSignal(Event* event);
public slots:
    void theSlot();
private:
    QPushButton* button;
    QString str;
    QString describe;
    int begin;
    int end;
    int weekday;
    int type;
    int subtype;
    QWidget* parent;
    void Interface_operation(QWidget* parent0);
    int index_mark;
};

class LabelGroup{
public:
    LabelGroup(QWidget* parent=0);
    void setText(QString);
    void setTime(int time);
    void setSize(int size);    //size为标签组纵向占用的像素数
    void setPlace(int x,int y);
    void WriteImage(QImage& image,int x,int y);
    bool isempty();
    void show();
    void hide();
private:
    QLabel label[5];
    int x,y;
    int size;
};


#endif // EVENT_H

