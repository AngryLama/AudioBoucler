#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWindow>
#include <QProgressBar>
#include <QGridLayout>
#include <QResizeEvent>
#include <QFileDialog>
#include <QGraphicsOpacityEffect>
#include <QDesktopWidget>
#include <QSystemTrayIcon>
#include "zonedessin.h"
#include "lecteur.h"
#include "infopiste.h"
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QCheckBox>
#include "playlist.h"
#include "conversion.h"

using namespace std;

typedef struct{
    QString chemin;
    int pos;
    bool isPlaylist=false;
    int posP=-1;
    qint64 debut=0;
    qint64 fin=0;
    bool bouclage=false;
    QString touche="-";
}ImportPiste;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void masquerLabelTemps(bool etat);
    void modifierOpacite(qreal value);
    void actualiser();
    void actualiserPistesPlaylist(const int pos=0);
    void actualiserTouches();
    void actualiserBoutonsPreSui(QTableWidget *tableau);
    void adapterInterface(int w, int h);
    void creerLigne(QString type, int x);
    void razInterface();
    void ajouterPiste();
    void verifChamps(QString text,QLineEdit *lineEdit);
    void verifChampsFin(QString &text,QLineEdit *lineEdit);

protected:
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);

private slots:
    void on_pushButton_Ajouter_clicked();

    void on_pushButton_ActualiserOutput_clicked();

    void on_pushButton_Muet_clicked();

    void on_horizontalSlider_Volume_valueChanged(int value);

    void on_pushButton_Lecture_clicked();

    void on_pushButton_Stop_clicked();

    void on_finTimerRefresh();

    void on_horizontalSlider_debut_valueChanged(int value);

    void on_horizontalSlider_fin_valueChanged(int value);

    void on_horizontalSlider_Opacite_valueChanged(int value);

    void on_checkBox_Playlist_clicked(bool checked);

    void on_pushButton_nouvellePlaylist_clicked();

    void on_pushButton_Supprimer_clicked();

    void on_pushButton_Precedent_clicked();

    void on_pushButton_Suivant_clicked();

    void on_pushButton_supprimerPlaylist_clicked();

    void on_pushButton_Monter_clicked();

    void on_pushButton_Descendre_clicked();

    void on_comboBox_Output_currentIndexChanged(const QString &arg1);

    void on_pushButton_AjouterDossier_clicked();

    void on_tableWidget_Pistes_cellDoubleClicked(int row, int column);

    void on_tableWidget_Pistes_currentCellChanged(int currentRow, int currentColumn, int previousRow/*, int previousColumn*/);

    void on_tableWidget_Pistes_itemChanged(QTableWidgetItem *item);

    void on_tableWidget_Playlist_itemChanged(QTableWidgetItem *item);

    void on_pushButton_Pause_clicked();

    void on_tableWidget_Playlist_currentCellChanged(int currentRow, int currentColumn/*, int previousRow, int previousColumn*/);

    void on_etatBouclagePiste(bool etat);

    void on_pushButton_Parametres_clicked();

    void on_tableWidget_Pistes_itemPressed(/*QTableWidgetItem *item*/);

    void on_tableWidget_PistesPlaylist_currentCellChanged(int currentRow/*, int currentColumn, int previousRow, int previousColumn*/);

    void on_etatBouclagePlaylist(bool etat);

    void on_pushButton_Exporter_clicked();

    void on_pushButton_Importer_clicked();

    void on_finVerifTemps(qint64 value=0);

    void on_lineEdit_cursDebut_textEdited(const QString &arg1);

    void on_lineEdit_cursDebut_editingFinished();

    void on_lineEdit_cursFin_textEdited(const QString &arg1);

    void on_lineEdit_cursFin_editingFinished();

    void on_pushButton_volume_clicked();

    void on_finTimerVerificationErreurImportation();

private:
    Ui::MainWindow *ui;
    QProgressBar *progressBar_Analyse;
    QString lastRepertoire;
    QList<zoneDessin*> pistes;
    QList<Playlist> playlist;
    Lecteur *lecteur;
    QTimer *refresh,*timerVerificationErreurImportation;
    QList<ImportPiste> listeImportPiste;
    QGraphicsOpacityEffect *effectG,*effectD;
    int enLectureP,enLecture,verifImport;
    QWidget *barreProgression;
    QList<QCheckBox*> bouclagePiste,bouclagePlaylist;
    QMessageBox *informations;
    QString erreur;
    bool saveMuet;
};

#endif // MAINWINDOW_H
