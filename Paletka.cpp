#include "Paletka.h"

Paletka::Paletka(float x_in, float y_in, float szerokosc_in, float wysokosc_in, float predkosc_in)//konstruktor
{
    x = x_in;
    y = y_in;
    szerokosc = szerokosc_in;
    wysokosc = wysokosc_in;
    predkosc = predkosc_in;

    shape.setSize({ szerokosc, wysokosc });
    shape.setOrigin(szerokosc / 2, wysokosc / 2);
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Magenta);
}

void Paletka::moveLeft()//przesuniecie w lewo
{
    x = x - predkosc;
    shape.setPosition(x, y);
}

void Paletka::moveRight()//przesuniecie w prawo
{
    x = x + predkosc;
    shape.setPosition(x, y);
}

void Paletka::clampToBounds(float WIDTH)//ograniczenie paletki zeby nie wychodzila poza okno
{
    if (x - szerokosc / 2 <= 0)
        x = szerokosc / 2;

    if (x + szerokosc / 2 >= WIDTH)
        x = WIDTH - szerokosc / 2;

    shape.setPosition(x, y);
}

void Paletka::draw(sf::RenderTarget& target)//rysowanie paletki
{
    target.draw(shape);
}
//gettery
float Paletka::getX() const { return x; }
float Paletka::getY() const { return y; }
float Paletka::getSzerokosc() const { return szerokosc; }
float Paletka::getWysokosc() const { return wysokosc; }
