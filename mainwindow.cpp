#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

#include <QPdfWriter>
#include <QPainter>
#include <QSqlQuery>
#include <QtCharts>
#include "qrcode.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_afficher_clicked()
{
    ui->tableView_enseignant->setModel(E.afficherenseignants());
}

void MainWindow::on_pushButton_ajouter_clicked()
{

    int id=ui->lineEdit_id->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    QString sexe=ui->comboBox_Sexe->currentText();
    int age=ui->lineEdit_age->text().toInt();
    QString matiere=ui->comboBox_matiere->currentText();
    enseignants E(id,nom,prenom,sexe,age,matiere);
        bool test=E.ajouterenseignants();
        if(test)
              {    QMessageBox::information(nullptr, QObject::tr("ajout avec succes"),
                                            QObject::tr("ajout successful.\n"
                                                        "Click Cancel to exit."), QMessageBox::Cancel);
                             ui->tableView_enseignant->setModel(E.afficherenseignants());
                             QString nomFile ="Historique";
                                          QFile file("C:\\Users\\user\\Documents\\projetseptembre\\"+nomFile+".txt");
                                          QString finalmsg="fichier modifie avec succes";
                                           if(!file.exists()){
                                           finalmsg="fichier cree avec succes";
                                           }
                                          file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);



                                          QTextStream txt(&file);
                                            QString d_info = QDateTime::currentDateTime().toString();

                                          QString message2=d_info+" - Un Enseignant a été ajouter avec le nom "+ nom +"\n";
                                          txt << message2;

              }
                            else
                                QMessageBox::critical(nullptr, QObject::tr("Ajout errer"),
                                            QObject::tr("ajout failed.\n"
                                                        "Click Cancel to exit."), QMessageBox::Cancel);

             ui->lineEdit_id->clear();
             ui->lineEdit_nom->clear();
             ui->lineEdit_prenom->clear();
             ui->comboBox_Sexe->setCurrentIndex(0);
             ui->lineEdit_age->clear();
             ui->comboBox_matiere->setCurrentIndex(0);

}

void MainWindow::on_pushButton_modifier_clicked()
{


    int id=ui->lineEdit_id->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    QString sexe=ui->comboBox_Sexe->currentText();
    int age=ui->lineEdit_age->text().toInt();
    QString matiere=ui->comboBox_matiere->currentText();


    enseignants E(id,nom,prenom,sexe,age,matiere);

    bool test=E.modifierenseignants(E.getid(),E.getnom(),E.getprenom(),E.getsexe(),E.getage(),E.getmatiere());

    QMessageBox msgBox;

    if ((ui->lineEdit_id->text()==0),(ui->lineEdit_nom->text()==""),(ui->lineEdit_prenom->text()==""),(ui->comboBox_Sexe->currentText()==""),(ui->lineEdit_age->text()==0),(ui->comboBox_matiere->currentText()==""))
    {
        QMessageBox::critical(this, QObject::tr("Modification Errer"),
                           QObject::tr("Echec de Modification!!!\n""Veuillez remplir tous le champs"), QMessageBox::Cancel);

    }
    else if(test)
    {
        QMessageBox::information(this, QObject::tr("Modification Succes"),
                           QObject::tr("Modifications avec Succes"), QMessageBox::Cancel);
        ui->tableView_enseignant->setModel(E.afficherenseignants());
        QString nomFile ="Historique";
                     QFile file("C:\\Users\\user\\Documents\\projetseptembre\\"+nomFile+".txt");
                     QString finalmsg="fichier modifie avec succes";
                      if(!file.exists()){
                      finalmsg="fichier cree avec succes";
                      }
                     file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);



                     QTextStream txt(&file);
                       QString d_info = QDateTime::currentDateTime().toString();

                     QString message2=d_info+" - Un Enseignant a été modifier avec le nom "+ nom +"\n";
                     txt << message2;


    }
    ui->lineEdit_id->clear();
    ui->lineEdit_nom->clear();
    ui->lineEdit_prenom->clear();
    ui->comboBox_Sexe->setCurrentIndex(0);
    ui->lineEdit_age->clear();
    ui->comboBox_matiere->setCurrentIndex(0);



}

