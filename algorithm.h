#ifndef ALGORITHM_H
#define ALGORITHM_H
#include<slavedata.h>
#include <ctime>
#include <stdlib.h>
class Algorithmm
{
public:
    Algorithmm();
    void setnr(int number);
    int returnvalue(int value, bool isvalue, std::vector<slavedata> slave, int adres, std::string slaveadres, int mode);
    int algorithm1(int value, bool isvalue, std::vector<slavedata> slave, int adres, std::string slaveadres, int mode);
    int algorithm2(int value, bool isvalue, std::vector<slavedata> slave, int adres, std::string slaveadres, int mode);


private:
    int nr;
};

#endif // ALGORITHM_H
