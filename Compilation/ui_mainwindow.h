/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOuvrir;
    QAction *actionOuvrir_2;
    QWidget *centralWidget;
    QPushButton *pushButton_Lecture;
    QPushButton *pushButton_Ajouter;
    QPushButton *pushButton_Quitter;
    QGroupBox *groupBox_Informations;
    QTableWidget *tableWidget_Info;
    QTableWidget *tableWidget_Touches;
    QPushButton *pushButton_Stop;
    QLabel *label_Titre;
    QSlider *horizontalSlider_debut;
    QSlider *horizontalSlider_fin;
    QTableWidget *tableWidget_Pistes;
    QPushButton *pushButton_Supprimer;
    QWidget *widget_G;
    QWidget *widget_D;
    QPushButton *pushButton_Monter;
    QPushButton *pushButton_Descendre;
    QTableWidget *tableWidget_Playlist;
    QPushButton *pushButton_nouvellePlaylist;
    QPushButton *pushButton_Precedent;
    QPushButton *pushButton_Suivant;
    QLabel *label_tempsActuel;
    QLabel *label_cursDebut;
    QLabel *label_cursFin;
    QLabel *label_tempsTotal;
    QPushButton *pushButton_supprimerPlaylist;
    QPushButton *pushButton_AjouterDossier;
    QPushButton *pushButton_Pause;
    QCheckBox *checkBox_Playlist;
    QPushButton *pushButton_Parametres;
    QGroupBox *groupBox_Parametres;
    QLabel *label_Opacite;
    QSlider *horizontalSlider_Opacite;
    QLabel *label_Output;
    QComboBox *comboBox_Output;
    QPushButton *pushButton_ActualiserOutput;
    QTableWidget *tableWidget_PistesPlaylist;
    QPushButton *pushButton_Exporter;
    QPushButton *pushButton_Importer;
    QLineEdit *lineEdit_tempsTotal;
    QLineEdit *lineEdit_tempsActuel;
    QLineEdit *lineEdit_cursDebut;
    QLineEdit *lineEdit_cursFin;
    QPushButton *pushButton_volume;
    QGroupBox *groupBox_volume;
    QSlider *horizontalSlider_Volume;
    QPushButton *pushButton_Muet;
    QLabel *label_tempsActuelPlaylist;
    QFrame *line_tempsPlaylist;
    QLabel *label_tempsTotalPlaylist;
    QLabel *label_titrePistePlaylist;
    QProgressBar *progressBar_Playlist;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1280, 730);
        MainWindow->setMinimumSize(QSize(1280, 730));
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        actionOuvrir = new QAction(MainWindow);
        actionOuvrir->setObjectName(QStringLiteral("actionOuvrir"));
        actionOuvrir_2 = new QAction(MainWindow);
        actionOuvrir_2->setObjectName(QStringLiteral("actionOuvrir_2"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton_Lecture = new QPushButton(centralWidget);
        pushButton_Lecture->setObjectName(QStringLiteral("pushButton_Lecture"));
        pushButton_Lecture->setEnabled(false);
        pushButton_Lecture->setGeometry(QRect(380, 565, 40, 40));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Icon/Play.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Lecture->setIcon(icon);
        pushButton_Lecture->setIconSize(QSize(20, 20));
        pushButton_Ajouter = new QPushButton(centralWidget);
        pushButton_Ajouter->setObjectName(QStringLiteral("pushButton_Ajouter"));
        pushButton_Ajouter->setGeometry(QRect(195, 425, 40, 40));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Icon/Ajout musique.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Ajouter->setIcon(icon1);
        pushButton_Ajouter->setIconSize(QSize(30, 30));
        pushButton_Quitter = new QPushButton(centralWidget);
        pushButton_Quitter->setObjectName(QStringLiteral("pushButton_Quitter"));
        pushButton_Quitter->setGeometry(QRect(1150, 600, 110, 30));
        groupBox_Informations = new QGroupBox(centralWidget);
        groupBox_Informations->setObjectName(QStringLiteral("groupBox_Informations"));
        groupBox_Informations->setGeometry(QRect(660, 420, 600, 160));
        QFont font;
        font.setPointSize(12);
        groupBox_Informations->setFont(font);
        groupBox_Informations->setAlignment(Qt::AlignCenter);
        tableWidget_Info = new QTableWidget(groupBox_Informations);
        if (tableWidget_Info->columnCount() < 4)
            tableWidget_Info->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_Info->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_Info->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_Info->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_Info->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget_Info->setObjectName(QStringLiteral("tableWidget_Info"));
        tableWidget_Info->setGeometry(QRect(10, 30, 571, 41));
        QFont font1;
        font1.setPointSize(14);
        tableWidget_Info->setFont(font1);
        tableWidget_Info->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget_Info->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget_Info->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget_Info->setSelectionMode(QAbstractItemView::NoSelection);
        tableWidget_Touches = new QTableWidget(groupBox_Informations);
        if (tableWidget_Touches->columnCount() < 4)
            tableWidget_Touches->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_Touches->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_Touches->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_Touches->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_Touches->setHorizontalHeaderItem(3, __qtablewidgetitem7);
        tableWidget_Touches->setObjectName(QStringLiteral("tableWidget_Touches"));
        tableWidget_Touches->setGeometry(QRect(10, 90, 571, 61));
        tableWidget_Touches->setFont(font1);
        tableWidget_Touches->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget_Touches->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget_Touches->setSelectionMode(QAbstractItemView::NoSelection);
        tableWidget_Touches->horizontalHeader()->setHighlightSections(false);
        tableWidget_Touches->raise();
        tableWidget_Info->raise();
        pushButton_Stop = new QPushButton(centralWidget);
        pushButton_Stop->setObjectName(QStringLiteral("pushButton_Stop"));
        pushButton_Stop->setEnabled(false);
        pushButton_Stop->setGeometry(QRect(480, 565, 40, 40));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Icon/Stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Stop->setIcon(icon2);
        pushButton_Stop->setIconSize(QSize(20, 20));
        label_Titre = new QLabel(centralWidget);
        label_Titre->setObjectName(QStringLiteral("label_Titre"));
        label_Titre->setGeometry(QRect(0, 0, 1281, 61));
        QFont font2;
        font2.setPointSize(24);
        label_Titre->setFont(font2);
        label_Titre->setAlignment(Qt::AlignCenter);
        horizontalSlider_debut = new QSlider(centralWidget);
        horizontalSlider_debut->setObjectName(QStringLiteral("horizontalSlider_debut"));
        horizontalSlider_debut->setEnabled(false);
        horizontalSlider_debut->setGeometry(QRect(20, 350, 1241, 20));
        horizontalSlider_debut->setMinimum(0);
        horizontalSlider_debut->setMaximum(10000);
        horizontalSlider_debut->setOrientation(Qt::Horizontal);
        horizontalSlider_fin = new QSlider(centralWidget);
        horizontalSlider_fin->setObjectName(QStringLiteral("horizontalSlider_fin"));
        horizontalSlider_fin->setEnabled(false);
        horizontalSlider_fin->setGeometry(QRect(20, 370, 1241, 20));
        horizontalSlider_fin->setMinimum(0);
        horizontalSlider_fin->setMaximum(10000);
        horizontalSlider_fin->setValue(10000);
        horizontalSlider_fin->setOrientation(Qt::Horizontal);
        tableWidget_Pistes = new QTableWidget(centralWidget);
        if (tableWidget_Pistes->columnCount() < 4)
            tableWidget_Pistes->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_Pistes->setHorizontalHeaderItem(0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_Pistes->setHorizontalHeaderItem(1, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_Pistes->setHorizontalHeaderItem(2, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_Pistes->setHorizontalHeaderItem(3, __qtablewidgetitem11);
        tableWidget_Pistes->setObjectName(QStringLiteral("tableWidget_Pistes"));
        tableWidget_Pistes->setGeometry(QRect(240, 425, 370, 135));
        tableWidget_Pistes->setFont(font1);
        tableWidget_Pistes->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        tableWidget_Pistes->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget_Pistes->setCornerButtonEnabled(false);
        tableWidget_Pistes->horizontalHeader()->setHighlightSections(false);
        pushButton_Supprimer = new QPushButton(centralWidget);
        pushButton_Supprimer->setObjectName(QStringLiteral("pushButton_Supprimer"));
        pushButton_Supprimer->setEnabled(false);
        pushButton_Supprimer->setGeometry(QRect(195, 585, 40, 40));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/Icon/Supprimer.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Supprimer->setIcon(icon3);
        pushButton_Supprimer->setIconSize(QSize(30, 30));
        widget_G = new QWidget(centralWidget);
        widget_G->setObjectName(QStringLiteral("widget_G"));
        widget_G->setGeometry(QRect(10, 60, 0, 280));
        widget_G->setStyleSheet(QStringLiteral("background-color: grey;"));
        widget_D = new QWidget(centralWidget);
        widget_D->setObjectName(QStringLiteral("widget_D"));
        widget_D->setGeometry(QRect(1260, 70, 0, 280));
        widget_D->setStyleSheet(QStringLiteral("background-color: grey;"));
        pushButton_Monter = new QPushButton(centralWidget);
        pushButton_Monter->setObjectName(QStringLiteral("pushButton_Monter"));
        pushButton_Monter->setEnabled(false);
        pushButton_Monter->setGeometry(QRect(195, 505, 40, 40));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/Icon/Monter.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Monter->setIcon(icon4);
        pushButton_Monter->setIconSize(QSize(25, 25));
        pushButton_Descendre = new QPushButton(centralWidget);
        pushButton_Descendre->setObjectName(QStringLiteral("pushButton_Descendre"));
        pushButton_Descendre->setEnabled(false);
        pushButton_Descendre->setGeometry(QRect(195, 545, 40, 40));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/Icon/Descendre.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Descendre->setIcon(icon5);
        pushButton_Descendre->setIconSize(QSize(25, 25));
        tableWidget_Playlist = new QTableWidget(centralWidget);
        if (tableWidget_Playlist->columnCount() < 3)
            tableWidget_Playlist->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget_Playlist->setHorizontalHeaderItem(0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget_Playlist->setHorizontalHeaderItem(1, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget_Playlist->setHorizontalHeaderItem(2, __qtablewidgetitem14);
        tableWidget_Playlist->setObjectName(QStringLiteral("tableWidget_Playlist"));
        tableWidget_Playlist->setGeometry(QRect(20, 425, 160, 135));
        QFont font3;
        font3.setPointSize(13);
        tableWidget_Playlist->setFont(font3);
        tableWidget_Playlist->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        tableWidget_Playlist->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        pushButton_nouvellePlaylist = new QPushButton(centralWidget);
        pushButton_nouvellePlaylist->setObjectName(QStringLiteral("pushButton_nouvellePlaylist"));
        pushButton_nouvellePlaylist->setGeometry(QRect(20, 560, 80, 20));
        pushButton_Precedent = new QPushButton(centralWidget);
        pushButton_Precedent->setObjectName(QStringLiteral("pushButton_Precedent"));
        pushButton_Precedent->setEnabled(false);
        pushButton_Precedent->setGeometry(QRect(330, 565, 40, 40));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Icon/Pr\303\251c\303\251dent.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Precedent->setIcon(icon6);
        pushButton_Precedent->setIconSize(QSize(20, 20));
        pushButton_Suivant = new QPushButton(centralWidget);
        pushButton_Suivant->setObjectName(QStringLiteral("pushButton_Suivant"));
        pushButton_Suivant->setEnabled(false);
        pushButton_Suivant->setGeometry(QRect(530, 565, 40, 40));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/Icon/Suivant.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Suivant->setIcon(icon7);
        pushButton_Suivant->setIconSize(QSize(20, 20));
        label_tempsActuel = new QLabel(centralWidget);
        label_tempsActuel->setObjectName(QStringLiteral("label_tempsActuel"));
        label_tempsActuel->setGeometry(QRect(520, 400, 130, 20));
        label_tempsActuel->setFont(font1);
        label_tempsActuel->setAlignment(Qt::AlignCenter);
        label_cursDebut = new QLabel(centralWidget);
        label_cursDebut->setObjectName(QStringLiteral("label_cursDebut"));
        label_cursDebut->setGeometry(QRect(520, 440, 130, 20));
        label_cursDebut->setFont(font1);
        label_cursDebut->setAlignment(Qt::AlignCenter);
        label_cursFin = new QLabel(centralWidget);
        label_cursFin->setObjectName(QStringLiteral("label_cursFin"));
        label_cursFin->setGeometry(QRect(520, 480, 130, 20));
        label_cursFin->setFont(font1);
        label_cursFin->setAlignment(Qt::AlignCenter);
        label_tempsTotal = new QLabel(centralWidget);
        label_tempsTotal->setObjectName(QStringLiteral("label_tempsTotal"));
        label_tempsTotal->setGeometry(QRect(520, 520, 130, 20));
        label_tempsTotal->setFont(font1);
        label_tempsTotal->setAlignment(Qt::AlignCenter);
        pushButton_supprimerPlaylist = new QPushButton(centralWidget);
        pushButton_supprimerPlaylist->setObjectName(QStringLiteral("pushButton_supprimerPlaylist"));
        pushButton_supprimerPlaylist->setGeometry(QRect(100, 560, 80, 20));
        pushButton_AjouterDossier = new QPushButton(centralWidget);
        pushButton_AjouterDossier->setObjectName(QStringLiteral("pushButton_AjouterDossier"));
        pushButton_AjouterDossier->setGeometry(QRect(195, 465, 40, 40));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/Icon/Ajout dossier musique.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_AjouterDossier->setIcon(icon8);
        pushButton_AjouterDossier->setIconSize(QSize(30, 30));
        pushButton_Pause = new QPushButton(centralWidget);
        pushButton_Pause->setObjectName(QStringLiteral("pushButton_Pause"));
        pushButton_Pause->setEnabled(false);
        pushButton_Pause->setGeometry(QRect(430, 565, 40, 40));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/Icon/Pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Pause->setIcon(icon9);
        pushButton_Pause->setIconSize(QSize(20, 20));
        checkBox_Playlist = new QCheckBox(centralWidget);
        checkBox_Playlist->setObjectName(QStringLiteral("checkBox_Playlist"));
        checkBox_Playlist->setGeometry(QRect(30, 385, 121, 31));
        QFont font4;
        font4.setPointSize(16);
        checkBox_Playlist->setFont(font4);
        checkBox_Playlist->setLayoutDirection(Qt::RightToLeft);
        pushButton_Parametres = new QPushButton(centralWidget);
        pushButton_Parametres->setObjectName(QStringLiteral("pushButton_Parametres"));
        pushButton_Parametres->setGeometry(QRect(1030, 600, 110, 30));
        groupBox_Parametres = new QGroupBox(centralWidget);
        groupBox_Parametres->setObjectName(QStringLiteral("groupBox_Parametres"));
        groupBox_Parametres->setGeometry(QRect(930, 520, 341, 80));
        groupBox_Parametres->setFont(font);
        groupBox_Parametres->setStyleSheet(QStringLiteral("background-color: white;"));
        groupBox_Parametres->setAlignment(Qt::AlignCenter);
        label_Opacite = new QLabel(groupBox_Parametres);
        label_Opacite->setObjectName(QStringLiteral("label_Opacite"));
        label_Opacite->setGeometry(QRect(10, 30, 71, 21));
        QFont font5;
        font5.setPointSize(10);
        label_Opacite->setFont(font5);
        horizontalSlider_Opacite = new QSlider(groupBox_Parametres);
        horizontalSlider_Opacite->setObjectName(QStringLiteral("horizontalSlider_Opacite"));
        horizontalSlider_Opacite->setGeometry(QRect(60, 30, 261, 21));
        horizontalSlider_Opacite->setFont(font5);
        horizontalSlider_Opacite->setMaximum(100);
        horizontalSlider_Opacite->setValue(75);
        horizontalSlider_Opacite->setSliderPosition(75);
        horizontalSlider_Opacite->setOrientation(Qt::Horizontal);
        label_Output = new QLabel(groupBox_Parametres);
        label_Output->setObjectName(QStringLiteral("label_Output"));
        label_Output->setGeometry(QRect(10, 50, 41, 21));
        label_Output->setFont(font5);
        comboBox_Output = new QComboBox(groupBox_Parametres);
        comboBox_Output->setObjectName(QStringLiteral("comboBox_Output"));
        comboBox_Output->setGeometry(QRect(50, 50, 211, 21));
        comboBox_Output->setFont(font5);
        pushButton_ActualiserOutput = new QPushButton(groupBox_Parametres);
        pushButton_ActualiserOutput->setObjectName(QStringLiteral("pushButton_ActualiserOutput"));
        pushButton_ActualiserOutput->setGeometry(QRect(260, 50, 71, 21));
        pushButton_ActualiserOutput->setFont(font5);
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/Icon/Boucle.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_ActualiserOutput->setIcon(icon10);
        tableWidget_PistesPlaylist = new QTableWidget(centralWidget);
        if (tableWidget_PistesPlaylist->columnCount() < 1)
            tableWidget_PistesPlaylist->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget_PistesPlaylist->setHorizontalHeaderItem(0, __qtablewidgetitem15);
        tableWidget_PistesPlaylist->setObjectName(QStringLiteral("tableWidget_PistesPlaylist"));
        tableWidget_PistesPlaylist->setGeometry(QRect(240, 425, 270, 135));
        tableWidget_PistesPlaylist->setFont(font1);
        tableWidget_PistesPlaylist->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        tableWidget_PistesPlaylist->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        pushButton_Exporter = new QPushButton(centralWidget);
        pushButton_Exporter->setObjectName(QStringLiteral("pushButton_Exporter"));
        pushButton_Exporter->setGeometry(QRect(760, 600, 81, 31));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/Icon/Export.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Exporter->setIcon(icon11);
        pushButton_Exporter->setIconSize(QSize(30, 30));
        pushButton_Importer = new QPushButton(centralWidget);
        pushButton_Importer->setObjectName(QStringLiteral("pushButton_Importer"));
        pushButton_Importer->setGeometry(QRect(850, 600, 81, 31));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/Icon/Import.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Importer->setIcon(icon12);
        pushButton_Importer->setIconSize(QSize(30, 30));
        lineEdit_tempsTotal = new QLineEdit(centralWidget);
        lineEdit_tempsTotal->setObjectName(QStringLiteral("lineEdit_tempsTotal"));
        lineEdit_tempsTotal->setGeometry(QRect(520, 540, 130, 20));
        lineEdit_tempsTotal->setFont(font1);
        lineEdit_tempsTotal->setAlignment(Qt::AlignCenter);
        lineEdit_tempsTotal->setReadOnly(true);
        lineEdit_tempsActuel = new QLineEdit(centralWidget);
        lineEdit_tempsActuel->setObjectName(QStringLiteral("lineEdit_tempsActuel"));
        lineEdit_tempsActuel->setGeometry(QRect(520, 420, 130, 20));
        lineEdit_tempsActuel->setFont(font1);
        lineEdit_tempsActuel->setAlignment(Qt::AlignCenter);
        lineEdit_tempsActuel->setReadOnly(true);
        lineEdit_cursDebut = new QLineEdit(centralWidget);
        lineEdit_cursDebut->setObjectName(QStringLiteral("lineEdit_cursDebut"));
        lineEdit_cursDebut->setGeometry(QRect(520, 460, 130, 20));
        lineEdit_cursDebut->setFont(font1);
        lineEdit_cursDebut->setAlignment(Qt::AlignCenter);
        lineEdit_cursFin = new QLineEdit(centralWidget);
        lineEdit_cursFin->setObjectName(QStringLiteral("lineEdit_cursFin"));
        lineEdit_cursFin->setGeometry(QRect(520, 500, 130, 20));
        lineEdit_cursFin->setFont(font1);
        lineEdit_cursFin->setAlignment(Qt::AlignCenter);
        pushButton_volume = new QPushButton(centralWidget);
        pushButton_volume->setObjectName(QStringLiteral("pushButton_volume"));
        pushButton_volume->setGeometry(QRect(940, 600, 80, 31));
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/Icon/Haut-parleur son.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_volume->setIcon(icon13);
        pushButton_volume->setIconSize(QSize(30, 30));
        groupBox_volume = new QGroupBox(centralWidget);
        groupBox_volume->setObjectName(QStringLiteral("groupBox_volume"));
        groupBox_volume->setGeometry(QRect(810, 530, 311, 71));
        groupBox_volume->setFont(font);
        groupBox_volume->setStyleSheet(QStringLiteral("background-color: white;"));
        groupBox_volume->setAlignment(Qt::AlignCenter);
        horizontalSlider_Volume = new QSlider(groupBox_volume);
        horizontalSlider_Volume->setObjectName(QStringLiteral("horizontalSlider_Volume"));
        horizontalSlider_Volume->setGeometry(QRect(10, 30, 251, 35));
        horizontalSlider_Volume->setMaximum(100);
        horizontalSlider_Volume->setValue(0);
        horizontalSlider_Volume->setOrientation(Qt::Horizontal);
        pushButton_Muet = new QPushButton(groupBox_volume);
        pushButton_Muet->setObjectName(QStringLiteral("pushButton_Muet"));
        pushButton_Muet->setGeometry(QRect(270, 30, 35, 35));
        pushButton_Muet->setIcon(icon13);
        pushButton_Muet->setIconSize(QSize(30, 30));
        label_tempsActuelPlaylist = new QLabel(centralWidget);
        label_tempsActuelPlaylist->setObjectName(QStringLiteral("label_tempsActuelPlaylist"));
        label_tempsActuelPlaylist->setGeometry(QRect(20, 100, 561, 161));
        QFont font6;
        font6.setPointSize(72);
        label_tempsActuelPlaylist->setFont(font6);
        label_tempsActuelPlaylist->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        line_tempsPlaylist = new QFrame(centralWidget);
        line_tempsPlaylist->setObjectName(QStringLiteral("line_tempsPlaylist"));
        line_tempsPlaylist->setGeometry(QRect(600, 100, 16, 161));
        QFont font7;
        font7.setPointSize(8);
        line_tempsPlaylist->setFont(font7);
        line_tempsPlaylist->setFrameShadow(QFrame::Plain);
        line_tempsPlaylist->setLineWidth(10);
        line_tempsPlaylist->setFrameShape(QFrame::VLine);
        label_tempsTotalPlaylist = new QLabel(centralWidget);
        label_tempsTotalPlaylist->setObjectName(QStringLiteral("label_tempsTotalPlaylist"));
        label_tempsTotalPlaylist->setGeometry(QRect(630, 100, 561, 161));
        label_tempsTotalPlaylist->setFont(font6);
        label_tempsTotalPlaylist->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_titrePistePlaylist = new QLabel(centralWidget);
        label_titrePistePlaylist->setObjectName(QStringLiteral("label_titrePistePlaylist"));
        label_titrePistePlaylist->setGeometry(QRect(430, 260, 361, 51));
        QFont font8;
        font8.setPointSize(20);
        label_titrePistePlaylist->setFont(font8);
        label_titrePistePlaylist->setLineWidth(1);
        label_titrePistePlaylist->setAlignment(Qt::AlignCenter);
        progressBar_Playlist = new QProgressBar(centralWidget);
        progressBar_Playlist->setObjectName(QStringLiteral("progressBar_Playlist"));
        progressBar_Playlist->setGeometry(QRect(250, 310, 721, 30));
        progressBar_Playlist->setValue(0);
        progressBar_Playlist->setTextVisible(false);
        MainWindow->setCentralWidget(centralWidget);
        groupBox_Informations->raise();
        pushButton_Lecture->raise();
        pushButton_Ajouter->raise();
        pushButton_Quitter->raise();
        pushButton_Stop->raise();
        label_Titre->raise();
        horizontalSlider_debut->raise();
        horizontalSlider_fin->raise();
        tableWidget_Pistes->raise();
        pushButton_Supprimer->raise();
        widget_G->raise();
        widget_D->raise();
        pushButton_Monter->raise();
        pushButton_Descendre->raise();
        tableWidget_Playlist->raise();
        pushButton_nouvellePlaylist->raise();
        pushButton_Precedent->raise();
        pushButton_Suivant->raise();
        label_tempsActuel->raise();
        label_cursDebut->raise();
        label_cursFin->raise();
        label_tempsTotal->raise();
        pushButton_supprimerPlaylist->raise();
        pushButton_AjouterDossier->raise();
        pushButton_Pause->raise();
        checkBox_Playlist->raise();
        pushButton_Parametres->raise();
        groupBox_Parametres->raise();
        tableWidget_PistesPlaylist->raise();
        pushButton_Exporter->raise();
        pushButton_Importer->raise();
        lineEdit_tempsTotal->raise();
        lineEdit_tempsActuel->raise();
        lineEdit_cursDebut->raise();
        lineEdit_cursFin->raise();
        pushButton_volume->raise();
        groupBox_volume->raise();
        label_tempsActuelPlaylist->raise();
        line_tempsPlaylist->raise();
        label_tempsTotalPlaylist->raise();
        label_titrePistePlaylist->raise();
        progressBar_Playlist->raise();

        retranslateUi(MainWindow);
        QObject::connect(pushButton_Quitter, SIGNAL(clicked()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Audio Boucler v1.03", 0));
        actionOuvrir->setText(QApplication::translate("MainWindow", "Ouvrir", 0));
        actionOuvrir_2->setText(QApplication::translate("MainWindow", "Ouvrir", 0));
#ifndef QT_NO_TOOLTIP
        pushButton_Lecture->setToolTip(QApplication::translate("MainWindow", "Lecture", 0));
#endif // QT_NO_TOOLTIP
        pushButton_Lecture->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_Ajouter->setToolTip(QApplication::translate("MainWindow", "Ajouter des pistes", 0));
#endif // QT_NO_TOOLTIP
        pushButton_Ajouter->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_Quitter->setToolTip(QApplication::translate("MainWindow", "Quitter", 0));
#endif // QT_NO_TOOLTIP
        pushButton_Quitter->setText(QApplication::translate("MainWindow", "Quitter", 0));
        groupBox_Informations->setTitle(QApplication::translate("MainWindow", "Informations", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_Info->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Format", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_Info->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Fr\303\251quence", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_Info->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Echantillonnage", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_Info->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "D\303\251bit", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_Touches->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "Type", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_Touches->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "N\302\260", 0));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_Touches->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "Nom", 0));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_Touches->horizontalHeaderItem(3);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "Touche", 0));
#ifndef QT_NO_TOOLTIP
        pushButton_Stop->setToolTip(QApplication::translate("MainWindow", "Stop", 0));
#endif // QT_NO_TOOLTIP
        pushButton_Stop->setText(QString());
        label_Titre->setText(QApplication::translate("MainWindow", "Ajoutez une piste pour commencer", 0));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_Pistes->horizontalHeaderItem(0);
        ___qtablewidgetitem8->setText(QApplication::translate("MainWindow", "Nom", 0));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_Pistes->horizontalHeaderItem(1);
        ___qtablewidgetitem9->setText(QApplication::translate("MainWindow", "Touche", 0));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_Pistes->horizontalHeaderItem(2);
        ___qtablewidgetitem10->setText(QApplication::translate("MainWindow", "Temps", 0));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_Pistes->horizontalHeaderItem(3);
        ___qtablewidgetitem11->setText(QApplication::translate("MainWindow", "Boucler", 0));
#ifndef QT_NO_TOOLTIP
        pushButton_Supprimer->setToolTip(QApplication::translate("MainWindow", "Supprimer", 0));
#endif // QT_NO_TOOLTIP
        pushButton_Supprimer->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_Monter->setToolTip(QApplication::translate("MainWindow", "Monter la piste", 0));
#endif // QT_NO_TOOLTIP
        pushButton_Monter->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_Descendre->setToolTip(QApplication::translate("MainWindow", "Descendre la piste", 0));
#endif // QT_NO_TOOLTIP
        pushButton_Descendre->setText(QString());
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget_Playlist->horizontalHeaderItem(0);
        ___qtablewidgetitem12->setText(QApplication::translate("MainWindow", "Nom", 0));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget_Playlist->horizontalHeaderItem(1);
        ___qtablewidgetitem13->setText(QApplication::translate("MainWindow", "Touche", 0));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget_Playlist->horizontalHeaderItem(2);
        ___qtablewidgetitem14->setText(QApplication::translate("MainWindow", "Boucler", 0));
#ifndef QT_NO_TOOLTIP
        pushButton_nouvellePlaylist->setToolTip(QApplication::translate("MainWindow", "Ajouter une playlist", 0));
#endif // QT_NO_TOOLTIP
        pushButton_nouvellePlaylist->setText(QApplication::translate("MainWindow", "+", 0));
#ifndef QT_NO_TOOLTIP
        pushButton_Precedent->setToolTip(QApplication::translate("MainWindow", "Pr\303\251c\303\251dent", 0));
#endif // QT_NO_TOOLTIP
        pushButton_Precedent->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_Suivant->setToolTip(QApplication::translate("MainWindow", "Suivant", 0));
#endif // QT_NO_TOOLTIP
        pushButton_Suivant->setText(QString());
        label_tempsActuel->setText(QApplication::translate("MainWindow", "Temps Actuel", 0));
        label_cursDebut->setText(QApplication::translate("MainWindow", "Curseur Debut", 0));
        label_cursFin->setText(QApplication::translate("MainWindow", "Curseur Fin", 0));
        label_tempsTotal->setText(QApplication::translate("MainWindow", "Temps Total", 0));
#ifndef QT_NO_TOOLTIP
        pushButton_supprimerPlaylist->setToolTip(QApplication::translate("MainWindow", "Supprimer la playlist", 0));
#endif // QT_NO_TOOLTIP
        pushButton_supprimerPlaylist->setText(QApplication::translate("MainWindow", "-", 0));
#ifndef QT_NO_TOOLTIP
        pushButton_AjouterDossier->setToolTip(QApplication::translate("MainWindow", "Ajouter un dossier", 0));
#endif // QT_NO_TOOLTIP
        pushButton_AjouterDossier->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_Pause->setToolTip(QApplication::translate("MainWindow", "Pause", 0));
#endif // QT_NO_TOOLTIP
        pushButton_Pause->setText(QString());
        checkBox_Playlist->setText(QApplication::translate("MainWindow", "Playlist ", 0));
#ifndef QT_NO_TOOLTIP
        pushButton_Parametres->setToolTip(QApplication::translate("MainWindow", "Param\303\250tres", 0));
#endif // QT_NO_TOOLTIP
        pushButton_Parametres->setText(QApplication::translate("MainWindow", "Param\303\250tres", 0));
        groupBox_Parametres->setTitle(QApplication::translate("MainWindow", "Param\303\250tres", 0));
        label_Opacite->setText(QApplication::translate("MainWindow", "Opacit\303\251 :", 0));
        label_Output->setText(QApplication::translate("MainWindow", "Sortie:", 0));
#ifndef QT_NO_TOOLTIP
        pushButton_ActualiserOutput->setToolTip(QApplication::translate("MainWindow", "Actualiser", 0));
#endif // QT_NO_TOOLTIP
        pushButton_ActualiserOutput->setText(QString());
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget_PistesPlaylist->horizontalHeaderItem(0);
        ___qtablewidgetitem15->setText(QApplication::translate("MainWindow", "Nom", 0));
#ifndef QT_NO_TOOLTIP
        pushButton_Exporter->setToolTip(QApplication::translate("MainWindow", "Exporter", 0));
#endif // QT_NO_TOOLTIP
        pushButton_Exporter->setText(QApplication::translate("MainWindow", "Exporter", 0));
#ifndef QT_NO_TOOLTIP
        pushButton_Importer->setToolTip(QApplication::translate("MainWindow", "Importer", 0));
#endif // QT_NO_TOOLTIP
        pushButton_Importer->setText(QApplication::translate("MainWindow", "Importer", 0));
#ifndef QT_NO_TOOLTIP
        pushButton_volume->setToolTip(QApplication::translate("MainWindow", "Volume", 0));
#endif // QT_NO_TOOLTIP
        pushButton_volume->setText(QApplication::translate("MainWindow", "Volume", 0));
        groupBox_volume->setTitle(QApplication::translate("MainWindow", "Volume", 0));
#ifndef QT_NO_TOOLTIP
        pushButton_Muet->setToolTip(QApplication::translate("MainWindow", "Muet", 0));
#endif // QT_NO_TOOLTIP
        pushButton_Muet->setText(QString());
        label_tempsActuelPlaylist->setText(QApplication::translate("MainWindow", "0:00:0", 0));
        label_tempsTotalPlaylist->setText(QApplication::translate("MainWindow", "0:00:0", 0));
        label_titrePistePlaylist->setText(QApplication::translate("MainWindow", "Piste", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
