#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

const float WIDTH = 640.f;
const float HEIGHT = 480.f;

Game::Game() : m_paletka(320.f, 440.f, 100.f, 20.f, 8.f),//konstruktor
m_pilka(320.f, 300.f, 4.f, 3.f, 8.f),
m_kamien(0, 0)
{
    m_czyKamien = false;//warunki poczatkowe
    m_gameOver = false;
    m_isCountingDown = false;
    m_countdownValue = 0;
    m_wygrana = false;

    sf::Image obrazek;//generowanie tla z gwiazdkami bo z pliku nie dzialalo
    obrazek.create(640, 480, sf::Color(2, 2, 25));
    srand(time(NULL));

    for (int i = 0; i < 500; i++)
    {
        int x = rand() % 640;
        int y = rand() % 480;
        int jasnosc = 150 + rand() % 101;
        obrazek.setPixel(x, y, sf::Color(jasnosc, jasnosc, jasnosc));
    }

    m_tloTexture.loadFromImage(obrazek);//robimy z obrazka teksture
    m_tloSprite.setTexture(m_tloTexture);//nakladamy na sprite
    //cegielki do bicia
    const int ILOSC_KOLUMN = 6;
    const int ILOSC_WIERSZY = 7;
    const float MARGINES = 0.f;
    const float ODSTEP = 2.f;
    const float ROZMIAR_BLOKU_X = (WIDTH - MARGINES * 2 - (ILOSC_KOLUMN - 1) * ODSTEP) / ILOSC_KOLUMN;
    const float ROZMIAR_BLOKU_Y = 25.f;

    for (int j = 0; j < ILOSC_WIERSZY; j++)
    {
        for (int i = 0; i < ILOSC_KOLUMN; i++)
        {
            float posX = MARGINES + i * (ROZMIAR_BLOKU_X + ODSTEP);
            float posY = 50.f + j * (ROZMIAR_BLOKU_Y + ODSTEP);
            int L = (j < 1) ? 3 : (j < 3) ? 2 : 1;//wiersz 0 najwiecej zyc (3) wiersz 6 najmniej (1)
            m_bloki.emplace_back(sf::Vector2f(posX, posY),
                sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y),
                L);
        }
    }
    //wszelakie napisy
    m_font.loadFromFile("arial.ttf");

    m_countdownText.setFont(m_font);
    m_countdownText.setCharacterSize(100);
    m_countdownText.setFillColor(sf::Color::Yellow);
    m_countdownText.setStyle(sf::Text::Bold);
    m_countdownText.setString("3");
    m_countdownText.setPosition(WIDTH / 2, HEIGHT / 2);

    m_wygranaText.setFont(m_font);
    m_wygranaText.setString("WYGRANA!");
    m_wygranaText.setCharacterSize(80);
    m_wygranaText.setFillColor(sf::Color::Green);
    m_wygranaText.setStyle(sf::Text::Bold);
    m_wygranaText.setPosition(WIDTH / 2 - 200, HEIGHT / 2 - 50);
}

