#include "cArqueros.h"
#include <time.h>



cArqueros::cArqueros() :cUnidad(rand() % 11 + 20, rand() % 21 + 60) {

}



cArqueros::~cArqueros() {

}

void cArqueros::recibirDano(int& dano)
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

void cArqueros::recibirBonus(BONUS bonus)
{
    if (bonus == BONUS::PUNTERIA)
        AT += AT * 0.5;
    else if (bonus == BONUS::COMIDA)
        HP += HP * 0.5;
    actualizarPorcetajeDeVida();
}
