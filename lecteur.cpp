#include "lecteur.h"

Lecteur::Lecteur(QObject *parent):QObject(parent)
{
    player = new QMediaPlayer;
    connect(player,SIGNAL(durationChanged(qint64)),this,SLOT(on_tempsDisponible(qint64)));
}

Lecteur::~Lecteur()
{
    delete player;
}

void Lecteur::lecture(QString piste, qint64 position)
{
    player->setMedia(QUrl::fromLocalFile(piste));
    player->play();
    changerPosition(position);
}

void Lecteur::changerOutput(QString nom)
{
    QMediaService *svc = player->service();
    QAudioOutputSelectorControl *out = qobject_cast<QAudioOutputSelectorControl *>
                                       (svc->requestControl(QAudioOutputSelectorControl_iid));
    out->setActiveOutput(nom);
    svc->releaseControl(out);
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
    if(player->state()==QMediaPlayer::StoppedState)
        return true;
    else return false;
}

bool Lecteur::enLecture()
{
    if(player->state()==QMediaPlayer::PlayingState)
        return true;
    else return false;
}

bool Lecteur::enPause()
{
    if(player->state()==QMediaPlayer::PausedState)
        return true;
    else return false;
}
