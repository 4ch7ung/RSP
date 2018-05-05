#include <stdexcept>
#include <ncurses.h>
#include "Module.hpp"
#include "math_functions.h"

LogModule::LogModule() {
    this->x = NULL;
}

LogModule::LogModule(double x) {
    this->x = new double(x);
}

LogModule::~LogModule() {
    delete this->x;
}

void LogModule::run() {
    initscr();
    if (this->x == NULL) {
        this->x = new double;
        printw("Input x: ");
        scanw("%lf", this->x);
    }
    double lnx;
    try {
        lnx = ln(*(this->x));
    } catch (std::exception& exception) {
        endwin();
        throw;
    }

    printw("Ln(%lf) = %.8lf\n", *(this->x), lnx);
    printw("Press any key to close...");
    refresh();
    getch();
    endwin();
}
