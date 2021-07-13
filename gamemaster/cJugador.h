#pragma once
#include <iostream>
#include "Defines.h"
#include "cListaT.h"

using namespace std;
class cPais;
class cTropa;

class cJugador
{

public:
	cJugador(JUGADORES jugador, string usuario = "", cListaT<cPais>* listaPaises = NULL);
	~cJugador();

	//distribuye a las tropas que se le asignaron en cada pais, formando cada ejercito.
	void distribucionTropasEnPaises(cListaT<cTropa>* listaTropas);
	//Elige el pais y la tropa a atacar dentro el del ejercito de ese pais. Luego elige con que pais (si tiene a mas de uno lim) y la tropa con lo va a atacar. 
	cPais* atacar(cListaT<cPais>* listaPaisesJugadorOponente);
	//agrega un pais a la lista de paises del jugador
	void agregarPais(cPais* paisAgregar);
	//cuando pierde un pais, lo quita de su lista de paises
	cPais* quitarPais(string paisQuitar);
	int getCantPaises();
	string getclave();
	cListaT<cPais>* getListaMisPaisesVecinos(cPais* pais);
	void agregarBonus(BONUS bonus);
private:
	const string usuario;
	const string contrasenia;
	int bajas;
	static int cantidadJugadores;
	const JUGADORES jugador;
	bool SigueJugando;
	cListaT<cPais>* listaPaises;

};

