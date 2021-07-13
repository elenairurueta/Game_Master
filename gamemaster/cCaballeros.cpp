#include "cCaballeros.h"


cCaballeros::cCaballeros():cUnidad(rand() % 11 + 30, rand() % 21 + 80) {

}



cCaballeros::~cCaballeros() {

}


void cCaballeros::recibirDano(int& dano)
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

void cCaballeros::recibirBonus(BONUS bonus)
{
    if (bonus == BONUS::ESTRATEGIA)
        AT += AT * 0.3;
    else if (bonus == BONUS::COMIDA)
        HP += HP * 0.5;
    actualizarPorcetajeDeVida();
}
