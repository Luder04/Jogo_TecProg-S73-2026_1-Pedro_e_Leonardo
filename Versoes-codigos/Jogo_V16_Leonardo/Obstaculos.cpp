#include "Obstaculos.h"
#include "Personagens.h"

using namespace Personagens;
using namespace Obstaculos;

// Classe abstrata
Obstaculo::Obstaculo() : Entidades::Entidade(), danoso(false) {
    ehObstaculo = true;
}
Obstaculo::~Obstaculo() { danoso = false;  }
void Obstaculo::salvarDataBuffer() {
	Entidade::salvarDataBuffer();
}
const int Obstaculo::getVidas() { return 0; } // tratar depois

// Plataforma
int Plataforma::qtd_plats = 0;

Plataforma::Plataforma() : Obstaculo(), altura(rand()%50 + 25.0f) {
	qtd_plats++;

	x = rand() % 50 + (250.0f * qtd_plats);
	y = 200;
	if(rand()%2 == 0){
        y += 50 + rand()%50; //Plataforma voadora ou não
	}

	sizex = rand() % 100 + 100.0f;
	sizey = altura;

    sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(sizex, altura));
	shape->setFillColor(sf::Color::White);

	shape->setPosition(x, y);

	pFig = shape;
}

Plataforma::~Plataforma() {
	altura = 0.0f;
	qtd_plats = 0;
}

void Plataforma::salvar() {
	Obstaculo::salvarDataBuffer();
}
void Plataforma::executar() {
    //desenhar();
}
void Plataforma::obstaculizar(Jogador* pJog) {}
