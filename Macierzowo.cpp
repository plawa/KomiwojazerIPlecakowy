#include "stdafx.h"
#include "Macierzowo.h"
#include <math.h>


//Konstruktor, kt�ry resetuje generator liczb pseudolowych i zapewnia, �e pierwsze
//wczytanie grafu przebiegnie bez pr�by usuwania poprzedniej (nieistniej�cej) instancji.
//---------------------------------------------------------------------------
Macierzowo::Macierzowo(){
	pierwszeWczytywanie = true;
	srand((size_t)time(NULL)); //na potrzeby u�ywania funkcji rand()
}

//Destruktor, wywo�uje funkcj� "usunGraf()"
//--------------------------------------------------------------------------
Macierzowo::~Macierzowo(){
	usunGraf();
}

void Macierzowo::problemKomiwojazera(){
	//definicja potrzebnych zmiennych
	wynik = new uint[n];
	tempSciezka = new uint[n];
	odwiedzone = new bool[n];
	for (uint i = 0; i < n; i++)
		odwiedzone[i] = false;
	sptr = shptr = 0;
	odleglosc = UINT_MAX;	//przypisanie maksymalnej mo�liwej warto�ci, aby pierwsza znaleziona odleglosc zosta�a przypisana
	tempOdleg = v0 = 0;
	KomiRekur(v0);		//start rekurencyjnego algorytmu
}

void Macierzowo::wyswietlRozwiazanie(){
	if (sptr) {
		cout << endl << "Najkrotsza odleglosc to: ";
		for (uint i = 0; i < sptr; i++)
			cout << wynik[i] << " ";
		cout << v0 << endl;
		cout << "odleglosc wynosi = " << odleglosc << endl;
	}
	else 
		cout << "We wczytanym grafie nie znaleziono cyklu Hamiltona!" << endl;
}

//***************************************************************
//*** ALGORYTM REKURENCYJNY ROZWI�ZUJ�CY PROBLEM KOMIWOJA�ERA ***
//***************************************************************
void Macierzowo::KomiRekur(uint v){
	tempSciezka[shptr++] = v;					//zapami�tujemy w tablicy wierzcho�ek przez kt�ry aktualnie b�dziemy przechodzi�
	if (shptr < n){								//je�li nie jest to jeszcze cykl Hamiltona (nie ��czy wszystkich wierzch.), to kontynuujemy poszukiwania
		odwiedzone[v] = true;					//oznaczamy bie��cy wierzcho�ek jako odwiedzony
		for (uint i = 0; i < n; i++)			//przegl�damy s�siad�w obecnego wierzcho�ka
			if (graf[v][i] && !odwiedzone[i]){	//je�li kraw�d� istnieje i s�siad nie zosta� jeszcze odwiedzony, to
				tempOdleg += graf[v][i];		//dodajemy wag� rozpatrywanej kraw�dzi do ��cznej, tymczasowej odleg�o�ci
				KomiRekur(i);					//kontynuujemy rekurencyjne wyszukiwanie cyklu Hamiltona
				tempOdleg -= graf[v][i];		//wracamy do poprzedniego stanu, by kontynowa� wyszukiwanie innych, mo�liwych cykli Hamiltona
			}
		odwiedzone[v] = false;					//przywracamy mo�liwo�� odwiedzenia obecnego wierzcho�ka ze wzgl�du na wyszukiwanie nowej permutacji
	}
	else if (graf[v0][v]){						//je�li znaleziono ju� cykl Hamiltona (przyp. podstawowy rekurencji), to
		tempOdleg += graf[v][v0];				//dodajemy jeszcze warto�� powrotu do wierzcho�ka pocz�tkowego
		if (tempOdleg < odleglosc){				//je�li wyszukany cykl reprezentuje najkr�tsz�, znalezion� do tej pory drog�, to
			odleglosc = tempOdleg;				//przypisujemy now�, kr�tsz� warto�� drogi do odleg�o�ci ko�cowej
			for (uint i = 0; i < shptr; i++)	//przypisujemy do wyniku ko�cowego wierzcho�ek po wierzcho�ku wyszukan� najkr�tsz� drog�
				wynik[i] = tempSciezka[i];
			sptr = shptr;
		}
		tempOdleg -= graf[v][v0];				//przywracamy poprzedni� warto�� odleg�o�ci, by rozwa�y� pozosta�e mo�liwe �cie�nki z poprzedniego miasta
	}
	shptr--;									//cofamy si� o wierzcho�ek wstecz, by rozwa�y� pozosta�e mo�liwe �cie�ki z poprzedniego miasta
}

