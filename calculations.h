#ifndef CALCULATIONS_H
#define CALCULATIONS_H
#include<iostream>
#include<QByteArray>
#include<QString>
#include<cstdlib>
#include<sstream>
#include<iomanip>
#include<QIODevice>




class calculations
{
public:
    calculations();
    std::string bytearraytostring(QByteArray array);
    QByteArray stringtobytearray(std::string string);
    int hexstringtoint(std::string str);   
    std::string CRCcalculator(std::string data);
private:


};

#endif // CALCULATIONS_H
