#include "calculations.h"

calculations::calculations()
{

}

std::string calculations::bytearraytostring(QByteArray array)
{
    QString DataAsString = array.toHex();
    return DataAsString.toLocal8Bit().constData();

}

QByteArray calculations::stringtobytearray(std::string string)
{
    QString qstrs = QString::fromStdString(string);
    return QByteArray::fromHex(qstrs.toLatin1());

}

int calculations::hexstringtoint(std::string str)
{
    char* chararray;
    chararray= &str[0];

    return (int)strtol(chararray, NULL, 16);
}

std::string calculations::CRCcalculator(std::string data)
{

    uint16_t crc = 0xFFFF;
    QByteArray array2 = stringtobytearray(data);
    const unsigned char* begin = reinterpret_cast<unsigned char*>(array2.data());
    for (int pos = 0; pos < array2.size(); pos++)

    {
    crc ^= (uint16_t)begin[pos];

    for (int i = 8; i != 0; i--) {
      if ((crc & 0x0001) != 0) {
        crc >>= 1;
        crc ^= 0xA001;
      }
      else
        crc >>= 1;
      }
    }

   char *str = (char *) &crc;
   QByteArray w =QByteArray::fromRawData(str, strlen(str));
   std::string s = bytearraytostring(w);
   s = s.substr(0,4);

   return s;
}






