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
    //_module._CpuModule->PopCompute(_module._CpuModule->openNbCore(_module._CpuModule->parseNbrCore()));
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

void DisplayNcurses::percent_color(int nb, int max, WINDOW *win)
{
    if (nb <= (max / 3)) {
        wattron(win,COLOR_PAIR(GREEN));
    }
    if (nb >(max / 3) && nb <= (max / 3) * 2) {
        wattron(win,COLOR_PAIR(YELLOW));
    }
    if (nb > (max / 3) * 2) {
        wattron(win,COLOR_PAIR(RED));
    }
}

void DisplayNcurses::color_remove(WINDOW *win) {
    wattroff(win,COLOR_PAIR(RED));
    wattroff(win,COLOR_PAIR(GREEN));
    wattroff(win,COLOR_PAIR(YELLOW));
    wattroff(win,COLOR_PAIR(CYAN));
    wattron(win,COLOR_PAIR(RIEN));
}

void DisplayNcurses::display_percent(float percent, WINDOW *win, int pos_y, int pos_x)
{
    percent /= 1.5;
    int max = 66;
    for (int i = 0; i < max; i++) {
        percent_color(i, max, win);
        if (i < percent)
            mvwprintw(win, pos_y, pos_x++, "|");
        if (i >= percent)
            mvwprintw(win, pos_y, pos_x++, ".");
        if (i == 2) {
            percent_color(percent, max, win);
            mvwprintw(win, pos_y, pos_x++, "%.2f%%", percent * 1.5);
            i += 6;
            pos_x += 5;
        }
    }
    color_remove(win);
}

void DisplayNcurses::display_ram(void)
{
    WINDOW *win = newwin(6, 75, _height, 0);
    _height += 6;
    int y = 0;
    _module._RamModule->get_ram_usage();
    refresh();
    box(win, 0, 0);
    wattron(win,COLOR_PAIR(CYAN));
    mvwprintw(win, y++, 1, " Current ram ");
    y++;
    wattroff(win,COLOR_PAIR(CYAN));
    display_percent(_module._RamModule->_ram_usage, win, y, 1);
    y++;
    y++;
    float ram_used = _module._RamModule->_total_ram - _module._RamModule->_free_ram;
    mvwprintw(win, y, 1, "Ram usage : ");
    percent_color(_module._RamModule->_ram_usage, 100, win);
    mvwprintw(win, y, 13, "%.0f", ram_used);
    color_remove(win);
    mvwprintw(win, y, 23, " / %.0fKB, %.0fKB free.", _module._RamModule->_total_ram, _module._RamModule->_free_ram);
    wrefresh(win);
    delwin(win);
}

void DisplayNcurses::display_sys()
{
    WINDOW *win = newwin(8, 75, _height, 0);
    _height += 8;
    int y = 0;
    refresh();
    box(win, 0, 0);
    wattron(win, COLOR_PAIR(CYAN));
    mvwprintw(win, y++, 1, " System Information ");
    y++;
    wattroff(win, COLOR_PAIR(CYAN));
    mvwprintw(win, y++, 1, "User \t: %s", _module._SysInfoModule->GetUser().c_str());
    mvwprintw(win, y++, 1, "Cpu \t%s", _module._SysInfoModule->getCpu().c_str());
    mvwprintw(win, y++, 1, "OS \t: %s", _module._SysInfoModule->OsInfo().c_str());
    mvwprintw(win, y++, 1, "Kernel : %s", _module._SysInfoModule->GetKernem().c_str());

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
    mvwprintw(win, y++, 1, "Uptime : %d:%d:%d", hours, minuts, second);
    wrefresh(win);
    delwin(win);
}

void DisplayNcurses::display_cpu(void)
{
    int dq_size = _module._CpuModule->PopCompute().size();
    WINDOW *win = newwin(6 + (dq_size / 2) + 3 , 150, _height, 0);
    _height += 6 + (dq_size / 2) + 3;
    int y = 0;
    refresh();
    box(win, 0, 0);
    wattron(win,COLOR_PAIR(CYAN));
    mvwprintw(win, y++, 1, " Current Cpu ");
    wattroff(win,COLOR_PAIR(CYAN));
    y++;
    mvwprintw(win, y++, 1, "Cpu \t%s", _module._SysInfoModule->getCpu().c_str());
    y++;
    display_percent(_module._CpuModule->TotalCPUpercent(_module._CpuModule->getTotalCpu()), win, y, 1);
    y++;
    y++;

    std::deque<float> dq = _module._CpuModule->PopCompute();
    mvwprintw(win, y++, 1, "Cpu core usage");
    for (int i = 0; i < dq_size / 2; i++) {
        mvwprintw(win, y, 1, "%d [", i);
        display_percent(dq.at(i), win, y, 5);
        mvwprintw(win, y, 72, "]  %d [", i + dq_size / 2);
        display_percent(dq.at(i + dq_size / 2), win, y, 80);
        mvwprintw(win, y, 147, "]");
        y++;
    }

    wrefresh(win);
    delwin(win);
}

void DisplayNcurses::launch_ncurses(void)
{
    
    _module._RamModule = new RamModule;
    _module._SysInfoModule = new SysInfoModule;
    _module._CpuModule = new CpuModule;

    init_ncurse_window();
    int c = 0;
    cbreak();
    while (c != 'q') {
        _height = 0;
        display_sys();
        display_cpu();
        display_ram();
        timeout(50);
        c = getch();
    }
    delete(_module._CpuModule);
    delete(_module._RamModule);
    delete(_module._SysInfoModule);
}
