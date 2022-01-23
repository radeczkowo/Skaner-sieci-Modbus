#include "taskhandlertwoports.h"

Taskhandlertwoports::Taskhandlertwoports(device* master, device* slave)
{
    startaddres="0000";
    this->master=master;
    this->slave=slave;
    retries= 2;
    timeout = 1000;
    specaction=false;
    timer= new QTimer();
    timer->setSingleShot(true);
    timer->setInterval(timeout);
    helpframe="";
    mode=0;
    init();
}

void Taskhandlertwoports::init()
{
    connect(timer, SIGNAL(timeout()), &loop, SLOT(quit()));
    connect(this, SIGNAL(finishedresponse()), &loop, SLOT(quit()));
    connect(master, &device::readdata, this, &Taskhandlertwoports::modifyregisters0304);
    connect(master, &device::readdata, this, &Taskhandlertwoports::slavewriteresponsehadler);
}

void Taskhandlertwoports::readmodifier0304(std::string frame, bool action)
{
    mode=0;
    emit passframe(frame);
    if(action&&blockinfo(frame,getslaves()))
    {
        specaction=true;
    }
    else
        specaction=false;
    startaddres=frame.substr(4,4);
    sendtoslave(frame);


}

void Taskhandlertwoports::modifyregisters0304(std::string frame)
{
    if(mode==0)
    {
        updatehelpframe(frame);
        setisbusy(true);
       if(frame.substr(2,2)== "03" || frame.substr(2,2)== "04")
       {
             if(checkframe(frame))
             {
               emit passframe(frame);
               slavesupdate(writeregisters(getslaves(),frame, startaddres));
               if(specaction)
               {
                   slave->writedata(editmultipleregisters(frame));
               }
               else
                   slave->writedata(frame);
               helpframe="";
           }
       }
       else if((helpframe.substr(2,2)== "03" || helpframe.substr(2,2)== "04"))
       {
               if(checkframe(helpframe))
               {
                   emit passframe(helpframe);
                   slavesupdate(writeregisters(getslaves(),helpframe, startaddres));
                   if(specaction)
                   {
                       slave->writedata(editmultipleregisters(helpframe));
                   }
                   else
                       slave->writedata(helpframe);
                 helpframe="";
               }
       }
       setisbusy(false);
       emit finishedresponse();
    }

}
void Taskhandlertwoports::slavewriteresponsehadler(std::string frame)
{
    slave->writedata(frame);
    emit finishedresponse();

}
void Taskhandlertwoports::sendtoslave(std::string frame)
{
    if(mode==0)
    {
        if(getisbusy()==false)
        {
            helpframe="";
            master->writedata(frame);
        }
    }
    else
    {
        master->writedata(frame);
    }
}

void Taskhandlertwoports::updatehelpframe(std::string f)
{
    helpframe=helpframe+f;
}

void Taskhandlertwoports::writemodifier10(std::string frame, bool action)
{
    mode=1;
    emit passframe(frame);
    startaddres=frame.substr(4,4);
    slavesupdate(writeregisters(getslaves(),frame, startaddres));
    if(action&&blockinfo(frame,getslaves()))
    {
        std::string newframe = frame.substr(0,12)+calc.CRCcalculator(frame.substr(0,12));
        slave->writedata(newframe);
    }
    else
    {
        sendtoslave(frame);
    }

}

std::string Taskhandlertwoports::editmultipleregisters(std::string frame)
{
    int mod=0;
    int hextoint=0;
    int address;
    if(frame.substr(2,2)=="03")
    {
        mod=1;
    }
    else if(frame.substr(2,2)=="04")
    {
        mod=2;
    }
    int size;
    std::string newframe;
    int start;
    newframe = frame.substr(0,6);
    size = calc.hexstringtoint(frame.substr(4,2));
    start=6;
    for(int i=0;i<size;i=i+2)
    {
        address=calc.hexstringtoint(startaddres)+i/2;
        std::string value =frame.substr(start+(i*2),4);
        hextoint=getalgorithm()->returnvalue(calc.hexstringtoint(value),true,getslaves(),address, frame.substr(0,2),mod);
        std::stringstream stream;
        stream << std::setfill ('0') << std::setw(4)<< std::hex << hextoint;
        std::string result( stream.str() );
       newframe+=result;
    }
    return newframe+calc.CRCcalculator(newframe);
}

