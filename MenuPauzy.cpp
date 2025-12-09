#include "MenuPauzy.h"
#include <iostream>

MenuPauzy::MenuPauzy(float width, float height)
{
    font.loadFromFile("arial.ttf");//czcionka z pliku
    //wyglad menu pauzy z kolejnymi opcjami
    options[0].setFont(font);
    options[0].setString("Kontynuuj");
    options[0].setPosition(width / 2 - 50, height / 2 - 80);
    options[1].setFont(font);
    options[1].setString("Zapisz");
    options[1].setPosition(width / 2 - 50, height / 2 - 40);
    options[2].setFont(font);
    options[2].setString("Wyjscie");
    options[2].setPosition(width / 2 - 50, height / 2);
    selected = 0;
    options[0].setFillColor(sf::Color::Blue);
}
//nawigacja menu pauzy
void MenuPauzy::moveUp()
{
    if (selected > 0)
    {
        options[selected].setFillColor(sf::Color::White);
        selected--;
        options[selected].setFillColor(sf::Color::Blue);
    }
}

void MenuPauzy::moveDown()
{
    if (selected < 2)
    {
        options[selected].setFillColor(sf::Color::White);
        selected++;
        options[selected].setFillColor(sf::Color::Blue);
    }
}

int MenuPauzy::getSelectedItem()//wybranie opcji
{
    return selected;
}

void MenuPauzy::draw(sf::RenderTarget& target)//rysowanie menu pauzy
{
    target.draw(options[0]);
    target.draw(options[1]);
    target.draw(options[2]);
}
