#pragma once
#include "stdafx.h"

typedef unsigned int uint;

class Macierzowo {
public:
	Macierzowo();
	~Macierzowo();
	bool wczytajZPliku(const char nazwaPliku[]);	//wczytuje graf z pliku tekstowego
	void wyswietl();								//wyœwietla graf w postaci macierzy s¹siedztwa na ekranie
	bool generujLosowo(uint n);						//generuje losowo graf pe³ny skierowany o podanej liczbie wierzcho³ków
	void problemKomiwojazera();						//rozwi¹zuje problem komiwoja¿era dla obecnie wczytanego grafu pe³nego skierowanego
	void wyswietlRozwiazanie();						//wyœwietla rozwi¹zanie problemu komiwoja¿era, po wczeœniejszym wykonaniu powy¿szej funkcji
private:
	void KomiRekur(uint v);
	bool utworzGraf(uint iloscWierzcholkow);		//tworzy pusty graf (same wierzcho³ki, bez krawêdzi)
	bool utworzGraf();								//tworzy pusty graf nie zmieniaj¹c obecnej iloœci wierzcho³ków
	void usunGraf();								//czyœci pamiêæ z nieu¿ywanego ju¿ grafu
	void usun(uint **macierz);
	void wyswietl(uint **macierz);
	bool pierwszeWczytywanie;
	uint **graf;									//nr wiersza/nr kolumny - macierz s¹siedztwa grafu
	uint n;											//iloœæ wierzcho³ków
	ifstream plik;									//uchwyt wejœcia pliku

	//dla komiwojazera
	uint *wynik;									//tablica z rozwi¹zaniem problemu komiwoja¿era
	uint *tempSciezka;								//tymczasowa sciezka, pomocnicza przy wyszukiwaniu cyklu Hamiltona
	bool *odwiedzone;								//tablica zawieraj¹ca informacje które wierzcho³ki zosta³y ju¿ odwiedzone
	bool znalezionoCykl;							//zawiera informacjê, czy problem zosta³ rozwiazany i czy znaleziono w nim choæ jeden cykl Hamiltona
	uint v0;										//wierzcho³ek pocz¹tkowy
	uint odleglosc;									//suma wag najkrótszego cyklu Hamiltona znalezionego podczas rozwi¹zywania problemu komiwoja¿era
	uint tempOdleg;									//suma wag obecnie rozpatrywanego cyklu Hamiltona
	uint wsk;									//przechowuje numer wierzcho³ka, z którego ostatnio wyszukiwano cykl
};
