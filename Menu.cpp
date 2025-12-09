#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height)
{
    font.loadFromFile("arial.ttf");//zaladowanie czciconki
    //menu z kolejnymi opcjami
    options[0].setFont(font);
    options[0].setString("Nowa gra");
    options[0].setPosition(width / 2 - 50, height / 2-80 );

    options[1].setFont(font);
    options[1].setString("Wczytaj");
    options[1].setPosition(width / 2 - 50, height / 2 - 40 );

    options[2].setFont(font);
    options[2].setString("Wyjscie");
    options[2].setPosition(width / 2 - 50, height / 2 );

    selected = 0;
    options[0].setFillColor(sf::Color::Blue);
}
//nawigacja po menu
void Menu::moveUp()
{
    if (selected > 0)
    {
        options[selected].setFillColor(sf::Color::White);
        selected--;
        options[selected].setFillColor(sf::Color::Blue);
    }
}

void Menu::moveDown()
{
    if (selected < 2)
    {
        options[selected].setFillColor(sf::Color::White);
        selected++;
        options[selected].setFillColor(sf::Color::Blue);
    }
}

int Menu::getSelectedItem()
{
    return selected;
}

void Menu::draw(sf::RenderTarget& target)
{
    target.draw(options[0]);
    target.draw(options[1]);
    target.draw(options[2]);
}
