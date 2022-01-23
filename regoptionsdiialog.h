#ifndef REGOPTIONSDIIALOG_H
#define REGOPTIONSDIIALOG_H
#include<scanner.h>
#include <QDialog>

namespace Ui {
class regoptionsdiialog;
}

class regoptionsdiialog : public QDialog
{
    Q_OBJECT

public:
    explicit regoptionsdiialog(QWidget *parent = nullptr,Scanner *scanner = nullptr);
    ~regoptionsdiialog();
    void setparams(std::string add,int mode);
    void setregistervalue(int nt, bool value, std::string add, int mode);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::regoptionsdiialog *ui;
    std::string regaddres;
    std::string address;
    Scanner * scanner;
    int mode;
};

#endif // REGOPTIONSDIIALOG_H
