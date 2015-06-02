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
	droga = UINT_MAX;	//przypisanie maksymalnej mo�liwej warto�ci, aby pierwsza znaleziona droga zosta�a przypisana
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
// o najmniejszej sumie wag kraw�dzi
// v - wierzcho�ek bie��cy
//----------------------------------------------------
void Macierzowo::KomiRekur(uint v)
{
	tempSciezka[shptr++] = v;                // zapami�tujemy w tablicy bie��cy wierzcho�ek

	if (shptr < n)                   // je�li to nie jest jeszcze �cie�ka Hamiltona, to kontynuujemy poszukiwania
	{
		odwiedzone[v] = true;            // Oznaczamy bie��cy wierzcho�ek jako odwiedzony
		for (uint i = 0; i < n; i++)        // Przegl�damy s�siad�w wierzcho�ka v
			if (graf[v][i] && !odwiedzone[i])  // Szukamy nieodwiedzonego jeszcze s�siada
			{
				tempDroga += graf[v][i];            // Dodajemy wag� kraw�dzi v-u do sumy
				KomiRekur(i);                 // Rekurencyjnie wywo�ujemy szukanie cyklu Hamiltona
				tempDroga -= graf[v][i];            // Usuwamy wag� kraw�dzi z sumy
			}
		odwiedzone[v] = false;           // Zwalniamy bie��cy wierzcho�ek
	}
	else if (graf[v0][v])               // Je�li znaleziona �cie�ka jest cyklem Hamiltona
	{
		tempDroga += graf[v][v0];               // to sprawdzamy, czy ma najmniejsz� sum� wag
		if (tempDroga < droga)                    // Je�li tak,
		{
			droga = tempDroga;                     // To zapami�tujemy t� sum�
			for (uint i = 0; i < shptr; i++)  // oraz kopiujemy stos Sh do S
				wynik[i] = tempSciezka[i];
			sptr = shptr;
		}
		tempDroga -= graf[v][v0];               // Usuwamy wag� kraw�dzi v-v0 z sumy
	}
	shptr--;                        // Usuwamy bie��cy wierzcho�ek ze �cie�ki
}

bool Macierzowo::utworzGraf(uint iloscWierzcholkow){
	if (pierwszeWczytywanie == false)	//je�li graf tworzony jest niepierwszy raz w obecnym obiekcie
		usunGraf();						//to czy�cimy
	n = iloscWierzcholkow;
	uint **tempGraf = new uint*[n];
	for (uint i = 0; i < n; i++) {
		tempGraf[i] = new uint[n];
		for (uint j = 0; j < n; j++)
			tempGraf[i][j] = 0;			//inicjalizacja zerami, kt�re oznaczaj� �e danych dw�ch wierzcho�k�w nie ��czy �adna kraw�d�
	}
	graf = tempGraf;
	pierwszeWczytywanie = false;
	return true;
}

bool Macierzowo::utworzGraf(){
	return utworzGraf(n);
}

bool Macierzowo::generujLosowoNieskierowany(uint n, int gestosc){
	//inicjalizacja macierzy, kt�ra przechowywa� b�dzie informacje czy dana kom�rka zosta�a ju� wcze�niej edytowana przez generator
	bool **zmodyfikowane = new bool*[n];
	for (uint i = 0; i < n; i++){
		zmodyfikowane[i] = new bool[n];
		for (uint j = 0; j < n; j++)
			zmodyfikowane[i][j] = false;
		zmodyfikowane[i][i] = true; //blokada przek�tnej (maj� tam by� same zera)
	}//koniec inicjalizacji macierzy boolowskiej
	
	uint licznik = 0;
	int minProcent = static_cast<int>(ceil(static_cast<float>(200 / n))); //min procent kraw�dzi, aby graf by� sp�jny
	int maxE = n*(n - 1) / 2; //max ilo�� kraw�dzi dla grafu nieskierowanego
	e = (int)floor((float)(maxE * gestosc / 100)); //ilo�� kraw�dzi do dodania wyliczona na podstawie g�sto�ci
	if (gestosc < minProcent || gestosc > 100)
		return false;
	utworzGraf(n);
	//iteracja poni�ej nast�puje po "tr�jk�cie" - cz�ci tablicy, kt�ra b�dzie symetrycznie odbijana wzgl�dem przek�tnej
	for (uint i = 0; i < n - 1; i++){ //najpierw inicjalizacja grafu (zapewnienie sp�jno�ci)
		//��cz� wierzcho�ki (1->2->3->4 ...), tworz�c najpierw graf sp�jny z wagami 1 do 9 i "odznaczam" w zmodyfikowanych
		graf[i][i + 1] = graf[i + 1][i] = rand() % 9 + 1; 
		zmodyfikowane[i][i + 1] = zmodyfikowane[i + 1][i] = true;
		licznik++;
	}
	while (licznik < e) { //nast�pnie uzupe�nianie losowymi warto�ciami do uzyskania po��danej ilo�ci kraw�dzi
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
	//inicjalizacja macierzy, kt�ra przechowywa� b�dzie informacje czy dana kom�rka zosta�a ju� wcze�niej edytowana przez generator
	bool **zmodyfikowane = new bool*[n];
	for (uint i = 0; i < n; i++){
		zmodyfikowane[i] = new bool[n];
		for (uint j = 0; j < n; j++)
			zmodyfikowane[i][j] = false; 
		zmodyfikowane[i][i] = true; //blokada, bo po przek�tnej tylko zera
	}//koniec inicjalizacji macierzy boolowskiej
	//------------------------------------
	uint licznik = 0, maxE = n * (n - 1); //max mo�liwa ilo�� kraw�dzi dla grafu skierowanego
	int minProcent = static_cast<int>(ceil(static_cast<float>(100/n)));
	e = static_cast<int>( floor( static_cast<float>(maxE*gestosc/100) ) ); //ilo�� kraw�dzi wyliczona na podstawie g�sto�ci
	//n0 = rand() % n; //losowanie wierzcho�ka pocz�tkowego dla PNS
	if (gestosc < minProcent || gestosc > 100)
		return false;
	utworzGraf(n);
	for (uint i = 0; i < n - 1; i++){ //najpierw inicjalizacja grafu
		//��cz� wierzcho�ki (1->2->3->4->...), tworz�c najpierw graf sp�jny z wagami 1 do 9 i "odznaczam" w zmodyfikowanych
		graf[i][i + 1] = rand() % 9 + 1; 
		zmodyfikowane[i][i + 1] = true;
		licznik++;
	}
	while(licznik < e) { //nast�pnie uzupe�nianie losowymi warto�ciami do uzyskania po��danej ilo�ci kraw�dzi
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
	plik.open(nazwaPliku); //uchwyt s�u��cy jedynie do odczytu, sprawdzenie czy otwarcie pliku si� powiod�o
	if (plik.is_open()){
		plik >> e >> n; //wczytuj� liczb� kraw�dzi i liczb� wierzcho�k�w
		utworzGraf();
		for (uint i = 0; i < e; i++){
			plik >> wiersz >> kolumna >> tempWaga;
			if (wiersz >= n || kolumna >= n)
				return false;
			graf[wiersz][kolumna] = tempWaga; //wierzcho�ki "wiersz" i "kolumna" reprezentuj� jedn� kraw�d�, wpisuje si� tam jej wag�
		}
		plik.close();
		return true;
	}
	else
		return false;
}
