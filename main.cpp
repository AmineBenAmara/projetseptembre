#include "mainwindow.h"
#include "connection.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    connection c;
    if (c.createconnection()) {
        w.show();
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                                 QObject::tr("Connection successful.\n"
                                             "Click OK to continue."), QMessageBox::Ok);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                               QObject::tr("Connection failed.\n"
                                           "Click OK to exit."), QMessageBox::Ok);
        return 1;
    }

    return a.exec();
}
