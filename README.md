# GraphicEngine
Multiplatformowy silnik graficzny 3D wykonany w oparciu o OpenGL.

## Struktura katalogów

	/src		Kod źródłowy
	/contrib	Biblioteki zewnętrzne
	/docs		Screenshoty
	/test		Testy jednostkowe
	/res		Zasoby
	/include	Pliki nagłówkowe


## Demo
    ESC - Wyjście z programu
    L-CTRL - Wyłączenie/Włączenie menu
    W, S, A, D - Poruszanie kamerą (jeśli menu wyłączone)

#### Wczytywanie modeli + YUV
Zadaniem tego dema jest wczytanie modelu kostki 
oraz pozwolenie na obracanie modelu 
i zmianę tekstury na któryś z komponentów YUV.

![alt text](https://github.com/Porok12/GraphicEngine/blob/master/docs/demo1.gif?raw=true)

#### Efekty cząsteczkowe
Zadaniem tego dema jest zaprezentowanie czterech 
przykładowych efektów cząsteczkowych.

![alt text](https://github.com/Porok12/GraphicEngine/blob/master/docs/demo2.gif?raw=true)

#### Rodzaje cieniowania
Zadaniem tego dema jest zaprezentowanie czterech różnych cieniowań.

![alt text](https://github.com/Porok12/GraphicEngine/blob/master/docs/demo3.gif?raw=true)

#### Rodzaje światła
Zadaniem tego dema jest pokazanie trzech rodzai świateł.

![alt text](https://github.com/Porok12/GraphicEngine/blob/master/docs/demo4.gif?raw=true)

#### Rodzaje tekstur
Zadaniem tego dema jest pokazanie wpływu różnych tekstur na wygląd modeli.
Za pomocą suwaka można zmieniać wartość korekcji gamma.

![alt text](https://github.com/Porok12/GraphicEngine/blob/master/docs/demo5.gif?raw=true)

#### Dithering
Zadaniem tego dema jest zaprezentowanie ditheringu 'ordered'.
Można zmieniać wielkość mapy progowania, ilość kolorów oraz rodzaj palety.

![alt text](https://github.com/Porok12/GraphicEngine/blob/master/docs/demo6.gif?raw=true)

#### Rozmycie gaussowskie
Zadaniem tego dema jest zaprezentowanie działania rozmycia Gaussa.
Można zmieniać jądro, sigme oraz ilość iteracji.

![alt text](https://github.com/Porok12/GraphicEngine/blob/master/docs/demo7.gif?raw=true)

#### Bresenham
Zadaniem tego dema jest zaprezentowanie rasteryzacji odcinka, okręgu i elipsy.
Za pomocą myszki można rysować kształty oraz wypełniać je kolorem (SCROLL zmienia kolor).

![alt text](https://github.com/Porok12/GraphicEngine/blob/master/docs/demo8.gif?raw=true)

#### Sierpinski
To demo pozwala na renderowanie piramidy Sierpińskiego, kostki Mengera. 
Ilość iteracji jest wybierana przez użytkownika. Wyłączenie menu (CTRL) pozwala na poruszanie się w przestrzeni (WSAD + myszka).

![alt text](https://github.com/Porok12/GraphicEngine/blob/master/docs/demo9.gif?raw=true)

## Wymagnia (Ubuntu)

    sudo apt-get install libboost-all-dev
    sudo apt-get install libgl1-mesa-dev
    sudo apt-get install libxrandr-dev
    sudo apt-get install libx11-dev libxrandr-dev libxcursor-dev libxi-dev libxinerama-dev


## Budowanie projektu

    cd <projekt>
    mkdir build
    cd build
    cmake ..
    make
