#pragma once
#include <SFML/Graphics.hpp>
#include "Paletka.h"

class Pilka
{
private:
    float x;
    float y;
    float vx;
    float vy;
    float radius;
    sf::CircleShape shape;

public:
    Pilka(float x_in, float y_in, float vx_in, float vy_in, float radius_in);

    void move();
    void bounceX();
    void bounceY();
    void collideWalls(float width, float height);
    bool colidePaddle(const Paletka& p);
    void draw(sf::RenderTarget& target);

    float getX() const;
    float getY() const;
    float getVx() const;
    float getVy() const;
    float getRadius() const;

    void setPosition(float newX, float newY)
    {
        x = newX;
        y = newY;
        shape.setPosition(x, y);
    }

    void setVelocity(float newVx, float newVy)
    {
        vx = newVx;
        vy = newVy;
    }
};
