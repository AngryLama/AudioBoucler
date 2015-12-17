#include "infopiste.h"

InfoPiste::InfoPiste(const QString _chemin, const qint64 _finPiste, const int _frequence, const int _debit)
    :finPiste(_finPiste),frequence(_frequence),debit(_debit)
{
    touche="-";
    valDebut=0;
    affDebut="0:00:0";
    echantillonage=16;
    boucler=false;
    if(_chemin!="")
        cheminPiste(_chemin);
}

void InfoPiste::cheminPiste(QString val){
    chemin=val;

    //Définition nom de piste
    int temp=val.lastIndexOf("/");
    temp++;
    nom=val.right(val.length()-temp);

    //Définition extension
    temp=val.lastIndexOf(".");
    temp++;
    extension=val.right(val.length()-temp);

    if(extension=="wav")
        analyseWAV();

    if(extension=="aif" || extension=="aiff")
        analyseAIFF();
}

void InfoPiste::analyseWAV(){
        //Ouverture du fichier
        QFile wavFile(chemin);
        wavFile.open(QFile::ReadOnly);
        
        //Lecture des données
        QByteArray wavFileContent = wavFile.readAll();

        //Taille (non sur disque)
        tailleFichier=wavFileContent.size();

        // Define the header components

        char fileType[4];

        qint32 fileSize;

        char waveName[4];

        char fmtName[3];

        qint32 fmtLength;

        short fmtType;

        short numberOfChannels;

        qint32 frequ;

        qint32 sampleRateXBitsPerSampleXChanngelsDivEight;

        short bitsPerSampleXChannelsDivEightPointOne;

        short bitsPerSample;

        char dataHeader[4];

        qint32 dataSize;

        // Create a data stream to analyze the data

        QDataStream analyzeHeaderDS(&wavFileContent,QIODevice::ReadOnly);

        analyzeHeaderDS.setByteOrder(QDataStream::LittleEndian);

        // Now pop off the appropriate data into each header field defined above

        analyzeHeaderDS.readRawData(fileType,4); // "RIFF"

        analyzeHeaderDS >> fileSize; // File Size

        analyzeHeaderDS.readRawData(waveName,4); // "WAVE"

        analyzeHeaderDS.readRawData(fmtName,3); // "fmt"

        analyzeHeaderDS >> fmtLength; // Format length

        analyzeHeaderDS >> fmtType; // Format type

        //Nombre de canaux
        analyzeHeaderDS >> numberOfChannels;
        numberOfChannels/=256;

        //Fréquence
        analyzeHeaderDS >> frequ;
        frequ/=256;
        
        analyzeHeaderDS >> sampleRateXBitsPerSampleXChanngelsDivEight; // (Sample Rate * BitsPerSample * Channels) / 8

        analyzeHeaderDS >> bitsPerSampleXChannelsDivEightPointOne; // (BitsPerSample * Channels) / 8.1
        
        //Echantillonage
        analyzeHeaderDS >> bitsPerSample;
        bitsPerSample/=256;

        analyzeHeaderDS.readRawData(dataHeader,4); // "data" header

        analyzeHeaderDS >> dataSize; // Data Size


        echantillonage=bitsPerSample;
}

void InfoPiste::analyseAIFF()
{
        QFile aiffFile(chemin);
        aiffFile.open(QFile::ReadOnly);

        QByteArray aiffFileContent = aiffFile.readAll();

        char temp[20];

        short nbCanaux;

        qint32 nbFrames;

        short bitsPerSample;

        QDataStream analyse(&aiffFileContent,QIODevice::ReadOnly);
        analyse.setByteOrder(QDataStream::BigEndian);

        analyse.readRawData(temp,20);

        analyse>>nbCanaux;

        analyse>>nbFrames;

        analyse>>bitsPerSample;
        echantillonage=bitsPerSample;

}
