#include "stdafx.h"
#include "Sdizo3.h"

#define BLEDNY_NUMER "Podano niewlasciwy wybor. Ponow probe.\n"
#define ZAPYTAJ_O_PROBLEM "Ktory problem chcesz rozwiazac?\n"\
		"1. Asymetryczny problem komiwojazera\n"\
		"2. Dyskretny problem plecakowy\n"\
		"0. Wyjscie\n"\
		"\nPodaj wybor: "
#define ZAPYTAJ_O_OPERACJE "\n0. Wyjscie z programu\n"\
		"1. Wczytaj z pliku\n"\
		"2. Wygeneruj graf losowo\n"\
		"3. Przeglad zupelny\n"\
		"\nPodaj wybor: "

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//									**** FUNKCJE UCHWYTU INTERFEJSU *****
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Sdizo3::wyswietlGraf(){
	printf("\n");
	macierzowo.wyswietl();
	printf("\n");
}

void Sdizo3::wczytajGraf(){
	char nazwa[30];
	printf("Podaj nazwe pliku tekstowego z ktorego chcesz wczytac graf: ");
	scanf("%s", &nazwa);
	if (macierzowo.wczytajZPliku(nazwa))
			wyswietlGraf();
	else
		printf("Blad odczytu! Podano nieprawidlowa nazwe, badz jego struktura zawiera bledy.\n");
}

void Sdizo3::wczytajPlecak(){	
	char nazwa[30];
	printf("Podaj nazwe pliku tekstowego z ktorego chcesz wczytac elementy plecaka: ");
	scanf("%s", &nazwa);
	// ????????
	if (macierzowo.wczytajZPliku(nazwa))
		; //	???????
	else
		printf("Blad odczytu! Podano nieprawidlowa nazwe, badz jego struktura zawiera bledy.\n");
}

void Sdizo3::generujGraf(){
	int iloscWierzch, gestosc;
	printf("\nPodaj ilosc wierzcholkow i gestosc grafu (w procentach) do wygenerowania: ");
	scanf_s("%d %d", &iloscWierzch, &gestosc);
	if (macierzowo.generujLosowoNieskierowany(iloscWierzch, gestosc))
		wyswietlGraf();
	else
		printf("Wystapil blad podczas generowania grafu! Czy podana zostala poprawna gestosc\ngrafu (zapewniajaca jego spojnosc)?\n");
}

void Sdizo3::generujPlecak(){
	; // ?????	??????	????
}

void Sdizo3::problemKomiwojazera(){
	
}

void Sdizo3::problemPlecakowy(){
	; // ??? ? ?? ? ??
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//												**** MAIN ****
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Sdizo3::menu() {
	unsigned char problem, operacja;
	do { 
		printf(ZAPYTAJ_O_PROBLEM);
		scanf_s("%d", &problem);
		fflush(stdin); 
	} while (problem >= 4);

	while (true){
		switch (problem){
		case 1:
			printf(ZAPYTAJ_O_OPERACJE); scanf_s("%d", &operacja);
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
			printf(ZAPYTAJ_O_OPERACJE); scanf_s("%d", &operacja);
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
		//case 3:
		//	eksperyment();
		case 0:
			exit(1);
		default:
			printf(BLEDNY_NUMER);
		}
		fflush(stdin);
	}
}