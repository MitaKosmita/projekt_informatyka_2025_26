#include "Stone.h"
//tablica kolorow blokow
const std::array<sf::Color, 4> Stone::m_colorLUT = {
    sf::Color::Transparent,//0hp
    sf::Color::Red,//1hp
    sf::Color::Yellow,//2hp
    sf::Color::Blue//3hp
};

Stone::Stone(sf::Vector2f startPos, sf::Vector2f rozmiar, int L)
{
    m_punktyZycia = L;
    m_jestZniszczony = false;

    setPosition(startPos);
    setSize(rozmiar);
    setOutlineThickness(2.f);
    aktualizujKolor();
}

void Stone::trafienie()//gdy pilka uderzy w blok
{
    if (m_jestZniszczony)
        return;

    m_punktyZycia--;
    aktualizujKolor();

    if (m_punktyZycia <= 0)
    {
        m_jestZniszczony = true;
        setOutlineThickness(0.f);
        setOutlineColor(sf::Color::Transparent);
    }
}

void Stone::aktualizujKolor()//zmiana koloru zaleznie od punktow zycia
{
    if (m_jestZniszczony)
    {
        setFillColor(sf::Color::Transparent);
    }
    else if (m_punktyZycia >= 0 && m_punktyZycia < m_colorLUT.size())
    {
        setFillColor(m_colorLUT[m_punktyZycia]);//kolor z tablicy na gorze
    }
}

bool Stone::isDestroyed() const//srpawdza czy blok jest zniszczony
{
    return m_jestZniszczony;
}

void Stone::draw(sf::RenderTarget& target) const//rysowanie
{
    if (!m_jestZniszczony)
        target.draw(*this);
}
int Stone:: getHP() const//ile hp ma blok
{
    return m_punktyZycia;
}