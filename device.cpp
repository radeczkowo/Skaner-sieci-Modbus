#include "device.h"

device::device(CSettings *csettings)
{
    this->csettings= csettings;
    serial = new QSerialPort();
    init();

}

void device::openport(QString port)
{
    serial->setPortName(port);
    serial->setBaudRate(csettings->getsettings().baudRate);
    serial->setDataBits(csettings->getsettings().dataBits);
    serial->setParity(csettings->getsettings().parity);
    serial->setStopBits(csettings->getsettings().stopBits);
    serial->setFlowControl(csettings->getsettings().flowControl);
    if (serial->open(QIODevice::ReadWrite)) {
       std::cout<< "dziala " << std::endl;
    } else {
        std::cout<< "Nie dziala " << std::endl;
    }

}

void device::init()
{
    connect(serial, &QSerialPort::errorOccurred, this, &device::handleError);
    connect(serial, &QSerialPort::readyRead, this, &device::readdatacontinously);
}

void device::readdatacontinously()
{
    QByteArray data = serial->readAll();
    std::string frame = calc.bytearraytostring(data);
    if(frame.length()>=12)
    {
        emit readdata(frame);
    }
}

void device::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        closeport();
    }
}

void device::closeport()
{
    if (serial->isOpen())
        serial->close();

}

void device::writedata(std::string frame)
{
    serial->write(calc.stringtobytearray(frame));
    serial->waitForBytesWritten(60);

}

bool device::isopen()
{
    return serial->isOpen();
}

QSerialPort* device::getport()
{
    return serial;
}
