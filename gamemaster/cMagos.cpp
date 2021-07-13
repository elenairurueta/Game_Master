#include "cMagos.h"


cMagos::cMagos() :cUnidad(rand() % 11 + 10, rand() % 21 + 40) {

}



cMagos::~cMagos() {

}


void cMagos::recibirDano(int& dano)
{
    HP -= dano;
    actualizarPorcetajeDeVida();
    if (HP <= 0) {
        dano = - HP; //acá HP sería el daño sobrante
        if (verificarBaja()) {
            throw new exception("RIP arquero");
        }
    }
    else
        dano = 0;

}

void cMagos::recibirBonus(BONUS bonus)
{
    if (bonus == BONUS::INTELIGENCIA)
        AT += AT * 0.2;
    else if (bonus == BONUS::COMIDA)
        HP += HP * 0.5;
    actualizarPorcetajeDeVida();
}
