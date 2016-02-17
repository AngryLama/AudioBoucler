#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Création message information
    informations=new QMessageBox;

    //Création barre de progression
    barreProgression = new QWidget(this);
    barreProgression->setGeometry(10,60,1,280);
    barreProgression->setStyleSheet("background-color: black;");
    barreProgression->hide();

    //Initialisation progressBar_Analyse
    progressBar_Analyse = new QProgressBar(this);
    progressBar_Analyse->setTextVisible(false);
    progressBar_Analyse->setMaximum(1000);
    progressBar_Analyse->raise();
    progressBar_Analyse->hide();

    //GroupBox
    ui->groupBox_Parametres->hide();
    ui->groupBox_volume->hide();

    //Initialisation tableau informations
    ui->tableWidget_Info->horizontalHeader()->setSectionsClickable(false);
    ui->tableWidget_Info->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget_Info->verticalHeader()->hide();
    ui->tableWidget_Info->insertRow(0);
    for(int x=0;x<4;x++){
        ui->tableWidget_Info->setItem(0,x,new QTableWidgetItem);
        ui->tableWidget_Info->item(0,x)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_Info->item(0,x)->setTextColor(Qt::black);
    }

    //tableWidget Pistes
    ui->tableWidget_Pistes->horizontalHeader()->setSectionsClickable(false);
    ui->tableWidget_Pistes->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget_Pistes->verticalHeader()->hide();
    ui->tableWidget_Pistes->setColumnWidth(1,100);
    ui->tableWidget_Pistes->setColumnWidth(2,100);
    ui->tableWidget_Pistes->setColumnWidth(3,30);
    ui->tableWidget_Pistes->horizontalHeaderItem(3)->setText("");
    ui->tableWidget_Pistes->horizontalHeaderItem(3)->setIcon(*(new QIcon(":/Icon/Boucle.png")));

    //tableWidget Pistes Playlist
    ui->tableWidget_PistesPlaylist->horizontalHeader()->setSectionsClickable(false);
    ui->tableWidget_PistesPlaylist->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget_PistesPlaylist->verticalHeader()->hide();

    //tableWidget Touches
    ui->tableWidget_Touches->horizontalHeader()->setSectionsClickable(false);
    ui->tableWidget_Touches->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget_Touches->verticalHeader()->hide();
    ui->tableWidget_Touches->setColumnWidth(0,80);
    ui->tableWidget_Touches->setColumnWidth(1,40);
    ui->tableWidget_Touches->setColumnWidth(3,80);

    //tableWidget Playlist
    ui->tableWidget_Playlist->horizontalHeader()->setSectionsClickable(false);
    ui->tableWidget_Playlist->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget_Playlist->verticalHeader()->hide();
    ui->tableWidget_Playlist->setColumnWidth(0,100);
    ui->tableWidget_Playlist->setColumnWidth(2,30);
    ui->tableWidget_Playlist->horizontalHeaderItem(2)->setText("");
    ui->tableWidget_Playlist->horizontalHeaderItem(2)->setIcon(*(new QIcon(":/Icon/Boucle.png")));

    //Masquer les labels de temps
    masquerLabelTemps(false);

    //Initialisation Timer
    refresh = new QTimer;
    connect(refresh,SIGNAL(timeout()),this,SLOT(on_finTimerRefresh()));
    verifTemps = new QTimer;
    connect(verifTemps,SIGNAL(timeout()),this,SLOT(on_finVerifTemps()));

    //Création des widgets
    effectG = new QGraphicsOpacityEffect(ui->widget_G);
    effectD = new QGraphicsOpacityEffect(ui->widget_D);
    modifierOpacite(0.75);

    //Initialisation de la liste des outputs
    on_pushButton_ActualiserOutput_clicked();

    //Initialisation du volume
    QFile confFile(QDir::currentPath()+"/config.ini");
    int volValue=50;
    if(confFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        char import[1024];
        confFile.readLine(import,sizeof(import));
        volValue=charToQString(import).toInt();
    }
    ui->horizontalSlider_Volume->setValue(volValue);

    //Initialisation de l'état playlist
    on_checkBox_Playlist_clicked(false);

    //Initialisation du répertoire par défaut
    lastRepertoire="/";

    //Initialisation des variables
    enLecture=-1;
    enLectureP=-1;
}

MainWindow::~MainWindow()
{
    delete informations;
    delete progressBar_Analyse;
    delete refresh;
    delete verifTemps;
    delete effectG;
    delete effectD;
    delete barreProgression;
    qDeleteAll(pistes);
    pistes.clear();
    qDeleteAll(bouclagePiste);
    bouclagePiste.clear();
    qDeleteAll(bouclagePlaylist);
    bouclagePlaylist.clear();
    delete ui;
}

