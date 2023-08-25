#include "eleve.h"


#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QFileDialog>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>


eleve::eleve()
{
    id=0; nom=" "; prenom=" "; sexe=" "; age=0; ; classe=" ";
}



eleve::eleve(int id,QString nom,QString prenom,QString sexe,int age,QString classe)
{
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->sexe=sexe;
    this->age=age;
    this->classe=classe;
}


int eleve::getid(){return id;}
QString eleve::getnom(){return nom;}
QString eleve::getprenom(){return prenom;}
QString eleve::getsexe(){return sexe;}
int eleve::getage(){return age;}
QString eleve::getclasse(){return classe;}


void eleve::setid(int id){this->id=id;}
void eleve::setnom(QString nom){this->nom=nom;}
void eleve::setprenom(QString prenom){this->prenom=prenom;}
void eleve::setsexe(QString sexe){this->sexe=sexe;}
void eleve::setage(int age){this->age=age;}
void eleve::setclasse(QString classe){this->classe=classe;}



/******************************************************************************************************************/

/*******************************************CRUDS*****************************************************/



bool eleve::ajoutereleve()
{

     QSqlQuery query;
     query.prepare("INSERT INTO eleve (ID, NOM, PRENOM ,SEXE, AGE, CLASSE) "
                   "VALUES (:id, :nom, :prenom, :sexe, :age, :classe)");
     query.bindValue(":id", id);
     query.bindValue(":nom", nom);
     query.bindValue(":prenom",prenom);
     query.bindValue(":sexe",sexe);
     query.bindValue(":age",age);
     query.bindValue(":classe",classe);
     return query.exec();

}



/***********************************************************************************************/


QSqlQueryModel* eleve::affichereleve()
{
     QSqlQueryModel* model=new QSqlQueryModel();

     model->setQuery("SELECT *  FROM eleve ");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));//nom entite
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("sexe"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("age"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("classe"));

     return model;
}


/***********************************************************************************************/


bool eleve::supprimereleve(int id)
{
    QSqlQuery query;
    query.prepare(" Delete from eleve where id=:id ");
    query.bindValue(":id",id);

    return query.exec();
}





/***********************************************************************************************/



bool eleve::modifiereleve(int id,QString nom,QString prenom,QString sexe,int age,QString classe)
{


    QSqlQuery query;
    query.prepare("update eleve set nom=:nom,prenom=:prenom,sexe=:sexe,age=:age,classe=:classe where id=:id");
    query.bindValue(":id",id);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":sexe",sexe);
    query.bindValue(":age",age);
    query.bindValue(":classe",classe);
    return query.exec();


}


QSqlQueryModel* eleve::Rechercheeleve(QString recherche)
 {
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("SELECT * FROM eleve WHERE nom LIKE '"+recherche+"%' OR prenom LIKE '"+recherche+"%' OR classe LIKE '"+recherche+"%'");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));//nom entite
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("sexe"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("age"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("classe"));

return model;
}



/***********************************************************************************************/


QSqlQueryModel * eleve::triereleveParnom()
{

    QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM eleve order by nom ASC");
           q->exec();
           model->setQuery(*q);
           return model;
}

QSqlQueryModel * eleve::triereleveParprenom()
{

    QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM eleve order by prenom ASC");
           q->exec();
           model->setQuery(*q);
           return model;
}

QSqlQueryModel * eleve::triereleveParclasse()
{

    QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM eleve order by classe ASC");
           q->exec();
           model->setQuery(*q);
           return model;
}