void Taskhandlertwoports::singleregisteredit06(std::string frame, bool action)
{
    mode=1;
    startaddres=frame.substr(4,4);
    slavesupdate(writeregisters(getslaves(),frame, startaddres));
    if(action&&blockinfo(frame,getslaves()))
    {
        slave->writedata(frame);
    }
    else
    {
        sendtoslave(frame);
    }
}

bool Taskhandlertwoports::checkframe(std::string frame)
{
    int number = calc.hexstringtoint(frame.substr(4,2));
    if((int)frame.size()<(10+number*2))
    {
        return false;
    }
    return true;

}

std::vector<slavedata> Taskhandlertwoports::writeregisters(std::vector<slavedata> slaves, std::string frame, std::string startaddres)
{
    bool is = false;
    int slavenr=0;
    for (size_t i=0; i < slaves.size(); i++)
    {
        if(slaves[i].getaddress()==frame.substr(0,2))
        {
            is = true;
            slavenr=i;
            break;
        }
    }
    if(is == false)
    {
        slavenr=slaves.size();
        emit newslaver(frame.substr(0,2));
        slaves.push_back(slavedata(frame.substr(0,2)));
    }
    int firstaddres = calc.hexstringtoint(startaddres);
    int currentaddres = 0;
    if(frame.substr(2,2)=="03")
    {
         int amountofreg = calc.hexstringtoint(frame.substr(4,2));
        for(int i=0; i<amountofreg;i=i+2)
        {
            currentaddres= calc.hexstringtoint(frame.substr(6+4*i/2,4));
            slaves[slavenr].writeholdingregister(firstaddres+i/2,currentaddres);
        }
    }
    else if(frame.substr(2,2)=="04")
    {
        int amountofreg = calc.hexstringtoint(frame.substr(4,2));
        for(int i=0; i<amountofreg;i=i+2)
        {

            currentaddres= calc.hexstringtoint(frame.substr(6+4*i/2,4));
            slaves[slavenr].writeinputregister(firstaddres+i/2,currentaddres);
        }
    }
    else if(frame.substr(2,2)=="10")
    {
        int amountofreg = calc.hexstringtoint(frame.substr(12,2));
        for(int i=0; i<amountofreg;i=i+2)
        {
            currentaddres= calc.hexstringtoint(frame.substr(14+4*i/2,4));
            slaves[slavenr].writeholdingregister(firstaddres+i/2,currentaddres);
        }
    }
    else if(frame.substr(2,2)=="06")
    {
        firstaddres = calc.hexstringtoint(frame.substr(4,4));
        currentaddres= calc.hexstringtoint(frame.substr(8,4));
        slaves[slavenr].writeholdingregister(firstaddres,currentaddres);
    }
    return slaves;
}

bool Taskhandlertwoports::blockinfo(std::string frame, std::vector<slavedata> slaves)
{
    int firstadd=0;
    int amount =0;
    bool is = false;
    int slavenr=0;
    if(slaves.size()==0)
    {
        return true;
    }
    for (size_t i=0; i < slaves.size(); i++)
    {
        if(slaves[i].getaddress()==frame.substr(0,2))
        {
            is = true;
            slavenr=i;
        }
    }
    if(is == false)
    {
        return true;       
    }
    else
    {
        firstadd=calc.hexstringtoint(frame.substr(4,4));
        amount=calc.hexstringtoint(frame.substr(8,4));

        if(frame.substr(2,2)=="03")
        {
            for(int j =0;j <= amount;j++)
            {
                if(slaves[slavenr].getholdregmodifyinfo(firstadd + j)==false)
                {
                   return false;
                }
            }
        }
        else if(frame.substr(2,2)=="10")
        {
            for(int j =0;j<amount;j++)
            {
                if(slaves[slavenr].getinregwriteinfo(firstadd + j)==false)
                {
                    return false;

                }
            }
        }
        else if(frame.substr(2,2)=="04")
        {

            for(int j =0;j<amount;j++)
            {
                if(slaves[slavenr].getinputregmodifyinfo(firstadd + j)==false)
                {
                    return false;

                }
            }
        }
    }

    return true;
}






