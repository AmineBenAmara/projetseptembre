#include "enseignants.h"

#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QFileDialog>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>


enseignants::enseignants()
{
    id=0; nom=" "; prenom=" "; sexe=" "; age=0; ; matiere= " ";// constructeur par defaut
}



enseignants::enseignants(int id,QString nom,QString prenom,QString sexe,int age,QString matiere)
{
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->sexe=sexe;
    this->age=age;
    this->matiere=matiere;
}


int enseignants::getid(){return id;}
QString enseignants::getnom(){return nom;}
QString enseignants::getprenom(){return prenom;}
QString enseignants::getsexe(){return sexe;}
int enseignants::getage(){return age;}
QString enseignants::getmatiere(){return matiere;}


void enseignants::setid(int id){this->id=id;}
void enseignants::setnom(QString nom){this->nom=nom;}
void enseignants::setprenom(QString prenom){this->prenom=prenom;}
void enseignants::setsexe(QString sexe){this->sexe=sexe;}
void enseignants::setage(int age){this->age=age;}
void enseignants::setmatiere(QString matiere){this->matiere=matiere;}



/******************************************************************************************************************/

/*******************************************CRUDS*****************************************************/



bool enseignants::ajouterenseignants()
{

     QSqlQuery query;
     query.prepare("INSERT INTO enseignants (id, NOM, PRENOM ,SEXE, AGE, MATIERE) "
                   "VALUES (:id, :nom, :prenom, :sexe, :age, :matiere)");// prparation de requette
     query.bindValue(":id", id); //remplir id2 dans id1
     query.bindValue(":nom", nom);
     query.bindValue(":prenom",prenom);
     query.bindValue(":sexe",sexe);
     query.bindValue(":age",age);
     query.bindValue(":matiere",matiere);
     return query.exec();

}



/***********************************************************************************************/


QSqlQueryModel* enseignants::afficherenseignants()
{
     QSqlQueryModel* model=new QSqlQueryModel();

     model->setQuery("SELECT *  FROM enseignants ");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));//nom entite
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("sexe"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("age"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("matiere"));

     return model;
}


/***********************************************************************************************/


bool enseignants::supprimerenseignants(int id)
{
    QSqlQuery query;
    query.prepare(" Delete from enseignants where id=:id ");
    query.bindValue(":id",id);

    return query.exec();
}



/***********************************************************************************************/



bool enseignants::supprimerTout()
{
    QSqlQuery query;
    query.prepare("delete from enseignants ");
    return query.exec();
}



/***********************************************************************************************/



bool enseignants::modifierenseignants(int id,QString nom,QString prenom,QString sexe,int age,QString matiere)
{

    QSqlQuery query;
    query.prepare("update enseignants set nom=:nom,prenom=:prenom,sexe=:sexe,age=:age,matiere=:matiere where id=:id");
    query.bindValue(":id",id);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":sexe",sexe);
    query.bindValue(":age",age);
    query.bindValue(":matiere",matiere);
    return query.exec();

}



/***********************************************************************************************/

QSqlQueryModel* enseignants::Rechercheenseignants(QString recherche)
 {
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("SELECT * FROM enseignants WHERE nom LIKE '"+recherche+"%' OR prenom LIKE '"+recherche+"%' OR matiere LIKE '"+recherche+"%'");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));//nom entite
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("sexe"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("age"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("matiere"));

return model;
}


/***********************************************************************************************/


QSqlQueryModel * enseignants::trierenseignantsParnom()
{

    QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM enseignants order by nom ASC");
           q->exec();
           model->setQuery(*q);
           return model;
}

QSqlQueryModel * enseignants::trierenseignantsParprenom()
{

    QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM enseignants order by prenom ASC");
           q->exec();
           model->setQuery(*q);
           return model;
}

QSqlQueryModel * enseignants::trierenseignantsParmatiere()
{

    QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM enseignants order by matiere ASC");
           q->exec();
           model->setQuery(*q);
           return model;
}

