#ifndef SETDIALOG_H
#define SETDIALOG_H
#include<scanner.h>
#include <QDialog>

namespace Ui {
class Setdialog;
}

class Setdialog : public QDialog
{
    Q_OBJECT

public:
    explicit Setdialog(QWidget *parent = nullptr, Scanner * scanner=nullptr);
    ~Setdialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Setdialog *ui;
    Scanner *scanner;
};

#endif // SETDIALOG_H
