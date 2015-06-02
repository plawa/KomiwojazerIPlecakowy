#pragma once
typedef unsigned int uint;

//struct przedmiot{
//	uint wartosc, rozmiar;
//};

class Plecak
{
public:
	Plecak();
	~Plecak();
	void problemPlecakowy();
	void wyswietlPlecak();
	void wyswietlPrzedmioty();
	bool generujPrzedmioty(uint iloscPrzedmiotow);
	bool wczytajZPliku(const char[]);
private:
	uint plecakRekur(uint dostepneMiejsce, uint n);
	void rezerwujPrzedmioty();
	void wyczysc();
	uint *rozmiar;
	uint *wartosc;
	bool *wPlecaku;
	uint wartoscWPlecaku;
	uint pojemnosc;									//pojemnoœæ plecaka
	uint n;											//iloœæ przedmiotów jakie chcemy umieœciæ w plecaku
	bool wczytanoPrzedmioty;
	ifstream plik;									//uchwyt wejœcia pliku
};
