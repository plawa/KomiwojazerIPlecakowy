#pragma once
#include "stdafx.h"

typedef unsigned int uint;

class Macierzowo {
public:
	Macierzowo();
	~Macierzowo();
	bool wczytajZPliku(const char nazwaPliku[]);	//wczytuje graf z pliku tekstowego
	void wyswietl();								//wy�wietla graf w postaci macierzy s�siedztwa na ekranie
	bool generujLosowo(uint n);						//generuje losowo graf pe�ny skierowany o podanej liczbie wierzcho�k�w
	void problemKomiwojazera();						//rozwi�zuje problem komiwoja�era dla obecnie wczytanego grafu pe�nego skierowanego
	void wyswietlRozwiazanie();						//wy�wietla rozwi�zanie problemu komiwoja�era, po wcze�niejszym wykonaniu powy�szej funkcji
private:
	void KomiRekur(uint v);
	bool utworzGraf(uint iloscWierzcholkow);		//tworzy pusty graf (same wierzcho�ki, bez kraw�dzi)
	bool utworzGraf();								//tworzy pusty graf nie zmieniaj�c obecnej ilo�ci wierzcho�k�w
	void usunGraf();								//czy�ci pami�� z nieu�ywanego ju� grafu
	void usun(uint **macierz);
	void wyswietl(uint **macierz);
	bool pierwszeWczytywanie;
	uint **graf;									//nr wiersza/nr kolumny - macierz s�siedztwa grafu
	uint n;											//ilo�� wierzcho�k�w
	ifstream plik;									//uchwyt wej�cia pliku

	//dla komiwojazera
	uint *wynik;									//tablica z rozwi�zaniem problemu komiwoja�era
	uint *tempSciezka;								//tymczasowa sciezka, pomocnicza przy wyszukiwaniu cyklu Hamiltona
	bool *odwiedzone;								//tablica zawieraj�ca informacje kt�re wierzcho�ki zosta�y ju� odwiedzone
	bool znalezionoCykl;							//zawiera informacj�, czy problem zosta� rozwiazany i czy znaleziono w nim cho� jeden cykl Hamiltona
	uint v0;										//wierzcho�ek pocz�tkowy
	uint odleglosc;									//suma wag najkr�tszego cyklu Hamiltona znalezionego podczas rozwi�zywania problemu komiwoja�era
	uint tempOdleg;									//suma wag obecnie rozpatrywanego cyklu Hamiltona
	uint wsk;									//przechowuje numer wierzcho�ka, z kt�rego ostatnio wyszukiwano cykl
};
