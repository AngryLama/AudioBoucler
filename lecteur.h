#ifndef LECTEUR_H
#define LECTEUR_H

#include <QtMultimedia>
#include "conversion.h"

class Lecteur:public QObject
{
    Q_OBJECT
public:
    Lecteur(QObject *parent=0);
    ~Lecteur();
    void muet(bool etat){player->setMuted(etat);}
    bool estMuet(){return player->isMuted();}
    void changerVolume(int valeur){player->setVolume(valeur);}
    void lecture(QString piste, qint64 position=0);
    void pause(){player->pause();}
    void reprendre(){player->play();}
    void stop(){player->stop();}
    void changerPosition(qint64 position){player->setPosition(position);}
    void changerOutput(QString nom);
    QString tempsActuelQ(){return msToQString(player->position());}
    QString tempsTotalQ(){return msToQString(player->duration());}
    qint64 tempsActuelI(){return player->position();}
    qint64 tempsTotalI(){return player->duration();}
    int tempsActuelP();
    QString retourType(){return player->metaData(QMediaMetaData::MediaType).toString();}
    bool enArret();
    bool enLecture();
    bool enPause();
    int retourDebit(){return player->metaData(QMediaMetaData::AudioBitRate).toInt()/1000;}
    int retourFrequence(){return player->metaData(QMediaMetaData::SampleRate).toInt();}
    QString retourEchantillonage(){return player->metaData(QMediaMetaData::MediaType).toString();}
    int retourValMoyenne(){return player->metaData(QMediaMetaData::AverageLevel).toInt();}

signals:
    tempsDisponible(qint64);

private slots:
    void on_tempsDisponible(qint64 value){emit tempsDisponible(value);}

private:
    QMediaPlayer *player;
};

#endif // LECTEUR_H
