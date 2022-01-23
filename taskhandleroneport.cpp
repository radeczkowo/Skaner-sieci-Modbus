#include "taskhandleroneport.h"

taskhandleroneport::taskhandleroneport(device * slave)
{
    this->slave=slave;

}

void taskhandleroneport::readmodifier0304(std::string frame, bool action)
{
    if(frame.length()%4==0)
    {
        startaddres=frame.substr(4,4);
    }

    if(action==true)
    {
        if(frame.length()%4==0)
        {
            slave->writedata(editmultipleregisters(frame));
        }

    }
    else
    {
        if((frame.length()%4!=0))
        {
            std::cout << "elo" << std::endl;
            slavesupdate(writeregisters(getslaves(),frame, frame.substr(4,4)));
        }
    }

}

void taskhandleroneport::writemodifier10(std::string frame, bool action)
{
    slavesupdate(writeregisters(getslaves(),frame, frame.substr(4,4)));
    if(action)
    {
    if(frame.size()!=16&&checkframe(frame))
    {
        if(blockinfo(frame,getslaves())&&action)
        {
            int hextoint=0;
            int size;
            std::string newframe;
            int start;
            newframe = frame.substr(0,12)+calc.CRCcalculator(frame.substr(0,12));
            slave->writedata(newframe);
            newframe = frame.substr(0,14);
            size = calc.hexstringtoint(frame.substr(12,2));
            start = 14;
            for(int i=0;i<size;i=i+2)
            {
                std::string value =frame.substr(start+(i*2),4);
                //hextoint=getalgorithm()->returnvalue(calc.hexstringtoint(value),true,getslaves(),0);
                std::stringstream stream;
                stream << std::setfill ('0') << std::setw(4)<< std::hex << hextoint;
                std::string result( stream.str() );
               newframe+=result;
            }
           std::this_thread::sleep_for (std::chrono::milliseconds(5));
           slave->writedata(newframe+calc.CRCcalculator(newframe));
        }
        }
    }

}

void taskhandleroneport::forcelistenonly(std::string adres)
{
    std::this_thread::sleep_for (std::chrono::milliseconds(3));
    adres+="0800040000";
    adres+=calc.CRCcalculator(adres);
    slave->writedata(adres);

}

void taskhandleroneport::restartcommunication(std::string adres)
{
    std::this_thread::sleep_for (std::chrono::milliseconds(3));
    adres+="0800010000";
    adres+=calc.CRCcalculator(adres);
    slave->writedata(adres);
}

void taskhandleroneport::singleregisteredit06(std::string frame, bool action)
{
    slavesupdate(writeregisters(getslaves(),frame, frame.substr(4,4)));
    if(action)
    {
    if(frame.size()!=16&&checkframe(frame))
    {
        if(blockinfo(frame,getslaves())&&action)
        {
            int hextoint=0;
            std::string newframe;
            slave->writedata(frame);
            newframe = frame.substr(0,8);
            //hextoint=getalgorithm()->returnvalue(calc.hexstringtoint(frame.substr(8,4)),true,getslaves(),0);
            std::stringstream stream;
            stream << std::setfill ('0') << std::setw(4)<< std::hex << hextoint;
            std::string result( stream.str() );
            newframe+=result;
           std::this_thread::sleep_for (std::chrono::milliseconds(5));
           slave->writedata(newframe+calc.CRCcalculator(newframe));
        }
        }
    }
}

std::string taskhandleroneport::editmultipleregisters(std::string frame)
{
    int hextoint=0;
    int size=0;
    std::string newframe;
    newframe = frame.substr(0,4);
    size = calc.hexstringtoint(frame.substr(8,4))*2;
    std::stringstream ss;
    ss << std::setfill ('0') << std::setw(2)<< std::hex << size;
    std::string res( ss.str() );
    newframe+=res;
    for(int i=0;i<size;i=i+2)
    {
        std::string value ="";
        //hextoint=getalgorithm()->returnvalue(calc.hexstringtoint(value),false,getslaves(),0);
        std::stringstream stream;
        stream << std::setfill ('0') << std::setw(4)<< std::hex << hextoint;
        std::string result( stream.str() );
       newframe+=result;
    }
    return newframe+calc.CRCcalculator(newframe);
}

std::vector<slavedata> taskhandleroneport::writeregisters(std::vector<slavedata> slaves, std::string frame, std::string startaddres)
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
            if(6+6+4*i/2>frame.size()-5)
            {
                break;
            }
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
    return slaves;
}

void taskhandleroneport::forcelitenonlyalldevices()
{
    setisbusy(true);
    for(int i=1;i<247;i++)
    {
        std::stringstream stream;
        stream << std::setfill ('0') << std::setw(2)<< std::hex << i;
        std::string result( stream.str() );
        forcelistenonly(result);
    }
    setisbusy(false);
}

void taskhandleroneport::restartalldevices()
{
    setisbusy(true);
    for(int i=0;i<247;i++)
    {
        std::stringstream stream;
        stream << std::setfill ('0') << std::setw(2)<< std::hex << i;
        std::string result( stream.str() );
        restartcommunication(result);
    }
    setisbusy(false);

}

bool taskhandleroneport::checkframe(std::string frame)
{
    if(frame.substr(2,2)== "03" || frame.substr(2,2)== "04")
    {
        int number = calc.hexstringtoint(frame.substr(4,2));
        if((int)frame.size()<(10+number*2))
        {
            return false;
        }
    }
    else if(frame.substr(2,2)== "10")
    {
        int number = calc.hexstringtoint(frame.substr(12,2));
        if((int)frame.size()<(18+number*2))
        {
            return false;
        }
    }
    else if(frame.substr(2,2)== "06")
    {
        if((int)frame.size()!=16)
        {
            return false;
        }
    }
    return true;
}

bool taskhandleroneport::blockinfo(std::string frame, std::vector<slavedata> slaves)
{
    int firstadd=0;
    int amount =0;
    bool is = false;
    int slavenr=0;
    for (size_t i=0; i < slaves.size(); i++)
    {
        if(slaves[i].getaddress()==frame.substr(0,2))
        {
            is = false;
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
        for(int i =0;i<amount;i++)
        {
            if(slaves[slavenr].getinregwriteinfo(firstadd + i)==false)
            {
                return false;

            }
        }
    }

    return true;
}

