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
	droga = UINT_MAX;	//przypisanie maksymalnej mo¿liwej wartoœci, aby pierwsza znaleziona droga zosta³a przypisana
	tempDroga = v0 = 0;
	KomiRekur(v0);		//start rekurencyjnego algorytmu
}

void Macierzowo::wyswietlRozwiazanie(){
	if (sptr) {
		cout << endl << "Najkrotsza droga to: ";
		for (uint i = 0; i < sptr; i++)
			cout << wynik[i] << " ";
		cout << v0 << endl;
		cout << "droga wynosi = " << droga << endl;
	}
	else 
		cout << "We wczytanym grafie nie znaleziono cyklu Hamiltona!" << endl;
}

// Rekurencyjna procedura poszukiwania cyklu Hamiltona
// o najmniejszej sumie wag krawêdzi
// v - wierzcho³ek bie¿¹cy
//----------------------------------------------------
void Macierzowo::KomiRekur(uint v)
{
	tempSciezka[shptr++] = v;                // zapamiêtujemy w tablicy bie¿¹cy wierzcho³ek

	if (shptr < n)                   // jeœli to nie jest jeszcze œcie¿ka Hamiltona, to kontynuujemy poszukiwania
	{
		odwiedzone[v] = true;            // Oznaczamy bie¿¹cy wierzcho³ek jako odwiedzony
		for (uint i = 0; i < n; i++)        // Przegl¹damy s¹siadów wierzcho³ka v
			if (graf[v][i] && !odwiedzone[i])  // Szukamy nieodwiedzonego jeszcze s¹siada
			{
				tempDroga += graf[v][i];            // Dodajemy wagê krawêdzi v-u do sumy
				KomiRekur(i);                 // Rekurencyjnie wywo³ujemy szukanie cyklu Hamiltona
				tempDroga -= graf[v][i];            // Usuwamy wagê krawêdzi z sumy
			}
		odwiedzone[v] = false;           // Zwalniamy bie¿¹cy wierzcho³ek
	}
	else if (graf[v0][v])               // Jeœli znaleziona œcie¿ka jest cyklem Hamiltona
	{
		tempDroga += graf[v][v0];               // to sprawdzamy, czy ma najmniejsz¹ sumê wag
		if (tempDroga < droga)                    // Jeœli tak,
		{
			droga = tempDroga;                     // To zapamiêtujemy tê sumê
			for (uint i = 0; i < shptr; i++)  // oraz kopiujemy stos Sh do S
				wynik[i] = tempSciezka[i];
			sptr = shptr;
		}
		tempDroga -= graf[v][v0];               // Usuwamy wagê krawêdzi v-v0 z sumy
	}
	shptr--;                        // Usuwamy bie¿¹cy wierzcho³ek ze œcie¿ki
}

bool Macierzowo::utworzGraf(uint iloscWierzcholkow){
	if (pierwszeWczytywanie == false)	//jeœli graf tworzony jest niepierwszy raz w obecnym obiekcie
		usunGraf();						//to czyœcimy
	n = iloscWierzcholkow;
	uint **tempGraf = new uint*[n];
	for (uint i = 0; i < n; i++) {
		tempGraf[i] = new uint[n];
		for (uint j = 0; j < n; j++)
			tempGraf[i][j] = 0;			//inicjalizacja zerami, które oznaczaj¹ ¿e danych dwóch wierzcho³ków nie ³¹czy ¿adna krawêdŸ
	}
	graf = tempGraf;
	pierwszeWczytywanie = false;
	return true;
}

bool Macierzowo::utworzGraf(){
	return utworzGraf(n);
}

