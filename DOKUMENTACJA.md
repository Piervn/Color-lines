# Dokumentacja dla użytkownika
## Zasady gry
Zadaniem gracza jest usuwanie kulek z planszy przez ustawianie obok siebie w ciągłej linii (poziomej, pionowej lub ukośnej) pięciu lub więcej kulek jednakowego koloru.

Za każdą usuniętą kulkę otrzymuje się jeden punkt.

W jednym ruchu dowolną kulkę można przestawić na puste pole planszy, jeśli istnieje do niego dojście, poruszając się po sąsiednich pustych polach planszy (sąsiednie pola przylegają do siebie bokiem).

Jeśli przestawienie powoduje usunięcie kulek, to gracz wykonuje od razu kolejne przestawienie, a jeśli nie powoduje, na planszy pojawiają się trzy nowe kulki.

Gra kończy się w momencie zapełnienia planszy.
## Działanie
* Aby przemieścić kulkę, należy kliknąć w wybraną kulkę, po czym kliknąć w wybrane puste pole.
* Kiedy użytkownik wybierze pole niedozwolone, pojawi się stosowny komunikat.
* Kiedy plansza zostanie wypełniona kulkami gra zakończy się, a wybranie kulki wyświetli stosowny komunikat.

Nad planszą znajduje się:

* Suma zdobytych przez gracza punktów.
* Wykaz 3 kolorów kulek, które pojawią się po kolejnym ruchu nie usuwającym kulek.
* Przycisk `Nowa gra` służący do rozpoczęcia nowej gry, co za tym idzie, zrestartowania planszy.
* Przycisk `Zapisz grę` służący do zapisania postępu gry. Jest to jeden slot do zapisu.
* Przycisk `Wczytaj grę` służący do wczytania postępu gry ze slotu. Jeśli gra nie została dotychczas zapisana, pojawi się stosowny komunikat.
* Przycisk `Wyjdź z gry` służący do opuszczenia gry.
