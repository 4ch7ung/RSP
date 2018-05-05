#ifndef _LOG_UI_H_
#define _LOG_UI_H_

#include "CursesUI.h"

class LogUI {
private:
    CursesUI * m_curses;
public:
    LogUI(CursesUI * curses);
    ~LogUI();
    void showGreeting();
    double inputX();
    void showLogX(double x, double logx);
    void wait();
};

#endif
