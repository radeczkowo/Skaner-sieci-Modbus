#ifndef CSETTINGS_H
#define CSETTINGS_H

#include <QtSerialBus/qtserialbusglobal.h>
#if QT_CONFIG(modbus_serialport)
#include <QSerialPort>
#endif

class CSettings
{
public:
    struct Settings {
        qint32 baudRate =  19200;
        QSerialPort::DataBits dataBits =  QSerialPort::Data8;
        QSerialPort::Parity parity = QSerialPort::EvenParity;
        QSerialPort::StopBits stopBits =  QSerialPort::OneStop;
        QSerialPort::FlowControl flowControl =  QSerialPort::NoFlowControl;
    };

    ~CSettings();
     CSettings();
     Settings getsettings() const;
     void updatesettings(qint32 baudRate, QSerialPort::DataBits dataBits, QSerialPort::Parity parity, QSerialPort::StopBits stopBits);
private:
    Settings settings;
};

#endif // CSETTINGS_H
