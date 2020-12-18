#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QDate>
#include <QMessageBox>
#include <QErrorMessage>

#include "MainWindow.h"
#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_loginButton_clicked();

    void on_driver_editingFinished();

private:
    Ui::LoginWindow *ui;
    MainWindow* main_window;
};
#endif // LOGINWINDOW_H
