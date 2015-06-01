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
	void wyswietl(); //wyœwietla graf w postaci macierzy s¹siedztwa na ekranie
	bool generujLosowoNieskierowany(uint v, int gestosc); //gêstoœæ w %
	bool generujLosowoSkierowany(uint v, int gestosc); //gêstoœæ w %
private:
	bool utworzGraf(uint iloscWierzcholkow); //tworzy pusty graf (same wierzcho³ki, bez krawêdzi)
	bool utworzGraf(); //tworzy pusty graf nie zmieniaj¹c obecnej iloœci wierzcho³ków
	void usunGraf(); //czyœci pamiêæ z nieu¿ywanego ju¿ grafu
	void usun(uint **macierz);
	void usun(bool **macierz);
	void wyswietl(uint **macierz);
	bool pierwszeWczytywanie;
	uint **graf; //nr wiersza/nr kolumny - macierz s¹siedztwa grafu
	uint v; //iloœæ wierzcho³ków
	uint e; //iloœæ krawêdzi
	FILE *plik; //uchwyt I/O
};
