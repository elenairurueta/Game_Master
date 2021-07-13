#pragma once
#include <iostream>
#include "cUnidad.h"
#include "cListaT.h"
using namespace std;

class cTropa :
	public cListaT<cUnidad>
{

public:
	cTropa(TIPOTROPA tipoTropa);
	~cTropa();

	//agrega unidades a la tropa siempre y cuando sean del mismo tipo, si no se pueden agregar, las elimina
	void agregarUnidades(cListaT<cUnidad>* unidadesAgregadas);
	//ataca a la tropa y devuelve el daño que va a causar dependiendo el tipo de tropa
	int atacar(TIPOTROPA unidadesAtacadas);
	//contrataca dependiendo el tipo de tropa
	int contrataque(TIPOTROPA unidadesAtacadas);
	//recibe el daño del ataque y lo reparte desde la unidad con menor a mayor HP 
	void recibirDano(int dano);
	//devuelve true si no quedan unidades vivas
	bool verificarBaja();

	void aplicarBonus(BONUS bonus);
	cTropa* dividirTropa();

#pragma region GETTERS
	int getTotalHP();
	int getTotalAT();
	string getTipoTropaString();
	TIPOTROPA getTipoTropa();
	string getclave();
#pragma endregion

#pragma region OPERATORS
	void operator-(int danio);

	//friend function
	friend ostream& operator<<(ostream& out, cTropa* tropa);
#pragma endregion
	string toString();

private:
#pragma region ATRIBUTOS
	const int id;
	TIPOTROPA tipoTropa;
	static int cantTropas;
#pragma endregion
};

