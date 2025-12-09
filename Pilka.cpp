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

bool Pilka::colidePaddle(const Paletka& p)//kolizja pilki i paletki 
{
    float lewaKrawedzPaletki = p.getX() - p.getSzerokosc() / 2;
    float prawaKrawedzPaletki = p.getX() + p.getSzerokosc() / 2;
    float gornaKrawedzPaletki = p.getY() - p.getWysokosc() / 2;
    float dolnaKrawedzPaletki = p.getY() + p.getWysokosc() / 2;

    if (x + radius >= lewaKrawedzPaletki &&
        x - radius <= prawaKrawedzPaletki &&
        y + radius >= gornaKrawedzPaletki &&
        y - radius <= dolnaKrawedzPaletki)
    {
       
        float odlegloscOdLewej = std::abs(x - lewaKrawedzPaletki);//odleglosci od krawedzi paletki
        float odlegloscOdPrawej = std::abs(x - prawaKrawedzPaletki);
        float odlegloscOdGory = std::abs(y - gornaKrawedzPaletki);
        float odlegloscOdDolu = std::abs(y - dolnaKrawedzPaletki);

        
        float najblizszaKrawedz = odlegloscOdLewej;
        int ktoraStrona = 0; // 0-lewo, 1-prawo, 2-góra, 3-dó³

        if (odlegloscOdPrawej < najblizszaKrawedz) {
            najblizszaKrawedz = odlegloscOdPrawej;
            ktoraStrona = 1;
        }
        if (odlegloscOdGory < najblizszaKrawedz) {
            najblizszaKrawedz = odlegloscOdGory;
            ktoraStrona = 2;
        }
        if (odlegloscOdDolu < najblizszaKrawedz) {
            najblizszaKrawedz = odlegloscOdDolu;
            ktoraStrona = 3;
        }

        
        if (ktoraStrona == 0 || ktoraStrona == 1) {//jak ma sie odbic pilka
            bounceX();//bok
            //ustawienie paletki
            if (ktoraStrona == 0) {//lewa strona
                x = lewaKrawedzPaletki - radius;
            }
            else {//prawa strona
                x = prawaKrawedzPaletki + radius;
            }
        }
        else { 
            vy = -std::abs(vy); //osbicie od gory

            //ustawienie paletki
            if (ktoraStrona == 2) {//góra
                y = gornaKrawedzPaletki - radius;
            }
            else {//dó³
                y = dolnaKrawedzPaletki + radius;
            }
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
