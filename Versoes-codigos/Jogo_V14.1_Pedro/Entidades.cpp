#include "Entidades.h"

using namespace Entidades;

Entidade::Entidade() : Ente(), x(-1), y(-1), sizex(0), sizey(0), buffer(NULL), ehObstaculo(false) {

}

Entidade::~Entidade() {
	x = -1;
	y = -1;
	sizex = 0;
	sizey = 0;
}

void Entidade::salvarDataBuffer() {

}

float Entidade::getx() { return x; }
float Entidade::gety() { return y; }
float Entidade::getSizex() { return sizex; }
float Entidade::getSizey() { return sizey; }
const bool Entidade::getObs() { return ehObstaculo; }
