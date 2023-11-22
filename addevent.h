#ifndef ADDEVENT_H
#define ADDEVENT_H

#include <QDialog>
#include <QString>
#include "Event.h"
#pragma execution_character_set("utf-8")

namespace Ui {
class AddEvent;
}

class AddEvent : public QDialog
{
    Q_OBJECT

signals:
    void OK(EventData*);
public:
    explicit AddEvent(QWidget *parent = nullptr);
    ~AddEvent();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::AddEvent *ui;
    friend class MainWindow;
    void clear_all();
};

#endif // ADDEVENT_H