void MainWindow::on_pushButton_supprimer_clicked()
{

    enseignants E1;
    E1.setid(ui->lineEdit_id->text().toInt());
    bool test=E1.supprimerenseignants(E1.getid());
    QMessageBox msgBox;
    if (ui->lineEdit_id->text()=="")
    {
        QMessageBox::critical(this, QObject::tr("Suppression Errer"),
                           QObject::tr("Echec de Suppression!!!\n""Veuillez remplir la label de id"), QMessageBox::Cancel);
    }
    else if (test)
    {
        QMessageBox::information(this, QObject::tr("Suppression avec Succes"),
                           QObject::tr("Suppression avec succes"), QMessageBox::Cancel);
        ui->tableView_enseignant->setModel(E.afficherenseignants());
        QString nomFile ="Historique";
                     QFile file("C:\\Users\\user\\Documents\\projetseptembre\\"+nomFile+".txt");
                     QString finalmsg="fichier modifie avec succes";
                      if(!file.exists()){
                      finalmsg="fichier cree avec succes";
                      }
                     file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);



                     QTextStream txt(&file);
                       QString d_info = QDateTime::currentDateTime().toString();

                     QString message2=d_info+" - Un Enseignant a été Supprimer\n";
                     txt << message2;

    }

    ui->lineEdit_nom->clear();
    ui->lineEdit_prenom->clear();
    ui->comboBox_Sexe->setCurrentIndex(0);
    ui->lineEdit_age->clear();
    ui->comboBox_matiere->setCurrentIndex(0);

}




void MainWindow::on_comboBox_activated()
{
    if(ui->comboBox->currentText()=="Nom")
    {
        ui->tableView_enseignant->setModel(E.trierenseignantsParnom());

    }else if(ui->comboBox->currentText()=="Prenom")
    {
        ui->tableView_enseignant->setModel(E.trierenseignantsParprenom());

    }else
    {
        ui->tableView_enseignant->setModel(E.trierenseignantsParmatiere());
    }
}



void MainWindow::on_lineEdit_recherche_enseignant_textChanged()
{

    QString rech=ui->lineEdit_recherche_enseignant->text();
    ui->tableView_enseignant->setModel(E.Rechercheenseignants(rech));
}




void MainWindow::on_tableView_enseignant_clicked(const QModelIndex &index)
{
    ui->lineEdit_id->setText(ui->tableView_enseignant->model()->data(ui->tableView_enseignant->model()->index(index.row(),0)).toString());
    ui->lineEdit_nom->setText(ui->tableView_enseignant->model()->data(ui->tableView_enseignant->model()->index(index.row(),1)).toString());
    ui->lineEdit_prenom->setText(ui->tableView_enseignant->model()->data(ui->tableView_enseignant->model()->index(index.row(),2)).toString());
    ui->comboBox_Sexe->setCurrentText(ui->tableView_enseignant->model()->data(ui->tableView_enseignant->model()->index(index.row(),3)).toString());
    ui->lineEdit_age->setText(ui->tableView_enseignant->model()->data(ui->tableView_enseignant->model()->index(index.row(),4)).toString());
    ui->comboBox_matiere->setCurrentText(ui->tableView_enseignant->model()->data(ui->tableView_enseignant->model()->index(index.row(),5)).toString());
}




void MainWindow::on_pushButton_stat_enseignants_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
                            model->setQuery("select * from enseignants where sexe = 'Homme' ");
                            float sexe=model->rowCount();
                            model->setQuery("select * from enseignants where sexe = 'Femme' ");
                            float sexee=model->rowCount();
                            float total=sexe+sexee;
                            QString a=QString("Homme  "+QString::number((sexe*100)/total,'f',2)+"%" );
                            QString b=QString("Femme "+QString::number((sexee*100)/total,'f',2)+"%" );
                            QPieSeries *series = new QPieSeries();
                            series->append(a,sexe);
                            series->append(b,sexee);
                    if (sexe!=0)
                    {QPieSlice *slice = series->slices().at(0);
                     slice->setLabelVisible();
                     slice->setPen(QPen());}
                    if ( sexee!=0)
                    {
                             // Add label, explode and define brush for 2nd slice
                             QPieSlice *slice1 = series->slices().at(1);
                             //slice1->setExploded();
                             slice1->setLabelVisible();
                    }

                            // Create the chart widget
                            QChart *chart = new QChart();
                            // Add data to chart with title and hide legend
                            chart->addSeries(series);
                            chart->setTitle("Pourcentage Par Sexe :Nombre Des Enseignants "+ QString::number(total));
                            chart->legend()->hide();
                            // Used to display the chart
                            QChartView *chartView = new QChartView(chart);
                            chartView->setRenderHint(QPainter::Antialiasing);
                            chartView->resize(1000,500);
                            chartView->show();

}




