#ifndef TASKHANDLERONEPORT_H
#define TASKHANDLERONEPORT_H
#include<taskhandler.h>
#include <QTimer>
#include <QEventLoop>
#include <thread>
#include <chrono>

class taskhandleroneport : public Taskhandler
{
    Q_OBJECT
public:
    taskhandleroneport(device*slave);
    void readmodifier0304(std::string frame, bool action);
    void writemodifier10(std::string frame, bool action);
    void forcelistenonly(std::string adres);
    void restartcommunication(std::string adres);
    virtual void singleregisteredit06(std::string frame, bool action);
    std::string editmultipleregisters(std::string frame);
    std::vector < slavedata > writeregisters(std::vector < slavedata > slaves, std::string frame, std::string startaddres);
    void forcelitenonlyalldevices();
    void restartalldevices();
    bool checkframe(std::string frame);
    bool blockinfo(std::string frame, std::vector<slavedata> slaves);


private:
    QTimer* timer;
    device* master;
    device* slave;
    calculations calc;
    QEventLoop loop;
    std::string startaddres;

};

#endif // TASKHANDLERONEPORT_H
