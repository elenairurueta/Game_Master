#pragma once
#include "cTropa.h"
#include "Defines.h"
#include <iostream>
using namespace std;

class cEjercito : public cListaT<cTropa>
{
public:
	cEjercito();
	~cEjercito();

	//agrega la tropa pasada por parámetro al ejército. Si la tropa a combinar es distinta de null, las combina. 
	void agregarOcombinarTropa(cTropa* tropaAgregar, cTropa* tropaCombinar = NULL);
	//muestra las tropas y elige con la que va a atacar o a la que va a atacar
	cTropa* elegirTropa(ROLES atacado_atacante);
	string toStringTropasListadas();
	string toStringParaElMapa();
	friend ostream& operator<<(ostream& out, cEjercito* ejercito);
};

