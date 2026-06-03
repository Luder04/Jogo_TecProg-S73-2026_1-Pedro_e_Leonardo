#include "Principal.h"

#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

void Jogo::randomizar() {
	srand(static_cast<unsigned int>(time(NULL)));
}

Jogo::Jogo() : pJog1(NULL), pJog2(NULL), proxFase(0), fase1(), fase2(), menu_principal() {
	randomizar();
	pJog1 = new Jogador();
	GC.setJog1(pJog1);
}

Jogo::~Jogo() {
    cout << "Deletando elemento de Id: " << pJog1->getId() << " Tipo: " << typeid(*pJog1).name() << "... ";
    delete pJog1;
    cout << "Deletado" << endl;
    pJog1=NULL;
}

Jogador* Jogo::getJogador1() {
	return pJog1;
}

void Jogo::executar() {

	Ente::setGG(&GG);

	menu_principal.setJogo(this);

	fase1.setJogadores(pJog1);
	fase1.setJogo(this);

	fase2.setJogadores(pJog1);
	fase2.setJogo(this);

	menu_principal.executar();
	if (proxFase == 1) {
		fase1.executar();
		fase1.limpar();//apaga toda a lista de entidades menos o jogador
	}
	if (proxFase == 2) {
		fase2.executar();
		fase2.limpar();
	}
}
