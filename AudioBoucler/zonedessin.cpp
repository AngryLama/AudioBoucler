#include "zonedessin.h"

zoneDessin::zoneDessin(QRect geometry, QWidget *parent):QWidget(parent)
{
    setGeometry(geometry);
    setStyleSheet("background-color: white;");
}

void zoneDessin::spectre()
{
    donnees.clear();
    valMax=0;
    //int hz=info.retourFrequenceI();
    QFile file(info.retourChemin());
    tailleFichier=file.size()-44;
    if(file.open(QFile::ReadOnly)){
        QByteArray data=file.readAll();
        QDataStream analyse(&data,QIODevice::ReadOnly);

        //Passer les metadonnées
        if(info.retourExtension()=="wav"){
            analyse.setByteOrder(QDataStream::LittleEndian);
            char meta[44];
            analyse.readRawData(meta,44);
        }

        if(info.retourExtension()=="aif" || info.retourExtension()=="aiff"){
            analyse.setByteOrder(QDataStream::BigEndian);
            char meta[28];
            analyse.readRawData(meta,28);
        }

        //int saut=(tailleFichier/width())+info.retourEchantillonageI();
        int saut=info.retourEchantillonageI();
        //char SData[16];
        char sautDonnees[saut];
        qint16 don;
        int x=0;
        while(!analyse.atEnd()){
            //analyse.readRawData(SData,16);
            //donnees[x]=QString::fromLatin1(SData).toInt();
            analyse>>don;
            donnees<<don;
            if(donnees[x]>valMax)
                valMax=donnees[x];
            analyse.readRawData(sautDonnees,saut);
            x++;
        }
        /*for(int x=0;x<10000;x++)
            donnees.removeLast();*/

        //Mise à l'échelle
        valMax-=10;
        for(int x=0;x<donnees.length();x++){
            donnees[x]=(donnees[x]*height()/2)/valMax;
            if(donnees[x]<0)
                donnees[x]*=(-1);
            if(donnees[x]==0)
                donnees[x]=height()/2;
            else donnees[x]+=height()/2;
        }
    }
    update();
}

void zoneDessin::paintEvent(QPaintEvent *event)
{
    //Permettre l'utilisation de StyleSheet
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    //Créer le painter
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(pen);
    pen.setWidth(2);
    painter.drawLine(0,height()/2,width(),height()/2);
    pen.setWidth(1);
    pen.setColor(Qt::black);
    //Vidage de la liste
    for(int x=0;x<width();x++){
        courbe<<height()/2;
    }
    //Création de la courbe
    int posX=0;
    int moy=donnees.length()/width();
    for(int x=0;posX<width();x+=moy){
        int temp=0;
        for(int y=0;y<moy;y++)
        if(x+y<donnees.length())
            temp+=donnees[x+y];
        temp/=moy;
        courbe[posX++]=temp;
    }
    //Définition de l'échelle
    int high=0;
    int low=height();
    for(int x=0;x<courbe.length();x++){
        if(courbe[x]>high)
            high=courbe[x];
        if(courbe[x]<low)
            low=courbe[x];
    }
    //int pour=(height()-5)-(height()/2);
    float coeff=(float)(height()-5)/(float)high;
    /*for(int x=0;x<courbe.length();x++){
        courbe[x]*=(courbe[x]*coeff)/high;
    }*/
    //Dessin sur le widget
    int y=0;
    /*for(int x=1;x<width();x++){
        painter.drawLine(y,courbe[x-1],y+1,courbe[x]);
        painter.drawLine(y,height()/2-(courbe[x-1]-(height()/2)),y+1,(height()/2)-(courbe[x]-(height()/2)));
        y++;
    }*/
    for(int x=1;x<width();x++){
        painter.drawLine(y,courbe[x-1]*((courbe[x-1]*coeff)/high),y+1,courbe[x]*((courbe[x]*coeff)/high));
        painter.drawLine(y,height()/2-(courbe[x-1]*((courbe[x-1]*coeff)/high)-(height()/2)),y+1,(height()/2)-(courbe[x]*((courbe[x]*coeff)/high)-(height()/2)));
        y++;
    }
    painter.end();
    event->accept();
}
