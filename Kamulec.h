#pragma once
#include <SFML/Graphics.hpp>

class Kamien
{
private:
    float x;
    float y;
    float predkoscY;
    bool spada;
    sf::ConvexShape ksztalt;

public:
    Kamien(float startX, float startY);
    void aktualizuj();
    bool czyPozaEkranem(float wysokoscEkranu);
    void rysuj(sf::RenderTarget& okno);
    float getY() const;
};