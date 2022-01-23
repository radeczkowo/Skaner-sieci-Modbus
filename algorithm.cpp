#include "algorithm.h"


Algorithmm::Algorithmm()
{
    nr=2;
    srand( time( NULL ) );

}
void Algorithmm::setnr(int number)
{
    nr=number;
}

int Algorithmm::returnvalue(int value, bool isvalue, std::vector<slavedata> slave, int adres, std::string slaveadres, int mode)
{
    //int ret=0;
    switch(nr)
    {
        case 1:
        return algorithm1(value,isvalue,slave,adres, slaveadres, mode);

        case 2:
        return algorithm2(value,isvalue,slave,adres, slaveadres, mode);

    }
    return 0;
}

int Algorithmm::algorithm1(int value, bool isvalue, std::vector<slavedata> slave, int adres, std::string slaveadres, int mode)
{
    if(isvalue)
    {
        int x = 80 + int((120-80+1) * rand()/(RAND_MAX+1.0));
        return (int)(value* x/100);
    }
    else
    {
        return 0;

    }

}

int Algorithmm::algorithm2(int value, bool isvalue, std::vector<slavedata> slave, int adres, std::string slaveadres, int mode)
{
    int slavenr;
    int nr;
    int size=0;
    bool isrregadres=false;
    if(slave.size()>0)
    {
        for(int i=0;i<slave.size();i++)
        {
            if(slaveadres==slave[i].address)
            {
                slavenr=i;
                break;
            }
        }
        if(mode==1)
        {
            if(slave[slavenr].holdingregistersdata.size()>0)
            {
                for(int i=0; i<slave[slavenr].holdingregistersdata.size(); i++)
                {
                    if(adres==slave[slavenr].holdingregistersdata[i].nr)
                    {
                        nr=i;
                        isrregadres=true;
                        break;
                    }
                }
                if(isrregadres)
                {
                    if(slave[slavenr].holdingregistersdata[nr].reg.size()>0)
                    {
                        int suma=0;
                        if(slave[slavenr].holdingregistersdata[nr].reg.size()>10)
                        {
                            size=10;
                            for(int i=0;i<size;i++)
                            {
                                 int x = 0 + int((slave[slavenr].holdingregistersdata[nr].reg.size()-1-0+1) * rand()/(RAND_MAX+1.0));
                                 std::cout<<x << std::endl;
                                 suma+=slave[slavenr].holdingregistersdata[nr].reg[x];
                            }
                           return (int)(suma/size);
                        }
                        else
                        {
                            size=slave[slavenr].holdingregistersdata[nr].reg.size();
                            for(int i=0;i<size;i++)
                            {
                                 int x = 0 + int((size-1-0+1) * rand()/(RAND_MAX+1.0));
                                 suma+=slave[slavenr].holdingregistersdata[nr].reg[x];
                            }
                           return (int)(suma/size);
                        }
                    }
                    else
                    {
                        return algorithm1(value,isvalue,slave,adres, slaveadres, mode);;
                    }

                }
                else
                {
                    return algorithm1(value,isvalue,slave,adres, slaveadres, mode);;
                }
            }
            else
            {
                return algorithm1(value,isvalue,slave,adres, slaveadres, mode);;
            }
        }
        else
        {
            if(slave[slavenr].inputregistersdata.size()>0)
            {
                for(int i=0; i<slave[slavenr].inputregistersdata.size(); i++)
                {
                    if(adres==slave[slavenr].inputregistersdata[i].nr)
                    {
                        nr=i;
                        isrregadres=true;
                        break;
                    }
                }
                if(isrregadres)
                {
                    if(slave[slavenr].inputregistersdata[nr].reg.size()>0)
                    {
                        int suma=0;
                        if(slave[slavenr].inputregistersdata[nr].reg.size()>10)
                        {
                            size=10;
                            for(int i=0;i<size;i++)
                            {
                                 int x = 0 + int((slave[slavenr].inputregistersdata[nr].reg.size()-1-0+1) * rand()/(RAND_MAX+1.0));
                                 suma+=slave[slavenr].inputregistersdata[nr].reg[x];
                            }
                           return (int)(suma/size);
                        }
                        else
                        {
                            size=slave[slavenr].inputregistersdata[nr].reg.size();
                            for(int i=0;i<size;i++)
                            {
                                 int x = 0 + int((size-1-0+1) * rand()/(RAND_MAX+1.0));
                                 suma+=slave[slavenr].inputregistersdata[nr].reg[x];
                            }
                           return (int)(suma/size);
                        }
                    }
                    else
                    {
                        return algorithm1(value,isvalue,slave,adres, slaveadres, mode);;
                    }

                }
                else
                {
                    return algorithm1(value,isvalue,slave,adres, slaveadres, mode);;
                }
            }
            else
            {
                return algorithm1(value,isvalue,slave,adres, slaveadres, mode);;
            }
        }

    }
    else
    {
        return algorithm1(value,isvalue,slave,adres, slaveadres, mode);;
    }

    return algorithm1(value,isvalue,slave,adres, slaveadres, mode);;

}