bool Macierzowo::generujLosowoNieskierowany(uint n, int gestosc){
	//inicjalizacja macierzy, która przechowywaæ bêdzie informacje czy dana komórka zosta³a ju¿ wczeœniej edytowana przez generator
	bool **zmodyfikowane = new bool*[n];
	for (uint i = 0; i < n; i++){
		zmodyfikowane[i] = new bool[n];
		for (uint j = 0; j < n; j++)
			zmodyfikowane[i][j] = false;
		zmodyfikowane[i][i] = true; //blokada przek¹tnej (maj¹ tam byæ same zera)
	}//koniec inicjalizacji macierzy boolowskiej
	
	uint licznik = 0;
	int minProcent = static_cast<int>(ceil(static_cast<float>(200 / n))); //min procent krawêdzi, aby graf by³ spójny
	int maxE = n*(n - 1) / 2; //max iloœæ krawêdzi dla grafu nieskierowanego
	e = (int)floor((float)(maxE * gestosc / 100)); //iloœæ krawêdzi do dodania wyliczona na podstawie gêstoœci
	if (gestosc < minProcent || gestosc > 100)
		return false;
	utworzGraf(n);
	//iteracja poni¿ej nastêpuje po "trójk¹cie" - czêœci tablicy, która bêdzie symetrycznie odbijana wzglêdem przek¹tnej
	for (uint i = 0; i < n - 1; i++){ //najpierw inicjalizacja grafu (zapewnienie spójnoœci)
		//³¹czê wierzcho³ki (1->2->3->4 ...), tworz¹c najpierw graf spójny z wagami 1 do 9 i "odznaczam" w zmodyfikowanych
		graf[i][i + 1] = graf[i + 1][i] = rand() % 9 + 1; 
		zmodyfikowane[i][i + 1] = zmodyfikowane[i + 1][i] = true;
		licznik++;
	}
	while (licznik < e) { //nastêpnie uzupe³nianie losowymi wartoœciami do uzyskania po¿¹danej iloœci krawêdzi
		int wiersz = rand() % n;
		int kolumna = rand() % n;
		int waga = rand() % 9 + 1;
		if (zmodyfikowane[wiersz][kolumna] == false) {
			graf[wiersz][kolumna] = graf[kolumna][wiersz] = waga;
			zmodyfikowane[wiersz][kolumna] = zmodyfikowane[kolumna][wiersz] = true;
			licznik++;
		}
	}
	usun(zmodyfikowane);
	return true;
}

bool Macierzowo::generujLosowoSkierowany(uint n, int gestosc){
	//inicjalizacja macierzy, która przechowywaæ bêdzie informacje czy dana komórka zosta³a ju¿ wczeœniej edytowana przez generator
	bool **zmodyfikowane = new bool*[n];
	for (uint i = 0; i < n; i++){
		zmodyfikowane[i] = new bool[n];
		for (uint j = 0; j < n; j++)
			zmodyfikowane[i][j] = false; 
		zmodyfikowane[i][i] = true; //blokada, bo po przek¹tnej tylko zera
	}//koniec inicjalizacji macierzy boolowskiej
	//------------------------------------
	uint licznik = 0, maxE = n * (n - 1); //max mo¿liwa iloœæ krawêdzi dla grafu skierowanego
	int minProcent = static_cast<int>(ceil(static_cast<float>(100/n)));
	e = static_cast<int>( floor( static_cast<float>(maxE*gestosc/100) ) ); //iloœæ krawêdzi wyliczona na podstawie gêstoœci
	//n0 = rand() % n; //losowanie wierzcho³ka pocz¹tkowego dla PNS
	if (gestosc < minProcent || gestosc > 100)
		return false;
	utworzGraf(n);
	for (uint i = 0; i < n - 1; i++){ //najpierw inicjalizacja grafu
		//³¹czê wierzcho³ki (1->2->3->4->...), tworz¹c najpierw graf spójny z wagami 1 do 9 i "odznaczam" w zmodyfikowanych
		graf[i][i + 1] = rand() % 9 + 1; 
		zmodyfikowane[i][i + 1] = true;
		licznik++;
	}
	while(licznik < e) { //nastêpnie uzupe³nianie losowymi wartoœciami do uzyskania po¿¹danej iloœci krawêdzi
		int wiersz = rand() % n;
		int kolumna = rand() % n;
		if (zmodyfikowane[wiersz][kolumna] == false) {
			graf[wiersz][kolumna] = rand() % 9 + 1;
			zmodyfikowane[wiersz][kolumna] = true;
			licznik++;
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

void Macierzowo::usun(bool **macierz){
	for (uint i = 0; i < n; i++)
		delete[] macierz[i];
	delete[] macierz;
}

bool Macierzowo::wczytajZPliku(const char nazwaPliku[]){
	uint wiersz, kolumna, tempWaga;
	plik.open(nazwaPliku); //uchwyt s³u¿¹cy jedynie do odczytu, sprawdzenie czy otwarcie pliku siê powiod³o
	if (plik.is_open()){
		plik >> e >> n; //wczytujê liczbê krawêdzi i liczbê wierzcho³ków
		utworzGraf();
		for (uint i = 0; i < e; i++){
			plik >> wiersz >> kolumna >> tempWaga;
			if (wiersz >= n || kolumna >= n)
				return false;
			graf[wiersz][kolumna] = tempWaga; //wierzcho³ki "wiersz" i "kolumna" reprezentuj¹ jedn¹ krawêdŸ, wpisuje siê tam jej wagê
		}
		plik.close();
		return true;
	}
	else
		return false;
}
