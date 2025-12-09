#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include "Paletka.h"
#include "Pilka.h"
#include "Stone.h"
#include <string>

struct BlockData {
    float x, y;
    int hp;
};//struktura przechowujaca dane bloku

class StatusGry {
private:
    //pobranie aktualnych pozycji
    sf::Vector2f paddlePosition;
    sf::Vector2f ballPosition;
    sf::Vector2f ballVelocity;
    std::vector<BlockData> blocks;

public:
    StatusGry() {}
    //przechowywanie aktualnego stanu gry 
    void capture(const Paletka& paletka, const Pilka& pilka, const std::vector<Stone>& stones) {
        //zapisanie wszystkich danych
        paddlePosition = sf::Vector2f(paletka.getX(), paletka.getY());
        ballPosition = sf::Vector2f(pilka.getX(), pilka.getY());
        ballVelocity = sf::Vector2f(pilka.getVx(), pilka.getVy());

        blocks.clear();//wyczyszczenie wektora bloków
        for (const auto& stone : stones) {
            BlockData dane;
            dane.x = stone.getPosition().x;
            dane.y = stone.getPosition().y;
            dane.hp = stone.getHP();
            blocks.push_back(dane);//dodanie bloku do wektora
        }
    }
    //gettery
    sf::Vector2f getPaddlePosition() const { return paddlePosition; }
    sf::Vector2f getBallPosition() const { return ballPosition; }
    sf::Vector2f getBallVelocity() const { return ballVelocity; }
    const std::vector<BlockData>& getBlocks() const { return blocks; }

    bool ZapiszdoPliku(const std::string& NazwaPliku)//zapisanie do pliku
    {
        std::ofstream file(NazwaPliku);
        if (!file.is_open())
        {
            return false;
        }
        //zapis kolejnych danych
        file << "paletka " << paddlePosition.x << " " << paddlePosition.y << std::endl;
        file << "pilka " << ballPosition.x << " " << ballPosition.y <<" " << ballVelocity.x<< " "<< ballVelocity.y<<std::endl;
        file << "liczba_blokow " << blocks.size() << std::endl;
        for (const auto& block : blocks)//zapis danych dla kazdego bloku
        {
            file << block.x << " " << block.y << " " <<block.hp<< std::endl;
        }
        file.close();
        return true;
    }
    bool WczytajzPliku(const std::string& NazwaPliku)//wczytanie danych
    {
        std::ifstream file(NazwaPliku);
        if (!file.is_open())
        {
            return false;
        }

        std::string pozycja;//zmienna do odczytu pozycji
        //pobranie kolejnych danych
        file >> pozycja >> paddlePosition.x >> paddlePosition.y;
        file >> pozycja >> ballPosition.x >> ballPosition.y >> ballVelocity.x >> ballVelocity.y;

        int liczbaBlokow;
        file >> pozycja >> liczbaBlokow;

        blocks.clear();//wyczyszczenie wektora
        //wstawiamy nowe bloki
        for (int i = 0; i < liczbaBlokow; ++i)
        {
            BlockData dane;
            file >> dane.x >> dane.y >> dane.hp;
            blocks.push_back(dane);//dodanie bloku do wektora
        }

        file.close();
        return true;
    }
};