bool Macierzowo::utworzGraf(uint iloscWierzcholkow){
	if (pierwszeWczytywanie == false)			//je�li graf tworzony jest niepierwszy raz w obecnym obiekcie
		usunGraf();								//to czy�cimy
	n = iloscWierzcholkow;
	uint **tempGraf = new uint*[n];
	for (uint i = 0; i < n; i++) {
		tempGraf[i] = new uint[n];
		for (uint j = 0; j < n; j++)
			tempGraf[i][j] = 0;					//inicjalizacja zerami, kt�re oznaczaj� �e danych dw�ch wierzcho�k�w nie ��czy �adna kraw�d�
	}
	graf = tempGraf;
	pierwszeWczytywanie = false;
	return true;
}

bool Macierzowo::utworzGraf(){
	return utworzGraf(n);
}

bool Macierzowo::generujLosowo(uint n){
	utworzGraf(n);
	for (uint i = 0; i < n; i++){
		for (uint j = 0; j < n; j++){
			if (j == i)
				continue;
			graf[i][j] = rand() % 10;
		}
	}
	return true;
}

void Macierzowo::wyswietl(uint **macierz){
	for (uint i = 0; i < n; i++){
		printf("\n");
		for (uint j = 0; j < n; j++)
			printf("%d ", macierz[i][j]);
	}
	printf("\n");
}

void Macierzowo::wyswietl(){
	wyswietl(graf);
}

void Macierzowo::usunGraf(){
	usun(graf);
}

void Macierzowo::usun(uint **macierz){
	for (uint i = 0; i < n; i++)
		delete[] macierz[i];
	delete[] macierz;
}

bool Macierzowo::wczytajZPliku(const char nazwaPliku[]){
	uint wiersz, waga;
	plik.open(nazwaPliku);						//otwarcie pliku do odczytu
	if (plik.is_open()){						//sprawdzenie czy otwarcie pliku powiod�o si�, je�li tak to kontynuujemy
		plik >> n;								//wczytuj� liczb� wierzcho�k�w (miast)
		utworzGraf();							//tworzy macierz n x n zainicjowan� zerami
		for (uint i = 0; i < n; i++){
			plik >> wiersz;						//pobiera nr wierzcho�ka z kt�rego wczytywane b�d� kraw�dzie
			if (wiersz >= n)					//je�li nr wiersza jest wi�kszy b�d� r�wny ilo�ci wierzcho�k�w
				return false;					//to przerywamy wczytywanie informuj�c o b��dzie
			for (uint j = 0; j < n; j++){
				if (wiersz == j)				//jesli wierzcho�ek chce wskazywa� kraw�dzi� na samego siebie, to
					continue;					//pomijamy ten krok p�tli zachowuj�c po przek�tnej zero (bez tworzenia p�tli w�asnych)
				plik >> waga;					//pobieramy wag�
				graf[wiersz][j] = waga;			//przypisujemy kraw�dzi wiersz -> j wag�
			}
		}
		plik.close();							//zamykamy plik
		return true;							//zwracamy informacj� o powodzeniu
	}
	else return false;							//je�li otwarcie pliku nie powiod�o si�, to zwracamy informacj� o b��du
}
