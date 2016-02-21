#ifndef LECTEUR_H
#define LECTEUR_H

#include <QtMultimedia>
#include "conversion.h"

class Lecteur : public QMediaPlayer
{
    Q_OBJECT
public:
    Lecteur(QObject *parent=0);
    ~Lecteur();
    void muet(bool etat){setMuted(etat);}
    bool estMuet(){return isMuted();}
    void changerVolume(int valeur){setVolume(valeur);}
    void lecture(QString piste, qint64 position=0);
    void reprendre(){play();}
    QString tempsActuelQ(){return msToQString(position());}
    QString tempsTotalQ(){return msToQString(duration());}
    qint64 tempsActuelI(){return position();}
    qint64 tempsTotalI(){return duration();}
    int tempsActuelP();
    QString retourType(){return metaData(QMediaMetaData::MediaType).toString();}
    bool enArret();
    bool enLecture();
    bool enPause();
    int retourDebit(){return metaData(QMediaMetaData::AudioBitRate).toInt()/1000;}
    int retourFrequence(){return metaData(QMediaMetaData::SampleRate).toInt();}
    QString retourEchantillonage(){return metaData(QMediaMetaData::MediaType).toString();}
    int retourValMoyenne(){return metaData(QMediaMetaData::AverageLevel).toInt();}
};

#endif // LECTEUR_H
