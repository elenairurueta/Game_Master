#pragma once
#include "Archivo.h"

template<class T>
void Archivo::escribirArchivoDat(cListaT<T>* lista)
{
	FILE* fp;
	/*char file[nombre.length() + ".dat"] = nombre;*/
	fp = fopen((nombre + ".dat").c_str(), "w+b");

	//fp = fopen(file, (ARCHIVO::DAT == tipo)? "w+d" : "w+t");
	if (fp == NULL)
		throw new exception("FILE_ERROR");

	fwrite(lista->vector, sizeof(T*), lista->CA, fp);
	fclose(fp);
	Log();
}

template<class T>
cListaT<T>* Archivo::leerArchivoDat()
{
	FILE* fp;
	fp = fopen((nombre + ".dat").c_str(), "r+b");
	if (fp == NULL)
		throw new exception("FILE_ERROR");

	cListaT<T>* lista = new cListaT<T>();

	T* elemento = NULL;
	do {
		elemento = new T();
		fread(elemento, sizeof(T), 1, fp);
		try {
			lista->AgregarItem(elemento);
		}
		catch (exception* ex) {
			cout << ex->what() << endl; //TODO: SACAR
		}
		catch (...) {
			break;
		}
	} while (!feof(fp));

	fclose(fp);
	return lista;
}



 Archivo::Archivo(string nombre, ARCHIVO tipo, time_t timeStamp):nombre(nombre), tipo(tipo)
 {
	 this->timeStamp = timeStamp;
 }

 Archivo::~Archivo()
 {
 }

 void Archivo::Log()
 {
	 this->timeStamp = time(0);
 }

string Archivo::leerArchivoTxt()
{
	/*FILE* fp;
	fp = fopen(nombre + (ARCHIVO::DAT == tipo) ? ".dat" : ".txt", (ARCHIVO::DAT == tipo) ? "w+d" : "w+t");
	if (fp == NULL)
		throw new exception("FILE_ERROR");

	fseek(fp, 0, SEEK_END);
	long int idx = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	int cant = idx / sizeof(char);
	char cadena[cant];

	for(int i=0; i< ; i++)
		fread(cadena + i, sizeof(char), 1, fp);
	string lista* =
	fclose(fp);
	return cadena;*/

	string cadena = "";
	string line = "";

	ifstream myfile;
	myfile.open(nombre + ".txt");
	if (myfile.fail())
		throw new exception("FILE_ERROR");

	while (!myfile.eof()) {
		getline(myfile, line);
		cadena += line + "\n";
	}
	myfile.close();
	cout << cadena << endl; //TODO sacar
	return cadena;
}