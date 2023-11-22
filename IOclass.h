#ifndef IOCLASS_H
#define IOCLASS_H

#include <QPen>
#include <QPainter>
#include <fstream>
#include <QString>
#pragma execution_character_set("utf-8")

QString getQStringTime(int time);
QString getQStringTime(int begin,int end);
int getNumber(std::ifstream& fin,int& flag);
QString getQString(std::ifstream& fin,int& flag,bool isend=false);
QStringList toStringList(QString s,int width,int align=0);
void drawRectangle(QImage& image,QColor color,int x1,int y1,int width,int height,int cheek=0);
void writeWord(QImage& image,QColor color,int x1,int y1,int width,int height,int size,QString str,QFont font,bool isBold,int align=Qt::AlignCenter);
void writeWordTime(QImage& image,int x1,int y1,int height,int size,int time,QFont font,int mode=0);
void setWhite(QImage& image,int x,int y);
void loadLabels();
bool ismark(QChar);
extern int MAX_LABELS;
extern int MAX_SUBLABELS;
extern int record_type;
extern QString *labeltext;
extern QString **sublabeltext;
#endif // IOCLASS_H
