#pragma once
#include <string>
using namespace std;
#define rondasMAX 10
#define cantLATINOAMERICA 11

enum class JUGADORES
{
	JUGADOR1, JUGADOR2, JUGADOR3, JUGADOR4, JUGADOR5, JUGADOR6, NINGUNO
};

enum class ROLES
{
	ATACADO, ATACANTE
};

enum class TIPOTROPA
{
	ARQUEROS, CABALLEROS, MAGOS
};

enum class MENU
{
	ATACAR = 1, PASAR, ABANDONAR
};

enum class ARCHIVO
{
	TXT, DAT
};

enum class MAPA
{
	LATINOAMERICA, AMERICA, EUROPA
};

enum class BONUS 
{
	COMIDA, INTELIGENCIA, ESTRATEGIA, PUNTERIA
};

