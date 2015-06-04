#pragma once
#include "stdafx.h"

typedef unsigned int uint;

struct przedmiot{
	przedmiot(uint rozm, uint wart){ rozmiar = rozm, wartosc = wart; }	//konstruktor

	uint rozmiar, wartosc;
};
struct porownajPrzedmiotyIloraz{
	//por�wnuje przedmioty malej�co po stosunku warto�ci do rozmiaru
	bool operator() (const przedmiot &przedmiot1, const przedmiot &przedmiot2){
		if (static_cast<double>(przedmiot1.wartosc) / static_cast<double>(przedmiot1.rozmiar) < 
		  static_cast<double>(przedmiot2.wartosc) / static_cast<double>(przedmiot2.rozmiar)) 
			return true;
		else return false;
	}
};
typedef priority_queue<przedmiot, vector<przedmiot>, porownajPrzedmiotyIloraz> KolejkaPrzedmIl;

struct porownajPrzedmiotyWartosc{
	//por�wnuje przedmioty malej�co po warto�ciach
	bool operator() (const przedmiot &przedmiot1, const przedmiot &przedmiot2){
		if (przedmiot1.wartosc < przedmiot2.wartosc)
			return true;
		else return false;
	}
};
typedef priority_queue<przedmiot, vector<przedmiot>, porownajPrzedmiotyWartosc> KolejkaPrzedmWar;

class Plecak
{
public:
	Plecak();
	~Plecak();
	bool problemPlecakowyIl();
	bool problemPlecakowyWar();
	void wyswietlPlecak();
	bool generujPrzedmioty(uint iloscPrzedmiotow, uint pojemnoscPlecaka);
	bool wczytajZPliku(const char[]);
private:
	uint plecakRekur(uint dostepneMiejsce, uint n);
	void wyczysc();
	KolejkaPrzedmIl przedmiotyIl;
	KolejkaPrzedmWar przedmiotyWar;
	list<przedmiot> plecak;
	uint wartoscWPlecaku;
	uint pojemnosc;									//pojemno�� plecaka
	uint n;											//ilo�� przedmiot�w jakie mamy do umieszczenia w plecaku
	bool wczytanoPrzedmioty;
	ifstream plik;									//uchwyt wej�cia pliku
};
