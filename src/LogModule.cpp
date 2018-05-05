#include <stdexcept>
#include <ncurses.h>
#include "LogModule.h"
#include "math_functions.h"

LogModule::LogModule(LogUI * ui) {
    this->m_ui = ui;
    this->x = NULL;
}

LogModule::~LogModule() {
    if (this->m_ui != NULL) {
        delete this->m_ui;
    }
    if (this->x != NULL) {
        delete this->x;
    }
}

void LogModule::setX(double x) {
    if (this->x != NULL) {
        delete this->x;
    }
    this->x = new double(x);
}

void LogModule::run() {
    m_ui->showGreeting();
    if (this->x == NULL) {
        this->x = new double;
        *(this->x) = m_ui->inputX();
    }
    double lnx;
    try {
        lnx = ln(*x);
    } catch (std::exception& exception) {
        throw;
    }
    m_ui->showLogX(*x, lnx);
    m_ui->wait();
}
