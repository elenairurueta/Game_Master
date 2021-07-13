#pragma once
#include "cPais.h"

cListaT<cPais> cPais::listaPaises = cListaT<cPais>();

cPais::cPais(string nombre, string nombreEnMapa, cEjercito* ejercito, cListaT<cPais>* PaisesVecinos) :nombre(nombre), nombreEnMapa(nombreEnMapa) { 
	if (ejercito != NULL)
		this->ejercito = ejercito;
	else
		this->ejercito = new cEjercito();
	this->control = JUGADORES::NINGUNO;
	if (PaisesVecinos != NULL)
		this->PaisesVecinos = PaisesVecinos;
	else
		this->PaisesVecinos = new cListaT<cPais>();
}

cPais::~cPais() {
	if (ejercito != NULL)
		delete ejercito;
}


void cPais::agregarTropas(cTropa* tropaAgregar)
{
	cTropa* tropaCombinar = NULL;
	do {
		do {
			tropaCombinar = NULL;
			getchar();
			cout << "Desea combinar con otra tropa? Ingrese 'si' o 'no': " << toStringTropasListadas() << endl;
			string opcion = ""; cin >> opcion;
			if (opcion == "si") {
				if (ejercito->getCA() <= 0)
				{
					cout << "No hay tropas para combinar. Vuelva a intentarlo." << endl;
					continue;
				}
				cout << "Con cual? ";
				int tropa = 0; cin >> tropa;
				tropaCombinar = ejercito->getItem(tropa - 1);
				break;
			}
			else if (opcion == "no")
			{
				break;
			}
			else {
				cout << "\nLa respuesta no es valida. Vuelva a intentarlo." << endl;
			}
		} while (true);

		try {
			ejercito->agregarOcombinarTropa(tropaAgregar, tropaCombinar);
		}
		catch (exception* ex) {
			cout << ex->what() << endl;
			continue;
		}
		break;
	} while (true);
}

cTropa* cPais::atacado() {

	return ejercito->elegirTropa(ROLES::ATACADO);
}

cTropa* cPais::atacante() {

	return ejercito->elegirTropa(ROLES::ATACANTE);
}
void cPais::recibirAtaque(cTropa* tropaAtacada, int dano) {

	if (ejercito->getItemPos(tropaAtacada->getclave()) < 0)
	{
		throw new exception("No se encuentra la tropa que se quiso atacar");
	}

	cout << tropaAtacada->getTotalHP() << endl;
	(*tropaAtacada) - dano;
	cout << tropaAtacada->getTotalHP() << endl;

	if (chequearPaisPerdido())
		throw new exception(("PAIS " + this->nombre + " GANADO").c_str());
}

void cPais::cambiarControl(JUGADORES NumeroJugador)
{
	control = NumeroJugador;
}

bool cPais::chequearPaisPerdido()
{
	int HPPais = 0;
	for (int i = 0; i < ejercito->getCA(); i++) {
		HPPais += (*ejercito)[i]->getTotalHP();
	}
	if (HPPais <= 0)
		return true;
	return false;
}

JUGADORES cPais::getControl()
{
	return control;
}

string cPais::getclave()
{
	return nombre;
}

void cPais::pasarTropa(cPais* paisQuePasa)
{
	cout << "Que tropa desea pasar al pais ganado?" << endl;
	cout << paisQuePasa->ejercito->toStringTropasListadas() << endl;
	int pos = 0;
	if (paisQuePasa->ejercito->getCA() > 1) {
		cout << "\n\nIngrese el numero de la tropa que desea pasar: ";
		cin >> pos;
		this->ejercito->AgregarItem((*(paisQuePasa->ejercito))[pos - 1]);
	}
	else if ((paisQuePasa->ejercito->getCA() == 1) && ((*(paisQuePasa->ejercito))[0]->getCA() > 1)) {
		cout << "\n\nLa tropa se dividira por la mitad";
		this->ejercito->AgregarItem((*(paisQuePasa->ejercito))[0]->dividirTropa());
	}
}

string cPais::toStringTropasListadas()
{
	return ejercito->toStringTropasListadas();
}

cTropa* cPais::sacarTropa(int pos)
{
	return ejercito->QuitarenPos(pos);
}

bool cPais::chequearVecino(cPais* pais)
{
	if (this->PaisesVecinos->BuscarItem(pais->getclave()) == NULL)
		return false;
	return true;
}

void cPais::aplicarBonusATropa(int pos, BONUS bonus)
{
	switch (bonus)
	{
	case BONUS::COMIDA:
		break;
	case BONUS::INTELIGENCIA:
		if ((*ejercito)[pos]->getTipoTropa() != TIPOTROPA::MAGOS)
			return;
		break;
	case BONUS::ESTRATEGIA:
		if ((*ejercito)[pos]->getTipoTropa() != TIPOTROPA::CABALLEROS)
			return;
		break;
	case BONUS::PUNTERIA:
		if ((*ejercito)[pos]->getTipoTropa() != TIPOTROPA::ARQUEROS)
			return;
		break;
	default:
		break;
	}
	(*ejercito)[pos]->aplicarBonus(bonus);

}

int cPais::getCantidadTropas()
{
	return ejercito->getCA();
}

string cPais::toString(string separador)
{
	return (nombre + to_string((int)control));
}

ostream& operator<<(ostream& out, cPais* Pais)
{
	out << Pais->nombre << "  (" << (int)Pais->control + 1 << ") \n" << Pais->ejercito << endl;
	return out;
}

