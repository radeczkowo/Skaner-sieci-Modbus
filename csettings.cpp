#include "csettings.h"


CSettings::CSettings()
{

}

CSettings::Settings CSettings::getsettings() const
{
    return settings;

}

void CSettings::updatesettings(qint32 baudRate, QSerialPort::DataBits dataBits, QSerialPort::Parity parity, QSerialPort::StopBits stopBits)
{
    settings.baudRate=baudRate;
    settings.dataBits=dataBits;
    settings.parity=parity;
    settings.stopBits=stopBits;
}



