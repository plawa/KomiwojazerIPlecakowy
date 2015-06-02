#pragma once
#include "stdafx.h"
#include "Macierzowo.h"

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
	Macierzowo komiwojazer;
	PomiarCzasu timer;
};
