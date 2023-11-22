#ifndef CHANGETIME_H
#define CHANGETIME_H

#include <QDialog>
#include <QTime>
#pragma execution_character_set("utf-8")

namespace Ui {
class changeTime;
}

class changeTime : public QDialog
{
    Q_OBJECT

public:
    explicit changeTime(QWidget *parent = nullptr);
    ~changeTime();

signals:
    void OK(QTime begin,QTime end);
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::changeTime *ui;
};

#endif // CHANGETIME_H
