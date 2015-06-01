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


bool Macierzowo::utworzGraf(uint iloscWierzcholkow){
	if (pierwszeWczytywanie == false)	//jeœli graf tworzony jest niepierwszy raz w obecnym obiekcie
		usunGraf();						//to czyœcimy
	v = iloscWierzcholkow;
	uint **tempGraf = new uint*[v];
	for (uint i = 0; i < v; i++) {
		tempGraf[i] = new uint[v];
		for (uint j = 0; j < v; j++)
			tempGraf[i][j] = 0;			//inicjalizacja zerami, które oznaczaj¹ ¿e danych dwóch wierzcho³ków nie ³¹czy ¿adna krawêdŸ
	}
	graf = tempGraf;
	pierwszeWczytywanie = false;
	return true;
}

bool Macierzowo::utworzGraf(){
	return utworzGraf(v);
}

bool Macierzowo::generujLosowoNieskierowany(uint v, int gestosc){
	//inicjalizacja macierzy, która przechowywaæ bêdzie informacje czy dana komórka zosta³a ju¿ wczeœniej edytowana przez generator
	bool **zmodyfikowane = new bool*[v];
	for (uint i = 0; i < v; i++){
		zmodyfikowane[i] = new bool[v];
		for (uint j = 0; j < v; j++)
			zmodyfikowane[i][j] = false;
		zmodyfikowane[i][i] = true; //blokada przek¹tnej (maj¹ tam byæ same zera)
	}//koniec inicjalizacji macierzy boolowskiej
	
	uint licznik = 0;
	int minProcent = static_cast<int>(ceil(static_cast<float>(200 / v))); //min procent krawêdzi, aby graf by³ spójny
	int maxE = v*(v - 1) / 2; //max iloœæ krawêdzi dla grafu nieskierowanego
	e = (int)floor((float)(maxE * gestosc / 100)); //iloœæ krawêdzi do dodania wyliczona na podstawie gêstoœci
	if (gestosc < minProcent || gestosc > 100)
		return false;
	utworzGraf(v);
	//iteracja poni¿ej nastêpuje po "trójk¹cie" - czêœci tablicy, która bêdzie symetrycznie odbijana wzglêdem przek¹tnej
	for (uint i = 0; i < v - 1; i++){ //najpierw inicjalizacja grafu (zapewnienie spójnoœci)
		//³¹czê wierzcho³ki (1->2->3->4 ...), tworz¹c najpierw graf spójny z wagami 1 do 9 i "odznaczam" w zmodyfikowanych
		graf[i][i + 1] = graf[i + 1][i] = rand() % 9 + 1; 
		zmodyfikowane[i][i + 1] = zmodyfikowane[i + 1][i] = true;
		licznik++;
	}
	while (licznik < e) { //nastêpnie uzupe³nianie losowymi wartoœciami do uzyskania po¿¹danej iloœci krawêdzi
		int wiersz = rand() % v;
		int kolumna = rand() % v;
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

bool Macierzowo::generujLosowoSkierowany(uint v, int gestosc){
	//inicjalizacja macierzy, która przechowywaæ bêdzie informacje czy dana komórka zosta³a ju¿ wczeœniej edytowana przez generator
	bool **zmodyfikowane = new bool*[v];
	for (uint i = 0; i < v; i++){
		zmodyfikowane[i] = new bool[v];
		for (uint j = 0; j < v; j++)
			zmodyfikowane[i][j] = false; 
		zmodyfikowane[i][i] = true; //blokada, bo po przek¹tnej tylko zera
	}//koniec inicjalizacji macierzy boolowskiej
	//------------------------------------
	uint licznik = 0, maxE = v * (v - 1); //max mo¿liwa iloœæ krawêdzi dla grafu skierowanego
	int minProcent = static_cast<int>(ceil(static_cast<float>(100/v)));
	e = static_cast<int>( floor( static_cast<float>(maxE*gestosc/100) ) ); //iloœæ krawêdzi wyliczona na podstawie gêstoœci
	//v0 = rand() % v; //losowanie wierzcho³ka pocz¹tkowego dla PNS
	if (gestosc < minProcent || gestosc > 100)
		return false;
	utworzGraf(v);
	for (uint i = 0; i < v - 1; i++){ //najpierw inicjalizacja grafu
		//³¹czê wierzcho³ki (1->2->3->4->...), tworz¹c najpierw graf spójny z wagami 1 do 9 i "odznaczam" w zmodyfikowanych
		graf[i][i + 1] = rand() % 9 + 1; 
		zmodyfikowane[i][i + 1] = true;
		licznik++;
	}
	while(licznik < e) { //nastêpnie uzupe³nianie losowymi wartoœciami do uzyskania po¿¹danej iloœci krawêdzi
		int wiersz = rand() % v;
		int kolumna = rand() % v;
		if (zmodyfikowane[wiersz][kolumna] == false) {
			graf[wiersz][kolumna] = rand() % 9 + 1;
			zmodyfikowane[wiersz][kolumna] = true;
			licznik++;
		}
	}
	return true;
}


void Macierzowo::wyswietl(uint **macierz){
	for (uint i = 0; i < v; i++){
		printf("\n");
		for (uint j = 0; j < v; j++)
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
	for (uint i = 0; i < v; i++)
		delete[] macierz[i];
	delete[] macierz;
}

void Macierzowo::usun(bool **macierz){
	for (uint i = 0; i < v; i++)
		delete[] macierz[i];
	delete[] macierz;
}

bool Macierzowo::wczytajZPliku(const char nazwaPliku[]){
	uint wiersz, kolumna, tempWaga;
	if (plik = fopen(nazwaPliku, "r")){ //uchwyt s³u¿¹cy jedynie do odczytu, sprawdzenie czy otwarcie pliku siê powiod³o
		fscanf_s(plik, "%d %d", &e, &v); //wczytujê liczbê krawêdzi i liczbê wierzcho³ków
		utworzGraf();
		for (uint i = 0; i < e; i++){
			fscanf_s(plik, "%d %d %d", &wiersz, &kolumna, &tempWaga);
			if (wiersz >= v || kolumna >= v)
				return false;
			graf[wiersz][kolumna] = tempWaga; //wierzcho³ki "wiersz" i "kolumna" reprezentuj¹ jedn¹ krawêdŸ, wpisuje siê tam jej wagê
		}
		fclose(plik);
		return true;
	}
	else
		return false;
}
