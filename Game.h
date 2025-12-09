#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Paletka.h"
#include "Pilka.h"
#include "Stone.h"
#include "Kamulec.h"
#include "Zapis.h" 

class Game
{
public:
    Game();
    void update(sf::Time dt);
    void render(sf::RenderTarget& target);
    bool isGameOver() const
    {
        return m_gameOver;
    }
    void startCountdown();
    void updateCountdown();
    void renderCountdown(sf::RenderTarget& target);
    bool isCountingDown() const
    {
        return m_isCountingDown;
    }
    void zamienPaletkeWKamien();
    bool wczytajGre(const std::string& nazwaPliku) {
        StatusGry status;
        if (status.WczytajzPliku(nazwaPliku)) {
            m_paletka.setPosition(status.getPaddlePosition().x,
                status.getPaddlePosition().y);
            m_pilka.setPosition(status.getBallPosition().x,
                status.getBallPosition().y);
            m_pilka.setVelocity(status.getBallVelocity().x,
                status.getBallVelocity().y);
            m_bloki.clear();
            auto& bloki = status.getBlocks();
            const float WIDTH = 640.f;
            const int ILOSC_KOLUMN = 6;
            const float MARGINES = 0.f;
            const float ODSTEP = 2.f;
            const float ROZMIAR_BLOKU_X = (WIDTH - MARGINES * 2 - (ILOSC_KOLUMN - 1) * ODSTEP) / ILOSC_KOLUMN;
            const float ROZMIAR_BLOKU_Y = 25.f;

            for (const auto& blok : bloki) 
            {
                Stone nowyBlok(sf::Vector2f(blok.x, blok.y),
                    sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y),
                    blok.hp);
                if (blok.hp <= 0) 
                {
                    nowyBlok.setOutlineThickness(0.f);
                    nowyBlok.setFillColor(sf::Color::Transparent);
                }
                else 
                {
                    nowyBlok.setOutlineThickness(2.f);
                    nowyBlok.setOutlineColor(sf::Color::White);
                }

                m_bloki.push_back(nowyBlok);
            }

            m_gameOver = false;
            return true;
        }
        return false;
    }

    const Paletka& getPaletka() const { return m_paletka; }
    const Pilka& getPilka() const { return m_pilka; }
    const std::vector<Stone>& getBloki() const { return m_bloki; }
    bool m_wygrana;
    sf::Clock m_wygranaClock;
    sf::Text m_wygranaText;
    sf::Texture m_tloTexture;
    sf::Sprite m_tloSprite;
private:
    const float WIDTH = 640.f;
    const float HEIGHT = 480.f;
    Paletka m_paletka;
    Pilka m_pilka;
    std::vector<Stone> m_bloki;
    sf::Clock m_deltaClock;
    bool m_gameOver = false;
    int m_countdownValue;
    bool m_isCountingDown;
    sf::Clock m_countdownClock;
    sf::Text m_countdownText;
    sf::Font m_font;
    bool m_czyKamien;
    Kamien m_kamien;

};