#include "lecteur.h"

Lecteur::Lecteur(QObject *parent):QMediaPlayer(parent)
{

}

Lecteur::~Lecteur()
{

}

void Lecteur::lecture(QString piste, qint64 position)
{
    setMedia(QUrl::fromLocalFile(piste));
    play();
    setPosition(position);
}

int Lecteur::tempsActuelP()
{
    qint64 tempA=tempsActuelI()/10;
    qint64 tempT=tempsTotalI()/1000;
    int pourcent;
    if(!tempT)
        pourcent=0;
    else pourcent=tempA/tempT;
    return pourcent;
}

bool Lecteur::enArret()
{
    return (state()==QMediaPlayer::StoppedState);
}

bool Lecteur::enLecture()
{
    return (state()==QMediaPlayer::PlayingState);
}

bool Lecteur::enPause()
{
    return (state()==QMediaPlayer::PausedState);
}
