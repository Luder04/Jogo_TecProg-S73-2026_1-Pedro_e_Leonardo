#include "Personagens.h"

using namespace Personagens;

Personagem::Personagem() : Entidade(), num_vidas(1) {
}
Personagem::~Personagem() {
	num_vidas = 0;
}
void Personagem::operator--() {
	num_vidas--;
}
void Personagem::salvarDataBuffer() {
	Entidade::salvarDataBuffer();
}

const int Personagem::getVidas() {
	return num_vidas;
}
void Personagem::setVidas(int n){
    num_vidas=n;
}
Jogador::Jogador() : Personagem(), pontos(0), vely(0), velx(0), forca_pulo(16), podePular(true), tempoInvencivel(0.2f), salvo(false) {
	sizex = 25.0f;
	sizey = 50.0f;

	sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(sizex, sizey));
	shape->setFillColor(sf::Color::Green);

	pFig = shape;
}

Jogador::~Jogador() {}

void Jogador::colidir() {}
void Jogador::executar() {
	float forca_andar = 5;
	float gravidade = 1;
	vely -= gravidade;
	velx = 0;


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && podePular == true) {
        vely = forca_pulo;
        podePular = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		velx = forca_andar;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		velx = -forca_andar;
    }

	mover(velx, vely);
	//desenhar();
}
void Jogador::salvar() {
	if (!salvo) {
		salvo = true;
		Personagem::salvarDataBuffer();
	}
}
void Jogador::mover(float velx, float vely) {
	x += velx;
	y += vely;
	pFig->move(velx, vely);
}
void Jogador::setPosition(float xNew, float yNew) {
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

void Jogador::operator++() {
	pontos++;
}

const int Jogador::getPontos() {
	return pontos;
}

// Inimigo
Inimigo::Inimigo() : Personagem(), nivel_maldade(rand() % 100 + 1), velx(3) {

}
Inimigo::~Inimigo() {
	nivel_maldade = 0;
}

void Inimigo::salvarDataBuffer() {
	Personagem::salvarDataBuffer();
}

float Inimigo::getVelx() {
	return velx;
}

void Inimigo::setVelx(float newVelx) {
	velx = newVelx;
}

//Inimigo facil
Goomba::Goomba() : Inimigo(), raio(5) {
	sizex = 25.0f;
	sizey = 25.0f;
	x = 1100;
	y = 200;
	num_vidas = 1;
	sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(sizex, sizey));
	shape->setFillColor(sf::Color(0x54270DFF));
	shape->setPosition(x, y);

	pFig = shape;
}
Goomba::~Goomba() {

}

void Goomba::danificar(Jogador* p) {
	p->operator--();
}
void Goomba::executar() {
	if (x < 400 && velx < 0) {
		velx = -velx;
	}
	if (x > 1000 && velx > 0) {
		velx = -velx;
	}

	x = pFig->getPosition().x;
	pFig->move(velx, 0);

	if (num_vidas > 0) {
		//desenhar();
	}
}
void Goomba::salvar() {
	Inimigo::salvarDataBuffer();
}
void Goomba::mover(float velx, float vely) {

}