void MainWindow::on_pushButton_QRcode_clicked()
{
    QString text ="Enseignants details : Nom : "+ ui->tableView_enseignant->model()->data(ui->tableView_enseignant->model()->index(ui->tableView_enseignant->currentIndex().row(),1)).toString()
                            +" / Prenom : "+ui->tableView_enseignant->model()->data(ui->tableView_enseignant->model()->index(ui->tableView_enseignant->currentIndex().row(),2)).toString()
                            +" / Sexe : "+ui->tableView_enseignant->model()->data(ui->tableView_enseignant->model()->index(ui->tableView_enseignant->currentIndex().row(),3)).toString()
                            +" / Age : "+ui->tableView_enseignant->model()->data(ui->tableView_enseignant->model()->index(ui->tableView_enseignant->currentIndex().row(),4)).toString()
                            +" / matiere : "+ui->tableView_enseignant->model()->data(ui->tableView_enseignant->model()->index(ui->tableView_enseignant->currentIndex().row(),5)).toString();
                    //text="user data";
                    using namespace qrcodegen;
                      // Create the QR Code object
                      QrCode qr = QrCode::encodeText( text.toUtf8().data(), QrCode::Ecc::MEDIUM );
                      qint32 sz = qr.getSize();
                      QImage im(sz,sz, QImage::Format_RGB32);
                        QRgb black = qRgb(  0,  0,  0);
                        QRgb white = qRgb(255,255,255);
                      for (int y = 0; y < sz; y++)
                        for (int x = 0; x < sz; x++)
                          im.setPixel(x,y,qr.getModule(x, y) ? black : white );
                      ui->qr_code->setPixmap( QPixmap::fromImage(im.scaled(256,256,Qt::KeepAspectRatio,Qt::FastTransformation),Qt::MonoOnly) );

}


/*********************************************************************************************************************/
/*********************************************************************************************************************/
/*********************************************************************************************************************/
/*********************************************************************************************************************/
/*********************************************************************************************************************/



void MainWindow::on_pushButton_afficher_eleve_clicked()
{
    ui->tableView_eleve->setModel(El.affichereleve());
}



void MainWindow::on_pushButton_ajouter_eleve_clicked()
{

    int id=ui->lineEdit_id_eleve->text().toInt();
    QString nom=ui->lineEdit_nom_eleve->text();
    QString prenom=ui->lineEdit_prenom_eleve->text();
    QString sexe=ui->comboBox_Sexe_eleve->currentText();
    int age=ui->lineEdit_age_eleve->text().toInt();
    QString classe=ui->comboBox_classe_eleve->currentText();

    eleve El(id,nom,prenom,sexe,age,classe);
        bool test=El.ajoutereleve();
        if(test)
              {    QMessageBox::information(nullptr, QObject::tr("ajout avec succes"),
                                            QObject::tr("ajout successful.\n"
                                                        "Click Cancel to exit."), QMessageBox::Cancel);
                             ui->tableView_eleve->setModel(El.affichereleve());
              }
                            else
                                QMessageBox::critical(nullptr, QObject::tr("Ajout errer"),
                                            QObject::tr("ajout failed.\n"
                                                        "Click Cancel to exit."), QMessageBox::Cancel);

             ui->lineEdit_id_eleve->clear();
             ui->lineEdit_nom_eleve->clear();
             ui->lineEdit_prenom_eleve->clear();
             ui->comboBox_Sexe_eleve->setCurrentIndex(0);
             ui->lineEdit_age_eleve->clear();
             ui->comboBox_classe_eleve->setCurrentIndex(0);


}

