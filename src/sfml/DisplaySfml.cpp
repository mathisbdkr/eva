/*
** EPITECH PROJECT, 2024
** B-PDG-300-PAR-3-1-PDGRUSH3-eva.legrand
** File description:
** DisplaySfml
*/

#include "DisplaySfml.hpp"

DisplaySfml::DisplaySfml() : window(sf::VideoMode(800, 600), "SFML Window")
{
    launch_sfml();
}


DisplaySfml::~DisplaySfml()
{
}

sf::Vector2f DisplaySfml::get_position(float x, float y)
{
    sf::Vector2f vector;

    vector.x = x;
    vector.y = y;
    return (vector);
}



void DisplaySfml::set_sprite()
{
    backgroundTexture.loadFromFile("assets/image/background.png");
    background.setTexture(backgroundTexture, false);
    background.setScale(get_position(0.5, 0.6));

    CPU_texture.loadFromFile("assets/image/cpu.png");
    CPU_sprite.setTexture(CPU_texture, false);
    CPU_sprite.setScale(get_position(0.1, 0.1));
    CPU_sprite.setPosition(get_position(20, 80));

    RAM_texture.loadFromFile("assets/image/ram.png");
    RAM_sprite.setTexture(RAM_texture, false);
    RAM_sprite.setScale(get_position(0.1, 0.1));
    RAM_sprite.setPosition(get_position(20, 20));

    SYS_texture.loadFromFile("assets/image/sys.png");
    SYS_sprite.setTexture(SYS_texture, false);
    SYS_sprite.setScale(get_position(0.15, 0.15));
    SYS_sprite.setPosition(get_position(15, 140));
}

void DisplaySfml::launch_sfml(void)
{
    sf::Event event;
    font.loadFromFile("./assets/fonts/RobotoRegular.ttf");
    while (window.isOpen()) {
        set_sprite();
        window.clear(sf::Color::Black);
        window.draw(background);

        window.draw(CPU_sprite);
        window.draw(RAM_sprite);
        window.draw(SYS_sprite);
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }  else if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (CPU_sprite.getGlobalBounds().contains(mousePosition)) {
                       _cpu = !_cpu;
                    }

                    if (RAM_sprite.getGlobalBounds().contains(mousePosition)) {
                        _ram = !_ram;
                    }

                    if (SYS_sprite.getGlobalBounds().contains(mousePosition)) {
                        _sys = !_sys;
                    }
                }
            }
        }
        if (_ram == true) {
            made_rond_rect(get_position(300, 100), get_position(250, 100), RGB(0,100,0), window);
        }
        if (_cpu == true) {
            made_rond_rect(get_position(300, 100), get_position(250, 250), RGB(178,34,34), window);
        }
        if (_sys == true) {
            made_rond_rect(get_position(300, 100), get_position(250, 400), RGB(0,0,205), window);
        }
        window.display();
    }
}
