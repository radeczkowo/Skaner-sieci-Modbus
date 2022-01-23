#ifndef SCANNER_H
#define SCANNER_H
#include <QTimer>
#include <QEventLoop>
#include <taskhandlertwoports.h>
#include <taskhandleroneport.h>
#include <algorithm.h>

class Scanner: public QObject
{
   Q_OBJECT
public:
    Scanner();
    void init();
    void openports(QString p1, QString p2);
    void closeports();

    void setmode(int modnr);
    int getmode() const;
    bool getconnected() const;
    bool getmodifying() const;
    void setblocking(bool value);
    void setmodifying(bool value);
    Taskhandler* gettaskhandler() const;
    CSettings* getsettings() const;

private slots:
    void slaveframe(std::string frame);
    void taskhandlerframe(std::string frame);
    void receiveslavee(std::string id);

signals:
    void passframe(std::string frame);
    void passslave(std::string id);

private:
    device* master;
    device* slave;
    CSettings* csettings;
    Taskhandler * taskhandler;
    bool blocking;
    bool modifying;
    int mode;
    bool connected;
    calculations calc;



};

#endif // SCANNER_H