void MainWindow::on_pushButton_modifier_eleve_clicked()
{


    int id=ui->lineEdit_id_eleve->text().toInt();
    QString nom=ui->lineEdit_nom_eleve->text();
    QString prenom=ui->lineEdit_prenom_eleve->text();
    QString sexe=ui->comboBox_Sexe_eleve->currentText();
    int age=ui->lineEdit_age_eleve->text().toInt();
    QString classe=ui->comboBox_classe_eleve->currentText();


    eleve El(id,nom,prenom,sexe,age,classe);

    bool test=El.modifiereleve(El.getid(),El.getnom(),El.getprenom(),El.getsexe(),El.getage(),El.getclasse());

    QMessageBox msgBox;

    if ((ui->lineEdit_id_eleve->text()==0),(ui->lineEdit_nom_eleve->text()==""),(ui->lineEdit_prenom_eleve->text()==""),(ui->comboBox_Sexe_eleve->currentText()==""),(ui->lineEdit_age_eleve->text()==0),(ui->comboBox_classe_eleve->currentText()==""))
    {
        QMessageBox::critical(this, QObject::tr("Modification Errer"),
                           QObject::tr("Echec de Modification!!!\n""Veuillez remplir tous le champs"), QMessageBox::Cancel);

    }
    else if(test)
    {
        QMessageBox::information(this, QObject::tr("Modification Succes"),
                           QObject::tr("Modifications avec Succes"), QMessageBox::Cancel);
        ui->tableView_eleve->setModel(El.affichereleve());

    }
    ui->lineEdit_id_eleve->clear();
    ui->lineEdit_nom_eleve->clear();
    ui->lineEdit_prenom_eleve->clear();
    ui->comboBox_Sexe_eleve->setCurrentIndex(0);
    ui->lineEdit_age_eleve->clear();
    ui->comboBox_classe_eleve->setCurrentIndex(0);



}

void MainWindow::on_pushButton_supprimer_eleve_clicked()
{
    eleve El1;
    El1.setid(ui->lineEdit_id_eleve->text().toInt());
    bool test=El1.supprimereleve(El1.getid());
    QMessageBox msgBox;
    if (ui->lineEdit_id_eleve->text()=="")
    {
        QMessageBox::critical(this, QObject::tr("Suppression Errer"),
                           QObject::tr("Echec de Suppression!!!\n""Veuillez remplir la label de id"), QMessageBox::Cancel);
    }
    else if (test)
    {
        QMessageBox::information(this, QObject::tr("Suppression avec Succes"),
                           QObject::tr("Suppression avec succes"), QMessageBox::Cancel);
        ui->tableView_eleve->setModel(El.affichereleve());
    }

    ui->lineEdit_id_eleve->clear();
    ui->lineEdit_nom_eleve->clear();
    ui->lineEdit_prenom_eleve->clear();
    ui->comboBox_Sexe_eleve->setCurrentIndex(0);
    ui->lineEdit_age_eleve->clear();
    ui->comboBox_classe_eleve->setCurrentIndex(0);
}


void MainWindow::on_lineEdit_recherche_textChanged()
{

    QString rech=ui->lineEdit_recherche->text();
    ui->tableView_eleve->setModel(El.Rechercheeleve(rech));
}


void MainWindow::on_comboBox_tri_eleve_activated()
{
    if(ui->comboBox_tri_eleve->currentText()=="Nom")
    {
        ui->tableView_eleve->setModel(El.triereleveParnom());

    }else if(ui->comboBox_tri_eleve->currentText()=="Prenom")
    {
        ui->tableView_eleve->setModel(El.triereleveParprenom());

    }else
    {
        ui->tableView_eleve->setModel(El.triereleveParclasse());
    }
}