void MainWindow::adapterInterface(int w,int h){
    w-=20;
    h-=20;
    //Définition du coeeficient de zoom
    float coeff=1;
    short decal=0;
    if(w>=1600 && h>=900){
        coeff=1.2;
        decal=8;
    }

    //ProgressBar
    progressBar_Analyse->setGeometry(10,60,w,280);

    //Sliders
    ui->horizontalSlider_debut->setGeometry(10,350,w,20);
    ui->horizontalSlider_fin->setGeometry(10,370,w,20);

    //Label titre
    ui->label_Titre->setGeometry(0,0,w,60);

    //Affichage temps Playlist
    ui->label_tempsActuelPlaylist->setGeometry(0,ui->label_Titre->y()+ui->label_Titre->height()+10,w/2-20,200);
    ui->line_tempsPlaylist->setGeometry(w/2-7,ui->label_tempsActuelPlaylist->y(),15,ui->label_tempsActuelPlaylist->height());
    ui->label_tempsTotalPlaylist->setGeometry(w/2+20,ui->label_tempsActuelPlaylist->y(),w-(w/2+20),ui->label_tempsActuelPlaylist->height());
    ui->label_titrePistePlaylist->setGeometry(0,ui->label_tempsActuelPlaylist->y()+ui->label_tempsActuelPlaylist->height(),w,60);
    ui->progressBar_Playlist->setGeometry(w/8,ui->label_titrePistePlaylist->y()+ui->label_titrePistePlaylist->height(),w-(w/8)*2,30);

    //Boutons
    ui->pushButton_Quitter->setGeometry(w-100*coeff,h-35*coeff,110*coeff,40*coeff);
    ui->pushButton_Precedent->setGeometry(330,ui->pushButton_Quitter->y(),40*coeff,40*coeff);
    ui->pushButton_Lecture->setGeometry(ui->pushButton_Precedent->x()+(40*coeff)+decal,ui->pushButton_Precedent->y(),40*coeff,40*coeff);
    ui->pushButton_Pause->setGeometry(ui->pushButton_Lecture->x()+(40*coeff)+decal,ui->pushButton_Precedent->y(),40*coeff,40*coeff);
    ui->pushButton_Stop->setGeometry(ui->pushButton_Pause->x()+(40*coeff)+decal,ui->pushButton_Precedent->y(),40*coeff,40*coeff);
    ui->pushButton_Suivant->setGeometry(ui->pushButton_Stop->x()+(40*coeff)+decal,ui->pushButton_Precedent->y(),40*coeff,40*coeff);

    //GroupBox Informations
    ui->groupBox_Informations->setGeometry((w/10)*6,415,w-((w/10)*6),ui->pushButton_Precedent->y()-420);
    ui->tableWidget_Touches->setGeometry(10,75,ui->groupBox_Informations->width()-25,ui->groupBox_Informations->height()-80);
    ui->tableWidget_Info->setGeometry(10,20,ui->groupBox_Informations->width()-25,60);

    //Playlist
    ui->tableWidget_Playlist->setGeometry(20,425,200,ui->pushButton_Precedent->y()-430);
    ui->pushButton_nouvellePlaylist->setGeometry(20,ui->tableWidget_Playlist->y()+ui->tableWidget_Playlist->height(),80,20*coeff);
    ui->pushButton_supprimerPlaylist->setGeometry(100,ui->tableWidget_Playlist->y()+ui->tableWidget_Playlist->height(),80,20*coeff);

    ui->pushButton_Ajouter->setGeometry(15,425,40*coeff,40*coeff);
    ui->pushButton_AjouterDossier->setGeometry(15,465+decal,40*coeff,40*coeff);
    ui->pushButton_Monter->setGeometry(15,505+(decal*2),40*coeff,40*coeff);
    ui->pushButton_Descendre->setGeometry(15,545+(decal*3),40*coeff,40*coeff);
    ui->pushButton_Supprimer->setGeometry(15,585+(decal*4),40*coeff,40*coeff);

    //Pistes + Up/Down
    ui->tableWidget_Pistes->setGeometry(ui->pushButton_Ajouter->x()+ui->pushButton_Ajouter->width()+5,425,(w-ui->groupBox_Informations->x())+30,ui->pushButton_Precedent->y()-430);
    ui->pushButton_Ajouter->setGeometry(ui->tableWidget_Playlist->x()+ui->tableWidget_Playlist->width()+15,425,40*coeff,40*coeff);
    ui->tableWidget_PistesPlaylist->setGeometry(ui->pushButton_Ajouter->x()+ui->pushButton_Ajouter->width(),425,w-ui->groupBox_Informations->x()-25,ui->pushButton_Precedent->y()-430);
    ui->pushButton_Ajouter->setGeometry(15,425,40*coeff,40*coeff);

    //Informations temps
    int infoTempsX=ui->tableWidget_Pistes->x()+ui->tableWidget_Pistes->width()+10;
    int infoTempsW=ui->groupBox_Informations->x()-infoTempsX-10;
    ui->label_tempsActuel->setGeometry(infoTempsX,ui->tableWidget_Pistes->y(),infoTempsW,30);
    ui->lineEdit_tempsActuel->setGeometry(infoTempsX,ui->label_tempsActuel->y()+30,infoTempsW,30);
    ui->label_cursDebut->setGeometry(infoTempsX,ui->lineEdit_tempsActuel->y()+30,infoTempsW,30);
    ui->lineEdit_cursDebut->setGeometry(infoTempsX,ui->label_cursDebut->y()+30,infoTempsW,30);
    ui->label_cursFin->setGeometry(infoTempsX,ui->lineEdit_cursDebut->y()+30,infoTempsW,30);
    ui->lineEdit_cursFin->setGeometry(infoTempsX,ui->label_cursFin->y()+30,infoTempsW,30);
    ui->label_tempsTotal->setGeometry(infoTempsX,ui->lineEdit_cursFin->y()+30,infoTempsW,30);
    ui->lineEdit_tempsTotal->setGeometry(infoTempsX,ui->label_tempsTotal->y()+30,infoTempsW,30);

    //Paramètres
    ui->pushButton_Parametres->setGeometry(ui->pushButton_Quitter->x()-120*coeff,ui->pushButton_Quitter->y(),110*coeff,40*coeff);
    ui->groupBox_Parametres->setGeometry(ui->pushButton_Parametres->x()-150,ui->pushButton_Parametres->y()-100,w-ui->pushButton_Parametres->x()+140,100);
    ui->label_Opacite->setGeometry(10,ui->groupBox_Parametres->height()-80,60*coeff,20);
    ui->horizontalSlider_Opacite->setGeometry(ui->label_Opacite->width()+10,ui->label_Opacite->y(),ui->groupBox_Parametres->width()-90,20);
    ui->label_Output->setGeometry(10,ui->groupBox_Parametres->height()-50,50,20*coeff);
    ui->comboBox_Output->setGeometry(70,ui->label_Output->y(),ui->groupBox_Parametres->width()-100,20*coeff);
    ui->pushButton_ActualiserOutput->setGeometry(ui->comboBox_Output->x()+ui->comboBox_Output->width(),ui->label_Output->y(),ui->comboBox_Output->height(),ui->comboBox_Output->height());

    //Volume
    ui->pushButton_volume->setGeometry(ui->pushButton_Parametres->x()-130*coeff,ui->pushButton_Quitter->y(),120*coeff,40*coeff);
    ui->groupBox_volume->setGeometry(ui->pushButton_volume->x()-150,ui->pushButton_volume->y()-75,w-ui->pushButton_volume->x()+100,75);
    ui->horizontalSlider_Volume->setGeometry(5,30,ui->groupBox_volume->width()-(35*coeff)-20,30);
    ui->pushButton_Muet->setGeometry(ui->horizontalSlider_Volume->x()+ui->horizontalSlider_Volume->width()+5,ui->horizontalSlider_Volume->y(),35*coeff,35*coeff);

    //Import/Export
    ui->pushButton_Importer->setGeometry(ui->pushButton_volume->x()-110*coeff,ui->pushButton_Quitter->y(),100*coeff,40*coeff);
    ui->pushButton_Exporter->setGeometry(ui->pushButton_Importer->x()-110*coeff,ui->pushButton_Quitter->y(),100*coeff,40*coeff);

    //Colonnes TableWidgets
    ui->tableWidget_Pistes->setColumnWidth(0,ui->tableWidget_Pistes->width()-250);
    ui->tableWidget_PistesPlaylist->setColumnWidth(0,ui->tableWidget_PistesPlaylist->width());
    ui->tableWidget_Touches->setColumnWidth(2,ui->tableWidget_Touches->width()-205);
    ui->tableWidget_Playlist->setColumnWidth(1,ui->tableWidget_Playlist->width()-150);
    ui->tableWidget_Info->setColumnWidth(0,ui->tableWidget_Info->width()/4);
    ui->tableWidget_Info->setColumnWidth(1,ui->tableWidget_Info->width()/4);
    ui->tableWidget_Info->setColumnWidth(2,ui->tableWidget_Info->width()/4);
    ui->tableWidget_Info->setColumnWidth(3,ui->tableWidget_Info->width()/4);

    on_checkBox_Playlist_clicked(ui->checkBox_Playlist->isChecked());
}

void MainWindow::creerLigne(QString type, int x)
{
    if(type=="p"){
        ui->tableWidget_Pistes->insertRow(x);
        ui->tableWidget_Pistes->setItem(x,0,new QTableWidgetItem);
        ui->tableWidget_Pistes->setItem(x,1,new QTableWidgetItem);
        ui->tableWidget_Pistes->setItem(x,2,new QTableWidgetItem);
        ui->tableWidget_Pistes->setCellWidget(x,3,bouclagePiste[x]);
        //Centrage
        ui->tableWidget_Pistes->item(x,1)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_Pistes->item(x,2)->setTextAlignment(Qt::AlignCenter);
        //Vérouillage
        ui->tableWidget_Pistes->item(x,0)->setFlags(ui->tableWidget_Pistes->item(x,0)->flags() ^ Qt::ItemIsEditable);
        ui->tableWidget_Pistes->item(x,2)->setFlags(ui->tableWidget_Pistes->item(x,2)->flags() ^ Qt::ItemIsEditable);
    }
    if(type=="pp"){
        ui->tableWidget_PistesPlaylist->insertRow(x);
        ui->tableWidget_PistesPlaylist->setItem(x,0,new QTableWidgetItem);
        ui->tableWidget_PistesPlaylist->item(x,0)->setFlags(ui->tableWidget_PistesPlaylist->item(x,0)->flags() ^ Qt::ItemIsEditable);
    }
    if(type=="pl"){
        ui->tableWidget_Playlist->insertRow(x);
        ui->tableWidget_Playlist->setItem(x,0,new QTableWidgetItem);
        ui->tableWidget_Playlist->setItem(x,1,new QTableWidgetItem);
        ui->tableWidget_Playlist->setCellWidget(x,2,bouclagePlaylist[x]);
        ui->tableWidget_Playlist->item(x,1)->setTextAlignment(Qt::AlignCenter);
    }
    if(type=="t"){
        ui->tableWidget_Touches->insertRow(x);
        ui->tableWidget_Touches->setItem(x,0,new QTableWidgetItem);
        ui->tableWidget_Touches->setItem(x,1,new QTableWidgetItem);
        ui->tableWidget_Touches->setItem(x,2,new QTableWidgetItem);
        ui->tableWidget_Touches->setItem(x,3,new QTableWidgetItem);
        //Centrage
        ui->tableWidget_Touches->item(x,0)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_Touches->item(x,1)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_Touches->item(x,3)->setTextAlignment(Qt::AlignCenter);
    }
}

void MainWindow::razInterface()
{
    if(ui->horizontalSlider_debut->isEnabled()){
        ui->horizontalSlider_debut->setEnabled(false);
        ui->horizontalSlider_fin->setEnabled(false);
    }
    ui->horizontalSlider_debut->setValue(ui->horizontalSlider_debut->minimum());
    ui->horizontalSlider_fin->setValue(ui->horizontalSlider_fin->maximum());
    barreProgression->setGeometry(10,60,1,280);
    ui->widget_G->setFixedWidth(0);
    ui->widget_D->setGeometry(width()-10,60,0,280);
    ui->label_tempsActuel->hide();
    ui->lineEdit_tempsActuel->setText("0:00:0");
    ui->lineEdit_tempsActuel->hide();
    ui->label_cursDebut->hide();
    ui->lineEdit_cursDebut->setText("0:00:0");
    ui->lineEdit_cursDebut->hide();
    ui->label_Titre->setText("Ajoutez une piste pour commencer");
    ui->label_cursFin->hide();
    ui->lineEdit_cursFin->setText("0:00:0");
    ui->lineEdit_cursFin->hide();
    ui->label_tempsTotal->hide();
    ui->lineEdit_tempsTotal->setText("0:00:0");
    ui->lineEdit_tempsTotal->hide();
    ui->tableWidget_Info->item(0,0)->setText("");
    ui->tableWidget_Info->item(0,1)->setText("");
    ui->tableWidget_Info->item(0,2)->setText("");
    ui->tableWidget_Info->item(0,3)->setText("");
}

