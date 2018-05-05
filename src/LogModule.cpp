#include <stdexcept>
#include <ncurses.h>
#include "LogModule.h"
#include "math_functions.h"

LogModule::LogModule(LogUI * ui) {
    this->m_ui = ui;
    this->x = nullptr;
}

LogModule::LogModule(LogUI * ui, double x) {
    this->m_ui = ui;
    this->x = new double(x);
}

LogModule::~LogModule() {
    if (this->m_ui != nullptr) {
        delete this->m_ui;
    }
    if (this->x != nullptr) {
        delete this->x;
    }
}

void LogModule::run() {
    m_ui->showGreeting();
    if (this->x == nullptr) {
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
