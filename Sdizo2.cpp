#include "stdafx.h"
#include "Sdizo2.h"

#define BLEDNY_NUMER "Podano niewlasciwy wybor. Ponow probe.\n"
#define ZAPYTAJ_O_PROBLEM "Ktory problem chcesz rozwiazac?\n"\
		"1. Wyznaczanie minimalnego drzewa rozpinajacego (MST)\n"\
		"2. Wyznaczanie najkrotszej sciezki w grafie\n"\
		"0. Wyjscie\n"\
		"\nPodaj wybor: "
#define ZAPYTAJ_O_OPERACJE "\n0. Wyjscie z programu\n"\
		"1. Wczytaj z pliku\n"\
		"2. Wygeneruj graf losowo\n"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Sdizo2::wyswietlGraf(){
	printf("\n*** POSTAC MACIERZOWA ***\n");
	macierzowo.wyswietl();
	printf("\n\n*** POSTAC LISTOWA *** format: (sasiad, waga)\n");
	listowo.wyswietl();
	printf("\n");
}

void Sdizo2::wczytajGraf(bool dlaPNS){
	char nazwa[30];
	printf("Podaj nazwe pliku tekstowego z ktorego chcesz wczytac graf: ");
	scanf("%s", &nazwa);
	if (dlaPNS){
		if (macierzowo.wczytajZPliku(nazwa, true) && listowo.wczytajZPliku(nazwa, true))
			wyswietlGraf();
	}
	else if (macierzowo.wczytajZPliku(nazwa) && listowo.wczytajZPliku(nazwa))
			wyswietlGraf();
	else
		printf("Blad odczytu! Podano nieprawidlowa nazwe, badz jego struktura zawiera bledy.\n");
}

void Sdizo2::generujGraf(bool dlaPNS){
	int iloscWierzch, gestosc;
	bool sukces;
	printf("\nPodaj ilosc wierzcholkow i gestosc grafu (w procentach) do wygenerowania: ");
	scanf_s("%d %d", &iloscWierzch, &gestosc);
	if (dlaPNS)
		sukces = macierzowo.generujLosowoSkierowany(iloscWierzch, gestosc) && listowo.kopiujZMacierzySkierowany(&macierzowo);
	else
		sukces = macierzowo.generujLosowoNieskierowany(iloscWierzch, gestosc) && listowo.kopiujZMacierzyNieskierowany(&macierzowo);
	if (sukces)
		wyswietlGraf();
	else
		printf("Wystapil blad podczas generowania grafu! Czy podana zostala poprawna gestosc\ngrafu (zapewniajaca jego spojnosc)?\n");
}

void Sdizo2::algorytmPrima(){
	printf("\n*** ALGORYTM PRIMA ***\n");
	macierzowo.algorytmPrima();
	macierzowo.wyswietlPrima();
	listowo.algorytmPrima();
	listowo.wyswietlPrima();
}

void Sdizo2::algorytmDijkstry(){
	printf("*** ALGORYTM DIJKSTRY ***\n\nMacierzowo:\n");
	macierzowo.algorytmDijkstry();
	macierzowo.wyswietlDijkstry();
	printf("\n\nListowo:\n");
	listowo.algorytmDijkstry();
	listowo.wyswietlDijkstry();
	printf("\n\nNajkrotsze drogi od wierzcholka poczatkowego nr %d (od prawej do lewej)\n", macierzowo.getV0());
	macierzowo.wyswietlDrogi();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Sdizo2::menu() {
	unsigned char problem, operacja;
	pobierzOpcje:
	do { printf(ZAPYTAJ_O_PROBLEM); scanf_s("%d", &problem); fflush(stdin); } while (problem >= 4);
	while (true){
		switch (problem){
		case 1:
			printf(ZAPYTAJ_O_OPERACJE "3. Algorytm Prima\n\nPodaj wybor: "); scanf_s("%d", &operacja);
			//*********************
			switch (operacja){
			case 1:
				wczytajGraf(false);
				break;
			case 2:
				generujGraf(false);
				break;
			case 3:
				algorytmPrima();
				break;
			case 0:
				exit(1); //wyjscie z programu
			default: printf(BLEDNY_NUMER);
			} //********************
			break;

		case 2:
			printf(ZAPYTAJ_O_OPERACJE "3. Algorytm Dijkstry\n\nPodaj wybor: "); scanf_s("%d", &operacja);
			//**********************
			switch (operacja){
			case 1:
				wczytajGraf(true);
				break;
			case 2:
				generujGraf(true);
				break;
			case 3:
				algorytmDijkstry();
				break;
			case 0:
				exit(1);
			default: printf(BLEDNY_NUMER);
			} //*******************
			break;

		case 3:
			eksperyment(); goto pobierzOpcje;
		case 0:
			exit(1);
		default:
			printf(BLEDNY_NUMER);
		}
		fflush(stdin);
	}
}

void Sdizo2::eksperyment(){
	//Macierzowo
	testPrima(50, 25);
	testPrima(75, 25);
	testPrima(100, 25);
	testPrima(125, 25);
	testPrima(150, 25);
	testPrima(50, 50);
	testPrima(75, 50);
	testPrima(100, 50);
	testPrima(125, 50);
	testPrima(150, 50);
	testPrima(50, 75);
	testPrima(75, 75);
	testPrima(100, 75);
	testPrima(125, 75);
	testPrima(150, 75);
	testPrima(50, 99);
	testPrima(75, 99);
	testPrima(100, 99);
	testPrima(125, 99);
	testPrima(150, 99);
}

void Sdizo2::testPrima(int iloscWierzch, int gestosc){
	double suma = 0;
	for (int i = 0; i < 25; i++){
		macierzowo.generujLosowoNieskierowany(iloscWierzch, gestosc);
		timer.startTimer();
		macierzowo.algorytmPrima();
		suma += timer.getTimer();
		macierzowo.czyscPrima();
	}
	printf("Sredni czas alg Prima (graf o %d wierzch i gestosci %d%%): %f [ms]\n", iloscWierzch, gestosc, suma / 25);
}

void Sdizo2::testDijkstry(int iloscWierzch, int gestosc){
	double suma = 0;
	for (int i = 0; i < 100; i++){
		macierzowo.generujLosowoSkierowany(iloscWierzch, gestosc);
		timer.startTimer();
		macierzowo.algorytmDijkstry();
		suma += timer.getTimer();
		macierzowo.czyscDijkstry();
	}
	printf("Sredni czas alg Dijkstry (graf o %d wierzch i gestosci %d%%): %f [ms]\n", iloscWierzch, gestosc, suma / 100);
}
