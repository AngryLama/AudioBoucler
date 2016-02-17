#ifndef ZONEDESSIN_H
#define ZONEDESSIN_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include <QPixmap>
#include <QFile>
#include <QMouseEvent>
#include "infopiste.h"

class zoneDessin : public QWidget
{
    Q_OBJECT
public:
    zoneDessin(QRect geometry,QWidget *parent=0);
    InfoPiste info;
    void spectre();

public slots:
    void paintEvent(QPaintEvent *event);

private:
    int tailleZone;
    int tailleFichier;
    QPixmap pixmap;
    QPen pen;
    int valMax;
    QList<int> donnees;
    QList<int> courbe;
};

#endif // ZONEDESSIN_H
