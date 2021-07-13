#pragma once
#include "cUnidad.h"
#include <iostream>
using namespace std;

class cMagos : public cUnidad
{

public:
	cMagos();
	~cMagos();

	//recibe del daño y lo resta del HP
    void recibirDano(int& dano);

	void recibirBonus(BONUS bonus);
};
