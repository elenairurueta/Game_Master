#include "cJugador.h"
#include "cListaT.h"
#include "cPais.h"
#include"cArqueros.h"
#include "cCaballeros.h"
#include "cMagos.h"

int cJugador::cantidadJugadores = 0;

cJugador::cJugador(JUGADORES jugador, string usuario, cListaT<cPais>* listaPaises) :usuario(usuario), jugador(jugador)
{
	if (listaPaises != NULL)
	{
		this->listaPaises = listaPaises;
	}
	else {
		this->listaPaises = new cListaT<cPais>();
	}
	cantidadJugadores++;

}

cJugador::~cJugador() {
	if (listaPaises != NULL)
	{
		delete listaPaises;
	}
}

void cJugador::distribucionTropasEnPaises(cListaT<cTropa>* listaTropas) {

	string pais = "";
	if (listaTropas != NULL)
	{
		for (int i = 0; i < listaTropas->getCA(); i++)
		{
			system("cls");
			cout << "JUGADOR " << ((int)jugador + 1) << endl;
			cout << "Donde desea agregar la siguiente tropa?\n" << (*listaTropas)[i] << endl;
			for (int j = 0; j < listaPaises->getCA(); j++)
			{
				cout << (*listaPaises)[j] << endl;
			}
			cout << "Ingrese el pais: ";
			cin >> pais;
			cPais* paisptr = listaPaises->BuscarItem(pais);
			if (paisptr == NULL) {
				i--;
				continue;
			}
			paisptr->agregarTropas((*listaTropas)[i]);
		}
	}
}

cPais* cJugador::atacar(cListaT<cPais>* listaPaisesJugadorOponente)
{
	int pos = 0;
	system("cls");
	cout << "A que pais desea atacar?" << endl;
	for (int i = 0; i < listaPaisesJugadorOponente->getCA(); i++)
	{
		cout << "\nPais " << i + 1 << ":\n\t" << (*listaPaisesJugadorOponente)[i] << endl;
	}

	cListaT<cPais>* listaMisPaisesVecinos = new cListaT<cPais>();
	cPais* paisAtacar = NULL;
	do {
		do {
			cout << "Ingrese el numero del pais: ";
			cin >> pos;
		} while (pos > listaPaisesJugadorOponente->getCA() || pos < 1);
		paisAtacar = listaPaisesJugadorOponente->getItem(pos - 1);
		if (paisAtacar != NULL)
			listaMisPaisesVecinos = getListaMisPaisesVecinos(paisAtacar);//TODO: hacer un metodo que devuelva los paises vecinos que pueda atacar
		else
			listaMisPaisesVecinos == NULL;

	} while (listaMisPaisesVecinos == NULL);//cambiar

	cTropa* tropaAtacada = paisAtacar->atacado();
	if (tropaAtacada == NULL)
		return paisAtacar;

	cout << "¿Con que pais desea atacar?" << endl;
	for (int i = 0; i < listaMisPaisesVecinos->getCA(); i++)
	{
		if ((*listaMisPaisesVecinos)[i]->getCantidadTropas() <= 0)
			continue;
		cout << "\nPais " << i + 1 << "\n\t" << (*listaMisPaisesVecinos)[i] << endl;
	}
	cout << "Ingrese el numero de pais: ";
	cin >> pos;
	cPais* paisAtacante = listaMisPaisesVecinos->getItem(pos-1);
	cTropa* tropaAtacante = paisAtacante->atacante();
	try {
		paisAtacar->recibirAtaque(tropaAtacada, tropaAtacante->atacar(tropaAtacada->getTipoTropa()));
	}
	catch (exception* ex) {
		paisAtacar->pasarTropa(paisAtacante);
		return paisAtacar;
	}
	
	try {
		do {
			string opcion;
			cout << "JUGADOR " << to_string((int)(paisAtacar->getControl()) + 1) << ": Desea contraatacar? Ingrese 'si' o 'no': ";
			cin >> opcion;
			if (opcion == "si")
				break;
			else if (opcion == "no")
				return NULL;
		} while (true);
		if (tropaAtacada->getCA() > 0) //si la tropa atacada sigue con vida, puede contraatacar
			paisAtacante->recibirAtaque(tropaAtacante, tropaAtacada->contrataque(tropaAtacante->getTipoTropa()));
	}
	catch (exception* ex) {

		TIPOTROPA unidad = (TIPOTROPA)(rand() % 3);
		cTropa* tropa = NULL;
		switch (unidad)
		{
		case TIPOTROPA::ARQUEROS:
			tropa->AgregarItem(new cArqueros());
			break;
		case TIPOTROPA::CABALLEROS:
			tropa->AgregarItem(new cCaballeros());
			break;
		case TIPOTROPA::MAGOS:
			tropa->AgregarItem(new cMagos());
			break;
		default:
			break;
		}
		paisAtacante->agregarTropas(tropa);
	}

	return NULL;
}

void cJugador::agregarPais(cPais* paisAgregar) {
	listaPaises->AgregarItem(paisAgregar);
	//paisAgregar->cambiarControl(this->jugador);
}

cPais* cJugador::quitarPais(string paisQuitar) {
	return listaPaises->Quitar(listaPaises->BuscarItem(paisQuitar));
}

int cJugador::getCantPaises()
{
	return listaPaises->getCA();
}

string cJugador::getclave()
{
	return usuario;
}

cListaT<cPais>* cJugador::getListaMisPaisesVecinos(cPais* pais)
{
	cListaT<cPais>* listaVecinos = new cListaT<cPais>();
	for (int i = 0; i < listaPaises->getCA(); i++)
	{
		if ((*listaPaises)[i]->chequearVecino(pais))
			listaVecinos->AgregarItem((*listaPaises)[i]);
	}
	if (listaVecinos != NULL)
		return listaVecinos;
	return NULL;
}

void cJugador::agregarBonus(BONUS bonus)
{
	cout << "Tus Tropas: ";
	for (int i = 0; i < listaPaises->getCA(); i++)
		cout << "\n" << (*listaPaises)[i]->getclave() << (*listaPaises)[i]->toStringTropasListadas();
	cPais* pais = NULL;
	do {
		cout << "\n\nIngrese el pais en donde se encuentra la tropa a aplicar el bonus recibido: ";
		string clave = "";
		cin >> clave;
		pais = listaPaises->BuscarItem(clave);
	} while (pais == NULL);
	cout << pais->toStringTropasListadas();
	cout << "\n\nIngrese el numero de tropa a aplicar el bonus recibido: ";
	int pos = 0;
	cin >> pos;
	pais->aplicarBonusATropa(pos - 1, bonus);
}

