#include "Pilka.h"
#include <cmath>

Pilka::Pilka(float x_in, float y_in, float vx_in, float vy_in, float radius_in)//konstruktor
{
    x = x_in;
    y = y_in;
    vx = vx_in;
    vy = vy_in;
    radius = radius_in;

    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::White);
}

void Pilka::move()//zmiana pozycji pilki
{
    x = x + vx;
    y = y + vy;
    shape.setPosition(x, y);
}

void Pilka::bounceX()//odbicie w osi X
{
    vx = -vx;
}

void Pilka::bounceY()//odbicie w osi Y
{
    vy = -vy;
}

void Pilka::collideWalls(float width, float height)//kolizje ze scianami
{
    if (x - radius <= 0 || x + radius >= width)
        bounceX();

    if (y - radius <= 0)
        bounceY();

    shape.setPosition(x, y);
}

bool Pilka::colidePaddle(const Paletka& p)
{
    float lewa = p.getX() - p.getSzerokosc() / 2;
    float prawa = p.getX() + p.getSzerokosc() / 2;
    float gora = p.getY() - p.getWysokosc() / 2;
    float dol = p.getY() + p.getWysokosc() / 2;

    if (x + radius >= lewa && x - radius <= prawa &&
        y + radius >= gora && y - radius <= dol)
    {
        //odleg³oœci od krawêdzi
        float odLewa = std::abs((x - radius) - lewa);
        float odPrawa = std::abs((x + radius) - prawa);
        float odGora = std::abs((y - radius) - gora);
        float odDol = std::abs((y + radius) - dol);

        float minOdleglosc = odLewa;
        int strona = 0; //0-lewo,1-prawo,2-góra,3-dó³

        if (odPrawa < minOdleglosc) { minOdleglosc = odPrawa; strona = 1; }
        if (odGora < minOdleglosc) { minOdleglosc = odGora; strona = 2; }
        if (odDol < minOdleglosc) { minOdleglosc = odDol; strona = 3; }

        if (strona == 0 || strona == 1) {
            bounceX();
            if (strona == 0) x = lewa - radius;
            else x = prawa + radius;
        }
        if (strona == 2) {
            vy = -std::abs(vy);
            y = gora - radius;
        }
        else {
            vy = std::abs(vy);
            y = dol + radius;
        }

        shape.setPosition(x, y);
        return true;
    }

    return false;
}

void Pilka::draw(sf::RenderTarget& target)
{
    target.draw(shape);
}

float Pilka::getX() const { return x; }
float Pilka::getY() const { return y; }
float Pilka::getVx() const { return vx; }
float Pilka::getVy() const { return vy; }
float Pilka::getRadius() const { return radius; }
