#include "slavedata.h"

slavedata::slavedata(std::string address)
{
    this->address=address;
}

void slavedata::writeinputregister(int nr, int value)
{
    bool is = false;
    for(unsigned int i=0;i<inputregistersdata.size();i++)
    {

        if(inputregistersdata[i].nr==nr)
        {
            is=true;
            inputregistersdata[i].reg.push_back(value);
            break;
        }
    }
    if(!is)
    {
        inputregistersdata.push_back(newregisters(nr));
        inputregistersdata[inputregistersdata.size()-1].reg.push_back(value);
    }
}

void slavedata::setblockmodifyholding( int nr, bool value)
{
    bool is =false;
    if(holdingregistersdata.size()==0)
    {
        holdingregistersdata.push_back(newregisters(nr));
        holdingregistersdata[holdingregistersdata.size()-1].block=value;
        is =true;
    }
    else
    {
        for(int i=0;i<holdingregistersdata.size();i++)
        {
            if(nr==holdingregistersdata[i].nr)
            {
                holdingregistersdata[i].block=value;
                is=true;
                break;
            }
        }
    }
    if(!is)
    {
        holdingregistersdata.push_back(newregisters(nr));
        holdingregistersdata[holdingregistersdata.size()-1].block=value;
    }

}

void slavedata::setmodifyholding(int nr, bool value)
{
    bool is =false;
    if(holdingregistersdata.size()==0)
    {
        holdingregistersdata.push_back(newregisters(nr));
        holdingregistersdata.at(holdingregistersdata.size()-1).modify=value;
        is =true;
    }
    else
    {
        for(int i=0;i<holdingregistersdata.size();i++)
        {
            if(nr==holdingregistersdata[i].nr)
            {
                holdingregistersdata[i].modify=value;
                is=true;
                break;
            }
        }
    }
    if(!is)
    {
        holdingregistersdata.push_back(newregisters(nr));
        holdingregistersdata[holdingregistersdata.size()-1].modify=value;
    }

}

void slavedata::setmodifyinput(int nr, bool value)
{
    bool is =false;
    if(inputregistersdata.size()==0)
    {
        inputregistersdata.push_back(newregisters(nr));
        inputregistersdata[inputregistersdata.size()-1].modify=value;
        is =true;
    }
    else
    {
        for(int i=0;i<inputregistersdata.size();i++)
        {
            if(nr==inputregistersdata[i].nr)
            {
                inputregistersdata[i].modify=value;
                is=true;
                break;
            }
        }
    }
    if(!is)
    {
        inputregistersdata.push_back(newregisters(nr));
        inputregistersdata[inputregistersdata.size()-1].modify=value;
    }
}

void slavedata::writeholdingregister(int nr, int value)
{
    bool is = false;
    for(unsigned int i=0;i<holdingregistersdata.size();i++)
    {

        if(holdingregistersdata[i].nr==nr)
        {
            is=true;
            holdingregistersdata[i].reg.push_back(value);
            break;
        }
    }
    if(!is)
    {
        holdingregistersdata.push_back(newregisters(nr));
        holdingregistersdata[holdingregistersdata.size()-1].reg.push_back(value);
    }

}

std::string slavedata::getaddress() const
{
    return address;
}

bool slavedata::getinregwriteinfo(int nr) const
{
    for(unsigned int i=0;i<inputregistersdata.size();i++)
    {

        if(inputregistersdata[i].nr==nr)
        {
            return inputregistersdata[i].block;
        }
    }
        return true;

}

bool slavedata::getinputregmodifyinfo(int nr)
{

    for(unsigned int i=0;i<inputregistersdata.size();i++)
    {

        if(inputregistersdata[i].nr==nr)
        {
            return inputregistersdata[i].modify;
        }
    }
        return true;

}

bool slavedata::getholdregmodifyinfo(int nr) const
{
    for(unsigned int i=0;i<holdingregistersdata.size();i++)
    {

        if(holdingregistersdata[i].nr==nr)
        {
            return holdingregistersdata[i].modify;
        }
    }
        return true;
}

slavedata::registers slavedata::newregisters(int number)
{
    registers reg;
    reg.nr=number;
    reg.modify=true;
    reg.block=true;
    return reg;
}




