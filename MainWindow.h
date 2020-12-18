#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QSet>
#include <QStandardItemModel>
#include <QStandardItem>
#include "database.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void set_db(Database* new_db);

private slots:
    void on_create_db_clicked();

    void on_delete_db_clicked();

    void on_clear_table_clicked();

    void on_create_table_clicked();

    void on_name_editingFinished();
    void on_load_clicked();

    void on_select_table_currentIndexChanged(const QString &arg1);



    void delete_row(int id);

    void on_delete_row_clicked();

    void on_clear_all_clicked();

private:
    Ui::MainWindow* ui;
    Database* db;
    QLineEdit *edit;
    QString newdb_name;
};

#endif // MAINWINDOW_H
