#ifndef ENSEIGNANTS_H
#define ENSEIGNANTS_H

#include <QString>
#include <QSqlQueryModel>


//CRUDS
class enseignants

{
public:
    enseignants();
    enseignants(int,QString,QString,QString,int,QString);
    int getid();
    QString getnom();
    QString getprenom();
    QString getsexe();
    int getage();
    QString getmatiere();



    void setid(int);
    void setnom(QString);
    void setprenom(QString);
    void setsexe(QString);
    void setage(int);
    void setmatiere(QString);


    bool ajouterenseignants();
    QSqlQueryModel* afficherenseignants();
    bool supprimerenseignants(int);
    bool supprimerTout();
    bool modifierenseignants(int,QString,QString,QString,int,QString);
    QSqlQueryModel* Rechercheenseignants(QString);
    QSqlQueryModel * trierenseignantsParnom();
    QSqlQueryModel * trierenseignantsParprenom();
    QSqlQueryModel * trierenseignantsParmatiere();
    void CREATION_PDF_enseignants();


private:
    int id,age;
    QString nom,prenom,sexe,matiere;
};


#endif // ENSEIGNANTS_H
