#include "stdafx.h"
#include "Plecak.h"

ostream& operator << (ostream& wyjscie, const przedmiot& przedm){				//przeci¹¿enie operatora dla przejrzystego wyœwietlania przedmiotów
	return wyjscie << "(" << przedm.rozmiar << ", " << przedm.wartosc << ")";
}
Plecak::Plecak()
{
	wczytanoPrzedmioty = false;
}
Plecak::~Plecak()
{
	wyczysc();
}

bool Plecak::problemPlecakowyIl(){				
	//rozwi¹zuje problem plecakowy z sortawaniem po ilorazie
	if (przedmiotyIl.empty())					//jeœli nie ma dostêpnych przedmiotów do rozdysponowania,
		return false;							//to zakoñcz
	plecak.clear();								//jeœli plecak nie jest pusty, to opró¿niamy
	uint dostepneMiejsce = pojemnosc;
	wartoscWPlecaku = 0;
	while (!przedmiotyIl.empty()){
		if (przedmiotyIl.top().rozmiar <= dostepneMiejsce){
			plecak.push_back(przedmiotyIl.top());
			dostepneMiejsce -= przedmiotyIl.top().rozmiar;
			wartoscWPlecaku += przedmiotyIl.top().wartosc;
			przedmiotyIl.pop();
		}
		else
			przedmiotyIl.pop();
	}
	return true;
}

bool Plecak::problemPlecakowyWar(){
	//rozwi¹zuje problem plecakowy z sortowaniem po wartoœci elementu
	if (przedmiotyWar.empty())					//jeœli nie ma dostêpnych przedmiotów do rozdysponowania,
		return false;							//to zakoñcz
	plecak.clear();								//jeœli plecak nie jest pusty, to opró¿niamy
	uint dostepneMiejsce = pojemnosc;
	wartoscWPlecaku = 0;
	while (!przedmiotyWar.empty()){
		if (przedmiotyWar.top().rozmiar <= dostepneMiejsce){
			plecak.push_back(przedmiotyWar.top());
			dostepneMiejsce -= przedmiotyWar.top().rozmiar;
			wartoscWPlecaku += przedmiotyWar.top().wartosc;
			przedmiotyWar.pop();
		}
		else
			przedmiotyWar.pop();
	}
	return true;
}

void Plecak::wyswietlPlecak(){
	cout << endl << "format: (rozmiar, wartosc)" << endl;
	for (list<przedmiot>::iterator iter = plecak.begin(); iter != plecak.end(); iter++)
		cout << *iter << ", ";
	cout << endl << endl << "Wszystkie przedmioty w plecaku warte sa " << wartoscWPlecaku << endl;
}

void Plecak::wyczysc(){
	while (!przedmiotyIl.empty()) { //nie trzeba sprawdzaæ warunku dla obu, bo zawieraj¹ tyle samo elementów
		przedmiotyIl.pop();
		przedmiotyWar.pop();
	}
	plecak.clear();
}

bool Plecak::generujPrzedmioty(uint iloscPrzedmiotow, uint pojemnoscPlecaka){
	uint calkowityRozmiar = 0;
	n = iloscPrzedmiotow;
	pojemnosc = pojemnoscPlecaka;
	if (wczytanoPrzedmioty)
		wyczysc();
	//cout << endl << "format: (rozmiar, wartosc)" << endl;
	for (uint i = 1; i < n; i++){					//w pêtli dodajemy o 1 mniej przedmiotów ni¿ ¿¹dane
		uint rozmiar = rand() % 20 + 1;
		przedmiot *nowy = new przedmiot(rozmiar, rand() % 50 + 1);
		przedmiotyIl.push(*nowy);
		//przedmiotyWar.push(*nowy);
		calkowityRozmiar += rozmiar;
		//cout << *nowy << ", ";
	}
	if (calkowityRozmiar < pojemnosc){				//jeœli sumaryczny rozmiar przedmiotów jest mniejsze od pojemnoœci plecaka, to
		//dodajemy przedmiot, który wype³ni tê ró¿nicê i bêdzie co najmniej o 1 wiêkszy
		przedmiot *nowy = new przedmiot(pojemnosc - calkowityRozmiar + rand() % 20 + 1, rand() % 50 + 1);
		przedmiotyIl.push(*nowy);
		//przedmiotyWar.push(*nowy);
		//cout << *nowy;
	}
	else {
		przedmiot *nowy = new przedmiot(rand() % 20 + 1, rand() % 50 + 1);
		przedmiotyIl.push(*nowy);
		//przedmiotyWar.push(*nowy);
		//cout << *nowy;
	}
	//cout << endl << endl << "pojemnosc plecaka wynosi: " << pojemnosc << endl;
	return true;
}

bool Plecak::wczytajZPliku(const char nazwaPliku[]){
	uint rozmiarTmp, wartoscTmp;
	plik.open(nazwaPliku);						//otwarcie pliku do odczytu
	if (plik.is_open()){						//sprawdzamy, czy otwarcie pliku powiod³o siê, jeœli tak to kontynuujemy
		if (wczytanoPrzedmioty)
			wyczysc();
		plik >> pojemnosc >> n;					//wczytujemy pojemnoœæ plecaka i liczbê elementów jakie chcemy w nim umieœciæ
		cout << endl << "format: (rozmiar, wartosc)" << endl;
		for (uint i = 0; i < n; i++){
			plik >> rozmiarTmp >> wartoscTmp;	//wczytujemy dodajemy do kolejki priorytetowej nowy przedmiot
			przedmiot *nowy = new przedmiot(rozmiarTmp, wartoscTmp);
			przedmiotyIl.push(*nowy);
			przedmiotyWar.push(*nowy);
			cout << *nowy << ", ";
		}
		plik.close();							//zamykamy plik
		wczytanoPrzedmioty = true;
		cout << "a pojemnosc plecaka wynosi: " << pojemnosc << endl;
		return true;							//zwracamy informacjê o powodzeniu
	}
	else return false;							//jeœli otwarcie pliku nie powiod³o siê, to zwracamy informacjê o b³êdzie
}
