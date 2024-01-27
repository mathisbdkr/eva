/*
** EPITECH PROJECT, 2024
** sf::ML_RUSH03
** File description:
** made_round_rect
*/

#include <SFML/Graphics.hpp>

sf::Color RGB(int r, int g, int b)
{
    sf::Color color;
    color.r = r;
    color.g = g;
    color.b = b;
    return color;
}

sf::Vector2f get_position(float x, float y)
{
    sf::Vector2f vector;

    vector.x = x;
    vector.y = y;
    return (vector);
}

static sf::CircleShape made_cercle(sf::Vector2f pos,
    sf::Color color)
{
    sf::CircleShape cercle;

    cercle.setPosition(pos);
    cercle.setRadius(20);
    cercle.setFillColor(color);

    return cercle;
}

static void round_right(sf::Vector2f size, sf::Vector2f pos, sf::Color color,
    sf::RenderWindow &window)
{
    sf::CircleShape cercle = made_cercle(
    get_position(pos.x + size.x - 20, pos.y + size.y - 20), color);

    window.draw(cercle);
    cercle = made_cercle(
    get_position(pos.x + size.x - 20, pos.y - 20), color);
    window.draw(cercle);
}

static void round_left(sf::Vector2f size, sf::Vector2f pos, sf::Color color,
    sf::RenderWindow &window)
{
    sf::CircleShape cercle = made_cercle(
    get_position(pos.x - 20, pos.y + size.y - 20), color);

    window.draw(cercle);
    cercle = made_cercle(
    get_position(pos.x - 20, pos.y - 20), color);
    window.draw(cercle);
}

void made_rond_rect(sf::Vector2f size, sf::Vector2f pos, sf::Color color,
    sf::RenderWindow &window)
{
    sf::RectangleShape rect;

    round_left(size, pos, color, window);
    round_right(size, pos, color, window);
    pos.x -= 20;
    size.x += 40;
    for (int i = 0; i < 2; i += 1) {
        rect.setPosition(pos);
        rect.setSize(size);
        rect.setFillColor(color);
        window.draw(rect);
        pos.y -= 20;
        pos.x += 20;
        size.y += 40;
        size.x -= 40;
    }
}
