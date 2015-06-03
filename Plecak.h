#pragma once
#include "stdafx.h"

typedef unsigned int uint;

struct przedmiot{
	przedmiot(uint rozm, uint wart){ rozmiar = rozm, wartosc = wart; }	//konstruktor

	uint rozmiar, wartosc;
};
struct porownajPrzedmioty{
	//porównuje przedmioty malej¹co po stosunku wartoœci do rozmiaru
	bool operator() (const przedmiot &przedmiot1, const przedmiot &przedmiot2){
		if (static_cast<double>(przedmiot1.wartosc) / static_cast<double>(przedmiot1.rozmiar) < 
		  static_cast<double>(przedmiot2.wartosc) / static_cast<double>(przedmiot2.rozmiar)) 
			return true;
		else return false;
	}
};
typedef priority_queue<przedmiot, vector<przedmiot>, porownajPrzedmioty> KolejkaPrzedm;

class Plecak
{
public:
	Plecak();
	~Plecak();
	bool problemPlecakowy();
	void wyswietlPlecak();
	bool generujPrzedmioty(uint iloscPrzedmiotow);
	bool wczytajZPliku(const char[]);
private:
	uint plecakRekur(uint dostepneMiejsce, uint n);
	void wyczysc();
	KolejkaPrzedm przedmioty;
	list<przedmiot> plecak;
	uint wartoscWPlecaku;
	uint pojemnosc;									//pojemnoœæ plecaka
	uint n;											//iloœæ przedmiotów jakie mamy do umieszczenia w plecaku
	bool wczytanoPrzedmioty;
	ifstream plik;									//uchwyt wejœcia pliku
};