void Game::update(sf::Time dt)
{
    if (m_isCountingDown)
    {
        updateCountdown();
        return;
    }

    if (m_czyKamien)//czy paletka zamienila sie w kamien
    {
        m_kamien.aktualizuj();
        if (m_kamien.czyPozaEkranem(480))//jesli kamien spafl za ekran to koniec gry
        {
            m_gameOver = true;
        }
        return;
    }

    if (m_wygrana)//jak ktos wygra to po 3 sekundach wylaczy sie okno
    {
        if (m_wygranaClock.getElapsedTime().asSeconds() >= 3.0f)
        {
            m_gameOver = true;
        }
        return;
    }
    //sterowanie
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        m_paletka.moveLeft();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        m_paletka.moveRight();

    m_paletka.clampToBounds(WIDTH);
    m_pilka.move();
    m_pilka.collideWalls(WIDTH, HEIGHT);
    m_pilka.colidePaddle(m_paletka);

    if (m_pilka.getY() - m_pilka.getRadius() > HEIGHT)
    {
        zamienPaletkeWKamien();
        return;
    }

    for (auto& blok : m_bloki)
    {
        if (!blok.isDestroyed() && blok.getHP() > 0)//sprawdzenie czy blok mozna trafic nadal
        {
            if (m_pilka.getX() + m_pilka.getRadius() >= blok.getPosition().x &&
                m_pilka.getX() - m_pilka.getRadius() <= blok.getPosition().x + blok.getSize().x &&
                m_pilka.getY() + m_pilka.getRadius() >= blok.getPosition().y &&
                m_pilka.getY() - m_pilka.getRadius() <= blok.getPosition().y + blok.getSize().y)
            { //sprawdzamy skad leci kulka
                float lewo = (m_pilka.getX() + m_pilka.getRadius()) - blok.getPosition().x;
                float prawo = (blok.getPosition().x + blok.getSize().x) - (m_pilka.getX() - m_pilka.getRadius());
                float gora = (m_pilka.getY() + m_pilka.getRadius()) - blok.getPosition().y;
                float dol = (blok.getPosition().y + blok.getSize().y) - (m_pilka.getY() - m_pilka.getRadius());

                float minX = (lewo < prawo) ? lewo : prawo;
                float minY = (gora < dol) ? gora : dol;

                if (minX < minY) m_pilka.bounceX();
                else m_pilka.bounceY();

                blok.trafienie();
                break;
            }
        }
    }

    bool wszystkieZniszczone = true;//zakladamy ze wszystkie bloki sa zniszczone
    for (const auto& blok : m_bloki)
    {
        if (!blok.isDestroyed() && blok.getHP() > 0)
        {
            wszystkieZniszczone = false;//jesli nie sa zniszczone to warunek nie jest spelniony i ulega korekcji
            break;
        }
    }

    if (wszystkieZniszczone)
    {
        m_wygrana = true;
        m_wygranaClock.restart();
        std::cout << "WYGRANA!!!!!\n";
    }
}

void Game::render(sf::RenderTarget& target)//rysowanie
{
    target.draw(m_tloSprite);

    if (m_czyKamien)
    {
        m_kamien.rysuj(target);
    }
    else
    {
        m_paletka.draw(target);
    }

    m_pilka.draw(target);

    for (auto& blok : m_bloki)
        blok.draw(target);

    renderCountdown(target);//odliczanie jesli aktywne

    if (m_wygrana)
    {
        sf::RectangleShape overlay(sf::Vector2f(640, 480));
        overlay.setFillColor(sf::Color(0, 0, 0, 180));//polprzezroczyste tlo 
        target.draw(overlay);
        target.draw(m_wygranaText);
    }
}

void Game::startCountdown()
{
    m_isCountingDown = true;
    m_countdownValue = 3;
    m_countdownClock.restart();
    m_countdownText.setString("3");
    m_countdownText.setScale(1.f, 1.f);
    m_countdownText.setFillColor(sf::Color::Yellow);
    m_countdownText.setPosition(WIDTH / 2 - m_countdownText.getLocalBounds().width / 2,
        HEIGHT / 2 - m_countdownText.getLocalBounds().height / 2);//wysrodkowanie tekstu
}

void Game::updateCountdown()
{
    if (!m_isCountingDown) return;

    if (m_countdownClock.getElapsedTime().asSeconds() >= 1.0f)//odliczanie co sekunde
    {
        m_countdownValue--;
        m_countdownClock.restart();

        if (m_countdownValue == 3)
            m_countdownText.setFillColor(sf::Color::Red);
        else if (m_countdownValue == 2)
            m_countdownText.setFillColor(sf::Color::Yellow);
        else if (m_countdownValue == 1)
            m_countdownText.setFillColor(sf::Color::Green);
        else if (m_countdownValue == 0)
            m_countdownText.setFillColor(sf::Color::Green);
        //aktualizuje tekst
        if (m_countdownValue > 0)
            m_countdownText.setString(std::to_string(m_countdownValue));
        else if (m_countdownValue == 0)
            m_countdownText.setString("START!");
        else
        {
            m_isCountingDown = false;
            return;
        }

        m_countdownText.setPosition(WIDTH / 2 - m_countdownText.getLocalBounds().width / 2,
            HEIGHT / 2 - m_countdownText.getLocalBounds().height / 2);
    }
}

void Game::renderCountdown(sf::RenderTarget& target)//wyswietlanie odliczania
{
    if (m_isCountingDown)
    {
        sf::RectangleShape overlay(sf::Vector2f(640, 480));
        overlay.setFillColor(sf::Color(0, 0, 0, 150));
        target.draw(overlay);
        target.draw(m_countdownText);
    }
}

void Game::zamienPaletkeWKamien()//mowi samo za siebie :D
{
    m_czyKamien = true;
    float xPaletki = m_paletka.getX();
    float yPaletki = m_paletka.getY();
    m_kamien = Kamien(xPaletki, yPaletki);
}