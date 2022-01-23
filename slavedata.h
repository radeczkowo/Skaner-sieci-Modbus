#ifndef SLAVEDATA_H
#define SLAVEDATA_H
#include<vector>
#include<iostream>

class slavedata
{
public:
    struct registers{
    public:
        int nr;
        std::vector<int> reg;
        bool modify =true;
        bool block = true;
    };

    slavedata(std::string address);
    void writeinputregister(int nr, int value);
    void setblockmodifyholding(int nr, bool value);
    void setmodifyholding(int nr, bool value);
    void setmodifyinput(int nr, bool value);
    void writeholdingregister(int nr, int value);
    std::string getaddress() const;
    bool getholdregmodifyinfo(int nr) const;
    bool getinregwriteinfo(int nr) const;
    bool getinputregmodifyinfo(int nr) ;
    registers newregisters(int number);
    void setvalue(int nr, bool value);

    std::string address;
    std::vector<registers>holdingregistersdata;
    std::vector<registers>inputregistersdata;
};

#endif // SLAVEDATA_H
