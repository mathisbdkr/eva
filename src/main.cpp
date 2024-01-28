/*
** EPITECH PROJECT, 2024
** B-PDG-300-PAR-3-1-PDGRUSH3-eva.legrand
** File description:
** main
*/

#include "IDisplay.hpp"
#include "IModule.hpp"
#include "ncurses/DisplayNcurses.hpp"
#include "sfml/DisplaySfml.hpp"
#include <chrono>
#include <thread>

void display_usage(void)
{
    std::cout << "MyGKrellm Usages" << std::endl << std::endl;
    std::cout << "-g --graphical\tUse graphical" << std::endl;
    std::cout << "-t --text\tUse tty mode" << std::endl;
}

bool is_graphical(char *str)
{
    if (strcmp(str, "-g") == 0 || strcmp(str, "--graphical") == 0) {
        return true;
    }
    return false;
}

bool is_text(char *str)
{
    if (strcmp(str, "-t") == 0 || strcmp(str, "--text") == 0) {
        return true;
    }
    return false;
}

int main(int ac, char **av)
{
    if (ac == 1) {
        display_usage();
        return 0;
    }
    if (is_graphical(av[1]) == true) {
        DisplaySfml disp_sfml;
    } else if (is_text(av[1]) == true) {
        DisplayNcurses disp_ncurses;
    } else {
        display_usage();
        return 0;
    }
}
