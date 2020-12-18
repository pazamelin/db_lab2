#include "database.h"

Database::Database()
{
    is_connected = false;
    last_status  = false;
}

void Database::initialize(QString driver,   QString port,     QString host,
                          QString username, QString password, QString dbname)
{
    auto connection = QSqlDatabase(QSqlDatabase::addDatabase(driver));

    connection.setPort(port.toInt());
    connection.setHostName(host);
    connection.setUserName(username);
    connection.setPassword(password);
    connection.setDatabaseName(dbname);

    if (connection.open())
    {
        this->is_connected = true;
        this->last_status  = true;

        qDebug() << "initialized with " << dbname;

        this->driver = driver;
        this->port = port;
        this->host = host;
        this->username = username;
        this->password = password;

        this->default_name = dbname;
        this->name = dbname;

        connection.close();
    }
    else
    {
        this->is_connected = false;
        this->last_status  = false;

        qDebug() << "failed to initialize with " << dbname;

    }
}

QSqlDatabase* Database::connect()
{
    auto connection =  new QSqlDatabase(QSqlDatabase::addDatabase(driver));
    connection->setPort(port.toInt());
    connection->setHostName(host);
    connection->setUserName(username);
    connection->setPassword(password);
    connection->setDatabaseName(name);

    if (connection->open())
    {
        this->is_connected = true;
        this->last_status  = true;

        qDebug() << "connected to " << name;
    }
    else
    {
        this->is_connected = false;
        this->last_status  = false;

        qDebug() << "failed to connect to " << name;

        delete connection;
        connection = nullptr;
    }

    return connection;
}

void Database::disconnect(QSqlDatabase* connection)
{
    if(this->is_connected && connection != nullptr)
    {
        connection->close();
        delete connection;
        connection = nullptr;

        qDebug() << "disconnected from " << this->name;

        this->is_connected = false;
    }
}

void Database::execute(QString statement, QString info)
{
    auto* db = connect();
    qDebug() << statement;
    if(this->is_connected)
    {
        {
            auto* query = new QSqlQuery();
            if(query->exec(statement))
            {
                this->last_status = true;
                qDebug() << "done:" << info;
            }
            else
            {
                this->last_status = false;
                qDebug() << "failed:" << info;
                qDebug() << query->lastError().text();
            }
        }

       this->disconnect(db);
    }
}

bool Database::execute_file(QString filename)
{
    bool no_errors = true;

    QFile file(filename);
    if(file.open(QFile::ReadOnly|QFile::Text))
    {
        QString content = file.readAll();

        int i = 1;
        QStringList queries = content.split(QString("sql;"));
        for(auto& queryString : queries)
        {
            queryString += "sql;";
        }

        foreach(QString queryString, queries)
        {
            execute(queryString, "file:" + filename + ", script:" + QString::number(i++));
            if(!this->last_status)
            {
                no_errors = false;
            }
        }
    }
    else
    {
       qDebug() << "failed to open " << filename;
       qDebug() << file.errorString();
       no_errors = false;
    }

    return no_errors;
}

bool Database::load_procedures(QString procedure_label, QString filename)
{
    this->loaded_procedures[procedure_label] = execute_file(filename);
    return loaded_procedures[procedure_label];
}

void Database::create_db(QString name)
{
    QString statement = "SELECT CreateDB('" + name + "')";
    QString info = "create database " + name;

    this->execute(statement, info);

    if(this->last_status)
    {
        this->name = name;

        auto* db = connect();
        disconnect(db);

        qDebug() << "switched to database" << name;
    }
}

void Database::delete_db(QString name)
{
    QString name_to_delete = this->name;
    this->name = this->default_name;
    QString statement = "SELECT DeleteDB('" + name + "')";
    QString info = "delete database " + name;

    this->execute(statement, info);

    if(this->last_status)
    {
        this->name = this->default_name;
    }
    else
    {
        this->name = name_to_delete;
    }
}

void Database::create_table(QString name)
{
    QString statement = "SELECT create_table_" + name + "()";
    QString info = "create table " + name;

    this->execute(statement, info);
}

void Database::clear_talbe(QString name)
{
    QString statement = "SELECT clear_table_" + name + "()";
    QString info = "clear table" + name;

    if(name == "/all")
    {
        QString statement = "SELECT clear_all_tables()";
        QString info = "clear all tables" + name;
    }

    this->execute(statement, info);
}

void Database::load_table(QString name, QTableView* view)
{
    // display
    QString pl_load = "load_table";
    QString pl_load_path  = ":/sql/sql/gettables.sql";
    load_procedures(pl_load, pl_load_path);

    QString statement = "SELECT * FROM get_" + name + "()";
    QString info = "get table" + name;

    QSqlQueryModel* model = new QSqlQueryModel();

    auto* connection = connect();

    QSqlQuery* query = new QSqlQuery(*connection);
    query->prepare(statement);
    query->exec();

    model->setQuery(*query);
    view->setModel(model);

    disconnect(connection);
    qDebug() << model->rowCount();
}


void Database::insert_data(QString tablename, QString filename)
{
    auto* connection = connect();

    QFile file(filename);
        if ( !file.open(QFile::ReadOnly | QFile::Text) )
        {
            qDebug() << "File not exists";
        } else
        {
            QString params = "";
            if(tablename == "genres") params = ("?, ?");
            if(tablename == "artists") params = ("?, ?, ?, ?, ?");
            if(tablename == "albums") params = ("?, ?, ?");
            if(tablename == "songs") params = ("?, ?, ?, ?, ?, ?");

            QSqlQuery* query = new QSqlQuery(*connection);
            QString statement = "SELECT insert_into_" + tablename + "(" + params + ")";

            // create a thread to retrieve data from a file
            int k = 0;

            QTextStream in(&file);
            while (!in.atEnd())
            {
                query->prepare(statement);

                int i = 0;
                QString line = in.readLine();

                for (QString item : line.split(","))
                {
                    if(i++ != 0)
                    {
                        query->addBindValue(item);
                    }
                }
                query->exec();
            }
            file.close();
        }

    disconnect(connection);
}

bool Database::get_last_status() const noexcept
{
    return this->last_status;
}
