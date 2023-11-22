#ifndef ADDTITLE_H
#define ADDTITLE_H

#include <QDialog>

namespace Ui {
class AddTitle;
}

class AddTitle : public QDialog
{
    Q_OBJECT

public:
    explicit AddTitle(QWidget *parent = nullptr);
    ~AddTitle();
signals:
    void OK(QString);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::AddTitle *ui;
};

#endif // ADDTITLE_H
