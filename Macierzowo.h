#pragma once
#include "stdafx.h"

typedef unsigned int uint;

class Macierzowo {
public:
	Macierzowo();
	~Macierzowo();
	bool wczytajZPliku(const char nazwaPliku[]);
	void wyswietl(); //wyœwietla graf w postaci macierzy s¹siedztwa na ekranie
	bool generujLosowoNieskierowany(uint v, int gestosc); //gêstoœæ w %
	bool generujLosowoSkierowany(uint v, int gestosc); //gêstoœæ w %
	void problemKomiwojazera();
	void wyswietlRozwiazanie();
private:
	void KomiRekur(uint v);
	bool utworzGraf(uint iloscWierzcholkow); //tworzy pusty graf (same wierzcho³ki, bez krawêdzi)
	bool utworzGraf(); //tworzy pusty graf nie zmieniaj¹c obecnej iloœci wierzcho³ków
	void usunGraf(); //czyœci pamiêæ z nieu¿ywanego ju¿ grafu
	void usun(uint **macierz);
	void usun(bool **macierz);
	void wyswietl(uint **macierz);
	bool pierwszeWczytywanie;
	uint **graf; //nr wiersza/nr kolumny - macierz s¹siedztwa grafu
	uint n; //iloœæ wierzcho³ków
	uint e; //iloœæ krawêdzi
	ifstream plik; //uchwyt I/O

	//dla komiwojazera
	uint *wynik;						//tablica z wynikiem
	uint *tempSciezka;					//tymczasowa sciezka, mozliwa najwieksza
	bool *odwiedzone;                    // Tablica odwiedzin
	uint v0, droga, tempDroga, sptr, shptr;
};
