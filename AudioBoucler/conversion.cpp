#include "conversion.h"

QString charToQString(const char *chaine)
{
    std::string conv=chaine;
    return QString::fromUtf8(const_cast<char *>(conv.c_str()));
}


uint QStringToKey(QString const & str){
    QKeySequence seq(str);
    uint keyCode;

    keyCode = seq[0];
    return keyCode;
}

QString msToQString(qint64 temps)
{
    qint64 conv[4];
    conv[0]=temps/100;
    conv[1]=0;
    conv[2]=0;
    conv[3]=0;

    while(conv[0]>=10)
    {
        conv[0]-=10;
        conv[1]++;
        if(conv[1]>=60){
            conv[1]-=60;
            conv[2]++;
        }
        if(conv[2]>=60){
            conv[2]-=60;
            conv[3]++;
        }
    };

    QString retour;
    if(conv[3]!=0){
        retour=QString::number(conv[3])+":";
        if(conv[2]<10)
            retour+="0";
    }
    retour+=QString::number(conv[2])+":";
    if(conv[1]<10)
        retour+="0";
    retour+=QString::number(conv[1])+":";
    /*if(conv[0]<10)
        retour+="0";*/
    retour+=QString::number(conv[0]);
    return retour;
}

qint64 QStringToMs(QString temps)
{
    QStringList conv=temps.split(":");
    qint64 retour=conv[2].toInt()*100;
    retour+=conv[1].toInt()*1000;
    retour+=conv[0].toInt()*60000;
    return retour;
}
