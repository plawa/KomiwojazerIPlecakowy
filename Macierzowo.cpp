#include "stdafx.h"
#include "Macierzowo.h"
#include <math.h>


//Konstruktor, który resetuje generator liczb pseudolowych i zapewnia, ¿e pierwsze
//wczytanie grafu przebiegnie bez próby usuwania poprzedniej (nieistniej¹cej) instancji.
//---------------------------------------------------------------------------
Macierzowo::Macierzowo(){
	pierwszeWczytywanie = true;
	srand((size_t)time(NULL)); //na potrzeby u¿ywania funkcji rand()
}

//Destruktor, wywo³uje funkcjê "usunGraf()"
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
	odleglosc = UINT_MAX;	//przypisanie maksymalnej mo¿liwej wartoœci, aby pierwsza znaleziona odleglosc zosta³a przypisana
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
//*** ALGORYTM REKURENCYJNY ROZWI¥ZUJ¥CY PROBLEM KOMIWOJA¯ERA ***
//***************************************************************
void Macierzowo::KomiRekur(uint v){
	tempSciezka[shptr++] = v;					//zapamiêtujemy w tablicy wierzcho³ek przez który aktualnie bêdziemy przechodziæ
	if (shptr < n){								//jeœli nie jest to jeszcze cykl Hamiltona (nie ³¹czy wszystkich wierzch.), to kontynuujemy poszukiwania
		odwiedzone[v] = true;					//oznaczamy bie¿¹cy wierzcho³ek jako odwiedzony
		for (uint i = 0; i < n; i++)			//przegl¹damy s¹siadów obecnego wierzcho³ka
			if (graf[v][i] && !odwiedzone[i]){	//jeœli krawêdŸ istnieje i s¹siad nie zosta³ jeszcze odwiedzony, to
				tempOdleg += graf[v][i];		//dodajemy wagê rozpatrywanej krawêdzi do ³¹cznej, tymczasowej odleg³oœci
				KomiRekur(i);					//kontynuujemy rekurencyjne wyszukiwanie cyklu Hamiltona
				tempOdleg -= graf[v][i];		//wracamy do poprzedniego stanu, by kontynowaæ wyszukiwanie innych, mo¿liwych cykli Hamiltona
			}
		odwiedzone[v] = false;					//przywracamy mo¿liwoœæ odwiedzenia obecnego wierzcho³ka ze wzglêdu na wyszukiwanie nowej permutacji
	}
	else if (graf[v0][v]){						//jeœli znaleziono ju¿ cykl Hamiltona (przyp. podstawowy rekurencji), to
		tempOdleg += graf[v][v0];				//dodajemy jeszcze wartoœæ powrotu do wierzcho³ka pocz¹tkowego
		if (tempOdleg < odleglosc){				//jeœli wyszukany cykl reprezentuje najkrótsz¹, znalezion¹ do tej pory drogê, to
			odleglosc = tempOdleg;				//przypisujemy now¹, krótsz¹ wartoœæ drogi do odleg³oœci koñcowej
			for (uint i = 0; i < shptr; i++)	//przypisujemy do wyniku koñcowego wierzcho³ek po wierzcho³ku wyszukan¹ najkrótsz¹ drog¹
				wynik[i] = tempSciezka[i];
			sptr = shptr;
		}
		tempOdleg -= graf[v][v0];				//przywracamy poprzedni¹ wartoœæ odleg³oœci, by rozwa¿yæ pozosta³e mo¿liwe œcie¿nki z poprzedniego miasta
	}
	shptr--;									//cofamy siê o wierzcho³ek wstecz, by rozwa¿yæ pozosta³e mo¿liwe œcie¿ki z poprzedniego miasta
}

bool Macierzowo::utworzGraf(uint iloscWierzcholkow){
	if (pierwszeWczytywanie == false)			//jeœli graf tworzony jest niepierwszy raz w obecnym obiekcie
		usunGraf();								//to czyœcimy
	n = iloscWierzcholkow;
	uint **tempGraf = new uint*[n];
	for (uint i = 0; i < n; i++) {
		tempGraf[i] = new uint[n];
		for (uint j = 0; j < n; j++)
			tempGraf[i][j] = 0;					//inicjalizacja zerami, które oznaczaj¹ ¿e danych dwóch wierzcho³ków nie ³¹czy ¿adna krawêdŸ
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
	if (plik.is_open()){						//sprawdzenie czy otwarcie pliku powiod³o siê, jeœli tak to kontynuujemy
		plik >> n;								//wczytujê liczbê wierzcho³ków (miast)
		utworzGraf();							//tworzy macierz n x n zainicjowan¹ zerami
		for (uint i = 0; i < n; i++){
			plik >> wiersz;						//pobiera nr wierzcho³ka z którego wczytywane bêd¹ krawêdzie
			if (wiersz >= n)					//jeœli nr wiersza jest wiêkszy b¹dŸ równy iloœci wierzcho³ków
				return false;					//to przerywamy wczytywanie informuj¹c o b³êdzie
			for (uint j = 0; j < n; j++){
				if (wiersz == j)				//jesli wierzcho³ek chce wskazywaæ krawêdzi¹ na samego siebie, to
					continue;					//pomijamy ten krok pêtli zachowuj¹c po przek¹tnej zero (bez tworzenia pêtli w³asnych)
				plik >> waga;					//pobieramy wagê
				graf[wiersz][j] = waga;			//przypisujemy krawêdzi wiersz -> j wagê
			}
		}
		plik.close();							//zamykamy plik
		return true;							//zwracamy informacjê o powodzeniu
	}
	else return false;							//jeœli otwarcie pliku nie powiod³o siê, to zwracamy informacjê o b³êdu
}
