#ifndef DEVICE_H
#define DEVICE_H
#include<csettings.h>
#include<iostream>
#include<calculations.h>
class device : public QObject
{
    Q_OBJECT
public:
    device(CSettings *csettings);
    void openport(QString port);
    void init();
    void closeport();
    void writedata(std::string frame);
    bool isopen();
    QSerialPort *getport();


private slots:
    void readdatacontinously();
    void handleError(QSerialPort::SerialPortError error);

signals:
    void readdata(std::string frame);

private:
    calculations calc;
    CSettings * csettings;
    QSerialPort *serial;


};

#endif // DEVICE_H
