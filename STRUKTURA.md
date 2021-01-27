# Struktura programu
## Moduły
Projekt złożony jest z następujących modułów:

* `main.c` - funkcja `main` oraz funkcje wywoływane po kliknięciu danych przycisków.
* `BFS.c` - algorytm BFS, dzięki któremu sprawdzam czy istnieje droga pomiędzy wybranymi przez gracza komórkami.
* `kolejka.c` - struktura danych - kolejka oraz operacje dodawania, usuwania itd. z kolejki.
* `kulki.h` - plik nagłówkowy zawierający wykorzystywane biblioteki oraz nagłówki wszystkich funkcji.

Zawiera również folder `grafika`, w którym znajdują się niezbędne pliki `.png`.

## Funkcje modułu `main.c`

* `saveGame()` - zapisywanie gry do pliku.
* `loadGame()` - wczytywanie gry z pliku.
* `intToString()` - zmiana typu zmiennej z `int` na `*char`.
* `putNextBalls()` - umieszczanie nowo wylosowanych kolorów kulek w spisie nad planszą.
* `nextBalls()` - losowanie kolorów następnych kulek.
* `deleteCorrectRow()` - usuwanie kulek, jeśli po ruchu znaleziono rząd / kolumne / skos złożony conajmniej z 5 kulek.
* `newGame()` - tworzenie nowej gry.
* `addBalls()` - dodawanie kulek na planszę o kolorach podanych w spisie u góry.
* `putColor()` - dany kolor kulki z wcześniej wylosowanego jej numeru.
* `putColor()` - dany kolor dla spisu nad planszą.
* `colorNum()` - losowanie numeru koloru kulki.
* `chooseBall()` - funkcja wykonywana po kliknięciu w pole na planszy. Sprawdzanie czy plansza jest pełna, sprawdzanie czy kliknięto w pole z kulką, zapisywywanie koordynatów pola.
* `moveBall()` - funkcja, w której dzieje się najwięcej, wywoływana po kilknięciu w pole na planszy. Sprawdzanie czy wcześniej kliknięto w pole z kulką i czy teraz kliknięto w puste pole. Sprawdzanie czy istnieje ścieżka pomiędzy wybranymi polami (algorytm BFS). Przemieszczenie kulki. Wykorzystanie powyższych funkcji do działań po ruchu.
* `main()` - tworzenie planszy, kontrolek nad planszą. Podstawowe rozpoczęcie gry.
