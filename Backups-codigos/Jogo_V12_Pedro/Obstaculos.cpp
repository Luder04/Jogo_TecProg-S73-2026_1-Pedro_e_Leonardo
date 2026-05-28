#include "Obstaculos.h"
#include "Personagens.h"

using namespace Personagens;
using namespace Obstaculos;

// Classe abstrata
Obstaculo::Obstaculo() : Entidades::Entidade(), danoso(false) {
    ehObstaculo = true;
}
Obstaculo::~Obstaculo() { danoso = false;  }
void Obstaculo::salvarDataBuffer() {}
const int Obstaculo::getVidas() { return 0; } // tratar depois

// Plataforma
int Plataforma::qtd_plats = 0;

Plataforma::Plataforma() : Obstaculo(), altura(rand()%1 + 200.0f) {
	qtd_plats++;

	if (qtd_plats > 1) {
		altura += 25 * qtd_plats;
	}
	

	sizex = rand() % 100 + 100.0f;
	sizey = 25.0f;
    sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(sizex, sizey));
	shape->setFillColor(sf::Color::White);

	shape->setPosition(rand() % 50 + (250.0f * qtd_plats), altura);

	pFig = shape;
}

Plataforma::~Plataforma() { altura = 0.0f; }

void Plataforma::salvar() {}
void Plataforma::executar() {}
void Plataforma::obstaculizar(Jogador* pJog) {}
