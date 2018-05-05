#ifndef _LOG_MODULE_H_
#define _LOG_MODULE_H_

#include "Module.h"
#include "LogUI.h"

class LogModule: public Module {
private:
    double * x;
    LogUI * m_ui;
public:
    LogModule(LogUI * ui);
    ~LogModule();

    void run();
    void setX(double x);
};

#endif
