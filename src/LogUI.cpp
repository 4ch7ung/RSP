#include "CursesUI.h"
#include "LogUI.h"
#include "ncurses.h"

LogUI::LogUI(CursesUI * curses) {
    this->m_curses = curses;
}

LogUI::~LogUI() {
    if (this->m_curses != nullptr) {
        delete this->m_curses;
    }
}

void LogUI::showGreeting() {
    printw("Hello from log module!\n");
}

double LogUI::inputX() {
    double x;
    printw("Input x: ");
    scanw((char *)"%lf", &x);
    return x;
}

void LogUI::showLogX(double x, double logx) {
    printw("Ln(%lf) = %.8lf\n", x, logx);
    printw("Press any key to close...");
    refresh();
}

void LogUI::wait() {
    getch();
}
