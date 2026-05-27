#include "Entidades.h"

using namespace Entidades;

Entidade::Entidade() : Ente(), x(-1), y(-1), buffer(NULL), ehObstaculo(false) {

}

Entidade::~Entidade() {
	x = -1;
	y = -1;
}

void Entidade::salvarDataBuffer() {

}

int Entidade::getx() { return x; }
int Entidade::gety() { return y; }
const bool Entidade::getObs() { return ehObstaculo; }
