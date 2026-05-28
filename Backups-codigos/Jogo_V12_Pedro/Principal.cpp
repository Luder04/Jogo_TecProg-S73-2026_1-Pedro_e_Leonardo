#include "Principal.h"
#include "Ente.h"
#include "menu.h"
#include "Fases.h"

#include <ctime>
#include <cstdlib>

using namespace Fases;

void Jogo::randomizar() {
	srand(static_cast<unsigned int>(time(NULL)));
}

Jogo::Jogo() : pJog1(NULL), pJog2(NULL), proxFase(0) {
	randomizar();
	pJog1 = new Jogador();
	GC.setJog1(pJog1);
}

Jogo::~Jogo() {
	delete pJog1;
	pJog1 = NULL;
}

Jogador* Jogo::getJogador1() {
	return pJog1;
}

void Jogo::executar() {

	Ente::setGG(&GG);

	Menu menu_principal;
	menu_principal.setJogo(this);

	FasePrimeira fase1;
	fase1.setJogadores(pJog1);
	fase1.setJogo(this);

	FaseSegunda fase2;
	fase2.setJogadores(pJog1);
	fase2.setJogo(this);

	menu_principal.executar();
	if (proxFase == 1) {
		fase1.executar();

	}
	if (proxFase == 2) {
		fase2.executar();
	}
}