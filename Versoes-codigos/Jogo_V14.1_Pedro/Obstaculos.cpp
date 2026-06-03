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

Plataforma::Plataforma() : Obstaculo(), altura(rand()%50 + 25.0f), posy(200) {
	qtd_plats++;

	if(rand()%2 == 0){
        posy += 50 + rand()%50; //Plataforma voadora ou não
	}

	sizex = rand() % 100 + 100.0f;
    sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(sizex, altura));
	shape->setFillColor(sf::Color::White);

	shape->setPosition(rand() % 50 + (250.0f * qtd_plats), posy);

	pFig = shape;
}

Plataforma::~Plataforma() { altura = 0.0f; }

void Plataforma::salvar() {}
void Plataforma::executar() { desenhar(); }
void Plataforma::obstaculizar(Jogador* pJog) {}
