#include "stdafx.h"
#include "Sdizo3.h"

#define BLEDNY_NUMER "Podano niewlasciwy wybor. Ponow probe.\n"
#define ZAPYTAJ_O_PROBLEM "Ktory problem chcesz rozwiazac?\n"\
		"1. Asymetryczny problem komiwojazera\n"\
		"2. Dyskretny problem plecakowy\n"\
		"3. Wykonaj test (wyniki w wyniki.txt)\n"\
		"0. Wyjscie\n"\
		"\nPodaj wybor: "
#define ZAPYTAJ_O_OPERACJE "\n0. Wyjscie z programu\n"\
		"1. Wczytaj z pliku\n"\
		"2. Wygeneruj graf losowo\n"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//										**** FUNKCJE INTERFEJSU *****
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Sdizo3::wyswietlGraf(){
	printf("\n");
	komiwojazer.wyswietl();
	printf("\n");
}

void Sdizo3::wczytajGraf(){
	char nazwa[30];
	printf("Podaj nazwe pliku tekstowego z ktorego chcesz wczytac graf: ");
	scanf("%s", &nazwa);
	if (komiwojazer.wczytajZPliku(nazwa))
			wyswietlGraf();
	else
		printf("Blad odczytu! Podano nieprawidlowa nazwe, badz jego struktura zawiera bledy.\n");
}

void Sdizo3::wczytajPlecak(){	
	char nazwa[30];
	printf("Podaj nazwe pliku tekstowego z ktorego chcesz wczytac elementy plecaka: ");
	scanf("%s", &nazwa);
	if (plecak.wczytajZPliku(nazwa))		//jeœli wczytywanie siê powiedzie
		return;								//to zakoñcz dzia³anie funkcji
	else
		printf("Blad odczytu! Podano nieprawidlowa nazwe, badz jego struktura zawiera bledy.\n");
}

void Sdizo3::generujGraf(){
	uint iloscWierzch;
	printf("\nPodaj ilosc wierzcholkow grafu do wygenerowania: ");
	scanf_s("%d", &iloscWierzch);
	if (komiwojazer.generujLosowo(iloscWierzch))
		wyswietlGraf();
	else
		printf("Wystapil blad podczas generowania grafu! Czy podana zostala poprawna gestosc\ngrafu (zapewniajaca jego spojnosc)?\n");
}

void Sdizo3::generujPlecak(){
	uint iloscPrzedm, poj;
	printf("Podaj ilosc przedmiotow do wygenerowania i pojemnosc plecaka: ");
	scanf_s("%d %d", &iloscPrzedm, &poj);
	if (plecak.generujPrzedmioty(iloscPrzedm, poj))
		return;
	else
		printf("Wystapil blad!\n");
}

void Sdizo3::problemKomiwojazera(){
	timer.startTimer();
	komiwojazer.problemKomiwojazera();
	cout << "czas: " << timer.getTimer() << endl;
	komiwojazer.wyswietlRozwiazanie();
}

void Sdizo3::problemPlecakowy(){
	plecak.problemPlecakowyIl();
	cout << endl << "Kryterium: stosunek wartosci do rozmiaru";
	plecak.wyswietlPlecak();
	plecak.problemPlecakowyWar();
	cout << endl << "Kryterium: wartosc";
	plecak.wyswietlPlecak();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//												**** MAIN ****
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Sdizo3::menu() {
	srand((size_t)time(NULL)); //na potrzeby u¿ywania funkcji rand()
	unsigned char problem, operacja;
	do { 
		printf(ZAPYTAJ_O_PROBLEM);
		scanf_s("%d", &problem);
		fflush(stdin); 
	} while (problem >= 4);

	while (true){
		switch (problem){
		case 1:
			printf(ZAPYTAJ_O_OPERACJE "3. Przeglad zupelny\n\nPodaj wybor: ");
			scanf_s("%d", &operacja);
			//*********************
			switch (operacja){
			case 1:
				wczytajGraf();
				break;
			case 2:
				generujGraf();
				break;
			case 3:
				problemKomiwojazera();
				break;
			case 0:
				exit(1); //wyjscie z programu
			default: printf(BLEDNY_NUMER);
			} //********************
			break;

		case 2:
			printf(ZAPYTAJ_O_OPERACJE "3. Algorytm zachlanny\n\nPodaj wybor: ");
			scanf_s("%d", &operacja);
			//**********************
			switch (operacja){
			case 1:
				wczytajPlecak();
				break;
			case 2:
				generujPlecak();
				break;
			case 3:
				problemPlecakowy();
				break;
			case 0:
				exit(1);
			default: printf(BLEDNY_NUMER);
			} //*******************
			break;
		case 3:
			eksperyment();
		case 0:
			exit(1);
		default:
			printf(BLEDNY_NUMER);
		}
		fflush(stdin);
	}
}

void Sdizo3::badajPlecakowy(uint N, uint B){
	double czas = 0.0;
	wyjscie << N << " " << B << " ";
	for (uint i = 0; i < 100; i++){
		plecak.generujPrzedmioty(N, B);
		timer.startTimer();
		plecak.problemPlecakowyIl();
		czas += timer.getTimer();
	}
	wyjscie << czas/100.0 << endl;
}

void Sdizo3::eksperyment(){
	wyjscie.open("wyniki.txt");
	if ( ! wyjscie.is_open()){
		cout << "Blad! Nie mozna otworzyc pliku do zapisu.";
		return;
	}
	cout << endl << "Prosze czekac. Gdy eksperyment zostanie wykonany, program zakonczy dzialanie."
		<< endl << "Wyniki zapisane zostana w pliku \"wyniki.txt\".";

	//wartoœci N: 625 1250 1875 2500 3125
	//wartoœci B: 125 250 375

	badajPlecakowy(625, 125);
	badajPlecakowy(625, 250);
	badajPlecakowy(625, 375);
	badajPlecakowy(1250, 125);
	badajPlecakowy(1250, 250);
	badajPlecakowy(1250, 375);
	badajPlecakowy(1875, 125);
	badajPlecakowy(1875, 250);
	badajPlecakowy(1875, 375);
	badajPlecakowy(2500, 125);
	badajPlecakowy(2500, 250);
	badajPlecakowy(2500, 375);
	badajPlecakowy(3125, 125);
	badajPlecakowy(3125, 250);
	badajPlecakowy(3125, 375);

	wyjscie.close();
}
