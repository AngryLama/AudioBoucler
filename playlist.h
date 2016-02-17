#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <QString>
#include "infopiste.h"

class Playlist
{
public:
    Playlist(const QString _nom);
    qint64 retourTempsTotal();

    //Nom
    void definirNom(const QString val){nom=val;}
    QString retourNom(){return nom;}

    //Pistes
    int nbPistes(){return pistes.count();}
    void ajouterPiste(const QString chemin);
    void supprimerPiste(const int position);
    void viderPlaylist(){pistes.clear();}
    void deplacerPiste(const int posActuel, const int posDesti){pistes.move(posActuel,posDesti);}
    QString retourNomPiste(const int pos){return pistes[pos].retourNom();}
    QString retourCheminPiste(const int pos){return pistes[pos].retourChemin();}
    void definirFinPiste(const int pos,const qint64 val){pistes[pos].definirFinPiste(val);}
    void definirFrequencePiste(const int pos,const int val){pistes[pos].definirFrequence(val);}
    void definirDebitPiste(const int pos,const int val){pistes[pos].definirDebit(val);}
    qint64 retourFinPiste(const int pos){return pistes[pos].retourFinPisteI();}

    //Bouclage
    void definirBouclage(bool val){boucler=val;}
    bool retourBouclage(){return boucler;}

    //Touche
    void definirTouche(const QString val){touche=val;}
    QString retourTouche(){return touche;}

private:
    QString nom;
    QList<InfoPiste> pistes;
    bool boucler;
    QString touche;
};

#endif // PLAYLIST_H
