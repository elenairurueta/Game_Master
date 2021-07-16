#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
//#include <windows.h>
//#include <mciapi.h>
//#include <mmsystem.h>
#include "funciones.h"
#include "GameMaster.h"
#include "Defines.h"
#include "cCaballeros.h"
#include "llenarArchivos.h"

using namespace std;

int main()
{
	llenarArchivoPaises(); //SOLO UNA VEZ
	GameMaster* Juego = NULL;
	do {
		try {
			Juego = new GameMaster();
			//Juego->imprimirMapa();
		}
		catch (exception* ex) {
			break;
		}
		system("pause");
		//PlaySound(TEXT("musicaJuego.wav"), NULL, SND_ASYNC);
		try
		{
			Juego->Inicio();
			Juego->imprimirMapa();
		}
		catch (exception* ex)
		{
			cout << ex->what();
		}

		do
		{
			Juego->imprimirMapa();
			try {
				Juego->ronda();
				rondasJugadas++;
			}
			catch (exception* ex)
			{
				cout << ex->what() << endl;
				break;
			}

		} while (rondasJugadas < rondasMAX);

		//PlaySound(NULL, NULL, 0);

		cout << "the end.";
	} while (true);
	delete Juego;
	return 0;
}