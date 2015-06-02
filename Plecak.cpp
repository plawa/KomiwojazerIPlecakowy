#include "stdafx.h"
#include "Plecak.h"


Plecak::Plecak()
{
	wczytanoPrzedmioty = false;
}


Plecak::~Plecak()
{
}

void Plecak::problemPlecakowy(){
	for (uint i = 0; i < n; i++)
		wPlecaku[i] = false;
	wartoscWPlecaku = plecakRekur(pojemnosc, n);
}

//************************************************************
//*** ALGORYTM REKURENCYJNY ROZWI�ZUJ�CY PROBLEM PLECAKOWY ***
//************************************************************
uint Plecak::plecakRekur(uint dostepneMiejsce, uint n)
{
	if (n == 0 || dostepneMiejsce == 0)						//przypadek podstawowy - dost�pne miejsce lub przedmioty ulegn� wyczerpaniu
		return 0;
	if (rozmiar[n - 1] > dostepneMiejsce)						//je�li rozmiar n-tego przedmiotu jest wi�kszy ni� pojemno�� plecaka, to
		return plecakRekur(dostepneMiejsce, n - 1);			//taki element nie mo�e zosta� w nim zawarty, szukamy dalej
	else {
		wPlecaku[n] = true;
		//zwraca maksymaln� mo�liw� (niewykraczaj�c� poza rozmiar plecaka) warto�� - pierwsza z elementem, lub druga bez niego
		return max(wartosc[n - 1] + plecakRekur(dostepneMiejsce - rozmiar[n - 1], n - 1), plecakRekur(dostepneMiejsce, n - 1));
	}
}

void Plecak::wyswietlPrzedmioty(){
	cout << "element: ";
	for (uint i = 0; i < n; i++)
		cout << i << " ";
	cout << endl << "rozmiar: ";
	for (uint i = 0; i < n; i++)
		cout << rozmiar[i] << " ";
	cout << endl << "wartosc: ";
	for (uint i = 0; i < n; i++)
		cout << wartosc[i] << " ";
	cout << endl;
}

void Plecak::wyswietlPlecak(){
	//cout << "element: ";
	//for (uint i = 0; i < n; i++)
	//	if (wPlecaku[i])
	//		cout << i << " ";
	//cout << endl << "rozmiar: ";
	//for (uint i = 0; i < n; i++)
	//	if (wPlecaku[i])
	//		cout << rozmiar[i] << " ";
	//cout << endl << "wartosc: ";
	//for (uint i = 0; i < n; i++)
	//	if (wPlecaku[i])
	//		cout << wartosc[i] << " ";
	cout << endl << endl << "Waszystkie przedmioty w plecaku warte sa " << wartoscWPlecaku << endl;
}

void Plecak::wyczysc(){
	delete[] wartosc, rozmiar, wPlecaku;
}

void Plecak::rezerwujPrzedmioty(){
	rozmiar = new uint[n];
	wartosc = new uint[n];
	wPlecaku = new bool[n];
}

bool Plecak::generujPrzedmioty(uint iloscPrzedmiotow){
	n = iloscPrzedmiotow;
	rezerwujPrzedmioty();
	for (uint i = 0; i < n; i++){
		rozmiar[i] = rand() % 30 + 1;
		wartosc[i] = rand() % 80 + 1;
	}
	return true;
}

bool Plecak::wczytajZPliku(const char nazwaPliku[]){
	plik.open(nazwaPliku);						//otwarcie pliku do odczytu
	if (plik.is_open()){						//sprawdzamy, czy otwarcie pliku powiod�o si�, je�li tak to kontynuujemy
		if (wczytanoPrzedmioty)
			wyczysc();
		plik >> pojemnosc >> n;					//wczytujemy pojemno�� plecaka i liczb� element�w jakie chcemy w nim umie�ci�
		rezerwujPrzedmioty();
		for (uint i = 0; i < n; i++)
			plik >> rozmiar[i] >> wartosc[i];	//wczytujemy i przypisujemy ka�demu przedmiotowi rozmiar oraz warto��
		plik.close();							//zamykamy plik
		wczytanoPrzedmioty = true;
		return true;							//zwracamy informacj� o powodzeniu
	}
	else return false;							//je�li otwarcie pliku nie powiod�o si�, to zwracamy informacj� o b��dzie
}
