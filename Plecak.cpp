#include "stdafx.h"
#include "Plecak.h"

ostream& operator << (ostream& wyjscie, const przedmiot& przedm){				//przeci��enie operatora dla przejrzystego wy�wietlania przedmiot�w
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
	//rozwi�zuje problem plecakowy z sortawaniem po ilorazie
	if (przedmiotyIl.empty())					//je�li nie ma dost�pnych przedmiot�w do rozdysponowania,
		return false;							//to zako�cz
	plecak.clear();								//je�li plecak nie jest pusty, to opr�niamy
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
	//rozwi�zuje problem plecakowy z sortowaniem po warto�ci elementu
	if (przedmiotyWar.empty())					//je�li nie ma dost�pnych przedmiot�w do rozdysponowania,
		return false;							//to zako�cz
	plecak.clear();								//je�li plecak nie jest pusty, to opr�niamy
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
	while (!przedmiotyIl.empty()) { //nie trzeba sprawdza� warunku dla obu, bo zawieraj� tyle samo element�w
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
	for (uint i = 1; i < n; i++){					//w p�tli dodajemy o 1 mniej przedmiot�w ni� ��dane
		uint rozmiar = rand() % 20 + 1;
		przedmiot *nowy = new przedmiot(rozmiar, rand() % 50 + 1);
		przedmiotyIl.push(*nowy);
		//przedmiotyWar.push(*nowy);
		calkowityRozmiar += rozmiar;
		//cout << *nowy << ", ";
	}
	if (calkowityRozmiar < pojemnosc){				//je�li sumaryczny rozmiar przedmiot�w jest mniejsze od pojemno�ci plecaka, to
		//dodajemy przedmiot, kt�ry wype�ni t� r�nic� i b�dzie co najmniej o 1 wi�kszy
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
	if (plik.is_open()){						//sprawdzamy, czy otwarcie pliku powiod�o si�, je�li tak to kontynuujemy
		if (wczytanoPrzedmioty)
			wyczysc();
		plik >> pojemnosc >> n;					//wczytujemy pojemno�� plecaka i liczb� element�w jakie chcemy w nim umie�ci�
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
		return true;							//zwracamy informacj� o powodzeniu
	}
	else return false;							//je�li otwarcie pliku nie powiod�o si�, to zwracamy informacj� o b��dzie
}
