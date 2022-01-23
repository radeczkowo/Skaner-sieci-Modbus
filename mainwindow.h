#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<tasksdialog.h>
#include<regoptionsdiialog.h>
#include<setdialog.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void init();
    void setupconnect();

private slots:
    void twoportsact();
    void oneportact();
    void onpushButtonclicked();
    void framehandler(std::string frame);
    void updateslaves(std::string id);
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    Scanner* scanner;
    TasksDialog* tasksdialog;
    regoptionsdiialog* regdialog;
    Setdialog* setdialog;
};
#endif // MAINWINDOW_H
