#include "regoptionsdiialog.h"
#include "ui_regoptionsdiialog.h"

regoptionsdiialog::regoptionsdiialog(QWidget *parent, Scanner *scanner) :
    QDialog(parent),
    ui(new Ui::regoptionsdiialog)
{
    ui->setupUi(this);
    this->scanner=scanner;
    this->setWindowTitle("Change register status");
    mode =0;
}

regoptionsdiialog::~regoptionsdiialog()
{
    delete ui;
}

void regoptionsdiialog::setparams(std::string add, int mode)
{
    address=add;
    this->mode=mode;
}

void regoptionsdiialog::setregistervalue(int nt, bool value, std::string add, int mode)
{
    scanner->gettaskhandler()->setregistervalue(nt,value,add, mode);

}

void regoptionsdiialog::on_pushButton_clicked()
{
    setregistervalue(ui->lineEdit->text().toInt(),true, address, mode);
}

void regoptionsdiialog::on_pushButton_2_clicked()
{
    setregistervalue(ui->lineEdit->text().toInt(),false, address, mode);
}
