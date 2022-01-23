#ifndef TASKHANDLER_H
#define TASKHANDLER_H
#include<device.h>
#include<calculations.h>
#include<algorithm.h>

class Taskhandler:public QObject
{
    Q_OBJECT
public:
    Taskhandler();
    virtual~Taskhandler();
    virtual void readmodifier0304(std::string frame, bool action);
    virtual void writemodifier10(std::string frame, bool action);
    virtual std::string editmultipleregisters(std::string frame);
    virtual void modifyregisters0304(std::string frame);
    virtual void forcelitenonlyalldevices();
    virtual void restartalldevices();
    virtual void singleregisteredit06(std::string frame, bool action);
    virtual std::vector < slavedata > writeregisters(std::vector < slavedata > slaves, std::string frame, std::string startaddres);
    virtual bool checkframe(std::string frame);
    virtual bool blockinfo(std::string frame, std::vector < slavedata > slaves);
    void setisbusy(bool is);
    bool getisbusy() const;
    Algorithmm* getalgorithm();
    void slavesupdate(std::vector < slavedata > slaves);
    std::vector < slavedata > getslaves();
    void setregistervalue(int nt, bool value, std::string add, int mode);

signals:
    void passframe(std::string frame);
    void newslaver(std::string id);

private:
    Algorithmm* alg;
    std::vector < slavedata > slaves;
    bool isbusy;


};

#endif // TASKHANDLER_H
