#include "Obstaculos.h"

using namespace Obstaculos;

// Classe abstrata
Obstaculo::Obstaculo() : Entidades::Entidade(), danoso(false) {
    ehObstaculo = true;
}
Obstaculo::~Obstaculo() { danoso = false;  }
void Obstaculo::salvarDataBuffer() {}
const int Obstaculo::getVidas() { return 0; } // tratar depois

// Plataforma
Plataforma::Plataforma() : Obstaculo(), altura(rand()%31 + 20) {
    sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(300.f, altura));
	shape->setFillColor(sf::Color::White);
	shape->setPosition(500, 200);

	pFig = shape;
}

Plataforma::~Plataforma() { altura = 0; }

void Plataforma::salvar() {}
void Plataforma::executar() {}
void Plataforma::obstaculizar(Jogador* pJog) {}
