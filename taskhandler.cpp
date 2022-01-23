#include "taskhandler.h"


Taskhandler::Taskhandler()
{
    alg=new Algorithmm();
}

Taskhandler::~Taskhandler()
{

}

void Taskhandler::readmodifier0304(std::string frame, bool action)
{

}

void Taskhandler::writemodifier10(std::string frame, bool action)
{

}

std::string Taskhandler::editmultipleregisters(std::string frame)
{

}

void Taskhandler::modifyregisters0304(std::string frame)
{

}

void Taskhandler::forcelitenonlyalldevices()
{

}

void Taskhandler::restartalldevices()
{

}

void Taskhandler::singleregisteredit06(std::string frame, bool action)
{

}

std::vector<slavedata> Taskhandler::writeregisters(std::vector<slavedata> slaves, std::string frame, std::string startaddres)
{

}

bool Taskhandler::checkframe(std::string frame)
{

}

bool Taskhandler::blockinfo(std::string frame, std::vector<slavedata> slaves)
{

}

void Taskhandler::setisbusy(bool is)
{
    isbusy=is;
}

bool Taskhandler::getisbusy() const
{
    return isbusy;
}

Algorithmm *Taskhandler::getalgorithm()
{
    return alg;
}

void Taskhandler::slavesupdate(std::vector<slavedata> slaves)
{
    this->slaves=slaves;
}

std::vector<slavedata> Taskhandler::getslaves()
{
    return slaves;
}

void Taskhandler::setregistervalue(int nt, bool value, std::string add, int mode)
{
    int slavenr;
    for(int i=0;i<slaves.size();i++)
    {
        if(add==slaves[i].address)
        {
            slavenr=i;
            break;
        }
    }
    if(mode==1)
    {
        slaves[slavenr].setmodifyholding(nt,value);
    }
    else if(mode==2)
    {
        slaves[slavenr].setmodifyinput(nt,value);

    }
    else if(mode==3)
    {
        slaves[slavenr].setblockmodifyholding(nt,value);
    }

}
