#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scanner = new Scanner();
    tasksdialog= new TasksDialog(nullptr,scanner);
    regdialog= new regoptionsdiialog(nullptr,scanner);
    setdialog= new Setdialog(nullptr, scanner);
    this->setWindowTitle("Modbus Scanner");
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    twoportsact();
    connect(ui->action2_ports, &QAction::triggered,
            this, &MainWindow::twoportsact);
    connect(ui->action1_port, &QAction::triggered,
            this, &MainWindow::oneportact);
    connect(ui->pushButton, &QPushButton::clicked,
            this, &MainWindow::onpushButtonclicked);
    connect(scanner,&Scanner::passframe,this, &MainWindow::framehandler);
    connect(ui->actionTask_settings, &QAction::triggered,
            tasksdialog, &TasksDialog::show);
    connect(ui->actionPort_settings, &QAction::triggered,
            setdialog, &TasksDialog::show);
    connect(scanner,&Scanner::passslave,this, &MainWindow::updateslaves);

}

void MainWindow::twoportsact()
{
      ui->action2_ports->setEnabled(false);
      ui->action1_port->setEnabled(true);
      ui->label->setVisible(true);
      ui->lineEdit->setVisible(true);
      ui->label_2->setText("Port2(master): ");
      scanner->setmode(2);
      tasksdialog->edit();
      ui->pushButton_6->setVisible(1);
      ui->pushButton_5->setVisible(1);
      ui->pushButton_4->setText("Blocking entries");
      ui->tableWidget_4->setVisible(1);
      ui->label_11->setVisible(1);
}

void MainWindow::oneportact()
{
    ui->action1_port->setEnabled(false);
    ui->action2_ports->setEnabled(true);
    ui->label->setVisible(false);
    ui->lineEdit->setVisible(false);
    ui->label_2->setText("Port: ");
    scanner->setmode(1);
    tasksdialog->edit();
    ui->pushButton_6->setVisible(0);
    ui->pushButton_5->setVisible(0);
    ui->pushButton_4->setText("Entries to modify");
    ui->tableWidget_4->setVisible(0);
    ui->label_11->setVisible(0);
}

void MainWindow::onpushButtonclicked()
{
    if(scanner->getconnected())
    {
        scanner->closeports();
        ui->pushButton->setText("Connect");
        statusBar()->showMessage(tr("Disconnected"));
    }
    else
    {
        scanner->openports(ui->lineEdit->text(),ui->lineEdit_2->text());
        if(scanner->getconnected())
        {
            ui->pushButton->setText("Disconnect");
            statusBar()->showMessage(tr("Connected"));

        }
        else
        {
           scanner->closeports();
           statusBar()->showMessage(tr("Connect failed"));
        }
    }
}

void MainWindow::framehandler(std::string frame)
{
    QTableWidgetItem *Itemad = new QTableWidgetItem();
    QTableWidgetItem *Itemfncode = new QTableWidgetItem();
    QTableWidgetItem *Itemdata = new QTableWidgetItem();
    QTableWidgetItem *ItemCRC = new QTableWidgetItem();
    if(ui->tableWidget->rowCount()>=30)
    {
        ui->tableWidget->removeRow(ui->tableWidget->rowCount()-1);
    }
    ui->tableWidget->insertRow(0);
    QString address = QString::fromStdString(frame.substr(0,2));
    QString fncode = QString::fromStdString(frame.substr(2,2));
    QString data = QString::fromStdString(frame.substr(4,frame.size()-8));
    QString CRC = QString::fromStdString(frame.substr(frame.size()-4,4));
    Itemad->setText(address);
    Itemfncode->setText(fncode);
    Itemdata->setText(data);
    ItemCRC->setText(CRC);
    ui->tableWidget->setItem(0,0,Itemad);
    ui->tableWidget->setItem(0,1,Itemfncode);
    ui->tableWidget->setItem(0,2,Itemdata);
    ui->tableWidget->setItem(0,3,ItemCRC);
}

void MainWindow::updateslaves(std::string id)
{
    ui->comboBox->addItem(QString::fromStdString(id));
    ui->comboBox_3->addItem(QString::fromStdString(id));

}

