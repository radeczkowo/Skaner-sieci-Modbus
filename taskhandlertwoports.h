#ifndef TASKHANDLERTWOPORTS_H
#define TASKHANDLERTWOPORTS_H
#include<taskhandler.h>
#include <QTimer>
#include <QEventLoop>
#include <sstream>
#include <iomanip>

class Taskhandlertwoports : public Taskhandler
{
    Q_OBJECT
public:
    Taskhandlertwoports(device* master, device* slave);
    void readmodifier0304(std::string frame, bool action);
    void writemodifier10(std::string frame, bool action);
    std::string editmultipleregisters(std::string frame);
    void singleregisteredit06(std::string frame, bool action);
    bool checkframe(std::string frame);
    std::vector < slavedata > writeregisters(std::vector < slavedata > slaves, std::string frame, std::string startaddres);
    bool blockinfo(std::string frame, std::vector < slavedata > slaves);
    void sendtoslave(std::string frame);
    void updatehelpframe(std::string f);
    void init();


private slots:
    void modifyregisters0304(std::string frame);
    void slavewriteresponsehadler(std::string frame);


signals:
    void finishedresponse();

private:
    QTimer* timer;
    device* master;
    device* slave;
    calculations calc;
    int retries;
    int timeout;
    QEventLoop loop;
    std::string startaddres;
    bool specaction;
    std::string helpframe;
    int mode;

};

#endif // TASKHANDLERTWOPORTS_H
