#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->centralwidget);
    newdb_name = "new_music_db";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_db(Database* new_db)
{
    this->db = new_db;
}

void MainWindow::on_create_db_clicked()
{
    QString procedure_label = "create_database";
    QString procedure_file  = ":/sql/sql/createdatabase.sql";
    this->db->load_procedures(procedure_label, procedure_file);

    this->db->create_db(newdb_name);

    if(ui->select_table->count() < 4)
    {
        ui->select_table->addItem("genres");
        ui->select_table->addItem("artists");
        ui->select_table->addItem("albums");
        ui->select_table->addItem("songs");
    }
}

void MainWindow::on_delete_db_clicked()
{
    QString procedure_label = "create_database";
    QString procedure_file  = ":/sql/sql/createdatabase.sql";
    this->db->load_procedures(procedure_label, procedure_file);

    this->db->delete_db(newdb_name);
    ui->select_table->clear();
}

void MainWindow::on_create_table_clicked()
{
    // create
    qDebug() << QDir::currentPath();
    QString pl_create = "create_table";
    QString pl_create_path  = ":/sql/sql/createtables.sql";

    this->db->load_procedures(pl_create, pl_create_path);

    QString new_table_name = ui->select_table->currentText();
    this->db->create_table(new_table_name);

    if(new_table_name == "songs")
    {
        QString pl_trigger= "trigger_albums";
        QString pl_trigger_file  = ":/sql/sql/indextriggers.sql";
        this->db->load_procedures(pl_trigger, pl_trigger_file);
    }

    this->db->load_table(new_table_name, this->ui->tableView);

    QString procedure_label = "delete_row";
    QString procedure_file  = ":/sql/sql/deleterow.sql";

    this->ui->tableView->setModel({});
    this->db->load_procedures(procedure_label , procedure_file);

    qDebug() << "LOADING:";
    this->db->load_table(new_table_name, this->ui->tableView);



}

void MainWindow::on_clear_table_clicked()
{
    qDebug() << QDir::currentPath();
    QString procedure_label = "clear_table";
    QString procedure_file  = ":/sql/sql/cleartables.sql";

    this->db->load_procedures(procedure_label, procedure_file);

    QString to_delete_table_name = ui->select_table->currentText();
    this->db->clear_talbe(to_delete_table_name);

    qDebug() << "LOADING:";
    this->db->load_table(to_delete_table_name, this->ui->tableView);

}

void MainWindow::on_name_editingFinished()
{
    newdb_name = ui->name->text();
    qDebug() << newdb_name;
}

void MainWindow::on_load_clicked()
{
    qDebug() << QDir::currentPath();
    QString procedure_label = "insert_table";
    QString procedure_file  = ":/sql/sql/inserttables.sql";

    this->db->load_procedures(procedure_label, procedure_file);

    QString table_name = ui->select_table->currentText();


    this->db->insert_data(table_name, ":/data/" + table_name + ".csv");

    qDebug() << "LOADING:";
    this->db->load_table(table_name, this->ui->tableView);
}

void MainWindow::on_select_table_currentIndexChanged(const QString &arg1)
{
    QString table_name = ui->select_table->currentText();
    this->db->load_table(table_name, this->ui->tableView);
}

void MainWindow::delete_row(int id)
{
    qDebug() << "DELETE BY ID:" << id;
     QString table_name = this->ui->select_table->currentText();
    QString statement = "SELECT delete_from_" + table_name + "(" + QString::number(id) + ")";
    QString info = "delete row";

    this->ui->tableView->setModel({});
    this->db->execute(statement, info);
    this->db->load_table(table_name, ui->tableView);
}

void MainWindow::on_delete_row_clicked()
{

    QString table_name = ui->select_table->currentText();


    QSet<int> rows_selected;

    // Get all selections
    QModelIndexList indexes = ui->tableView->selectionModel()->selection().indexes();

    for (int i = 0; i < indexes.count(); ++i)
    {
        QModelIndex index_ = indexes.at(i);
        rows_selected.insert(index_.row());
        qDebug() << index_.row();
    }

    qDebug() << "ALL ROWS:";
    for(auto row : rows_selected)
    {
        qDebug() << row << " ";
    }

    QSet<int> ids_to_delete;
    for(const auto& row : rows_selected)
    {
        auto id = ui->tableView->model()->index(row, 0).data().toInt();
        ids_to_delete.insert(id);
    }

    qDebug() << "ALL COLS:";
    for(auto id : ids_to_delete)
    {
        qDebug() << " deleting:" << id << " ";
    }

    for(auto id : ids_to_delete)
    {
        this->delete_row(id);
    }
}

void MainWindow::on_clear_all_clicked()
{
    qDebug() << QDir::currentPath();
    QString procedure_label = "clear_table";
    QString procedure_file  = ":/sql/sql/cleartables.sql";

    this->db->load_procedures(procedure_label, procedure_file);

    QSet<QString> tables = {"genres","artists", "albums", "songs"};
    for(const auto& table : tables)
    {
        this->db->clear_talbe(table);
        this->db->load_table(table, this->ui->tableView);
    }
}
