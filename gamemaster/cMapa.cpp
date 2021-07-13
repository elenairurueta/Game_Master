#pragma once
#include "cMapa.h"

cMapa::cMapa(MAPA nombre, cListaT<cPais>* listaPaises):nombre(nombre) {

	if (listaPaises == NULL) {
		listaPaises = new cListaT<cPais>(); //creamos la lista de países
	}
	this->listaPaises = listaPaises;
	switch (nombre)
	{
	case MAPA::LATINOAMERICA:
		archivoMapa = new Archivo("mapaLatinoamerica", ARCHIVO::TXT); //creamos los archivos del mapa y listaPaises
		archivoListaPaises = new Archivo("listaPaisesLatinoamerica", ARCHIVO::DAT);
		break;
	case MAPA::AMERICA:
		archivoMapa = new Archivo("mapaAmerica", ARCHIVO::TXT);
		archivoListaPaises = new Archivo("listaPaisesAmerica", ARCHIVO::DAT);
		break;
	case MAPA::EUROPA:
		archivoMapa = new Archivo("mapaEuropa", ARCHIVO::TXT);
		archivoListaPaises = new Archivo("listaPaisesEuropa", ARCHIVO::DAT);
		break;
	default:
		break;
	}
	poblacionar(); //leemos los archivos e inicializamos mapa y listaPaises
}
cMapa::~cMapa() {
	if (listaPaises != NULL)
		delete listaPaises;
}

void cMapa::poblacionar()
{
	mapa = archivoMapa->leerArchivoTxt();
	listaPaises = archivoListaPaises->leerArchivoDat<cPais>();
}


bool cMapa::chequearConquista() {

	JUGADORES ganador = (*listaPaises)[0]->getControl();

	for (int i = 0; i < (listaPaises->getCA()); i++) {
		if ((*listaPaises)[i]->getControl() != ganador)
			return false;
	}

	return true;
}


void cMapa::definirPaisesVecinos()
{
}

void cMapa::imprimirMapa()
{
	string mapaImprimir = mapa;
	string substr = "";
	size_t pos = 0;

	for (int i = 0; i < listaPaises->getCA(); i++)
	{
		substr = ((*listaPaises)[i]->nombreEnMapa).substr(0, 2); //primeras dos letras
		pos = mapaImprimir.find(substr) + 5; // CO (X)
		mapaImprimir.replace(pos, 1, to_string((int)((*listaPaises)[i]->getControl()) + 1));

		pos = mapaImprimir.find((*listaPaises)[i]->nombreEnMapa);
		substr = (*listaPaises)[i]->ejercito->toStringParaElMapa();
		mapaImprimir.replace(pos, 11, substr);

	}
	cout << mapaImprimir << endl;
}



