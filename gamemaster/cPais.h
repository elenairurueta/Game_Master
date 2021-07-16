#pragma once
#include "cEjercito.h"
#include "Defines.h"
#include <iostream>
using namespace std;

class cPais
{

public:
	cPais(string nombre = "", string nombreEnMapa = "", cEjercito* ejercito = NULL);
	~cPais();

	//agrega tropas al ejercito, pregunta si las quiere combinar o agregar
	void agregarTropas(cTropa* tropaAgregar);
	//elige la tropa que va a atacar
	cTropa* atacado();
	//elige la tropa con la que va a atacar
	cTropa* atacante();
	//cambia el control del pais cuando un jugador lo pierde
	void cambiarControl(JUGADORES NumeroJugador);
	//verifica que el jugador haya perdido el pais, si murieron todas sus tropas
	bool chequearPaisPerdido();
	//distribuye el daño entre las unidades de la tropa que se pasa por párametro
	void recibirAtaque(cTropa* tropaAtacada, int dano);
	JUGADORES getControl();
	string getclave();
	void pasarTropa(cPais* paisQuePasa);
	string toStringTropasListadas();
	cTropa* sacarTropa(int pos);
	bool chequearVecino(cPais* pais);
	void aplicarBonusATropa(int pos, BONUS bonus);
	int getCantidadTropas();

	friend class cMapa;
	friend ostream& operator<<(ostream& out, cPais* Pais);
	friend void llenarArchivoPaises();

	string toString(string separador = "\n");

	void inicializarEjercito();

private:
	JUGADORES control;
	static cListaT<cPais> listaPaises;
	const string nombre;
	cEjercito* ejercito;
	cListaT<cPais>* PaisesVecinos;
	const string nombreEnMapa;
};


