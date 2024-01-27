/*
** EPITECH PROJECT, 2024
** B-PDG-300-PAR-3-1-PDGRUSH3-eva.legrand
** File description:
** DisplaySFML
*/

#ifndef DISPLAYSFML_HPP_
    #define DISPLAYSFML_HPP_

#include "../IModule.hpp"
#include "../IDisplay.hpp"

class DisplaySfml : public Krell::IDisplay {
    private:
        Krell::IModule _module;
    public:
        DisplaySfml();
        ~DisplaySfml();
};

enum {
    RIEN,
    GREEN,
    BLUE,
    RED,
    YELLOW,
    CYAN
};

#endif /* !DISPLAYSFML_HPP_ */
