#include "cEjercito.h"
#include "cListaT.h"

cEjercito::cEjercito():cListaT<cTropa>() {
}

cEjercito::~cEjercito() {
}

void cEjercito::agregarOcombinarTropa(cTropa* tropaAgregar, cTropa* tropaCombinar ) {
	if (tropaCombinar == NULL)
	{
		AgregarItem(tropaAgregar);
	}
	else
	{
		tropaCombinar->agregarUnidades(tropaAgregar);	}
}

cTropa* cEjercito::elegirTropa(ROLES atacado_atacante) { //  Atacado -> a que tropa     Atacante-> con que tropa
	if (CA <= 0)
		return NULL;
	if (atacado_atacante == ROLES::ATACADO)
	{
		cout << "¿A que tropa desea atacar?" << endl;
	}
	else if (atacado_atacante == ROLES::ATACANTE)
	{
		cout << "¿Con que tropa desea atacar?" << endl;
	}
	cout << toStringTropasListadas() << endl;
	cout << "Ingrese la tropa: ";
	int tropa = 0; cin >> tropa;

	return (*this)[tropa - 1];
}

string cEjercito::toStringTropasListadas()
{
	string cadena = "";
	for (int i = 0; i < CA; i++)
	{
		cadena += "\n" + to_string(i + 1) + ": " + (this->getItem(i))->getTipoTropaString() + " " + to_string((this->getItem(i))->getCA());
	}
	return cadena;
}

string cEjercito::toStringParaElMapa()
{
	string cadena = "";
	int caballeros = 0, arqueros = 0, magos = 0;
	for (int i = 0; i < CA; i++)
	{
		if ((*this)[i]->getTipoTropa() == TIPOTROPA::ARQUEROS)
			arqueros += (*this)[i]->getCA();
		else if ((*this)[i]->getTipoTropa() == TIPOTROPA::CABALLEROS)
			caballeros += (*this)[i]->getCA();
		else if ((*this)[i]->getTipoTropa() == TIPOTROPA::MAGOS)
			magos += (*this)[i]->getCA();
	}
	if (caballeros < 10)
		cadena += "0" + to_string(caballeros) + "C ";
	else
		cadena += to_string(caballeros) + "C ";

	if (arqueros < 10)
		cadena += "0" + to_string(arqueros) + "A ";
	else
		cadena += to_string(arqueros) + "A ";

	if (magos < 10)
		cadena += "0" + to_string(magos) + "M";
	else
		cadena += to_string(magos) + "M";

	if (cadena == "")
		return "00C 00A 00M";

	return cadena;
}

ostream& operator<<(ostream& out, cEjercito* ejercito)
{
	if (ejercito == NULL)
		out << "";
	for (int i = 0; i < ejercito->CA; i++)
	{
		out << "\n\t\t" << (*ejercito)[i];
	}
	return out;
}

