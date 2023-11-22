#ifndef CHANGEHEIGHT_H
#define CHANGEHEIGHT_H

#include <QDialog>

namespace Ui {
class ChangeHeight;
}

class ChangeHeight : public QDialog
{
    Q_OBJECT

signals:
    void OK(int);
public:
    explicit ChangeHeight(QWidget *parent = nullptr);
    ~ChangeHeight();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::ChangeHeight *ui;
};

#endif // CHANGEHEIGHT_H
