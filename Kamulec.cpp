#include "Kamulec.h"
#include <SFML/Graphics.hpp>
#include <cmath>

Kamien::Kamien(float x_in, float y_in)
{
    x = x_in;
    y = y_in;
    predkoscY = -10.0f;//predkosc poczatkowa bo chcemy zeby najpierw kamien "podskoczyl"
    spada = false;
    ksztalt.setPointCount(10);//kamien to wielokat o 10 katach
    ksztalt.setPoint(0, sf::Vector2f(5, 10));
    ksztalt.setPoint(1, sf::Vector2f(20, 0));
    ksztalt.setPoint(2, sf::Vector2f(50, 5));
    ksztalt.setPoint(3, sf::Vector2f(75, 8));
    ksztalt.setPoint(4, sf::Vector2f(85, 25));
    ksztalt.setPoint(5, sf::Vector2f(80, 45));
    ksztalt.setPoint(6, sf::Vector2f(60, 55));
    ksztalt.setPoint(7, sf::Vector2f(35, 52));
    ksztalt.setPoint(8, sf::Vector2f(15, 48));
    ksztalt.setPoint(9, sf::Vector2f(0, 35));
    ksztalt.setOrigin(42, 27);//punkt srodkowy kamiena mniej wiecej (85-0 i 55-0)
    ksztalt.setPosition(x, y);
    //kolor kamienia i obramowanie zeby bylo przyjemnniejsze dla oka
    ksztalt.setFillColor(sf::Color(140, 140, 140));
    ksztalt.setOutlineThickness(2);
    ksztalt.setOutlineColor(sf::Color(90, 90, 90));
}

void Kamien::aktualizuj()//sprawdzanie stanu kamienia
{
    if (!spada && predkoscY < 0)
    {
        predkoscY += 1.0f;//zwalnia jak leci do gory
        if (predkoscY >= 0) spada = true;
    }

    if (spada)
    {
        predkoscY += 1.5f;//przyspiesza jak leci w dol (grawitacja)
        ksztalt.rotate(3.0f);
    }

    y += predkoscY;
    ksztalt.setPosition(x, y);
}

bool Kamien::czyPozaEkranem(float wysokoscEkranu)//czy kamien jest poza ekranem (zeby wylaczyc okno)
{
    return y > wysokoscEkranu + 100;
}

void Kamien::rysuj(sf::RenderTarget& okno)//rysowanie kamienia
{
    okno.draw(ksztalt);
}

float Kamien::getY() const//getter Y zeby sprawdzic czy poza ekranem
{
    return y;
}