#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "enseignants.h"
#include "eleve.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_afficher_clicked();

    void on_pushButton_ajouter_clicked();

    void on_pushButton_modifier_clicked();

    void on_pushButton_supprimer_clicked();

    void on_pushButton_afficher_eleve_clicked();

    void on_pushButton_ajouter_eleve_clicked();

    void on_pushButton_modifier_eleve_clicked();

    void on_pushButton_supprimer_eleve_clicked();

    void on_lineEdit_recherche_textChanged();

    void on_lineEdit_recherche_enseignant_textChanged();

    void on_comboBox_activated();

    void on_comboBox_tri_eleve_activated();

    void on_tableView_enseignant_clicked(const QModelIndex &index);

    void on_tableView_eleve_clicked(const QModelIndex &index);

    void on_pushButton_stat_eleve_clicked();

    void on_pushButton_stat_enseignants_clicked();

    void on_pushButton_QRcode_clicked();

    void on_pushButton_pdf_eleve_clicked();

private:
    Ui::MainWindow *ui;
    enseignants E;
    eleve El;
};
#endif // MAINWINDOW_H
