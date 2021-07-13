#pragma once
#include <time.h>
#include <string>
using namespace std;
class cRegistro
{
	const string usuario;
	const string contrasenia;

	time_t timeStamp; //ult acceso

	int win;
	int lose;
	int quit;

public:
	cRegistro(string usuario = "", string contrasenia = "");
	~cRegistro();
	void winner();
	void loser();
	void quitter();
	bool esContrasenia(string contrasenia) {	
		if (contrasenia == this->contrasenia)	return true;
		return false;	}
	string getclave() {
		return usuario;
	}
};
inline cRegistro::cRegistro(string usuario, string contrasenia):usuario(usuario), contrasenia(contrasenia)
{
	this->win = 0;
	this->quit = 0;
	this->lose = 0;
	this->timeStamp = time(0);	}

inline cRegistro::~cRegistro()
{
}

inline void cRegistro::winner()
{
	win++;
}

inline void cRegistro::loser()
{
	lose++;
}

inline void cRegistro::quitter()
{
	quit++;
}