void MainWindow::on_pushButton_2_clicked()
{
    ui->tableWidget_3->clear();
    ui->tableWidget_3->setColumnCount(0);
    ui->tableWidget_3->setRowCount(0);
    ui->tableWidget_3->verticalHeader()->hide();
    int slavenr;
    bool is=false;
    if(scanner->gettaskhandler()->getslaves().size()>0)
    {
        for(int i=0;i<scanner->gettaskhandler()->getslaves().size();i++)
        {
            if(ui->comboBox->currentText().toLocal8Bit().constData()==scanner->gettaskhandler()->getslaves()[i].address)
            {
                slavenr=i;
                is =true;
                break;
            }
        }
    }

    ui->tableWidget_3->insertColumn(0);
    ui->tableWidget_3->setHorizontalHeaderItem(0,new QTableWidgetItem("Address"));
    int rowcount = ui->lineEdit_4->text().toInt();
    int columncount = ui->lineEdit_3->text().toInt();
    for(int i=1;i<=rowcount;i++)
    {
        ui->tableWidget_3->insertColumn(i);
        ui->tableWidget_3->setHorizontalHeaderItem(i,new QTableWidgetItem("Value"));
    }
    for(int i=0;i<columncount;i++)
    {
        ui->tableWidget_3->insertRow(i);
    }
    if(is)
    {
        if(ui->comboBox_2->currentText()=="Holding registers")
        {
            int addsize= scanner->gettaskhandler()->getslaves()[slavenr].holdingregistersdata.size();
            for(int i=0;i<addsize;i++)
            {
                if(i==columncount)
                {
                    break;
                }

                QTableWidgetItem *address = new QTableWidgetItem();
                address->setText(QString::number(scanner->gettaskhandler()->getslaves()[slavenr].holdingregistersdata[i].nr));
                ui->tableWidget_3->setItem(i,0,address);
                int regsize=scanner->gettaskhandler()->getslaves()[slavenr].holdingregistersdata[i].reg.size();
                for(int j=0;j<regsize;j++)
                {
                    if(j==rowcount)
                    {
                        break;
                    }
                    QTableWidgetItem *item = new QTableWidgetItem(QString::number(scanner->gettaskhandler()->getslaves()[slavenr].holdingregistersdata[i].reg[j]));
                    ui->tableWidget_3->setItem(i,j+1,item);
                }
            }
        }
        else
        {
            int addsize= scanner->gettaskhandler()->getslaves()[slavenr].inputregistersdata.size();
            for(int i=0;i<addsize;i++)
            {
                if(i==columncount)
                {
                    break;
                }

                QTableWidgetItem *address = new QTableWidgetItem();
                address->setText(QString::number(scanner->gettaskhandler()->getslaves()[slavenr].inputregistersdata[i].nr));
                ui->tableWidget_3->setItem(i,0,address);
                int regsize=scanner->gettaskhandler()->getslaves()[slavenr].inputregistersdata[i].reg.size();
                for(int j=0;j<regsize;j++)
                {
                    if(j==rowcount)
                    {
                        break;
                    }
                    QTableWidgetItem *item = new QTableWidgetItem(QString::number(scanner->gettaskhandler()->getslaves()[slavenr].inputregistersdata[i].reg[j]));
                    ui->tableWidget_3->setItem(i,j+1,item);
                }
            }

        }
    }



}