void MainWindow::on_tableView_eleve_clicked(const QModelIndex &index)
{

    ui->lineEdit_id_eleve->setText(ui->tableView_eleve->model()->data(ui->tableView_eleve->model()->index(index.row(),0)).toString());
    ui->lineEdit_nom_eleve->setText(ui->tableView_eleve->model()->data(ui->tableView_eleve->model()->index(index.row(),1)).toString());
    ui->lineEdit_prenom_eleve->setText(ui->tableView_eleve->model()->data(ui->tableView_eleve->model()->index(index.row(),2)).toString());
    ui->comboBox_Sexe_eleve->setCurrentText(ui->tableView_eleve->model()->data(ui->tableView_eleve->model()->index(index.row(),3)).toString());
    ui->lineEdit_age_eleve->setText(ui->tableView_eleve->model()->data(ui->tableView_eleve->model()->index(index.row(),4)).toString());
    ui->comboBox_classe_eleve->setCurrentText(ui->tableView_eleve->model()->data(ui->tableView_eleve->model()->index(index.row(),5)).toString());


}


void MainWindow::on_pushButton_stat_eleve_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
                        model->setQuery("select * from eleve where age < 10 ");
                        float age=model->rowCount();
                        model->setQuery("select * from eleve where age  between 10 and 15 ");
                        float agee=model->rowCount();
                        model->setQuery("select * from eleve where age > 15 ");
                        float ageee=model->rowCount();
                        float total=age+agee+ageee;
                        QString a=QString("moins de 10 ans "+QString::number((age*100)/total,'f',2)+"%" );
                        QString b=QString("entre 10 et 15 Ans"+QString::number((agee*100)/total,'f',2)+"%" );
                        QString c=QString("+15 Ans"+QString::number((ageee*100)/total,'f',2)+"%" );
                        QPieSeries *series = new QPieSeries();
                        series->append(a,age);
                        series->append(b,agee);
                        series->append(c,ageee);
                if (age!=0)
                {QPieSlice *slice = series->slices().at(0);
                 slice->setLabelVisible();
                 slice->setPen(QPen());}
                if ( agee!=0)
                {
                         // Add label, explode and define brush for 2nd slice
                         QPieSlice *slice1 = series->slices().at(1);
                         //slice1->setExploded();
                         slice1->setLabelVisible();
                }
                if(ageee!=0)
                {
                         // Add labels to rest of slices
                         QPieSlice *slice2 = series->slices().at(2);
                         //slice1->setExploded();
                         slice2->setLabelVisible();
                }
                        // Create the chart widget
                        QChart *chart = new QChart();
                        // Add data to chart with title and hide legend
                        chart->addSeries(series);
                        chart->setTitle("Pourcentage Par Age :Nombre Des Eléves "+ QString::number(total));
                        chart->legend()->hide();
                        // Used to display the chart
                        QChartView *chartView = new QChartView(chart);
                        chartView->setRenderHint(QPainter::Antialiasing);

                        chartView->resize(1000,500);
                        chartView->show();

}



void MainWindow::on_pushButton_pdf_eleve_clicked()
{
    QPdfWriter pdf("C:\\Users\\user\\Documents\\projetseptembre\\PDF_Eleves\\PDF_Eleves.pdf");

   QPainter painter(&pdf);
   int i = 4000;
          painter.setPen(Qt::red);
          painter.setFont(QFont("Time New Roman", 25));
          painter.drawText(3000,1400,"Liste Des Employes");
          painter.setPen(Qt::black);
          painter.setFont(QFont("Time New Roman", 15));
          painter.drawRect(100,3000,9400,500);
          painter.setFont(QFont("Time New Roman", 9));
          painter.drawText(400,3300,"Nom");
          painter.drawText(1700,3300,"Prenom");
          painter.drawText(2800,3300,"Sexe");
          painter.drawText(4000,3300,"Age");
          painter.drawText(5000,3300,"Classe");
          painter.drawRect(100,3000,9400,9000);

          QSqlQuery query;
          query.prepare("select * from eleve");
          query.exec();
          while (query.next())
          {
              painter.drawText(400,i,query.value(1).toString());
              painter.drawText(1700,i,query.value(2).toString());
              painter.drawText(2800,i,query.value(3).toString());
              painter.drawText(4000,i,query.value(4).toString());
              painter.drawText(5000,i,query.value(5).toString());


             i = i + 350;
          }
          QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
          QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);
}
