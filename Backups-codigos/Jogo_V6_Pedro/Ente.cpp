#include "Ente.h"

Ente::Ente() : id(cont_id++), pFig(NULL) {}
Ente::~Ente() {};

void Ente::desenhar() {
	pGG->desenharEnte(this);
}

int Ente::cont_id(0);
GerenciadorGrafico* Ente::pGG;

void Ente::setGG(GerenciadorGrafico* pG) {
	if (!pG) { cout << "Gerenciador Gráfico não criado [Ente]" << endl; }
	if (!pGG){ pGG = pG; }
}

sf::RectangleShape Ente::getFig() {
	return *pFig;
}
