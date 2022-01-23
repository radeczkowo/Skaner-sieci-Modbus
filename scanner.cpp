#include "scanner.h"

Scanner::Scanner()
{
    mode        = 2;
    connected   = false;
    csettings   = new CSettings();
    master      = new device(csettings);
    slave       = new device(csettings);
    modifying   = false;
    blocking    = false;

    init();
}



void Scanner::init()
{
    connect(slave, &device::readdata, this, &Scanner::slaveframe);
}

void Scanner::openports(QString p1, QString p2)
{
      if(mode==2)
        {
            slave->openport(p1);
            master->openport(p2);
            if(master->isopen()&&slave->isopen())
            {
                connected=true;
                taskhandler = new Taskhandlertwoports(master, slave);
                connect(taskhandler, &Taskhandler::passframe, this, &Scanner::taskhandlerframe);
                connect(taskhandler, &Taskhandler::newslaver, this, &Scanner::receiveslavee);
            }
            else
                connected=false;
        }
        if(mode==1)
        {
            slave->openport(p2);
            if(slave->isopen())
            {
                taskhandler = new taskhandleroneport(slave);
                connected=true;
                connect(taskhandler, &Taskhandler::passframe, this, &Scanner::taskhandlerframe);
                connect(taskhandler, &Taskhandler::newslaver, this, &Scanner::receiveslavee);
            }
            else
                connected=false;
        }

}

void Scanner::closeports()
{
    if(mode==2)
    {
        slave->closeport();
        master->closeport();

    }
    if(mode==1)
    {
        slave->closeport();
    }
    connected =false;
}


void Scanner::setmode(int modnr)
{
    mode=modnr;
}

int Scanner::getmode() const
{
    return mode;
}

bool Scanner::getconnected() const
{
    return connected;
}

bool Scanner::getmodifying() const
{
    return modifying;
}

void Scanner::setblocking(bool value)
{
    blocking = value;
}

void Scanner::setmodifying(bool value)
{
    modifying = value;
}    

Taskhandler *Scanner::gettaskhandler() const
{
    return taskhandler;
}

CSettings *Scanner::getsettings() const
{
    return csettings;
}

void Scanner::slaveframe(std::string frame)
{
    if(!taskhandler->getisbusy())
    {

        if(mode==2)
        {
            if(frame.substr(2,2)== "03" || frame.substr(2,2)== "04")
            {
                taskhandler->readmodifier0304(frame, modifying);

            }
            else if(frame.substr(2,2)== "10")
            {
                taskhandler->writemodifier10(frame,blocking);
            }
            else if(frame.substr(2,2)== "06")
            {
                taskhandler->singleregisteredit06(frame,blocking);
            }
        }
        else
        {
            if(frame.substr(2,2)== "03" || frame.substr(2,2)== "04")
            {
                taskhandler->readmodifier0304(frame, modifying);
            }
            else if(frame.substr(2,2)== "10")
            {
                taskhandler->writemodifier10(frame, modifying);
            }
       }
    }
    else
    {
        std::cout << "pelo" << std::endl;
    }
}
void Scanner::taskhandlerframe(std::string frame)
{
    emit passframe(frame);
}

void Scanner::receiveslavee(std::string id)
{
    emit passslave(id);
}