void MainWindow::masquerLabelTemps(bool etat)
{
    if(etat){
        ui->label_tempsActuel->show();
        ui->lineEdit_tempsActuel->show();
        ui->label_cursDebut->show();
        ui->lineEdit_cursDebut->show();
        ui->label_cursFin->show();
        ui->lineEdit_cursFin->show();
        ui->label_tempsTotal->show();
        ui->lineEdit_tempsTotal->show();
    }else{
        ui->label_tempsActuel->hide();
        ui->lineEdit_tempsActuel->hide();
        ui->label_cursDebut->hide();
        ui->lineEdit_cursDebut->hide();
        ui->label_cursFin->hide();
        ui->lineEdit_cursFin->hide();
        ui->label_tempsTotal->hide();
        ui->lineEdit_tempsTotal->hide();
    }
}

void MainWindow::modifierOpacite(qreal value)
{
    effectG->setOpacity(value);
    ui->widget_G->setGraphicsEffect(effectG);
    effectD->setOpacity(value);
    ui->widget_D->setGraphicsEffect(effectD);
}

void MainWindow::actualiser()
{
    if(ui->checkBox_Playlist->isChecked()){
        actualiserPistesPlaylist();
        ui->label_Titre->setText(ui->tableWidget_Playlist->item(ui->tableWidget_Playlist->currentRow(),0)->text());
    }else{
        if(ui->tableWidget_Pistes->rowCount()>0){
            if(!ui->checkBox_Playlist->isChecked()){
                if(!ui->horizontalSlider_debut->isEnabled()){
                    ui->horizontalSlider_debut->setEnabled(true);
                    ui->horizontalSlider_fin->setEnabled(true);
                }
                ui->label_tempsActuel->show();
                ui->lineEdit_tempsActuel->show();
                ui->label_cursDebut->show();
                ui->lineEdit_cursDebut->show();
                ui->label_cursFin->show();
                ui->lineEdit_cursFin->show();
                ui->label_tempsTotal->show();
                ui->lineEdit_tempsTotal->show();
                barreProgression->show();
            }
        }else{
            razInterface();
        }
    }

    //Activation précédent suivant
    if(ui->checkBox_Playlist->isChecked())
        actualiserBoutonsPreSui(ui->tableWidget_PistesPlaylist);
    else actualiserBoutonsPreSui(ui->tableWidget_Pistes);

    ui->centralWidget->setFocus();
}

void MainWindow::actualiserPistesPlaylist(const int pos)
{
    //Suppression des lignes
    while(ui->tableWidget_PistesPlaylist->rowCount()!=0)
        ui->tableWidget_PistesPlaylist->removeRow(0);
    //Création du tableau
    for(int x=0;x<playlist[ui->tableWidget_Playlist->currentRow()].nbPistes();x++){
        creerLigne("pp",x);
        ui->tableWidget_PistesPlaylist->item(x,0)->setText(playlist[ui->tableWidget_Playlist->currentRow()].retourNomPiste(x));
    }
    ui->label_tempsTotalPlaylist->setText(msToQString(playlist[ui->tableWidget_Playlist->currentRow()].retourTempsTotal()));
    ui->tableWidget_PistesPlaylist->setCurrentCell(pos,0);
    //Mise à jour maximum progressBar
    qint64 temp=0;
    for(int x=0;x<playlist[ui->tableWidget_Playlist->currentRow()].nbPistes();x++)
        temp+=playlist[ui->tableWidget_Playlist->currentRow()].retourFinPiste(x);
    ui->progressBar_Playlist->setMaximum(temp);
    centralWidget()->setFocus();
}

void MainWindow::actualiserTouches()
{
    if(ui->checkBox_Playlist->isChecked())
        for(int x=0;x<ui->tableWidget_Playlist->rowCount();x++)
            ui->tableWidget_Playlist->item(x,1)->setText(playlist[x].retourTouche());

    while(ui->tableWidget_Touches->rowCount()!=0)
        ui->tableWidget_Touches->removeRow(0);

    for(int x=0;x<pistes.count();x++){
        if(pistes[x]->info.retourTouche()!="-"){
            creerLigne("t",ui->tableWidget_Touches->rowCount());
            ui->tableWidget_Touches->item(ui->tableWidget_Touches->rowCount()-1,0)->setText("Piste");
            ui->tableWidget_Touches->item(ui->tableWidget_Touches->rowCount()-1,1)->setText(QString::number(x+1));
            ui->tableWidget_Touches->item(ui->tableWidget_Touches->rowCount()-1,2)->setText(pistes[x]->info.retourNom());
            ui->tableWidget_Touches->item(ui->tableWidget_Touches->rowCount()-1,3)->setText(pistes[x]->info.retourTouche());
        }
    }
    for(int x=0;x<ui->tableWidget_Playlist->rowCount();x++){
        if(playlist[x].retourTouche()!="-"){
            creerLigne("t",ui->tableWidget_Touches->rowCount());
            ui->tableWidget_Touches->item(ui->tableWidget_Touches->rowCount()-1,0)->setText("Playlist");
            ui->tableWidget_Touches->item(ui->tableWidget_Touches->rowCount()-1,1)->setText(QString::number(x+1));
            ui->tableWidget_Touches->item(ui->tableWidget_Touches->rowCount()-1,2)->setText(ui->tableWidget_Playlist->item(x,0)->text());
            ui->tableWidget_Touches->item(ui->tableWidget_Touches->rowCount()-1,3)->setText(playlist[x].retourTouche());
        }
    }
}

