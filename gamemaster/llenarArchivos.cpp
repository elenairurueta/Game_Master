//EJECUTAR SOLO UNA VEZ
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "llenarArchivos.h"


void llenarArchivoPaises(){

	cPais* pais = NULL;
	cListaT<cPais>* listaPaises = new cListaT<cPais>();

	pais = new cPais("Mexico", "MEXICOOOOOO"); listaPaises->AgregarItem(pais);
	pais = new cPais("Cuba", "CUBAAAAAAAA"); listaPaises->AgregarItem(pais);
	pais = new cPais("Colombia", "COLOMBIAAAA"); listaPaises->AgregarItem(pais);
	pais = new cPais("Venezuela", "VENEZUELAAA"); listaPaises->AgregarItem(pais);
	pais = new cPais("Ecuador", "ECUADORRRRR"); listaPaises->AgregarItem(pais);
	pais = new cPais("Peru", "PERUUUUUUUU"); listaPaises->AgregarItem(pais);
	pais = new cPais("Brasil", "BRASILLLLLL"); listaPaises->AgregarItem(pais);
	pais = new cPais("Bolivia", "BOLIVIAAAAA"); listaPaises->AgregarItem(pais);
	pais = new cPais("Argentina", "ARGENTINAAA"); listaPaises->AgregarItem(pais);
	pais = new cPais("Chile", "CHILEEEEEEE"); listaPaises->AgregarItem(pais);
	pais = new cPais("Uruguay", "URUGUAYYYYY"); listaPaises->AgregarItem(pais);


	(listaPaises->BuscarItem("Mexico"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Cuba"));
	(listaPaises->BuscarItem("Mexico"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Colombia"));
	(listaPaises->BuscarItem("Cuba"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Mexico"));
	(listaPaises->BuscarItem("Cuba"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Venezuela"));
	(listaPaises->BuscarItem("Colombia"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Venezuela"));
	(listaPaises->BuscarItem("Colombia"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Brasil"));
	(listaPaises->BuscarItem("Colombia"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Ecuador"));
	(listaPaises->BuscarItem("Colombia"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Peru"));
	(listaPaises->BuscarItem("Colombia"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Mexico"));
	(listaPaises->BuscarItem("Venezuela"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Colombia"));
	(listaPaises->BuscarItem("Venezuela"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Brasil"));
	(listaPaises->BuscarItem("Venezuela"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Cuba"));
	(listaPaises->BuscarItem("Ecuador"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Peru"));
	(listaPaises->BuscarItem("Ecuador"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Colombia"));
	(listaPaises->BuscarItem("Peru"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Colombia"));
	(listaPaises->BuscarItem("Peru"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Ecuador"));
	(listaPaises->BuscarItem("Peru"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Brasil"));
	(listaPaises->BuscarItem("Peru"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Bolivia"));
	(listaPaises->BuscarItem("Peru"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Chile"));
	(listaPaises->BuscarItem("Brasil"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Colombia"));
	(listaPaises->BuscarItem("Brasil"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Venezuela"));
	(listaPaises->BuscarItem("Brasil"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Peru"));
	(listaPaises->BuscarItem("Brasil"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Bolivia"));
	(listaPaises->BuscarItem("Brasil"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Argentina"));
	(listaPaises->BuscarItem("Brasil"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Uruguay"));
	(listaPaises->BuscarItem("Bolivia"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Peru"));
	(listaPaises->BuscarItem("Bolivia"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Brasil"));
	(listaPaises->BuscarItem("Bolivia"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Argentina"));
	(listaPaises->BuscarItem("Bolivia"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Chile"));
	(listaPaises->BuscarItem("Argentina"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Chile"));
	(listaPaises->BuscarItem("Argentina"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Uruguay"));
	(listaPaises->BuscarItem("Argentina"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Brasil"));
	(listaPaises->BuscarItem("Argentina"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Bolivia"));
	(listaPaises->BuscarItem("Chile"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Argentina"));
	(listaPaises->BuscarItem("Chile"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Bolivia"));
	(listaPaises->BuscarItem("Chile"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Peru"));
	(listaPaises->BuscarItem("Uruguay"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Argentina"));
	(listaPaises->BuscarItem("Uruguay"))->PaisesVecinos->AgregarItem(listaPaises->BuscarItem("Brasil"));


	Archivo* archivoListaPaises = new Archivo("listaPaisesLatinoamerica", ARCHIVO::DAT);
	archivoListaPaises->escribirArchivoDat(listaPaises);
	delete archivoListaPaises; delete listaPaises;

	cRegistro* registro = new cRegistro("elena", "44006960");
	cListaT<cRegistro>* listaRegistros = new cListaT<cRegistro>();
	listaRegistros->AgregarItem(registro);
	Archivo* archivoRegistros = new Archivo("registroJugadores", ARCHIVO::DAT);
	archivoRegistros->escribirArchivoDat(listaRegistros);
	delete archivoRegistros; delete listaRegistros;
}