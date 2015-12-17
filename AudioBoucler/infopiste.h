#ifndef INFOPISTE_H
#define INFOPISTE_H

#include <QString>
#include <QApplication>
#include "lecteur.h"
#include "conversion.h"

class InfoPiste
{
public:
    InfoPiste(const QString _chemin="", const qint64 _finPiste=0, const int _frequence=0, const int _debit=0);

    //Nom et chemin
    void cheminPiste(QString val);
    QString retourNom(){return nom;}
    QString retourChemin(){return chemin;}
    QString retourExtension(){return extension;}

    //Touche de lancement
    void definirTouche(QString val){touche=val;}
    QString retourTouche(){return touche;}

    //Définition des temps
    void changerDebut(qint64 val){valDebut=val;affDebut=msToQString(val);}
    void changerFin(qint64 val){valFin=val;affFin=msToQString(val);}
    void definirFinPiste(qint64 val){finPiste=val;affPiste=msToQString(val);}

    //Debut défini
    qint64 retourDebutI(){return valDebut;}
    QString retourDebutQ(){return affDebut;}

    //Fin définie
    qint64 retourFinI(){return valFin;}
    QString retourFinQ(){return affFin;}

    //Fin Piste
    qint64 retourFinPisteI(){return finPiste;}
    QString retourFinPisteQ(){return affPiste;}

    //Frequence
    void definirFrequence(int val){frequence=val;}
    int retourFrequenceI(){return frequence;}
    QString retourFrequenceQ(){return QString::number(frequence)+" Hz";}

    //Echantillonage
    void definirEchantillonage(int val){echantillonage=val;}
    int retourEchantillonageI(){return echantillonage;}
    QString retourEchantillonageQ(){return QString::number(echantillonage)+" Bits";}

    //Debit
    void definirDebit(int val){debit=val;}
    int retourDebitI(){return debit;}
    QString retourDebitQ(){return QString::number(debit)+" Kbits/s";}

    //Valeur moyenne
    void definirValMoyenne(int val){valMoyenne=val;}
    int retourValMoyenne(){return valMoyenne;}

    //Analyse
    void analyseWAV();
    void analyseAIFF();

    //Bouclage
    void definirBouclage(bool etat){boucler=etat;}
    bool retourBouclage(){return boucler;}

private:
    //Noms
    QString nom;
    QString chemin;
    QString extension;

    //Touche lancement
    QString touche;

    //Temps
    qint64 valDebut;
    QString affDebut;
    qint64 valFin;
    QString affFin;
    qint64 finPiste;
    QString affPiste;

    //Données
    int frequence;
    int debit;
    int echantillonage;
    int tailleFichier;
    int nbCanaux;
    int valMoyenne;

    //Bouclage
    bool boucler;
};

#endif // INFOPISTE_H
