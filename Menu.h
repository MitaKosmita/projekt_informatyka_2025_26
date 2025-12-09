#pragma once
#include <SFML/Graphics.hpp>

class Menu
{
public:
    Menu(float width, float height);

    void moveUp();
    void moveDown();
    int getSelectedItem();
    void draw(sf::RenderTarget& target);

private:
    int selected;
    sf::Font font;
    sf::Text options[3];
};