void MainWindow::actualiserBoutonsPreSui(QTableWidget *tableau)
{
    bool verif;
    if(tableau->rowCount()>1)
        verif=true;
    else verif=false;
    ui->pushButton_Precedent->setEnabled(verif);
    ui->pushButton_Suivant->setEnabled(verif);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    event->accept();
    adapterInterface(event->size().width(),event->size().height());
    for(int x=0;x<pistes.count();x++){
        pistes[x]->setFixedWidth(event->size().width()-20);
        pistes[x]->update();
    }
    if(ui->checkBox_Playlist->isChecked()){

    }else{
        on_horizontalSlider_debut_valueChanged(ui->horizontalSlider_debut->value());
        on_horizontalSlider_fin_valueChanged(ui->horizontalSlider_fin->value());
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Space){
        if(ui->pushButton_Lecture->isEnabled())
            ui->pushButton_Lecture->click();
        else ui->pushButton_Stop->click();
    }

    if(event->key()==Qt::Key_0 && ui->pushButton_Stop->isEnabled())
        ui->pushButton_Stop->click();

    if(event->key()==Qt::Key_Up && ui->tableWidget_Pistes->currentRow()>0)
            ui->tableWidget_Pistes->setCurrentCell(ui->tableWidget_Pistes->currentRow()-1,0);

    if(event->key()==Qt::Key_Down && ui->tableWidget_Pistes->currentRow()<ui->tableWidget_Pistes->rowCount()-1)
            ui->tableWidget_Pistes->setCurrentCell(ui->tableWidget_Pistes->currentRow()+1,0);

    bool verif=false;
    int x=0;
    while(!verif && x<ui->tableWidget_Touches->rowCount()){
        if((unsigned)event->key()==QStringToKey(ui->tableWidget_Touches->item(x,3)->text()))
            verif=true;
        else x++;
    }
    if(verif){
        if(ui->tableWidget_Touches->item(x,0)->text()=="Piste"){
            if(ui->checkBox_Playlist->isChecked()){
                ui->checkBox_Playlist->click();
            }
            ui->tableWidget_Pistes->setCurrentCell(ui->tableWidget_Touches->item(x,1)->text().toInt()-1,0);
            on_pushButton_Lecture_clicked();
        }else{
            enLectureP=ui->tableWidget_Touches->item(x,1)->text().toInt()-1;
            enLecture=0;
            lecteur.lecture(playlist[enLectureP].retourCheminPiste(enLecture));
            ui->pushButton_Lecture->setEnabled(false);
            ui->pushButton_Pause->setEnabled(true);
            ui->pushButton_Stop->setEnabled(true);
            ui->centralWidget->setFocus();
            refresh->start(10);
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    int posP=ui->tableWidget_Pistes->currentRow();
    if(!ui->checkBox_Playlist->isChecked() && posP>-1
            && event->globalX()>=pistes[posP]->x()+pos().x() && event->globalX()<=pistes[posP]->x()+pistes[posP]->width()+pos().x()
            && event->globalY()>=pistes[posP]->y()+pos().y() && event->globalY()<=pistes[posP]->y()+pistes[posP]->height()+pos().y()){
        int large=event->globalX()-pos().x()-pistes[posP]->x()/*-5*/;
        qint64 value=(((float)large/(float)pistes[posP]->width())*pistes[posP]->info.retourFinPisteI());
        if(event->button() == Qt::LeftButton){
            ui->horizontalSlider_debut->setValue(value);
        } else ui->horizontalSlider_fin->setValue(value);
        ui->centralWidget->setFocus();
    }
}

void MainWindow::on_pushButton_Ajouter_clicked()
{
    QStringList retour=QFileDialog::getOpenFileNames(this,"Choisir un fichier audio",lastRepertoire,"Audio(*.mp3 *.wav *.aiff *.aif *.m4a *.flac *.ogg)");
    int y=0;
    for(int x=0;x<retour.length();x++){
        ImportPiste temp;
        temp.chemin=retour[x];
        if(ui->checkBox_Playlist->isChecked()){
            temp.pos=playlist[ui->tableWidget_Playlist->currentRow()].nbPistes()+y++;
            temp.isPlaylist=true;
            temp.posP=ui->tableWidget_Playlist->currentRow();
            listeImportPiste << temp;
        }else{
            temp.pos=pistes.length()+y++;
            listeImportPiste << temp;
        }
    }
    ajouterPiste();
}

void MainWindow::on_pushButton_ActualiserOutput_clicked()
{
    ui->comboBox_Output->clear();
    foreach(const QAudioDeviceInfo &deviceInfo, QAudioDeviceInfo::availableDevices(QAudio::AudioOutput))
        ui->comboBox_Output->addItem(deviceInfo.deviceName(),
                                       QVariant::fromValue(deviceInfo));
}

void MainWindow::on_pushButton_Muet_clicked()
{
    if(!lecteur.estMuet()){
        lecteur.muet(true);
        ui->pushButton_volume->setText("Volume : Muet");
        ui->pushButton_volume->setIcon(QIcon(":/Icon/Muet.png"));
        ui->pushButton_Muet->setIcon(QIcon(":/Icon/Muet.png"));
    }else{
        lecteur.muet(false);
        ui->pushButton_volume->setText("Volume : "+QString::number(ui->horizontalSlider_Volume->value())+"%");
        ui->pushButton_volume->setIcon(QIcon(":/Icon/Haut-parleur son.png"));
        ui->pushButton_Muet->setIcon(QIcon(":/Icon/Haut-parleur son.png"));
    }
}

void MainWindow::on_horizontalSlider_Volume_valueChanged(int value)
{
    if(lecteur.estMuet())
        on_pushButton_Muet_clicked();
    lecteur.changerVolume(value);
    ui->pushButton_volume->setText("Volume : "+QString::number(value)+"%");
}

void MainWindow::on_pushButton_Lecture_clicked()
{
    if(lecteur.enPause()){
        lecteur.reprendre();
    }else{
        if(ui->checkBox_Playlist->isChecked()){
            enLecture=ui->tableWidget_PistesPlaylist->currentRow();
            enLectureP=ui->tableWidget_Playlist->currentRow();
            lecteur.lecture(playlist[enLectureP].retourCheminPiste(enLecture));
        }else{
            enLecture=ui->tableWidget_Pistes->currentRow();
            enLectureP=-1;
            lecteur.lecture(pistes[enLecture]->info.retourChemin(),pistes[enLecture]->info.retourDebutI());
        }
    }
    ui->pushButton_Pause->setEnabled(true);
    ui->pushButton_Stop->setEnabled(true);
    ui->centralWidget->setFocus();
    ui->pushButton_Lecture->setEnabled(false);
    refresh->start(10);
}

void MainWindow::on_pushButton_Stop_clicked()
{
    lecteur.stop();
    ui->pushButton_Lecture->setEnabled(true);
    ui->pushButton_Pause->setEnabled(false);
    ui->pushButton_Stop->setEnabled(false);
    refresh->stop();
    enLectureP=-1;
    enLecture=-1;
    ui->centralWidget->setFocus();
}

void MainWindow::on_finTimerRefresh()
{
    if(ui->checkBox_Playlist->isChecked()){
        qint64 temp=0;
        for(int x=0;x<enLecture;x++)
            temp+=playlist[enLectureP].retourFinPiste(x);
        temp+=lecteur.tempsActuelI();
        ui->label_tempsActuelPlaylist->setText(msToQString(temp));
        ui->progressBar_Playlist->setValue(temp);
    }else{
        ui->lineEdit_tempsActuel->setText(lecteur.tempsActuelQ());
    }

    if(enLectureP==-1 && enLecture==ui->tableWidget_Pistes->currentRow()){
        int val=(lecteur.tempsActuelI()*(width()-20))/pistes[ui->tableWidget_Pistes->currentRow()]->info.retourFinPisteI();
        barreProgression->setGeometry(10+val,60,1,280);
    }
    if(enLectureP!=-1 && lecteur.tempsActuelI()>=playlist[enLectureP].retourFinPiste(enLecture)){
        if(enLecture+1<playlist[enLectureP].nbPistes()){
            ui->tableWidget_PistesPlaylist->setCurrentCell(enLecture+1,0);
            on_pushButton_Lecture_clicked();
        }else if(playlist[enLectureP].retourBouclage()){
            ui->tableWidget_PistesPlaylist->setCurrentCell(0,0);
            on_pushButton_Lecture_clicked();
        }else{
            on_pushButton_Stop_clicked();
        }
    }
    if(enLectureP==-1 && enLecture!=-1){
        if(lecteur.tempsActuelI()>=pistes[enLecture]->info.retourFinI()){
            if(pistes[enLecture]->info.retourBouclage())
                lecteur.lecture(pistes[enLecture]->info.retourChemin(),pistes[enLecture]->info.retourDebutI());
            else on_pushButton_Stop_clicked();
        }
    }
}

void MainWindow::on_horizontalSlider_debut_valueChanged(int value)
{
    if(ui->tableWidget_Pistes->rowCount()>0){
        int valeurFin=ui->horizontalSlider_fin->value();
        if(value>valeurFin)
            ui->horizontalSlider_debut->setValue(valeurFin);
        else{
            int valG=(value*(pistes[ui->tableWidget_Pistes->currentRow()]->width()))/pistes[ui->tableWidget_Pistes->currentRow()]->info.retourFinPisteI();
            ui->widget_G->setFixedWidth(valG);
            ui->lineEdit_cursDebut->setText(msToQString(value));
            pistes[ui->tableWidget_Pistes->currentRow()]->info.changerDebut(value);
        }
        ui->tableWidget_Pistes->item(ui->tableWidget_Pistes->currentRow(),2)->setText(msToQString(pistes[ui->tableWidget_Pistes->currentRow()]->info.retourFinI()-pistes[ui->tableWidget_Pistes->currentRow()]->info.retourDebutI()));
    }
}

void MainWindow::on_horizontalSlider_fin_valueChanged(int value)
{
    if(ui->tableWidget_Pistes->rowCount()>0){
        int valeurDebut=ui->horizontalSlider_debut->value();
        if(value<valeurDebut)
            ui->horizontalSlider_fin->setValue(valeurDebut);
        else{
            int valD=(value*(pistes[ui->tableWidget_Pistes->currentRow()]->width()))/pistes[ui->tableWidget_Pistes->currentRow()]->info.retourFinPisteI();
            ui->widget_D->setGeometry(valD+10,60,(pistes[ui->tableWidget_Pistes->currentRow()]->width())-valD,280);
            ui->lineEdit_cursFin->setText(msToQString(value));
            pistes[ui->tableWidget_Pistes->currentRow()]->info.changerFin(value);
        }
        ui->tableWidget_Pistes->item(ui->tableWidget_Pistes->currentRow(),2)->setText(msToQString(pistes[ui->tableWidget_Pistes->currentRow()]->info.retourFinI()-pistes[ui->tableWidget_Pistes->currentRow()]->info.retourDebutI()));
    }
}

void MainWindow::on_horizontalSlider_Opacite_valueChanged(int value)
{
    modifierOpacite((qreal)value/100);
}

void MainWindow::on_checkBox_Playlist_clicked(bool checked)
{
    //Définition du coeeficient de zoom
    float coeff=1;
    short decal=0;
    if(width()>=1600 && height()>=900){
        coeff=1.2;
        decal=8;
    }
    if(lecteur.enLecture())
        on_pushButton_Stop_clicked();
    if(!ui->tableWidget_Playlist->rowCount())
        on_pushButton_nouvellePlaylist_clicked();
    if(checked){
        if(pistes.count()>0)
            pistes[ui->tableWidget_Pistes->currentRow()]->hide();
        ui->tableWidget_Playlist->show();
        ui->tableWidget_Pistes->hide();
        ui->tableWidget_PistesPlaylist->show();
        ui->pushButton_nouvellePlaylist->show();
        ui->pushButton_supprimerPlaylist->show();
        ui->label_tempsActuel->hide();
        ui->lineEdit_tempsActuel->hide();
        ui->label_cursDebut->hide();
        ui->lineEdit_cursDebut->hide();
        ui->label_cursFin->hide();
        ui->lineEdit_cursFin->hide();
        ui->label_tempsTotal->hide();
        ui->lineEdit_tempsTotal->hide();
        ui->horizontalSlider_debut->hide();
        ui->horizontalSlider_fin->hide();
        ui->widget_G->hide();
        ui->widget_D->hide();
        barreProgression->hide();
        ui->label_tempsActuelPlaylist->show();
        ui->line_tempsPlaylist->show();
        ui->label_tempsTotalPlaylist->show();
        //Décalage des boutons
        ui->pushButton_Ajouter->setGeometry(ui->tableWidget_Playlist->x()+ui->tableWidget_Playlist->width()+5,425,40*coeff,40*coeff);
        ui->pushButton_AjouterDossier->setGeometry(ui->tableWidget_Playlist->x()+ui->tableWidget_Playlist->width()+5,465+decal,40*coeff,40*coeff);
        ui->pushButton_Monter->setGeometry(ui->tableWidget_Playlist->x()+ui->tableWidget_Playlist->width()+5,505+(decal*2),40*coeff,40*coeff);
        ui->pushButton_Descendre->setGeometry(ui->tableWidget_Playlist->x()+ui->tableWidget_Playlist->width()+5,545+(decal*3),40*coeff,40*coeff);
        ui->pushButton_Supprimer->setGeometry(ui->tableWidget_Playlist->x()+ui->tableWidget_Playlist->width()+5,585+(decal*4),40*coeff,40*coeff);
        ui->label_Titre->setText(ui->tableWidget_Playlist->item(ui->tableWidget_Playlist->currentRow(),0)->text());
        actualiserPistesPlaylist(ui->tableWidget_Playlist->currentRow());
        if(ui->tableWidget_PistesPlaylist->currentRow()>-1){
            ui->label_titrePistePlaylist->show();
            ui->label_titrePistePlaylist->setText(ui->tableWidget_PistesPlaylist->currentItem()->text());
            ui->progressBar_Playlist->show();
        }else{
            ui->label_titrePistePlaylist->hide();
            ui->progressBar_Playlist->hide();
        }
    }else{
        if(pistes.count()!=0)
            pistes[ui->tableWidget_Pistes->currentRow()]->show();
        ui->tableWidget_Playlist->hide();
        ui->tableWidget_Pistes->show();
        ui->tableWidget_PistesPlaylist->hide();
        ui->pushButton_nouvellePlaylist->hide();
        ui->pushButton_supprimerPlaylist->hide();
        if(ui->tableWidget_Pistes->currentRow()>-1){
            ui->label_tempsActuel->show();
            ui->lineEdit_tempsActuel->show();
            ui->label_cursDebut->show();
            ui->lineEdit_cursDebut->show();
            ui->label_cursFin->show();
            ui->lineEdit_cursFin->show();
            ui->label_tempsTotal->show();
            ui->lineEdit_tempsTotal->show();
        }
        ui->horizontalSlider_debut->show();
        ui->horizontalSlider_fin->show();
        ui->widget_G->show();
        ui->widget_D->show();
        barreProgression->show();
        ui->label_tempsActuelPlaylist->hide();
        ui->line_tempsPlaylist->hide();
        ui->label_tempsTotalPlaylist->hide();
        ui->label_titrePistePlaylist->hide();
        ui->progressBar_Playlist->hide();
        //Décalage des boutons
        ui->pushButton_Ajouter->setGeometry(15,425,40*coeff,40*coeff);
        ui->pushButton_AjouterDossier->setGeometry(15,465+decal,40*coeff,40*coeff);
        ui->pushButton_Monter->setGeometry(15,505+(decal*2),40*coeff,40*coeff);
        ui->pushButton_Descendre->setGeometry(15,545+(decal*3),40*coeff,40*coeff);
        ui->pushButton_Supprimer->setGeometry(15,585+(decal*4),40*coeff,40*coeff);
        if(ui->tableWidget_Pistes->rowCount()>0)
            ui->label_Titre->setText(ui->tableWidget_Pistes->item(ui->tableWidget_Pistes->currentRow(),0)->text());
        else ui->label_Titre->setText("Ajoutez une piste pour commencer");
    }
}

void MainWindow::on_pushButton_nouvellePlaylist_clicked()
{
    int x=ui->tableWidget_Playlist->rowCount();
    playlist<<Playlist("Playlist "+QString::number(x+1));
    bouclagePlaylist<<new QCheckBox;
    bouclagePlaylist.last()->setObjectName(QString::number(x));
    connect(bouclagePlaylist.last(),SIGNAL(clicked(bool)),this,SLOT(on_etatBouclagePlaylist(bool)));
    creerLigne("pl",x);
    ui->tableWidget_Playlist->item(x,0)->setText(playlist[x].retourNom());
    ui->tableWidget_Playlist->item(x,1)->setText(playlist[x].retourTouche());
    ui->tableWidget_Playlist->setCurrentCell(x,0);
    if(ui->tableWidget_Playlist->rowCount()<=1)
        ui->pushButton_supprimerPlaylist->setEnabled(false);
    else ui->pushButton_supprimerPlaylist->setEnabled(true);
    centralWidget()->setFocus();
}

void MainWindow::on_pushButton_Supprimer_clicked()
{
    if(lecteur.enLecture())
        on_pushButton_Stop_clicked();
    int nbSuppr;
    if(ui->checkBox_Playlist->isChecked()){
        nbSuppr=ui->tableWidget_PistesPlaylist->currentRow();
        playlist[ui->tableWidget_Playlist->currentRow()].supprimerPiste(nbSuppr);
    }else{
        nbSuppr=ui->tableWidget_Pistes->currentRow();
        ui->tableWidget_Pistes->removeRow(nbSuppr);
        pistes[nbSuppr]->hide();
        pistes.removeAt(nbSuppr);
        bouclagePiste.removeAt(nbSuppr);
    }
    actualiser();
    actualiserTouches();
    if(ui->checkBox_Playlist->isChecked()){
        if(ui->tableWidget_PistesPlaylist->rowCount()!=0){
            if(ui->tableWidget_PistesPlaylist->rowCount()==nbSuppr)
                ui->tableWidget_PistesPlaylist->setCurrentCell(nbSuppr-1,0);
            else ui->tableWidget_PistesPlaylist->setCurrentCell(nbSuppr,0);
        }
    }else{
        if(ui->tableWidget_Pistes->rowCount()!=0){
            if(ui->tableWidget_Pistes->rowCount()==nbSuppr)
                ui->tableWidget_Pistes->setCurrentCell(nbSuppr-1,0);
            else ui->tableWidget_Pistes->setCurrentCell(nbSuppr,0);
        }
    }
}

void MainWindow::on_pushButton_Precedent_clicked()
{
    if(ui->checkBox_Playlist->isChecked()){
        if(ui->tableWidget_PistesPlaylist->currentRow()==0)
            ui->tableWidget_PistesPlaylist->setCurrentCell(ui->tableWidget_PistesPlaylist->rowCount()-1,0);
        else ui->tableWidget_PistesPlaylist->setCurrentCell(ui->tableWidget_PistesPlaylist->currentRow()-1,0);
    }else{
        if(ui->tableWidget_Pistes->currentRow()==0)
            ui->tableWidget_Pistes->setCurrentCell(ui->tableWidget_Pistes->rowCount()-1,0);
        else ui->tableWidget_Pistes->setCurrentCell(ui->tableWidget_Pistes->currentRow()-1,0);
    }
}

void MainWindow::on_pushButton_Suivant_clicked()
{
    if(ui->checkBox_Playlist->isChecked()){
        if(ui->tableWidget_PistesPlaylist->currentRow()==ui->tableWidget_PistesPlaylist->rowCount()-1)
            ui->tableWidget_PistesPlaylist->setCurrentCell(0,0);
        else ui->tableWidget_PistesPlaylist->setCurrentCell(ui->tableWidget_PistesPlaylist->currentRow()+1,0);
    }else{
        if(ui->tableWidget_Pistes->currentRow()==ui->tableWidget_Pistes->rowCount()-1)
            ui->tableWidget_Pistes->setCurrentCell(0,0);
        else ui->tableWidget_Pistes->setCurrentCell(ui->tableWidget_Pistes->currentRow()+1,0);
    }
}

void MainWindow::on_pushButton_supprimerPlaylist_clicked()
{
    int pos=ui->tableWidget_Playlist->currentRow();
    playlist.removeAt(pos);
    bouclagePlaylist.removeAt(pos);
    ui->tableWidget_Playlist->removeRow(pos);
    if(pos<1)
        ui->tableWidget_Playlist->setCurrentCell(pos,0);
    else ui->tableWidget_Playlist->setCurrentCell(pos-1,0);
    if(ui->tableWidget_Playlist->rowCount()<=1)
        ui->pushButton_supprimerPlaylist->setEnabled(false);
    else ui->pushButton_supprimerPlaylist->setEnabled(true);
    centralWidget()->setFocus();
}

void MainWindow::on_pushButton_Monter_clicked()
{
    if(ui->checkBox_Playlist->isChecked()){
        int posPiste=ui->tableWidget_PistesPlaylist->currentRow();
        playlist[ui->tableWidget_Playlist->currentRow()].deplacerPiste(posPiste,posPiste-1);
        actualiserPistesPlaylist(posPiste-1);
    }else{

    }
}

void MainWindow::on_pushButton_Descendre_clicked()
{
    if(ui->checkBox_Playlist->isChecked()){
        int posPiste=ui->tableWidget_PistesPlaylist->currentRow();
        playlist[ui->tableWidget_Playlist->currentRow()].deplacerPiste(posPiste,posPiste+1);
        actualiserPistesPlaylist(posPiste+1);
    }else{

    }
}

void MainWindow::on_comboBox_Output_currentIndexChanged(const QString &arg1)
{
    lecteur.changerOutput(arg1);
}

void MainWindow::on_pushButton_AjouterDossier_clicked()
{
    QString source = QFileDialog::getExistingDirectory(this, tr("Choisir un dossier"),
                                                     "/home",
                                                     QFileDialog::ShowDirsOnly
                                                     | QFileDialog::DontResolveSymlinks);
    if(source.length()>3)
        source+="/";

    QDirIterator *recherche;
    QStringList filtre;
    filtre << "*.mp3" << "*.wav" << "*.aiff" << "*.aif" << "*.m4a" << "*.flac" << "*.ogg";

    //if(ui->checkBox_SousDossiers->checkState())
        //recherche=new QDirIterator(source,filtre,QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
    /*else */recherche=new QDirIterator(source,filtre,QDir::Files | QDir::NoSymLinks);

    int x=0;
    while(recherche->hasNext()){
        ImportPiste temp;
        temp.chemin=recherche->next();
        if(ui->checkBox_Playlist->isChecked()){
            temp.pos=playlist[ui->tableWidget_Playlist->currentRow()].nbPistes()+x++;
            temp.isPlaylist=true;
            temp.posP=ui->tableWidget_Playlist->currentRow();
            listeImportPiste << temp;
        }else{
            temp.pos=pistes.length()+x++;
            listeImportPiste << temp;
        }
    }
    delete recherche;
    ajouterPiste();
}

void MainWindow::on_tableWidget_Pistes_cellDoubleClicked(int row, int column)
{
    if(ui->checkBox_Playlist->isChecked()){
        on_pushButton_Lecture_clicked();
    }else{
        if(column==0 || column==2)
            ui->tableWidget_Pistes->editItem(ui->tableWidget_Pistes->item(row,1));
    }
}

void MainWindow::on_tableWidget_Pistes_currentCellChanged(int currentRow, int currentColumn, int previousRow/*, int previousColumn*/)
{
    if(currentRow>-1 && currentColumn>-1){
        //Modification des boutons
        ui->pushButton_Lecture->setEnabled(true);
        if(currentRow==0)
            ui->pushButton_Monter->setEnabled(false);
        else ui->pushButton_Monter->setEnabled(true);
        if(currentRow+1==ui->tableWidget_Pistes->rowCount())
            ui->pushButton_Descendre->setEnabled(false);
        else ui->pushButton_Descendre->setEnabled(true);
        ui->pushButton_Supprimer->setEnabled(true);

        //Affichage du spectre
        if(previousRow>-1)
            pistes[previousRow]->hide();
        pistes[currentRow]->show();

        //Modification de l'affichage
        ui->lineEdit_tempsActuel->setText("0:00:0");
        ui->label_Titre->setText(ui->tableWidget_Pistes->item(currentRow,0)->text());
        ui->lineEdit_cursDebut->setText(pistes[currentRow]->info.retourDebutQ());
        ui->lineEdit_cursFin->setText(pistes[currentRow]->info.retourFinQ());
        ui->lineEdit_tempsTotal->setText(pistes[currentRow]->info.retourFinPisteQ());

        //Modification des pistes
        qint64 debut=pistes[currentRow]->info.retourDebutI();
        qint64 fin=pistes[currentRow]->info.retourFinI();
        qint64 finPiste=pistes[currentRow]->info.retourFinPisteI();
        int tempLecture=enLecture;
        enLecture=-1;
        ui->horizontalSlider_debut->setMaximum(finPiste);
        ui->horizontalSlider_fin->setMaximum(finPiste);
        ui->horizontalSlider_debut->setValue(0);
        ui->horizontalSlider_fin->setValue(finPiste);
        ui->horizontalSlider_debut->setValue(debut);
        ui->horizontalSlider_fin->setValue(fin);
        enLecture=tempLecture;

        //Actualisation des informations
        ui->tableWidget_Info->item(0,0)->setText(pistes[currentRow]->info.retourExtension());
        ui->tableWidget_Info->item(0,1)->setText(pistes[currentRow]->info.retourFrequenceQ());
        ui->tableWidget_Info->item(0,2)->setText(pistes[currentRow]->info.retourEchantillonageQ());
        ui->tableWidget_Info->item(0,3)->setText(pistes[currentRow]->info.retourDebitQ());
        ui->centralWidget->setFocus();
    }else{
        ui->pushButton_Lecture->setEnabled(false);
        ui->pushButton_Supprimer->setEnabled(false);
    }
}

void MainWindow::on_tableWidget_Pistes_itemChanged(QTableWidgetItem *item)
{
    if(item->column()==1){
        if(item->text().length()>1)
            item->setText(item->text().left(1));
        if((item->text()==" " || item->text()=="0") && item->text()!="-"){
            item->setText("-");
        }
        if(item->text().length()==1 && item->text()!="-" && item->text()!=pistes[item->row()]->info.retourTouche()){
            bool verif=true;
            if(ui->tableWidget_Touches->rowCount()>0){
                int x=0;
                while(verif && x<ui->tableWidget_Touches->rowCount()){
                    if(item->text()==ui->tableWidget_Touches->item(x,3)->text() && x!=item->row())
                        verif=false;
                    else x++;
                }
            }
            if(verif){
                pistes[item->row()]->info.definirTouche(item->text());
            }else{
                informations->setText("Touche déjà utilisée");
                informations->exec();
                item->setText("-");
                pistes[item->row()]->info.definirTouche("-");
            }
        }
        actualiserTouches();
        ui->centralWidget->setFocus();
    }
}

void MainWindow::ajouterPiste()
{
    if(listeImportPiste.length()!=0 && listeImportPiste[0].chemin!=""){
        QFile test(listeImportPiste[0].chemin);
        if(test.exists()){
            int temp=listeImportPiste[0].chemin.lastIndexOf("/");
            lastRepertoire=listeImportPiste[0].chemin.left(temp);
            if(listeImportPiste[0].isPlaylist){
                playlist[listeImportPiste[0].posP].ajouterPiste(listeImportPiste[0].chemin);
            }else{
                pistes<<new zoneDessin(QRect(10,60,width()-20,280),this);
                pistes.last()->lower();
                pistes.last()->hide();
                pistes.last()->info.cheminPiste(listeImportPiste[0].chemin);
                progressBar_Analyse->show();
            }
            verifImport=0;
            saveMuet=lecteur.estMuet();
            lecteur.muet(true);
            lecteur.lecture(listeImportPiste[0].chemin);
            verifTemps->start(10);
        }else{
            QMessageBox message;
            message.setWindowTitle("Erreur de fichier");
            message.addButton("Rechercher",QMessageBox::AcceptRole);
            message.addButton("Ignorer",QMessageBox::RejectRole);
            message.setText("Fichier introuvable: "+listeImportPiste[0].chemin);

            if(message.exec()==QMessageBox::AcceptRole){
                listeImportPiste[0].chemin=QFileDialog::getOpenFileName(this,"Choisir un fichier audio",lastRepertoire,"Audio(*.mp3 *.wav *.aiff *.aif *.m4a *.flac *.ogg)");
            }else{
                listeImportPiste.removeFirst();
            }
            ajouterPiste();
        }
    }
}

void MainWindow::verifChamps(QString text, QLineEdit *lineEdit)
{
    if(text.right(1)==" ")
        lineEdit->setText(text.left(text.length()-1));
    else{
        text.remove(":");
        bool verif;
        text.toInt(&verif);
        if(!verif)
            lineEdit->setText(text.left(text.length()-1));
        else{
            QStringList temps=ui->lineEdit_tempsTotal->text().split(":");
            short decal=0;
            if(temps[0].toInt()<10)
                decal=1;
            if(text.length()>=(3-decal)){
                text.insert((2-decal),":");
                if(text.right(1).toInt()>5){
                    text=text.left(text.length()-1);
                    text+="5";
                }
            }
            if(text.length()>=(6-decal))
                text.insert((5-decal),":");
            if(text.length()>(7-decal)){
                text=text.left(text.length()-1);
                /*QStringList temps=text.split(":");
                if(temps[0])*/
                lineEdit->editingFinished();
            }
            lineEdit->setText(text);
        }
    }
}

void MainWindow::verifChampsFin(QString &text, QLineEdit *lineEdit)
{
    if(text.length()==1){
        text="0:0"+text+":0";
    }else if(text.length()==2){
        text="0:"+text+":0";
    }else if(text.length()==3){
        text=text+"0:0";
    }else if(text.length()==4 || (text.length()==5 && text.indexOf(":")==2)){
        text=text+":0";
    }
    lineEdit->setText(text);
}

void MainWindow::on_tableWidget_Playlist_itemChanged(QTableWidgetItem *item)
{
    if(item->column()==1){
        if(item->text().length()>1)
            item->setText(item->text().left(1));
        if((item->text()==" " || item->text()=="0") && item->text()!="-"){
            item->setText("-");
        }
        if(item->text().length()==1 && item->text()!="-" && item->text()!=playlist[item->row()].retourTouche()){
            bool verif=true;
            if(ui->tableWidget_Touches->rowCount()>0){
                int x=0;
                while(verif && x<ui->tableWidget_Touches->rowCount()){
                    if(item->text()==ui->tableWidget_Touches->item(x,3)->text() && x!=item->row())
                        verif=false;
                    else x++;
                }
            }
            if(verif){
                playlist[item->row()].definirTouche(item->text());
            }else{
                informations->setText("Touche déjà utilisée");
                informations->exec();
                item->setText("-");
                playlist[item->row()].definirTouche("-");
            }
        }
        actualiserTouches();
    }
    if(item->column()==0){
        if(ui->checkBox_Playlist->isChecked())
            ui->label_Titre->setText(item->text());
    }
}

void MainWindow::on_pushButton_Pause_clicked()
{
    refresh->stop();
    lecteur.pause();
    ui->pushButton_Pause->setEnabled(false);
    ui->pushButton_Lecture->setEnabled(true);
    ui->centralWidget->setFocus();
}

void MainWindow::on_tableWidget_Playlist_currentCellChanged(int currentRow, int currentColumn/*, int previousRow, int previousColumn*/)
{
    if(currentRow>-1){
        if(ui->tableWidget_Playlist->rowCount()<=1)
            ui->pushButton_supprimerPlaylist->setEnabled(false);
        else ui->pushButton_supprimerPlaylist->setEnabled(true);
        if(currentColumn==0){
            playlist[currentRow].definirNom(ui->tableWidget_Playlist->currentItem()->text());
            if(ui->checkBox_Playlist->isChecked())
                ui->label_Titre->setText(ui->tableWidget_Playlist->currentItem()->text());
        }
        actualiserPistesPlaylist();
    }
}

void MainWindow::on_etatBouclagePiste(bool etat)
{
    QCheckBox *ptrSource=(QCheckBox*)sender();
    pistes[ptrSource->objectName().toInt()]->info.definirBouclage(etat);
    centralWidget()->setFocus();
}

void MainWindow::on_pushButton_Parametres_clicked()
{
    if(ui->groupBox_Parametres->isVisible()){
        ui->groupBox_Parametres->hide();
    }else{
        if(ui->groupBox_volume->isVisible())
            ui->groupBox_volume->hide();
        ui->groupBox_Parametres->show();
    }
}

void MainWindow::on_tableWidget_Pistes_itemPressed(/*QTableWidgetItem *item*/)
{
    centralWidget()->setFocus();
}

void MainWindow::on_tableWidget_PistesPlaylist_currentCellChanged(int currentRow/*, int currentColumn, int previousRow, int previousColumn*/)
{
    if(currentRow>-1){
        //Mise à jour du titre
        ui->label_titrePistePlaylist->show();
        ui->label_titrePistePlaylist->setText(ui->tableWidget_PistesPlaylist->currentItem()->text());
        ui->progressBar_Playlist->show();

        //Modification des boutons
        ui->pushButton_Lecture->setEnabled(true);
        if(currentRow==0)
            ui->pushButton_Monter->setEnabled(false);
        else ui->pushButton_Monter->setEnabled(true);
        if(currentRow+1==ui->tableWidget_PistesPlaylist->rowCount())
            ui->pushButton_Descendre->setEnabled(false);
        else ui->pushButton_Descendre->setEnabled(true);
        ui->pushButton_Supprimer->setEnabled(true);

        //Mise à jour du temps actuel
        if(lecteur.enArret() && playlist[ui->tableWidget_Playlist->currentRow()].nbPistes()==ui->tableWidget_PistesPlaylist->rowCount()){
            qint64 temp=0;
            for(int x=0;x<currentRow;x++)
                temp+=playlist[ui->tableWidget_Playlist->currentRow()].retourFinPiste(x);
            ui->label_tempsActuelPlaylist->setText(msToQString(temp));
            ui->progressBar_Playlist->setValue(temp);
        }
    }else{
        ui->pushButton_Lecture->setEnabled(false);
        ui->pushButton_Supprimer->setEnabled(false);
        ui->label_titrePistePlaylist->hide();
        ui->progressBar_Playlist->hide();
    }
    centralWidget()->setFocus();
}

void MainWindow::on_etatBouclagePlaylist(bool etat)
{
    QCheckBox *ptrSource=(QCheckBox*)sender();
    playlist[ptrSource->objectName().toInt()].definirBouclage(etat);
    centralWidget()->setFocus();
}

void MainWindow::on_pushButton_Exporter_clicked()
{
    QString temp=QFileDialog::getSaveFileName(this,"Choisir destination",lastRepertoire,"Fichier Session(*.session)");
    if(temp!=""){
        QFile destination(temp);
        destination.open(QIODevice::WriteOnly | QIODevice::Text);
        //Entête pistes
        destination.write(QString("pi"+QString::number(pistes.count())+"\n").toUtf8());
        for(int x=0;x<pistes.count();x++){
            destination.write(QString(pistes[x]->info.retourChemin()+
                                      "\n"+QString::number(pistes[x]->info.retourDebutI())+
                                      "\n"+QString::number(pistes[x]->info.retourFinI())+
                                      "\n"+QString::number(pistes[x]->info.retourBouclage())+
                                      "\n"+pistes[x]->info.retourTouche()).toUtf8()+"\n");
        }
        //Entête playlist
        destination.write(QString("pl"+QString::number(playlist.count())+"\n").toUtf8());
        for(int x=0;x<playlist.count();x++){
            destination.write(QString(playlist[x].retourNom()+"*"
                                      +QString::number(playlist[x].nbPistes())+"*"
                                      +playlist[x].retourTouche()+"*"
                                      +QString::number(playlist[x].retourBouclage())+"\n").toUtf8());
            for(int y=0;y<playlist[x].nbPistes();y++){
                destination.write(QString(playlist[x].retourCheminPiste(y)+"\n").toUtf8());
            }
            destination.write(" ");
        }
        destination.close();
        informations->setText("Exportation réussie");
        informations->exec();
    }
}

void MainWindow::on_pushButton_Importer_clicked()
{
    QMessageBox message;
    message.setWindowTitle("Importation");
    message.addButton("Continuer",QMessageBox::AcceptRole);
    message.addButton("Annuler",QMessageBox::RejectRole);
    message.setText("L'importation mettra fin à la session actuelle\nSouhaitez-vous continuer ?");

    if(message.exec()==QMessageBox::AcceptRole){
        QString temp=QFileDialog::getOpenFileName(this,"Choisir source",lastRepertoire,"Fichier Session(*.session)");
        if(temp!=""){
            //Remise à zéro
            while(ui->tableWidget_Pistes->rowCount()>0){
                ui->tableWidget_Pistes->removeRow(0);
            }
            pistes.clear();
            bouclagePiste.clear();
            while(ui->tableWidget_PistesPlaylist->rowCount()>0){
                ui->tableWidget_PistesPlaylist->removeRow(0);
            }
            while(ui->tableWidget_Playlist->rowCount()>0){
                ui->tableWidget_Playlist->removeRow(0);
            }
            playlist.clear();
            bouclagePlaylist.clear();
            ui->pushButton_nouvellePlaylist->click();
            if(ui->checkBox_Playlist->isChecked())
                ui->checkBox_Playlist->click();
            razInterface();
            //Importation
            bool verif=true;
            QFile source(temp);
            if(source.open(QIODevice::ReadOnly | QIODevice::Text)){
                //Traitement des pistes
                char import[1024];
                qint64 line=source.readLine(import,sizeof(import));
                QString lecture=charToQString(import);
                if(line!=-1){
                    //Importation des pistes
                    if(lecture.left(2)=="pi"){
                        lecture=lecture.remove("pi");
                        int nbP=lecture.toInt();
                        for(int x=0;x<nbP;x++){
                            source.readLine(import,sizeof(import));
                            QString temp=charToQString(import);
                            ImportPiste importTemp;
                            importTemp.chemin=temp.left(temp.length()-1);
                            importTemp.pos=x;
                            //Import Debut
                            source.readLine(import,sizeof(import));
                            importTemp.debut=charToQString(import).toInt();
                            //Import Fin
                            source.readLine(import,sizeof(import));
                            importTemp.fin=charToQString(import).toInt();
                            //Import bouclage
                            source.readLine(import,sizeof(import));
                            importTemp.bouclage=charToQString(import).toInt();
                            //Import touche
                            source.readLine(import,sizeof(import));
                            temp=charToQString(import);
                            importTemp.touche=temp.left(temp.length()-1);
                            listeImportPiste<<importTemp;
                        }
                    }else{
                        verif=false;
                        message.setText("Fichier corrompu");
                    }
                    if(verif){
                        //Importation des playlist
                        source.readLine(import,sizeof(import));
                        lecture=charToQString(import);
                        if(lecture.left(2)=="pl"){
                            lecture=lecture.remove("pl");
                            int nbPlaylist=lecture.toInt();
                            for(int x=0;x<nbPlaylist;x++){
                                if(x>0)
                                    on_pushButton_nouvellePlaylist_clicked();
                                source.readLine(import,sizeof(import));
                                lecture=charToQString(import);
                                QStringList decompo=lecture.split("*");
                                ui->tableWidget_Playlist->item(x,0)->setText(decompo[0]);
                                ui->tableWidget_Playlist->item(x,1)->setText(decompo[2]);
                                bouclagePlaylist[x]->setChecked(decompo[3].left(1).toInt());
                                for(int y=0;y<decompo[1].toInt();y++){
                                    source.readLine(import,sizeof(import));
                                    lecture=charToQString(import);
                                    ImportPiste temp;
                                    temp.chemin=lecture.left(lecture.length()-1);
                                    temp.pos=y;
                                    temp.isPlaylist=true;
                                    temp.posP=x;
                                    listeImportPiste<<temp;
                                }
                            }
                        }else{
                            verif=false;
                            message.setText("Import des playlist échoué");
                        }
                    }
                }else{
                    verif=false;
                    informations->setText("Lecture impossible");
                }
            }else{
                informations->setText("Impossible d'ouvrir le fichier");
            }
            if(verif){
                ajouterPiste();
            }else{
                informations->exec();
            }
        }
    }
}

void MainWindow::on_finVerifTemps()
{
    if(lecteur.tempsTotalI()>0){
        progressBar_Analyse->setValue(progressBar_Analyse->maximum());
        verifTemps->stop();
        progressBar_Analyse->hide();
        progressBar_Analyse->setValue(0);
        int pos;
        if(listeImportPiste[0].isPlaylist){
            int posP=listeImportPiste[0].posP;
            pos=listeImportPiste[0].pos;
            playlist[posP].definirFinPiste(pos,lecteur.tempsTotalI());
            playlist[posP].definirFrequencePiste(pos,lecteur.retourFrequence());
            playlist[posP].definirDebitPiste(pos,lecteur.retourDebit());
        }else{
            pos=listeImportPiste[0].pos;
            while(pos>pistes.count()-1)
                pos--;
            ui->label_Titre->setText(pistes[pos]->info.retourNom());
            pistes[pos]->info.definirFinPiste(lecteur.tempsTotalI());
            if(listeImportPiste[0].debut!=0)
                pistes[pos]->info.changerDebut(listeImportPiste[0].debut);
            if(listeImportPiste[0].fin!=0)
                pistes[pos]->info.changerFin(listeImportPiste[0].fin);
            else pistes[pos]->info.changerFin(lecteur.tempsTotalI());
            pistes[pos]->info.definirFrequence(lecteur.retourFrequence());
            pistes[pos]->info.definirDebit(lecteur.retourDebit());
            pistes[pos]->info.definirValMoyenne(lecteur.retourValMoyenne());
            masquerLabelTemps(true);
            pistes[pos]->spectre();
            bouclagePiste<<new QCheckBox;
            bouclagePiste.last()->setObjectName(QString::number(bouclagePiste.count()-1));
            connect(bouclagePiste.last(),SIGNAL(clicked(bool)),this,SLOT(on_etatBouclagePiste(bool)));
            bouclagePiste.last()->setChecked(listeImportPiste[0].bouclage);
            creerLigne("p",pos);
            ui->tableWidget_Pistes->item(pos,0)->setText(pistes[pos]->info.retourNom());
            ui->tableWidget_Pistes->item(pos,1)->setText(listeImportPiste[0].touche);
            ui->tableWidget_Pistes->item(pos,2)->setText(msToQString(pistes[pos]->info.retourFinI()-pistes[pos]->info.retourDebutI()));
            ui->horizontalSlider_debut->setEnabled(true);
            ui->horizontalSlider_fin->setEnabled(true);
            masquerLabelTemps(false);
        }
        lecteur.stop();
        lecteur.muet(saveMuet);
        actualiser();
        if(listeImportPiste[0].isPlaylist==ui->checkBox_Playlist->isChecked()){
            if(ui->checkBox_Playlist->isChecked()){
                ui->tableWidget_Playlist->setCurrentCell(listeImportPiste[0].posP,0);
            }else{
                ui->tableWidget_Pistes->setCurrentCell(pos,0);
            }
        }
        listeImportPiste.removeFirst();
        if(listeImportPiste.count()!=0)
            ajouterPiste();
        else if(erreur!=""){
            informations->setWindowTitle("Importation");
            informations->setText("Une erreur s'est produite lors de l'importation du fichier:"+erreur);
            erreur.clear();
            informations->exec();
        }
    }else{
        verifImport+=100;
        progressBar_Analyse->setValue(progressBar_Analyse->value()+100);
        if(verifImport>2000){
            progressBar_Analyse->setValue(progressBar_Analyse->maximum());
            verifTemps->stop();
            progressBar_Analyse->hide();
            progressBar_Analyse->setValue(0);
            lecteur.stop();
            lecteur.muet(saveMuet);
            erreur+="\n"+listeImportPiste.first().chemin;
            listeImportPiste.removeFirst();
            pistes.removeLast();
            if(listeImportPiste.count()!=0)
                ajouterPiste();
            else if(erreur!=""){
                informations->setWindowTitle("Importation");
                informations->setText("Une erreur s'est produite lors de l'importation du fichier:"+erreur);
                erreur.clear();
                informations->exec();
            }
        }
    }
}

void MainWindow::on_lineEdit_cursDebut_textEdited(const QString &arg1)
{
    verifChamps(arg1,ui->lineEdit_cursDebut);
}

void MainWindow::on_lineEdit_cursDebut_editingFinished()
{
    QString temp=ui->lineEdit_cursDebut->text();
    verifChampsFin(temp,ui->lineEdit_cursDebut);
    qint64 value=QStringToMs(temp);
    if(value>ui->horizontalSlider_debut->maximum())
        ui->horizontalSlider_debut->setValue(ui->horizontalSlider_debut->maximum());
    else ui->horizontalSlider_debut->setValue(value);
    centralWidget()->setFocus();
}

void MainWindow::on_lineEdit_cursFin_textEdited(const QString &arg1)
{
    verifChamps(arg1,ui->lineEdit_cursFin);
}

void MainWindow::on_lineEdit_cursFin_editingFinished()
{
    QString temp=ui->lineEdit_cursFin->text();
    verifChampsFin(temp,ui->lineEdit_cursFin);
    qint64 value=QStringToMs(temp);
    if(value>ui->horizontalSlider_fin->maximum())
        ui->horizontalSlider_fin->setValue(ui->horizontalSlider_fin->maximum());
    else ui->horizontalSlider_fin->setValue(value);
    centralWidget()->setFocus();
}

void MainWindow::on_pushButton_volume_clicked()
{
    if(ui->groupBox_volume->isVisible()){
        ui->groupBox_volume->hide();
        QFile confFile(QDir::currentPath()+"/config.ini");
        if(confFile.open(QIODevice::WriteOnly | QIODevice::Text)){
            confFile.write(QString::number(ui->horizontalSlider_Volume->value()).toUtf8());
        }
    }else{
        if(ui->groupBox_Parametres->isVisible())
            ui->groupBox_Parametres->hide();
        ui->groupBox_volume->show();
    }
}
