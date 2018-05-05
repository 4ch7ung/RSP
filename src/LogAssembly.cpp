#include "LogAssembly.h"
#include "LogModule.h"
#include "CursesUI.h"
#include "LogUI.h"

LogModule* LogAssembly::createModule() {
    CursesUI * curses = new CursesUI();
    LogUI * logUI = new LogUI(curses);
    LogModule * module = new LogModule(logUI);
    return module;
}
