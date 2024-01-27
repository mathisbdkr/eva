/*
** EPITECH PROJECT, 2024
** B-PDG-300-PAR-3-1-PDGRUSH3-eva.legrand
** File description:
** DisplayNcurses
*/

#include "DisplayNcurses.hpp"
#include <chrono>
#include <thread>

DisplayNcurses::DisplayNcurses()
{
    _module._RamModule = new RamModule;
    launch_ncurses();
}

DisplayNcurses::~DisplayNcurses()
{
    endwin();
}

void DisplayNcurses::init_ncurse_window(void)
{
    initscr();
    start_color();
    curs_set(FALSE);
    init_pair(RIEN, COLOR_WHITE, COLOR_BLACK);
    init_pair(RED, COLOR_RED, COLOR_BLACK);
    init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
    init_pair(CYAN, COLOR_CYAN, COLOR_BLACK);
}

void DisplayNcurses::get_terminal_size() {
    getmaxyx(stdscr, _size_x, _size_y);
}

void DisplayNcurses::percent_color(int nb, int max)
{
    if (nb <= (max / 3)) {
        attron(COLOR_PAIR(GREEN));
    }
    if (nb >(max / 3) && nb <= (max / 3) * 2) {
        attron(COLOR_PAIR(YELLOW));
    }
    if (nb > (max / 3) * 2) {
        attron(COLOR_PAIR(RED));
    }
}

void DisplayNcurses::color_remove() {
    attroff(COLOR_PAIR(RED));
    attroff(COLOR_PAIR(GREEN));
    attroff(COLOR_PAIR(YELLOW));
    attron(COLOR_PAIR(RIEN));
}

void DisplayNcurses::display_percent(float percent)
{
    percent /= 2;
    int max = 50;
    for (int i = 0; i < max; i++) {
        percent_color(i, max);
        if (i < percent)
            printw("|");
        if (i >= percent)
            printw(".");
        if (i == 2) {
            percent_color(percent, max);
            printw("%.2f%%", percent * 2);
            i += 6;
        }
    }
    color_remove();
}

void DisplayNcurses::display_ram(void)
{
    _module._RamModule->get_ram_usage();
    attron(COLOR_PAIR(CYAN));
    printw("\nCurrent ram\n");
    attroff(COLOR_PAIR(CYAN));
    display_percent(_module._RamModule->_ram_usage);
    color_remove();
    float ram_used = _module._RamModule->_total_ram - _module._RamModule->_free_ram;
    printw("\nram usage : ");
    percent_color(_module._RamModule->_ram_usage, 100);
    printw("%.0f", ram_used);
    color_remove();
    printw(" / %.0fKB, %.0fKB free.\n", _module._RamModule->_total_ram, _module._RamModule->_free_ram);
}

void DisplayNcurses::display_sys()
{
    attron(COLOR_PAIR(CYAN));
    printw("\nSystem Information\n");
    attroff(COLOR_PAIR(CYAN));
    printw("User \t: %s\n", _module._SysInfoModule->GetUser().c_str());
    printw("Cpu \t%s\n", _module._SysInfoModule->getCpu().c_str());
    printw("OS \t: %s\n", _module._SysInfoModule->OsInfo().c_str());
    printw("Kernel \t: %s\n", _module._SysInfoModule->GetKernem().c_str());

    long int all_second = _module._SysInfoModule->GetUpTime();
    int hours = all_second / 3600;
    int minuts = all_second / 60;
    int second = all_second;
    for (int i = 0; i < hours; i++) {
        minuts -= 60;
        second -= 3600;
    }
    for (int i = 0; i < minuts; i++) {
        second -= 60;
    }
    printw("Uptime \t: %d:%d:%d\n", hours, minuts, second);
}

void DisplayNcurses::display_cpu(void)
{
    attron(COLOR_PAIR(CYAN));
    printw("\nCurrent Cpu\n");
    attroff(COLOR_PAIR(CYAN));
    display_percent(_module._CpuModule->TotalCPUpercent());
    color_remove();
}

void DisplayNcurses::launch_ncurses(void)
{
    
    _module._RamModule = new RamModule;
    _module._SysInfoModule = new SysInfoModule;
    _module._CpuModule = new CpuModule;

    init_ncurse_window();
    while (1) {
        clear();

        display_sys();
        display_ram();
        display_cpu();
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}
