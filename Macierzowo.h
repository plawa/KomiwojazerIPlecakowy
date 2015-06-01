#pragma once
#include "stdafx.h"

using namespace std;
#define UINT_MAX 4294967295 //max zakres dla unsigned int

typedef unsigned int uint;

class Macierzowo {
public:
	Macierzowo();
	~Macierzowo();
	bool wczytajZPliku(const char nazwaPliku[]);
	void wyswietl(); //wy�wietla graf w postaci macierzy s�siedztwa na ekranie
	bool generujLosowoNieskierowany(uint v, int gestosc); //g�sto�� w %
	bool generujLosowoSkierowany(uint v, int gestosc); //g�sto�� w %
private:
	bool utworzGraf(uint iloscWierzcholkow); //tworzy pusty graf (same wierzcho�ki, bez kraw�dzi)
	bool utworzGraf(); //tworzy pusty graf nie zmieniaj�c obecnej ilo�ci wierzcho�k�w
	void usunGraf(); //czy�ci pami�� z nieu�ywanego ju� grafu
	void usun(uint **macierz);
	void usun(bool **macierz);
	void wyswietl(uint **macierz);
	bool pierwszeWczytywanie;
	uint **graf; //nr wiersza/nr kolumny - macierz s�siedztwa grafu
	uint v; //ilo�� wierzcho�k�w
	uint e; //ilo�� kraw�dzi
	FILE *plik; //uchwyt I/O
};
