/*
** EPITECH PROJECT, 2024
** B-PDG-300-PAR-3-1-PDGRUSH3-eva.legrand
** File description:
** DisplayNcurses
*/

#ifndef DISPLAYNCURSES_HPP_
    #define DISPLAYNCURSES_HPP_

    #include <ncurses.h>
    #include "../IModule.hpp"
    #include "../IDisplay.hpp"

class DisplayNcurses : public Krell::IDisplay {
    private:
        Krell::IModule _module;
        std::deque<std::string> _dq;
        std::size_t _dq_size;
        int _height;
    public:
        DisplayNcurses();
        ~DisplayNcurses();
        void init_ncurse_window();
        void display_ram();
        void launch_ncurses();
        void percent_color(int nb, int max, WINDOW *win);
        void color_remove(WINDOW *win);
        void display_percent(float percent, WINDOW *win, int pos_y, int pos_x);
        void display_sys();
        void display_cpu(void);
        int get_height();
};

enum {
    RIEN,
    GREEN,
    BLUE,
    RED,
    YELLOW,
    CYAN
};

#endif /* !DISPLAYNCURSES_HPP_ */
