#include "connection.h"

connection::connection()
{

}
bool connection::createconnection()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("amine-bd");
db.setUserName("amine");//inserer nom de l'utilisateur
db.setPassword("amine123");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;


    return  test;
}

void connection::closeconnection()
{  db.close();
}
