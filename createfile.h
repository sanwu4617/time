#ifndef CREATEFILE_H
#define CREATEFILE_H

#include <QDialog>
#include "Event.h"

namespace Ui {
class CreateFile;
}

class CreateFile : public QDialog
{
    Q_OBJECT

public:
    explicit CreateFile(QWidget *parent = nullptr);
    ~CreateFile();
signals:
    void OK(int* create);
private slots:
    void on_Button_OK_clicked();

    void on_Button_Cancel_clicked();

private:
    Ui::CreateFile *ui;
    void clear_all();
};

#endif // CREATEFILE_H
