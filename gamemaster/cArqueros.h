#pragma once

#include "cUnidad.h"
#include <iostream>
using namespace std;

class cArqueros : public cUnidad
{

public:
	cArqueros();
	~cArqueros();

	//recibe del da�o y lo resta del HP
	void recibirDano(int& dano);

	void recibirBonus(BONUS bonus);

};