void MainWindow::on_pushButton_3_clicked()
{
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setColumnCount(0);
    ui->tableWidget_2->setRowCount(0);
    ui->tableWidget_4->clear();
    ui->tableWidget_4->setColumnCount(0);
    ui->tableWidget_4->setRowCount(0);
    int slavenr=0;
    for(int i=0;i<scanner->gettaskhandler()->getslaves().size();i++)
    {
        if(ui->comboBox->currentText().toLocal8Bit().constData()==scanner->gettaskhandler()->getslaves()[i].address)
        {
            slavenr=i;
            break;
        }
    }
    if(scanner->getmode()==2)
    {
        if(scanner->gettaskhandler()->getslaves()[slavenr].holdingregistersdata.size()>0)
        {
            ui->tableWidget_2->insertColumn(0);
            ui->tableWidget_2->setHorizontalHeaderItem(0,new QTableWidgetItem("Address"));
            ui->tableWidget_2->insertColumn(1);
            ui->tableWidget_2->setHorizontalHeaderItem(1,new QTableWidgetItem("Modify register"));
            ui->tableWidget_2->insertColumn(2);
            ui->tableWidget_2->setHorizontalHeaderItem(2,new QTableWidgetItem("Block register"));
            int count = ui->lineEdit_5->text().toInt();
            for(int i=0;i<count;i++)
            {
                ui->tableWidget_2->insertRow(i);
            }

            for(int i=0;i<scanner->gettaskhandler()->getslaves()[slavenr].holdingregistersdata.size();i++)
            {
                if(i ==count)
                {
                    break;
                }
                QTableWidgetItem *address = new QTableWidgetItem();
                address->setText(QString::number(scanner->gettaskhandler()->getslaves()[slavenr].holdingregistersdata[i].nr));
                ui->tableWidget_2->setItem(i,0,address);
                 QTableWidgetItem *a = new QTableWidgetItem();
                if(scanner->gettaskhandler()->getslaves()[slavenr].holdingregistersdata[i].modify==true)
                {
                    a->setText("Yes");
                }
                else
                {
                    a->setText("No");
                }
                ui->tableWidget_2->setItem(i,1,a);
                QTableWidgetItem *b = new QTableWidgetItem();
               if(scanner->gettaskhandler()->getslaves()[slavenr].holdingregistersdata[i].block==true)
               {
                   b->setText("Yes");
               }
               else
               {
                   b->setText("No");
               }
               ui->tableWidget_2->setItem(i,2,b);
            }
        }
        if(scanner->gettaskhandler()->getslaves()[slavenr].inputregistersdata.size()>0)
        {
            ui->tableWidget_4->insertColumn(0);
            ui->tableWidget_4->setHorizontalHeaderItem(0,new QTableWidgetItem("Address"));
            ui->tableWidget_4->insertColumn(1);
            ui->tableWidget_4->setHorizontalHeaderItem(1,new QTableWidgetItem("Modify register"));
            int count = ui->lineEdit_5->text().toInt();
            for(int i=0;i<count;i++)
            {
                ui->tableWidget_4->insertRow(i);
            }

            for(int i=0;i<scanner->gettaskhandler()->getslaves()[slavenr].inputregistersdata.size();i++)
            {
                if(i ==count)
                {
                    break;
                }
                QTableWidgetItem *ad = new QTableWidgetItem();
                ad->setText(QString::number(scanner->gettaskhandler()->getslaves()[slavenr].inputregistersdata[i].nr));
                ui->tableWidget_4->setItem(i,0,ad);
                 QTableWidgetItem *z = new QTableWidgetItem();
                if(scanner->gettaskhandler()->getslaves()[slavenr].inputregistersdata[i].modify==true)
                {
                    z->setText("Yes");
                }
                else
                {
                    z->setText("No");
                }
                ui->tableWidget_4->setItem(i,1,z);
            }
        }
    }
    else
    {

        if(scanner->gettaskhandler()->getslaves()[slavenr].holdingregistersdata.size()>0)
        {
            ui->tableWidget_2->insertColumn(0);
            ui->tableWidget_2->setHorizontalHeaderItem(0,new QTableWidgetItem("Address"));
            ui->tableWidget_2->insertColumn(1);
            ui->tableWidget_2->setHorizontalHeaderItem(2,new QTableWidgetItem("Entries odify status"));
            int count = ui->lineEdit_5->text().toInt();
            for(int i=0;i<count;i++)
            {
                ui->tableWidget_2->insertRow(i);
            }

            for(int i=0;i<scanner->gettaskhandler()->getslaves()[slavenr].holdingregistersdata.size();i++)
            {

                QTableWidgetItem *b = new QTableWidgetItem();
               if(scanner->gettaskhandler()->getslaves()[slavenr].holdingregistersdata[i].block==true)
               {
                   b->setText("Yes");
               }
               else
               {
                   b->setText("No");
               }
               ui->tableWidget_2->setItem(i,1,b);
            }
        }

    }
}

void MainWindow::on_pushButton_6_clicked()
{

    if(ui->comboBox->currentText()!="")
    {
        regdialog->setparams(ui->comboBox->currentText().toLocal8Bit().constData(),1);
        regdialog->show();
    }


}

void MainWindow::on_pushButton_5_clicked()
{
    if(ui->comboBox->currentText()!="")
    {
        regdialog->setparams(ui->comboBox->currentText().toLocal8Bit().constData(),2);
        regdialog->show();
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    if(ui->comboBox->currentText()!="")
    {
        regdialog->setparams(ui->comboBox->currentText().toLocal8Bit().constData(),3);
        regdialog->show();
    }

}

