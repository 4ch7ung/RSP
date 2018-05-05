#include "ncurses.h"
#include "CursesUI.h"

CursesUI::CursesUI() {
    this->init();
}

CursesUI::~CursesUI() {
    this->deinit();
}

void CursesUI::init() {
    initscr();
}

void CursesUI::deinit() {
    endwin();
}
