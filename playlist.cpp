#include "playlist.h"

Playlist::Playlist(const QString _nom):nom(_nom)
{
    touche="-";
    boucler=false;
}

qint64 Playlist::retourTempsTotal()
{
    qint64 temps=0;
    for(int x=0;x<nbPistes();x++)
        temps+=pistes[x].retourFinPisteI();
    return temps;
}

void Playlist::ajouterPiste(const QString chemin)
{
    if(chemin!=""){
        pistes<<InfoPiste(chemin);
    }
}

void Playlist::supprimerPiste(const int position)
{
    if(position>-1 && position<pistes.count()){
        pistes.removeAt(position);
    }
}

