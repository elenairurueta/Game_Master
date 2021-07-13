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
	llenarArchivoPaises(); //SACAR

	GameMaster* Juego = new GameMaster();
	system("pause");
	//PlaySound(TEXT("musicaJuego.wav"), NULL, SND_ASYNC);
	try
	{
		Juego->Inicio();
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
	delete Juego;
	
	system("pause");
	return 0;
}