
#include "cTropa.h"
#include "cArqueros.h"
#include "cCaballeros.h"
#include "cMagos.h"


int cTropa::cantTropas = 0;

cTropa::cTropa(TIPOTROPA tipoTropa):cListaT<cUnidad>(), id(cantTropas) {

	this->tipoTropa = tipoTropa;
	cantTropas++;
}
cTropa::~cTropa() {

}

void cTropa::agregarUnidades(cListaT<cUnidad>* unidadesAgregadas)
{
	if (unidadesAgregadas == NULL)
		throw new exception("No existe la lista de unidades que se esta intentando agregar");

	cUnidad* unidad = NULL;
	for (int i = 0; i < unidadesAgregadas->getCA(); i++) {
		switch (tipoTropa)
		{
		case TIPOTROPA::ARQUEROS:
			unidad = dynamic_cast<cArqueros*>((*unidadesAgregadas)[i]);
			if (unidad == NULL) {
				throw new exception("No se pueden combinar unidades distintas en una tropa");
			}
			break;
		case TIPOTROPA::CABALLEROS:
			unidad = dynamic_cast<cCaballeros*>((*unidadesAgregadas)[i]);
			if (unidad == NULL) {
				throw new exception("No se pueden combinar unidades distintas en una tropa");
			}
			break;
		case TIPOTROPA::MAGOS:
			unidad = dynamic_cast<cMagos*>((*unidadesAgregadas)[i]);
			if (unidad == NULL) {
				throw new exception("No se pueden combinar unidades distintas en una tropa");
			}
			break;
		default:
			break;
		}
		this->AgregarItem((*unidadesAgregadas)[i]);
	}
}

int cTropa::atacar(TIPOTROPA unidadesAtacadas)
{
	int dano = getTotalAT();
	switch (tipoTropa)
	{
	case TIPOTROPA::ARQUEROS:
		switch (unidadesAtacadas)
		{
		case TIPOTROPA::ARQUEROS:
			break;
		case TIPOTROPA::CABALLEROS:
			dano -= (dano * 0.25);
			break;
		case TIPOTROPA::MAGOS:
			dano += (dano * 0.25);
			break;
		default:
			break;
		}
		break;
	case TIPOTROPA::CABALLEROS:
		switch (unidadesAtacadas)
		{
		case TIPOTROPA::ARQUEROS:
			dano += (dano * 0.25);
			break;
		case TIPOTROPA::CABALLEROS:
			break;
		case TIPOTROPA::MAGOS:
			dano -= (dano * 0.25);
			break;
		default:
			break;
		}
		break;
	case TIPOTROPA::MAGOS:
		switch (unidadesAtacadas)
		{
		case TIPOTROPA::ARQUEROS:
			dano -= (dano * 0.25);
			break;
		case TIPOTROPA::CABALLEROS:
			dano += (dano * 0.25);
			break;
		case TIPOTROPA::MAGOS:
			break;
		default:
			break;
		}
		break;
	default:
		return 0;  break;
	}
	return dano;
	//caballero>>arquero
	//arquero>>mago
	//mago>>caballero
	//TODO: arquero segundo ataque aleatorio con +50%
	//TODO: mago ataca en zona 
}

int cTropa::contrataque(TIPOTROPA unidadesAtacadas) {

	int dano = atacar(unidadesAtacadas);
	if (tipoTropa == TIPOTROPA::CABALLEROS)
		dano += (dano * 0.25);
	return dano;
}

void cTropa::recibirDano(int dano) {

	int contador = 0;
	cUnidad* UnidadAux = NULL;
	for (int i = 0; i < CA - 1; i++)
	{
		contador = 0;
		for (int j = 0; j < CA - 1; j++)
		{
			if ((*this)[j]->getHP() > (*this)[j + 1]->getHP())
			{
				UnidadAux = (*this)[j];
				(*this)[j] = (*this)[j + 1];
				(*this)[j + 1] = UnidadAux;
				contador++;
			}
		}
		if (contador == 0)
			break;
	}


	do
	{
		try
		{
			(*this)[0]->recibirDano(dano);
		}
		catch (exception* ex)
		{
			delete (this->QuitarenPos(0));

		}
		if (verificarBaja())
		{
			throw new exception("Se murieron todas las unidades de la tropa");
		}

	} while (dano > 0);

}

bool cTropa::verificarBaja()
{
	if (CA == 0)
		return true;
	return false;
}

void cTropa::aplicarBonus(BONUS bonus)
{
	for (int i = 0; i < CA; i++)
		(*this)[i]->recibirBonus(bonus);
}

cTropa* cTropa::dividirTropa()
{
	if (CA < 2)
		return NULL;
	int total = CA, cant = 0;
	if (CA % 2 != 0) {
		total--;
	}
	cant += total / 2;

	cTropa* otraTropa = new cTropa(this->getTipoTropa());
	for (int i = 0; i < cant; i++) {
		otraTropa->AgregarItem(this->QuitarenPos(i));
	}
	return otraTropa;
}

#pragma region GETTERS

int cTropa::getTotalHP()
{
	int acum = 0;
	for (unsigned int i = 0; i < CA; i++)
	{
		acum += vector[i]->getHP();
	}
	return acum;
}

int cTropa::getTotalAT()
{
	int acum = 0;
	for (unsigned int i = 0; i < CA; i++)
	{
		acum += vector[i]->getAT();
	}
	return acum;
}

string cTropa::getTipoTropaString()
{
	switch (tipoTropa)
	{
	case TIPOTROPA::ARQUEROS:
		return "A";
		break;
	case TIPOTROPA::CABALLEROS:
		return "C";
		break;
	case TIPOTROPA::MAGOS:
		return "M";
		break;
	default:
		return " ";
		break;
	}
}

TIPOTROPA cTropa::getTipoTropa()
{
	return tipoTropa;
}

string cTropa::getclave()
{
	return to_string(id);
}

#pragma endregion

#pragma region OPERATORS
ostream& operator<<(ostream& out, cTropa* tropa)
{
	out << tropa->toString() << "  ( HP: " << tropa->getTotalHP() << " AT: " << tropa->getTotalAT() << " ) " << endl;
	return out;
}

void cTropa::operator-(int danio)
{
	recibirDano(danio);
}


#pragma endregion

string cTropa::toString()
{
	return (getTipoTropaString() + " " + to_string(CA));
}