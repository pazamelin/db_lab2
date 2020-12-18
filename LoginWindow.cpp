#include "LoginWindow.h"
#include "./ui_LoginWindow.h"


LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->currentDateTime->setText(QDate::currentDate().toString());
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_loginButton_clicked()
{
    const auto driver{ui->driver->text()};
    const auto port{ui->port->text()};
    const auto host{ui->host->text()};
    const auto username{ui->username->text()};
    const auto password{ui->password->text()};
    const auto dbname{ui->dbname->text()};

    Database* db = new Database;
    db->initialize(driver, port, host, username, password, dbname);

    if (db->get_last_status())
    {
        hide();
        main_window = new MainWindow();
        main_window->set_db(db);
        main_window->show();
    }
    else
    {
        QMessageBox Msgbox;
        Msgbox.setText("failed to connect!");
        Msgbox.exec();
    }

}

void LoginWindow::on_driver_editingFinished()
{

}
