#ifndef ELEVE_H
#define ELEVE_H

#include <QString>
#include <QSqlQueryModel>

class eleve
{

public:
    eleve();
    eleve(int,QString,QString,QString,int,QString);
    int getid();
    QString getnom();
    QString getprenom();
    QString getsexe();
    int getage();
    QString getclasse();



    void setid(int);
    void setnom(QString);
    void setprenom(QString);
    void setsexe(QString);
    void setage(int);
    void setclasse(QString);


    bool ajoutereleve();
    QSqlQueryModel* affichereleve();
    bool supprimereleve(int);
    bool supprimerTout();
    bool modifiereleve(int,QString,QString,QString,int,QString);
    QSqlQueryModel* Rechercheeleve(QString);
    QSqlQueryModel * triereleveParnom();
    QSqlQueryModel * triereleveParprenom();
    QSqlQueryModel * triereleveParclasse();
    void CREATION_PDF_eleve();


private:
    int id,age;
    QString nom,prenom,sexe,classe;
};

#endif // ELEVE_H
