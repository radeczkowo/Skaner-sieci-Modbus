#include "setdialog.h"
#include "ui_setdialog.h"

Setdialog::Setdialog(QWidget *parent, Scanner * scanner) :
    QDialog(parent),
    ui(new Ui::Setdialog)
{
    ui->setupUi(this);
    this->scanner=scanner;
    ui->comboBox->setCurrentIndex(1);
    ui->comboBox_2->setCurrentText("19200");
    ui->comboBox_3->setCurrentText("8");
    ui->comboBox_3->setCurrentText("1");
}

Setdialog::~Setdialog()
{
    delete ui;
}

void Setdialog::on_pushButton_clicked()
{
    qint32 baudRate =  19200;
    QSerialPort::DataBits dataBits =  QSerialPort::Data8;
    QSerialPort::Parity parity = QSerialPort::EvenParity;
    QSerialPort::StopBits stopBits =  QSerialPort::OneStop;

    if(ui->comboBox->currentText()=="Even")
        parity = QSerialPort::EvenParity;
    else if(ui->comboBox->currentText()=="No")
        parity = QSerialPort::NoParity;
    else if(ui->comboBox->currentText()=="Odd")
        parity = QSerialPort::OddParity;

    if(ui->comboBox_2->currentText().toInt()==1200)
        baudRate=1200;
    else if(ui->comboBox_2->currentText().toInt()==2400)
        baudRate=2400;
    else if(ui->comboBox_2->currentText().toInt()==4800)
        baudRate=4800;
    else if(ui->comboBox_2->currentText().toInt()==9600)
        baudRate=9600;
    else if(ui->comboBox_2->currentText().toInt()==19200)
        baudRate=19200;
    else if(ui->comboBox_2->currentText().toInt()==38400)
        baudRate=38400;
    else if(ui->comboBox_2->currentText().toInt()==57600)
        baudRate=57600;
    else if(ui->comboBox_2->currentText().toInt()==115200)
        baudRate=115200;

    if(ui->comboBox_3->currentText().toInt()==8)
        dataBits=QSerialPort::Data8;

    if(ui->comboBox_4->currentText().toInt()==1)
        stopBits =  QSerialPort::OneStop;
    else if(ui->comboBox_4->currentText().toInt()==2)
        stopBits =  QSerialPort::TwoStop;
    else if(ui->comboBox_4->currentText().toInt()==3)
        stopBits =  QSerialPort::OneAndHalfStop;

    scanner->getsettings()->updatesettings(baudRate,dataBits,parity,stopBits);
    hide();

}
