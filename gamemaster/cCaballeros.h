#pragma once

#include "cUnidad.h"
#include <iostream>
using namespace std;

class cCaballeros : public cUnidad
{

public:
	cCaballeros();
    ~cCaballeros();

	//recibe del da�o y lo resta del HP
	void recibirDano(int& dano);

	void recibirBonus(BONUS bonus);
};
