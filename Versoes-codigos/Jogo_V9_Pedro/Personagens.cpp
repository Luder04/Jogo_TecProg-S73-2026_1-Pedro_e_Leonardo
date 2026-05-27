#include "Personagens.h"

using namespace Personagens;

Personagem::Personagem() : Entidade(), num_vidas(5) {
}
Personagem::~Personagem() {
	num_vidas = 0;
}
void Personagem::operator--() {
	num_vidas--;
}
void Personagem::salvarDataBuffer() {}

const int Personagem::getVidas() {
	return num_vidas;
}

Jogador::Jogador() : Personagem(), pontos(0), vely(0), forca_andar(7), forca_pulo(16), podePular(true), tempoInvencivel(1.5f) {
	sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(50.f, 100.f));
	shape->setFillColor(sf::Color::Green);
	/*shape->setPosition(100, 200);  //posição inicial do jogador é definida em cada fase
	x = 100;
	y = 200;*/

	pFig = shape;
}
Jogador::~Jogador() {}

void Jogador::colidir() {}
void Jogador::executar() {

}
void Jogador::salvar() {}
void Jogador::mover(float velx, float vely) {
	x += velx;
	y += vely;
	pFig->move(velx, vely);
}
void Jogador::setPosition(int xNew, int yNew) {
	x = xNew;
	y = yNew;
	pFig->setPosition(xNew, yNew);
}

void Jogador::operator--() {
	if (relogioDano.getElapsedTime().asSeconds() >= tempoInvencivel) {
		if (num_vidas > 0) {
			Personagem::operator--();
			setPosition(100, 200);
		}
		relogioDano.restart();
	}
	else {
		std::cout << "Dano ignorado! Jogador invencivel por mais: " << (tempoInvencivel - relogioDano.getElapsedTime().asSeconds()) << "s" << std::endl;
	}
}

// Inimigo
Inimigo::Inimigo() : Personagem(), nivel_maldade(rand() % 100 + 1) {

}
Inimigo::~Inimigo() {
	nivel_maldade = 0;
}

void Inimigo::salvarDataBuffer() {

}

//Inimigo facil
Goomba::Goomba() : Inimigo(), raio(5), x_inic(800), x_atual(x_inic), velocidade(4) {
	num_vidas = 1;
	sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(50.f, 50.f));
	shape->setFillColor(sf::Color(0x54270DFF));
	shape->setPosition(x_inic, 200);

	pFig = shape;
}
Goomba::~Goomba() {

}

void Goomba::danificar(Jogador* p) {
	p->operator--();
}
void Goomba::executar() {
	if (x_atual < 400 && velocidade < 0) {
		velocidade = -velocidade;
	}
	if (x_atual > 1000 && velocidade > 0) {
		velocidade = -velocidade;
	}

	x_atual = pFig->getPosition().x;
	pFig->move(velocidade, 0);
}
void Goomba::salvar() {

}
void Goomba::mover(float velx, float vely) {

}