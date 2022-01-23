#include "tasksdialog.h"
#include "ui_tasksdialog.h"

TasksDialog::TasksDialog(QWidget *parent, Scanner *scanner) :
    QDialog(parent),
    ui(new Ui::TasksDialog)
{
    ui->setupUi(this);
    this->scanner=scanner;
    this->setWindowTitle("Task Dialog");
    connect(ui->pushButton, &QPushButton::clicked,
            this, &TasksDialog::apply);
}

TasksDialog::~TasksDialog()
{
    delete ui;
}

void TasksDialog::update()
{
    if(scanner->getmode()==2)
    {
        if(ui->checkBox->isChecked())
            scanner->setmodifying(true);
        else
            scanner->setmodifying(false);
        if(ui->checkBox_2->isChecked())
            scanner->setblocking(true);
        else
            scanner->setblocking(false);
    }
    else
    {
        if(ui->checkBox_2->isChecked())
        {
            if(scanner->getmodifying()==false)
            {
                scanner->gettaskhandler()->forcelitenonlyalldevices();
            }
            scanner->setmodifying(true);
        }
        else
        {
            if(scanner->getmodifying()==true)
            {
                scanner->gettaskhandler()->restartalldevices();
            }
            scanner->setmodifying(false);
        }
    }


}

void TasksDialog::edit()
{
    if(scanner->getmode()==2)
    {
        ui->label_2->setVisible(1);
        ui->label_3->setText("Block entries");
        ui->checkBox->setVisible(1);
    }
    else
    {
        ui->label_2->setVisible(0);
        ui->label_3->setText("Modify");
        ui->checkBox->setVisible(0);
    }

}

void TasksDialog::apply()
{
    update();
    hide();
}



