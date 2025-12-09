#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "MenuPauzy.h"
#include "Game.h"
#include <iostream>
#include "Zapis.h"

enum class GameState { Menu, Playing, Paused, Exiting }; //wyliczenie pozwalajace przyjac kilka stanow gry 

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "Arkanoid");
    window.setFramerateLimit(60);
    //tworzenie menu i gry
    Menu menu(640.0f, 480.0f);
    MenuPauzy menuPauzy(640.0f, 480.0f);
    Game game;

    GameState currentState = GameState::Menu;
    sf::Clock clock;//odpalenie zegara do klatek

    while (window.isOpen())
    {
        sf::Time dt = clock.restart();//ile czasu minelo od poprzedniej klatki
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (currentState == GameState::Menu)//menu glowne
            {
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Up) menu.moveUp();
                    if (event.key.code == sf::Keyboard::Down) menu.moveDown();

                    if (event.key.code == sf::Keyboard::Enter)
                    {
                        if (menu.getSelectedItem() == 0)//nowa gra
                        {
                            currentState = GameState::Playing;
                            game.startCountdown();
                        }
                        else if (menu.getSelectedItem() == 1)//wczytanie
                        {
                            if (game.wczytajGre("savegame.txt"))
                            {
                                std::cout << "Gra wczytana!\n";
                                currentState = GameState::Playing;
                                game.startCountdown();
                            }
                            else
                            {
                                std::cout << "Blad wczytywania gry!\n";
                            }
                        }
                    }
                }
            }
            else if (currentState == GameState::Playing)
            {
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Escape)
                        currentState = GameState::Paused;
                }
            }
            else if (currentState == GameState::Paused)//escape
            {
                if (event.type == sf::Event::KeyPressed)//mawigacja w menu pauzy
                {
                    if (event.key.code == sf::Keyboard::Up) menuPauzy.moveUp();
                    if (event.key.code == sf::Keyboard::Down) menuPauzy.moveDown();

                    if (event.key.code == sf::Keyboard::Enter)
                    {
                        if (menuPauzy.getSelectedItem() == 0)//kontynuuj
                        {
                            currentState = GameState::Playing;
                            game.startCountdown();//odliczanie
                        }
                        else if (menuPauzy.getSelectedItem() == 1)//zapis
                        {
                            StatusGry status;
                            status.capture(game.getPaletka(), game.getPilka(), game.getBloki());
                            if (status.ZapiszdoPliku("savegame.txt"))
                            {
                                std::cout << "GRA ZOSTALA ZAPISANA";
                            }
                        }
                        else if (menuPauzy.getSelectedItem() == 2)//wyjscie z gry
                            window.close();
                    }
                }
            }
        }

        if (currentState == GameState::Playing)
            game.update(dt);//sprawdzanie kolizji itp

        if (game.isGameOver())
        {
            std::cout << "MISS! KONIEC GRY\n";
            window.close();
        }

        window.clear();

        if (currentState == GameState::Menu)
            menu.draw(window);//rysowanie menu glownego
        else if (currentState == GameState::Playing)
            game.render(window);//rysowanie ogolne wszystkich obiektow w grze
        else if (currentState == GameState::Paused)
        {
            game.render(window);
            sf::RectangleShape tlo(sf::Vector2f(640.0f, 480.0f));
            tlo.setFillColor(sf::Color(0, 0, 0, 150));//fajne przezroczyste tlo hihi
            window.draw(tlo);
            menuPauzy.draw(window);//menu 2
        }

        window.display();
    }

    return 0;
}