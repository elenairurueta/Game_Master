#pragma once

#include "GameMaster.h"
#include "cUnidad.h"
#include "cArqueros.h"
#include "cCaballeros.h"
#include "cMagos.h"
#include "Globals.h"
#include "Archivo.h"


GameMaster::GameMaster() {
	imprimirPantallaInicial();
	system("pause");
	this->archivoJugadores = new Archivo("registroJugadores");
	this->registroJugadores = archivoJugadores->leerArchivoDat<cRegistro>();
	this->listaJugadores = definirJugadores();
	this->mapa = crearMapa();
	this->turno = JUGADORES::JUGADOR1;
}
GameMaster::~GameMaster() {
	if (listaJugadores != NULL)
	{
		delete listaJugadores;
	}
	if (mapa != NULL)
	{
		delete mapa;
	}
}

void GameMaster::ronda() {

	//1° - rondaDistribuirTropa
	for (int i = 0; i < listaJugadores->getCA(); i++)
	{
		distribucionTropasEnJugador(generadorDeListaTropa(false));
	}
	mapa->imprimirMapa();
	//2° - rondaAtaqueDefensa
	int ataques = 0;
	cJugador* jugadorRetirado = NULL;
	for (int i = 0; i < listaJugadores->getCA(); i++) //para cada jugador
	{
		system("cls");
		mapa->imprimirMapa(); system("pause");

		cout << "\t<< JUGADOR " << i + 1 << " >> \n\n";
		determinarBonus();
		try {
			ataques = 0;
			turno = (JUGADORES)i;
			do {

				system("cls");
				mapa->imprimirMapa();

				switch (menuTurno())
				{
				case MENU::ATACAR:
					atacar();
					ataques++;
					break;
				case MENU::PASAR:
					throw new exception("CONTINUE");
					break;
				case MENU::ABANDONAR:
					imprimirRedefinicionJugadores((*listaJugadores)[(int)turno]);	jugadorRetirado = listaJugadores->QuitarenPos((int)turno);
					i--;	throw new exception("QUIT");
					break;
				default:
					break;
				}
			} while (ataques <= 3);
		}
		catch (exception* ex) {
			if (strcmp(ex->what(), "CONTINUE") == 0) //para pasar al siguiente jugador
				continue;
			if (strcmp(ex->what(), "QUIT") == 0) //para pasar al siguiente jugador
				continue;
			else 
				throw ex;
		}
	}

}
void GameMaster::Inicio()
{
	distribucionPaises();

	mapa->imprimirMapa();

	for (int i = 0; i < listaJugadores->getCA(); i++)
	{
		distribucionTropasEnJugador(generadorDeListaTropa(true));
		AumentarTurno();
	}
	rondasJugadas = 0;

	// Al ser el inicio de la partida, solo se distribuyen los paises y sus respectivas tropas
}
void GameMaster::distribucionPaises() {
	cListaT<cPais>* paisesDisponibles = new cListaT<cPais>();
	for (int i = 0; i < this->mapa->listaPaises->getCA(); i++)
		paisesDisponibles->AgregarItem((*((this->mapa)->listaPaises))[i]);
	if (paisesDisponibles->getCA() == 0)
		throw new exception("No hay paises para distribuir");

	int PaisesResto = (this->mapa->listaPaises->getCA()) % (listaJugadores->getCA());
	srand(time(NULL));

	cPais* paisAux = NULL;
	int pos = 0;
	for (int i = 0; i < PaisesResto; i++)
	{
		pos = rand() % listaJugadores->getCA();
		paisAux = paisesDisponibles->QuitarenPos(rand() % paisesDisponibles->getCA());
		(*listaJugadores)[pos]->agregarPais(paisAux);
		paisAux->cambiarControl((JUGADORES)pos);
	}
	int paisesPorJugador = (paisesDisponibles->getCA()) / (listaJugadores->getCA());

	for (int i = 0; i < paisesPorJugador; i++)
	{
		for (int j = 0; j < listaJugadores->getCA(); j++)
		{
			paisAux = paisesDisponibles->QuitarenPos(rand() % paisesDisponibles->getCA());
			(*listaJugadores)[j]->agregarPais(paisAux);
			paisAux->cambiarControl((JUGADORES)j);
		}
	}
	delete paisesDisponibles;
}
void GameMaster::distribucionTropasEnJugador(cListaT<cTropa>* listaTropas) {
	if (listaTropas != NULL)
		(*listaJugadores)[int(turno)]->distribucionTropasEnPaises(listaTropas);
}
cListaT<cTropa>* GameMaster::generadorDeListaTropa(bool inicio) {

	srand(time(NULL));
	cListaT<cTropa>* listaTropa = new cListaT<cTropa>;

	if (inicio) //Si es la primer ronda, cada jugador empieza con 10 tropas
	{
		for (int i = 0; i < 1; i++) //3 tropas de cada tipo 
			//TODO: volver a como estaba
		{
			listaTropa->AgregarItem(generadorDeTropa(TIPOTROPA::ARQUEROS));
			listaTropa->AgregarItem(generadorDeTropa(TIPOTROPA::CABALLEROS));
			listaTropa->AgregarItem(generadorDeTropa(TIPOTROPA::MAGOS));
		}

		TIPOTROPA tropaRand = TIPOTROPA(rand() % 3); //Tropa 10 random
		listaTropa->AgregarItem(generadorDeTropa(tropaRand));
		return listaTropa;
	}

	//TODO: descomentar

	//int cantTropasAgregar = ((*listaJugadores)[int(turno)]->getCantPaises()) / 2; //Cantidad de tropas para agregar al inicio de la ronda

	//for (int i = 0; i < cantTropasAgregar; i++)
	//{
	//	TIPOTROPA tropaRandom = TIPOTROPA(rand() % 3);
	//	listaTropa->AgregarItem(generadorDeTropa(tropaRandom));
	//}
	return listaTropa;
}
cTropa* GameMaster::generadorDeTropa(TIPOTROPA tropa)
{ //TODO: entre arqueros y magos tienen el mismo rand() (y entre la misma tropa)
	srand(time(NULL));
	cTropa* tropaAux = NULL;
	int cantUnidadesCaballeros, cantUnidadesArqueros, cantUnidadesMagos;
	switch (tropa)
	{
	case TIPOTROPA::ARQUEROS:
		tropaAux = new cTropa(TIPOTROPA::ARQUEROS);
		cantUnidadesArqueros = rand() % 16 + 15;
		for (int i = 0; i < cantUnidadesArqueros; i++)
		{
			tropaAux->AgregarItem(new cArqueros());
		}
		break;
	case TIPOTROPA::CABALLEROS:
		tropaAux = new cTropa(TIPOTROPA::CABALLEROS);
		cantUnidadesCaballeros = rand() % 11 + 10;
		for (int i = 0; i < cantUnidadesCaballeros; i++)
		{
			tropaAux->AgregarItem(new cCaballeros());
		}

		break;
	case  TIPOTROPA::MAGOS:
		tropaAux = new cTropa(TIPOTROPA::MAGOS);
		cantUnidadesMagos = rand() % 16 + 15;
		for (int i = 0; i < cantUnidadesMagos; i++)
		{
			tropaAux->AgregarItem(new cMagos());
		}
		break;
	default:
		break;
	}
	return tropaAux;
}
void GameMaster::AumentarTurno()
{
	if ((int)turno >= (listaJugadores->getCA() - 1))
	{
		turno = JUGADORES::JUGADOR1;
		rondasJugadas++;
	}
	else
	{
		turno = (JUGADORES)((int)turno + 1);
	}
}
void GameMaster::imprimirPantallaInicial()
{ 
	cout << "\n\n\n\n\n\t\t\t                                                                                           __          "<< endl;
	cout << "\t\t\t                                                                                          /\\ \\__      " << endl;
	cout << "\t\t\t   __           __         ___ ___        __              ___ ___        __         ____  \\ \\ ,_\\      __      _ __ " << endl;
	cout << "\t\t\t  /'_` \\     /'__`\\      /'__` __`\\     /'__`\\          /'__` __`\\     /'__`\\      /',__\\  \\ \\ \\/     /'__`\\  /\\`'__\\ " << endl;
	cout << "\t\t\t /\\ \\L\\ \\   /\\ \\L\\.\\_   /\\ \\/\\ \\/\\ \\   /\\  __/         /\\ \\/\\ \\/\\ \\   /\\ \\L\\.\\_   /\\__, `\\  \\ \\ \\_   /\\  __/  \\ \\ \\/ " << endl;
	cout << "\t\t\t \\ \\___  \\  \\ \\__/.\\_\\  \\ \\_\\ \\_\\ \\_\\  \\ \\____\\        \\ \\_\\ \\_\\ \\_\\  \\ \\__/.\\_\\  \\/\\____/   \\ \\__\\  \\ \\____\\  \\ \\_\\ " << endl;
	cout << "\t\t\t  \\/___L\\ \\  \\/__/\\/_/   \\/_/\\/_/\\/_/   \\/____/         \\/_/\\/_/\\/_/   \\/__/\\/_/   \\/___/     \\/__/   \\/____/   \\/_/ " << endl;
	cout << "\t\t\t   /\\____/         " << endl; 
	cout << "\t\t\t   \\_/__/ " << endl;

	int opcion = 0;
	cout << "\n\n\n\t\t\t\t\t\t\t\t\t<< MENU INICIAL >>\n\t\t\t\t\t\t\t\t\t1. Jugar\n\t\t\t\t\t\t\t\t\t2. Reglas\n\t\t\t\t\t\t\t\t\t3. Estadisticas\n\t\t\t\t\t\t\t\t\t4. Salir\n\t\t\t\t\t\t\t\t\tIngrese una opcion: ";
	cin >> opcion;
	switch (opcion)
	{
	case 1: 
		break;
	case 2: 
		imprimirReglas();
		break;
	case 3:
		imprimirEstadisticas();
		break;
	case 4:
		throw new exception("QUIT");
	default:
		break;
	}
}
void GameMaster::imprimirRedefinicionJugadores(cJugador* jugadorRetirado)
{
	cout << "El jugador " << jugadorRetirado->getclave() << "se ha retirado" << endl;
	cout << "Nueva distribucion de jugadores: " << listaJugadores << endl;
}
MENU GameMaster::menuTurno()
{
	int opcion = 0;
	do {
		cout << "Desea:\n\t1. Atacar\n\t2. Pasar\n\t3. Abandonar" << endl;
		cout << "Ingrese la opcion: " << endl;
		 cin >> opcion;
	} while (opcion < 1 || opcion > 3);
	if (opcion == 3)
		(registroJugadores->BuscarItem(((*listaJugadores)[(int)turno])->getclave()))->quitter();

	return (MENU)opcion;
}
cListaT<cJugador>* GameMaster::definirJugadores()
{
	int cantJugadores = 0;
	do {
		cout << "\t<<De 2 a 5 Jugadores>> \n\tIngrese la cantidad de jugadores: ";
		cin >> cantJugadores;
	} while ((cantJugadores < 2) || (cantJugadores > 6));

	cListaT<cJugador>* listaJugadores = new cListaT<cJugador>(cantJugadores);
	cJugador* aux = NULL;
	string usuario = "", contrasenia = ""; int pos = -1; string registro = "";
	for (int i = 0; i < cantJugadores; i++)
	{
		cout << "JUGADOR " << i + 1 << endl;
		cout << "\tIngrese su usuario: ";
		cin >> usuario;
		pos = registroJugadores->getItemPos(usuario);
		if (pos == -1) {
			cout << "El usuario ingresado no se encuentra registrado. Desea registrarlo? Ingrese 'si' o 'no': "; cin >> registro;
			if (registro == "no") {
				i--;
				continue;
			}
			else if (registro == "si") {
				cout << "Ingrese una contrasenia: "; cin >> contrasenia;
				registroJugadores->AgregarItem(new cRegistro(usuario, contrasenia));
			}
		}
		else
		{
			do {
				cout << "\tIngrese su contrasenia: ";
				cin >> contrasenia;	
			} while (!(*registroJugadores)[pos]->esContrasenia(contrasenia));
		}
		aux = new cJugador((JUGADORES) i, usuario);
		try {
			listaJugadores->AgregarItem(aux);
		}
		catch (exception* ex) {
			cout << "El usuario ingresado no esta disponible. Ingese otro.";
			i--;
		}

	}
	return listaJugadores;
}
cMapa* GameMaster::crearMapa()
{
	int continente;
	cMapa* miMapa = NULL;
	system("cls");
	cout << "\nCONTINENTE" << endl;
	cout << "Eliga el mapa del continente donde quiere jugar" << endl;
	do {
		cout << "\t1. latinoAmerica\n\t2. America (PROXIMAMENTE)\n\t3. Europa (PROXIMAMENTE)" << endl;
		cin >> continente;
		if (continente == ((int)MAPA::LATINOAMERICA + 1)) {
			//creo listaPaises con el archivo, se la paso a mapa
			miMapa = new cMapa(MAPA::LATINOAMERICA);
			miMapa->poblacionar();
			return miMapa;
		}
		else {
			cout << "El continente ingresado no es correcto. Vuelva a intentarlo: " << endl;
		}
	} while (continente != ((int)MAPA::LATINOAMERICA + 1));


	return NULL;
}
void GameMaster::determinarBonus()
{
	int bonus = rand() % 8 + 1;
	BONUS premio;
	switch (bonus) {
	case 1:
	case 2:
	case 3:
	case 4:
		premio = (BONUS)bonus;
		break;
	default:
		return;
	}

	cout << "\n\n\t\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "\n\t\t\t\t\t\tHAS RECIBIDO UN BONUS: " << endl;
	cout << "\n\t\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

	switch (premio)
	{	
	case BONUS::COMIDA:
		cout << historiaComida << endl;
		break;
	case BONUS::INTELIGENCIA:
		cout << historiaInteligencia << endl;
		break;
	case BONUS::ESTRATEGIA:
		cout << historiaEstrategia << endl;
		break;
	case BONUS::PUNTERIA:
		cout << historiaPunteria << endl;
		break;
	default:
		return;
	}
	(*listaJugadores)[(int)turno]->agregarBonus(premio);
}
void GameMaster::imprimirMapa()
{
	mapa->imprimirMapa();
}
void GameMaster::imprimirReglas()
{
	//TODO: hacer
}
void GameMaster::imprimirEstadisticas()
{
	//TODO: hacer
}
void GameMaster::atacar()
{
	cPais* paisGanado = (*listaJugadores)[(int)turno]->atacar(getListaPaisesOponentes());
	if (paisGanado != NULL) {
		(*listaJugadores)[(int)turno]->agregarPais((*listaJugadores)[(int)(paisGanado->getControl())]->quitarPais(paisGanado->getclave()));
		if (mapa->chequearConquista()) {
			JUGADORES jugadorGanador = turno;
			cRegistro* registro = NULL;
			for (int i = 0; i < listaJugadores->getCA(); i++)
			{
				registro = registroJugadores->BuscarItem(((*listaJugadores)[i])->getclave());

				if (i == (int)jugadorGanador)
					registro->winner();
				else
					registro->loser();
			}
			throw new exception(("WINNER: " + (*listaJugadores)[(int)jugadorGanador]->getclave()).c_str());
		}
	}
}
void GameMaster::escribirRegistroJugadores()
{
	archivoJugadores->escribirArchivoDat(registroJugadores);
}
cListaT<cPais>* GameMaster::getListaPaisesOponentes() {

	cListaT<cPais>* PaisesOponentes = new cListaT<cPais>();
	for (int i = 0; i < (mapa->listaPaises)->getCA(); i++)
	{
		if ((*(mapa->listaPaises))[i]->getControl() != turno)
		{
			PaisesOponentes->AgregarItem((*(mapa->listaPaises))[i]);
		}
	}
	return PaisesOponentes;
}
                      