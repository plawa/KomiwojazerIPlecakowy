#pragma once
#include "stdafx.h"

typedef unsigned int uint;

class Macierzowo {
public:
	Macierzowo();
	~Macierzowo();
	bool wczytajZPliku(const char nazwaPliku[]);
	void wyswietl(); //wy�wietla graf w postaci macierzy s�siedztwa na ekranie
	bool generujLosowoNieskierowany(uint v, int gestosc); //g�sto�� w %
	bool generujLosowoSkierowany(uint v, int gestosc); //g�sto�� w %
	void problemKomiwojazera();
	void wyswietlRozwiazanie();
private:
	void KomiRekur(uint v);
	bool utworzGraf(uint iloscWierzcholkow); //tworzy pusty graf (same wierzcho�ki, bez kraw�dzi)
	bool utworzGraf(); //tworzy pusty graf nie zmieniaj�c obecnej ilo�ci wierzcho�k�w
	void usunGraf(); //czy�ci pami�� z nieu�ywanego ju� grafu
	void usun(uint **macierz);
	void usun(bool **macierz);
	void wyswietl(uint **macierz);
	bool pierwszeWczytywanie;
	uint **graf; //nr wiersza/nr kolumny - macierz s�siedztwa grafu
	uint n; //ilo�� wierzcho�k�w
	uint e; //ilo�� kraw�dzi
	ifstream plik; //uchwyt I/O

	//dla komiwojazera
	uint *wynik;						//tablica z wynikiem
	uint *tempSciezka;					//tymczasowa sciezka, mozliwa najwieksza
	bool *odwiedzone;                    // Tablica odwiedzin
	uint v0, droga, tempDroga, sptr, shptr;
};
