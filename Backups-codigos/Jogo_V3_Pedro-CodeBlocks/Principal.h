#pragma once

#include "Gerenciadores.h"
#include "stdio.h"
#include "Personagens.h"

using namespace Personagens;

class Jogo {
private:

	Jogador* pJog1;
	Jogador* pJog2;
	Gerenciadores::GerenciadorGrafico GG;
	Gerenciadores::GerenciadorColisoes GC;

public:
	Jogo();
	~Jogo();

	void executar();
};