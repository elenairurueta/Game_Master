#pragma once
#include "cMapa.h"
#include "cJugador.h"
#include "Defines.h"
#include "funciones.h"
#include "cRegistro.h"
class GameMaster
{

public:
	GameMaster();
	~GameMaster();
	//distribuye en igual cantidad de paises dependiendo la cantidad de jugadores, y los que sobran los sortea
	void distribucionPaises();
	//distribuye las tropas entre los jugadores, llama a cJugador->distribucionTropasEnPaises, al inicio del juego 10 a c/u y en cada ronda reparte la mitad de la cantidad de paises a c/u
	void distribucionTropasEnJugador(cListaT<cTropa>* listaTropas);
	//crea las tropas aleatorias y llama a distribucionTropasEnJugadores
	cListaT<cTropa>* generadorDeListaTropa(bool inicio);
	//llama a generadorDeTropas, en cada turno, un Jugador realiza hasta tres ataques y otro contraataca. Hacemos un do while, y en cada vuelta cambia el turno. 
	void ronda();
	//devuelve una lista de paises cuyo control sea distinto al que está jugando(turno)
	cListaT<cPais>* getListaPaisesOponentes();
	cTropa* generadorDeTropa(TIPOTROPA tropa);
	void Inicio();
	void AumentarTurno();

	void imprimirPantallaInicial();
	void imprimirRedefinicionJugadores(cJugador* jugadorRetirado);
	MENU menuTurno();
	cListaT<cJugador>* definirJugadores();
	cMapa* crearMapa();
	void determinarBonus();
	void imprimirMapa();
	void imprimirReglas();
	void imprimirEstadisticas();
	void atacar();
	void escribirRegistroJugadores();

private:
	JUGADORES turno;
	cMapa* mapa;
	cListaT<cJugador>* listaJugadores;

	Archivo* archivoJugadores;
	cListaT<cRegistro>* registroJugadores;
	//TODO: lista usuarios y contraseñas
};