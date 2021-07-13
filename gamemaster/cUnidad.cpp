#include <string>
#include "cUnidad.h"

int cUnidad::unidadesCreadas = 0;

cUnidad::cUnidad(int AT, int HP) :HPinicial(HP), id(unidadesCreadas)
{
	this->AT = AT;
	this->HP = HP;
	this->porcentajeVida = 100;
	unidadesCreadas++;
}

cUnidad::~cUnidad() {

}

void cUnidad::actualizarPorcetajeDeVida() {

	if (HP < 0)
		porcentajeVida = 0;
}

bool cUnidad::verificarBaja() {

	if (porcentajeVida <= 10)
		return true;
	return false;
}

int cUnidad::getHP()
{
	return HP;
}

int cUnidad::getAT()
{
	return AT;
}

string cUnidad::getclave()
{
	return to_string(id);
}
