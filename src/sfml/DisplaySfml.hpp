/*
** EPITECH PROJECT, 2024
** B-PDG-300-PAR-3-1-PDGRUSH3-eva.legrand
** File description:
** DisplaySFML
*/

#include <SFML/Graphics.hpp>

#ifndef DISPLAYSFML_HPP_
    #define DISPLAYSFML_HPP_

#include "../IModule.hpp"
#include "../IDisplay.hpp"

class DisplaySfml : public Krell::IDisplay {
    private:
        Krell::IModule _module;
        sf::RenderWindow window;
        sf::Font font;
        sf::Text text;
        sf::Sprite background;
        sf::Texture backgroundTexture;
        sf::Texture CPU_texture;
        sf::Texture RAM_texture;
        sf::Texture SYS_texture;
        sf::Sprite CPU_sprite;
        sf::Sprite RAM_sprite;
        sf::Sprite SYS_sprite;
        bool rect_visible;
        bool _ram = false;
        bool _cpu = false;
        bool _sys = false;
    public:
        DisplaySfml();
        ~DisplaySfml();
        void launch_sfml();
        void set_sprite();
        sf::Vector2f get_position(float x, float y);
};

void made_rond_rect(sf::Vector2f size, sf::Vector2f pos, sf::Color color,
    sf::RenderWindow &window);
sf::Color RGB(int r, int g, int b);

#endif /* !DISPLAYSFML_HPP_ */
