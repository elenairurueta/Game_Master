#pragma once
#include "cPais.h"
#include "Archivo.h"
#include "cListaT.h"
#include <iostream>
#include <string>

using namespace std;

class cMapa
{
	friend class GameMaster;
public:
	cMapa(MAPA mapa = MAPA::LATINOAMERICA, cListaT<cPais>* listaPaises = NULL);
	~cMapa();

	//lo llamamos en cada turno, después de cada ataque para verificar si algún jugador ganó
	bool chequearConquista();
	//levantamos el archivo de paises para formar la listaPaises
	void poblacionar();
	//define los paises vecinos de cada pais para formar su listaPaisesVecinos
	void definirPaisesVecinos();

	void imprimirMapa();

private:
	const MAPA nombre;
	string mapa;
	cListaT<cPais>* listaPaises;

	Archivo* archivoMapa;
	Archivo* archivoListaPaises;
};

