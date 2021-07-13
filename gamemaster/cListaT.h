#pragma once
#define NMAX 10
#include <iostream>
#include <string>

using namespace std;
template<class T>
class cListaT
{
	friend class Archivo;
protected:
	T** vector;
	unsigned int CA, TAM;

	void Redimensionalizar(int cant = NMAX);

public:
	cListaT(unsigned int TAM = NMAX);
	~cListaT();

	bool AgregarItem(T* item);

	T* Quitar(string clave);
	T* Quitar(T* item);
	T* QuitarenPos(unsigned int pos);

	void Eliminar(string clave);
	void Eliminar(const T* item);
	void Eliminar(unsigned int pos);

	string toString(string separador = "");
	void Listar(string separador = "");
	T* BuscarItem(string clave);
	T* getItem(unsigned int pos);

	int getItemPos(string clave);

	unsigned int getCA();
	unsigned int getTAM();
	T*& operator[](unsigned int pos) {
		if (pos < CA)
			return vector[pos];
		throw new exception("La posicion de la lista a la que se está intentendo acceder no existe");
	}	
};

template<class T>
unsigned int cListaT<T>::getTAM()
{
	return TAM;
}
template<class T>
unsigned int cListaT<T>::getCA()
{
	return CA;
}
template<class T>
void cListaT<T>::Redimensionalizar(int cant)
{
	if (cant <= 0)
		return;
	T** auxiliar = new T * [TAM + cant]();
	for (int i = 0; i < (TAM + cant); i++)
	{
		if (i < CA)
		{
			auxiliar[i] = vector[i];
		}
		else
			auxiliar[i] = NULL;
	}
	delete[] vector;
	vector = auxiliar;
	auxiliar = NULL;
	TAM += cant;
}


template<class T>
cListaT<T>::cListaT(unsigned int TAM)
{
	vector = new T * [TAM];
	for (unsigned int i = 0; i < TAM; i++)
	{
		vector[i] = NULL;
	}

	this->TAM = TAM;
	CA = 0;
}
template<class T>
cListaT<T>::~cListaT()
{
	if (vector != NULL)
	{
		for (unsigned int i = 0; i < CA; i++)
		{
			if (vector[i] != NULL)
				delete vector[i];
		}
		delete[] vector;
	}
}

template<class T>
string cListaT<T>::toString(string separador) {
	string cadena = "";
	for (unsigned int i = 0; i < CA; i++)
	{
		cadena += separador;
		cadena += vector[i]->toString(separador + "\t\t");
	}
	return cadena;
}
template<class T>
void cListaT<T>::Listar(string separador)
{
	cout << toString(separador);
}
template<class T>
bool cListaT<T>::AgregarItem(T* item)
{
	if (item == NULL)throw new exception("No hay objeto para agregar");
	T* i_f = BuscarItem(item->getclave());
	if (i_f != NULL)throw new exception("Ya se encuentra en la lista");

	if (CA >= TAM)
		Redimensionalizar();
	vector[CA] = item;
	CA++;
	return true;
}

template<class T>
T* cListaT<T>::Quitar(string clave) {

	unsigned int pos = getItemPos(clave);
	if (pos >= CA)return NULL;
	return QuitarenPos(pos);

}
template<class T>
T* cListaT<T>::Quitar(T* item) {
	unsigned int pos = getItemPos(item->getclave());
	if (pos >= CA)return NULL;
	return QuitarenPos(pos);
}
template<class T>
T* cListaT<T>::QuitarenPos(unsigned int pos) {
	if(pos >= CA) return NULL;
	T* aux = NULL;
	aux = vector[pos];
	CA--;
	for (unsigned int j = pos; j < CA; j++)
	{
		vector[j] = vector[j + 1];
	}
	vector[CA] = NULL;
	return aux;
}

template<class T>
void cListaT<T>::Eliminar(string clave) {

	unsigned int pos = getItemPos(clave);
	if (pos >= CA)throw new exception("Posicion invalida");
	Eliminar(pos);
}
template<class T>
void cListaT<T>::Eliminar(const T* item) {

	Eliminar(item->getclave());
}
template<class T>
void cListaT<T>::Eliminar(unsigned int pos) {
	T* aux = QuitarenPos(pos);
	if (aux != NULL)
		delete aux;
	else throw new exception("No se pudo eliminar");
}

template<class T>
T* cListaT<T>::BuscarItem(string clave)
{
	for (unsigned int i = 0; i < CA; i++)
	{
		if (vector[i]->getclave() == clave)
			return vector[i];
	}
	return NULL;
}

template<class T>
T* cListaT<T>::getItem(unsigned int pos)
{
	if (pos < CA)
		return vector[pos];
	else return NULL;
}
template<class T>
int cListaT<T>::getItemPos(string clave)
{
	for (unsigned int i = 0; i < CA; i++)
	{
		if (vector[i]->getclave() == clave)
			return i;
	}

	return -1;
}

template<class T>
cListaT<T>& operator+=(cListaT<T>& lista, T* objeto) {
	if (lista.AgregarItem(objeto))
		return lista;
	throw new exception("El objeto no se pudo agregar");
}
template<class T>
cListaT<T>& operator+(cListaT<T>& lista, T* objeto) {
	if (lista.AgregarItem(objeto))
		return lista;
	throw new exception("El objeto no se pudo agregar");
}
