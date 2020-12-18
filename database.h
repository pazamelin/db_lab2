#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QMessageBox>
#include <QErrorMessage>
#include <QFile>

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

#include <QStandardItemModel>
#include <QStandardItem>
#include <QTableView>
#include <QMainWindow>

class Database
{
public:
    Database();

    void initialize(QString driver,   QString port,     QString host,
                    QString username, QString password, QString dbname);

    QSqlDatabase* connect();
    void disconnect(QSqlDatabase* connection);

    void execute(QString statement, QString info);
    bool execute_file(QString filename);
    bool load_procedures(QString procedure_label, QString filename);

    void create_db(QString name);
    void delete_db(QString name);

    void create_table(QString name);
    void clear_talbe(QString name);
    void load_table(QString name, QTableView* view);
    void insert_data(QString tablename, QString filename);

    bool get_last_status() const noexcept;

private:
    // database info
    QString default_name;

    QString driver;
    QString host;
    QString name;
    QString port;

    // user info
    QString username;
    QString password;

    // flags
    bool is_connected;
    bool last_status;

    // procedures loaded
    QMap<QString, bool> loaded_procedures;
};

#endif // DATABASE_H
