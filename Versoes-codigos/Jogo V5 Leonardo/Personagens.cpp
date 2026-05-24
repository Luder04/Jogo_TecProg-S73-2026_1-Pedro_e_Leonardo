#include "Personagens.h"

using namespace Personagens;

Personagem::Personagem() : Entidade(), num_vidas(5) {
}
Personagem::~Personagem() {
	num_vidas = 0;
}
void Personagem::salvarDataBuffer() {}

Jogador::Jogador() : Personagem(), pontos(0), vely(0), podePular(true) {
	sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(50.f, 100.f));
	shape->setFillColor(sf::Color::Green);
	/*shape->setPosition(100, 200);  //posição inicial do jogador é definida em cada fase
	x = 100;
	y = 200;*/

	pFig = shape;
}
Jogador::~Jogador() {}

void Jogador::colidir() {}
void Jogador::executar() {}
void Jogador::salvar() {}
void Jogador::mover(float velx, float vely) {
	x += velx;
	y += vely;
	pFig->move(velx, vely);
	desenhar();
}
void Jogador::setPosition(int xNew, int yNew) {
	x = xNew;
	y = yNew;
	pFig->setPosition(xNew, yNew);
	desenhar();
}
