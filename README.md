#informatyka_2025_projekt
Autor: Jakub Mitura s204082
Temat projektu: Gra typu bricks breaker

Zakres indywidualny: Celem gry jest zniszczenie wszystkich bloków widocznych na ekranie. Gracz robi to, odbijając piłkę tak, aby trafiała w kolejne bloki i powodowała ich zniknięcie. Po usunięciu wszystkich elementów pojawia się zielony napis WYGRANA, a aplikacja zamyka się po 3 sekundach.
W tle generowane jest losowe, gwieździste niebo, które ma imitować kosmos i nadaje rozgrywce dodatkowej estetyki. Na dole ekranu znajduje się paletka sterowana przez gracza. Jej zadaniem jest uniemożliwić piłce wypadnięcie poniżej dolnej krawędzi. Jeśli jednak do tego dojdzie, paletka zamienia się w kamień i spada poza ekran, a po 3 sekundach gra zostaje zamknięta.

Gra posiada 9 klas oraz spełnia wymagania projektu narzucone przez prowadzącego. Poniżej krótkie wyjaśnienie spełnienia każdego wymogu 
Klasy:
    Game - zarzadzanie rozgrywkaS
    Paletka, Pilka, Stone - obiekty gry 
    Kamien - animacja pod koniec gry
    Menu, MenuPauzy - interfejs
    StatusGry, Zapis - system zapisu

Wymagania:

1.Program w trybie graficznym z animowanymi obiektami. 
    Program wykorzustuje biblioteke SFML do renderowania grafiki 2D oraz rysuje różne kształty

2.Sterowanie użytkownika z klawiatury
    Sterowanie za pomocą A/D oraz strzałek

3.Co najmniej 4 elementy animowane (w tym jeden o nieregularnym kształcie i jedendynamiczny tekstowy).
    Elementami animowanymi są: Paletka, Piłka, Stone, Napis przed początkiem gry, po odpałzowaniu oraz WYGRANA na koniec, elementem animowanym o nieregularnym kształcie jest kamień (10pkt) w który zmienia się paletka po przegraniu gry i który wypada poza dolną krawędź ekranu (jak w mario)

4.Mechanizmy kolizji pomiędzy obiektami.
    Kolizje pomiędzy paletką i piłką oraz piłką i ścianami, blokami

Punkty 5 i 6 są zrealizowane razem
5.Struktury danych i klasy przechowujące obiekty i ich parametry.
6.Zapis i odczyt stanu gry.
    Struktury danych oraz klasy przechowujące obiekty i ich parametry związane są z zapisem stanu gry.

7.Funkcje z arametrem przekazywanym przez wskaźnik lub referencję.
    Zrealizowane w kolizjach, rysowaniu obiektów oraz przekazywaniu danych.

8.Obsługa zakończenia programu, przechodzenie między ekranami.
    Obsługa zakończenia gry oraz przejść między ekranami została zrealizowana przy użyciu enum class GameState. Dzięki temu nie ma potrzeby posługiwania się cyframi, które byłyby mniej czytelne i nienaturalne podczas zarządzania stanami gry.

9.Obiektowa architektura programu – klasy reprezentujące obiekty, logikę i interfejs.
    Game - zarzadzanie rozgrywka
    Paletka - sterowanie, rysowanie paletki 
    Pilka - fizyka i rysowanie piłki
    Stone - stan i wygląd bloków
    Kamien - animacja pod koniec gry
    Menu, MenuPauzy - interfejs
    StatusGry - przechwytywanie stanu gry 
