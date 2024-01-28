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
        sf::Vector2f _pos_ram;
        sf::Vector2f _pos_cpu;
        sf::Vector2f _pos_sys;
        enum {
            CPU,
            RAM,
            SYS
        };
        float cpu_usage_value = 0;
    public:
        DisplaySfml();
        ~DisplaySfml();
        void launch_sfml();
        void set_sprite();
        sf::Vector2f get_position(float x, float y);
        void display_info();
        void display_sys_info();
        void display_ram_info();
        void display_cpu_info();
};

sf::RectangleShape made_rond_rect(sf::Vector2f size, sf::Vector2f pos, sf::Color color,
    sf::RenderWindow &window);
sf::Color RGB(int r, int g, int b);
sf::Text made_txt(const char *text, sf::Vector2f pos, sf::Vector2f size, sf::Font font);

#endif /* !DISPLAYSFML_HPP_ */
