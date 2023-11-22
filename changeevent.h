#ifndef CHANGEEVENT_H
#define CHANGEEVENT_H

#include <QDialog>
#include "Event.h"
#pragma execution_character_set("utf-8")

namespace Ui {
class ChangeEvent;
}

class ChangeEvent : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeEvent(QWidget *parent = nullptr);
    void setData(Event* event);
    ~ChangeEvent();

signals:
    void close_signal();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::ChangeEvent *ui;
    Event* event;
    void setsubtype(int index);
    void clear_all();
};

#endif // CHANGEEVENT_H
