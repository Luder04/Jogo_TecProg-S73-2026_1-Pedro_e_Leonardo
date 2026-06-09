#include "Ente.h"
int Ente::cont_id = 0;
GerenciadorGrafico* Ente::pGG;

Ente::Ente() : id(cont_id++), pFig(NULL) {}
Ente::~Ente() {};

void Ente::desenhar() {
	pGG->desenharEnte(this);
}

void Ente::setGG(GerenciadorGrafico* pG) {
	if (!pG) { cout << "Gerenciador Gráfico não criado [Ente]" << endl; }
	if (!pGG){ pGG = pG; }
}

sf::Shape& Ente::getFig() {
	return *pFig;
}

int Ente::getId() const {
    return id;
}
