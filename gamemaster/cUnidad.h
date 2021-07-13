#pragma once
#include <iostream>
#include <string>
#include "Defines.h"
using namespace std;
class cUnidad
{

public:
	cUnidad(int AT = 0, int HP = 100);
	virtual ~cUnidad();

	//actualiza el porcentaje de vida teniendo en cuenta el HP y el HPinicial
	void actualizarPorcetajeDeVida();
	//recibe del daño y lo resta del HP
	virtual void recibirDano(int& dano) = 0;
	bool verificarBaja();
	int getHP();
	int getAT();
	string getclave();
	virtual void recibirBonus(BONUS bonus) = 0;

protected:
	int AT;
	int HP;
	const int HPinicial;
	float porcentajeVida;
	const int id;
	static int unidadesCreadas;
};
