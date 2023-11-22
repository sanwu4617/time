#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QList>
#include <qtextcodec.h>
#include <QImage>
#include <QFont>
#include <fstream>
#include <QLineEdit>
#include <QVector>

#include "Event.h"
#include "changetime.h"
#include "addevent.h"
#include "changeevent.h"
#include "changeheight.h"
#include "addtitle.h"
#include "createfile.h"
#pragma execution_character_set("utf-8")

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_2_triggered();

    void on_pushButton_clicked();

private slots:
    void resetplace(QTime begin,QTime end);
    void addevent(EventData*);
    void changeevent(Event* event);
    void setplace();
    void changeHeight(int h);
    void addtitle(QString s);
    void on_verticalScrollBar_sliderReleased();
    void eventsort();
    void createfile(int* create);

    void on_pushButton_2_clicked();

    void on_Save_clicked();

    void on_Load_clicked();

    void on_action_triggered();

    void on_action_3_triggered();

    void on_type_record_clicked();

    void on_type_plan_clicked();

    void on_Create_clicked();

private:
    Ui::MainWindow *ui;
    changeTime *ct;
    AddEvent *win_addevent;
    ChangeEvent *win_ce;
    ChangeHeight *win_ch;
    AddTitle* win_at;
    CreateFile* win_cf;

    int begin;
    int end;
    int up;
    int down;
    int height;
    int offset;

    QList<QLabel*> timelist;
    QList<Event*> eventlist;
    bool isSetup;
    QString table_title;

    LabelGroup **labels;
    LabelGroup ***sublabels;
    int label_count;
    int sublabel_count;
    int *statictics;
    int **sub_statictics;

    void setLabel();
    void clearTimelist();

    void setRecordType();
    void countLabels();
};
#endif // MAINWINDOW_H
