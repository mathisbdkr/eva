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
        int _size_x;
        int _size_y;
        WINDOW *_win;
    public:
        DisplayNcurses();
        ~DisplayNcurses();
        void init_ncurse_window();
        void display_ram();
        void launch_ncurses();
        void get_terminal_size();
        void percent_color(int nb, int max);
        void color_remove();
        void display_percent(float percent);
        void display_sys();
        void display_cpu(void);
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
