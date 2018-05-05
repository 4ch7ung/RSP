#include "LogAssembly.h"
#include "LogModule.h"
#include "CursesUI.h"
#include "LogUI.h"

LogModule* LogAssembly::createModule(const double * x) {
    CursesUI * curses = new CursesUI();
    LogUI * logUI = new LogUI(curses);
    LogModule * module;
    if (x == nullptr) {
        module = new LogModule(logUI);
    } else {
        module = new LogModule(logUI, *x);
    }
    return module;
}
