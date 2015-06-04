#pragma once
#include "stdafx.h"
#include "Macierzowo.h"
#include "Plecak.h"

class Sdizo3 {
public:
	void menu();
private:
	void wyswietlGraf();
	void wczytajGraf();
	void wczytajPlecak();
	void generujGraf();
	void generujPlecak();
	void problemPlecakowy();
	void problemKomiwojazera();

	void badajPlecakowy(uint N, uint B);
	void eksperyment();
	Macierzowo komiwojazer;
	Plecak plecak;
	PomiarCzasu timer;
	ofstream wyjscie;
};
