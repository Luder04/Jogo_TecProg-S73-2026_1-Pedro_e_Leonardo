#pragma once

#include "Gerenciadores.h"
#include "stdio.h"
#include "Personagens.h"
#include "Fases.h"
#include "Ente.h"
#include "menu.h"

using namespace Fases;
using namespace Personagens;

class Jogo {
private:

	Jogador* pJog1;
	Jogador* pJog2;
	Gerenciadores::GerenciadorGrafico GG;
	Gerenciadores::GerenciadorColisoes GC;

    FasePrimeira fase1;
    FaseSegunda fase2;

    Menu menu_principal;

public:
	int proxFase;

public:
	Jogo();
	~Jogo();

	Jogador* getJogador1();
	void executar();

	void randomizar();
};
