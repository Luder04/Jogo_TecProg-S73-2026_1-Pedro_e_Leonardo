#include "Entidades.h"
#include <fstream>

using namespace Entidades;

int Entidade::fase = 0;
Entidade::Entidade() : Ente(), x(-1), y(-1), sizex(0), sizey(0), buffer(NULL), ehObstaculo(false) {

}

Entidade::~Entidade() {
	x = -1;
	y = -1;
	sizex = 0;
	sizey = 0;
}

void Entidade::setBuffer(std::streambuf* sb) {
    buffer.rdbuf(sb);
}

void Entidade::salvarDataBuffer() {
    buffer << "Fase:" << fase << " "
        << typeid(*this).name() << " "
        << x << " "
        << y << " "
        << sizex << " "
        << sizey << "\n";
}

std::ostream& Entidade::getConteudoBuffer() {
    return buffer;
}

ostream& Entidade::getBuffer() { return buffer; }
float Entidade::getx() { return x; }
float Entidade::gety() { return y; }
float Entidade::getSizex() { return sizex; }
float Entidade::getSizey() { return sizey; }
const bool Entidade::getObs() { return ehObstaculo; }
void Entidade::setFase(int f) { fase = f; };
