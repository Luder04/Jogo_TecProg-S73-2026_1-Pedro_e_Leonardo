#include "Gerenciadores.h"
#include <iostream>
#include "Ente.h"
#include "Personagens.h"

using namespace std;
using namespace Gerenciadores;

//GRAFICO
GerenciadorGrafico::GerenciadorGrafico() : obj(sf::VideoMode({ 1280, 720 }), "Jogo") {
	sf::View view;
	view.setCenter(sf::Vector2f(640.f, 360.f));
	view.setSize(sf::Vector2f(1280.f, -720.f));
	obj.setView(view);

	obj.setFramerateLimit(60);
}
GerenciadorGrafico::~GerenciadorGrafico() { obj.close(); }
void GerenciadorGrafico::desenharEnte(Ente* pE) {
	obj.draw(pE->getFig());
}
void GerenciadorGrafico::desenharFundo() {
	sf::RectangleShape ceu;
	ceu.setFillColor(sf::Color(104, 173, 237));
	ceu.setPosition(0, 200);
	ceu.setSize({1280, 520});
	obj.draw(ceu);

	sf::RectangleShape chao;
	chao.setFillColor(sf::Color(143, 123, 93));
	chao.setPosition(0, 0);
	chao.setSize({ 1280, 200 });
	obj.draw(chao);
}
bool GerenciadorGrafico::isOpen() {
	return obj.isOpen();
}
void GerenciadorGrafico::atualizarEventos() {
	sf::Event evento;
	while (obj.pollEvent(evento)) {
		if (evento.type == sf::Event::Closed) {
			obj.close();
		}
	}
}
void GerenciadorGrafico::clear() {
	obj.clear();
}
void GerenciadorGrafico::display() {
	obj.display();
}
sf::RenderWindow& GerenciadorGrafico::getJanela() const{
    return const_cast<sf::RenderWindow&>(obj);
}

//COLISOES
GerenciadorColisoes::GerenciadorColisoes() : pJog1(NULL) {

}
GerenciadorColisoes::~GerenciadorColisoes() {}
void GerenciadorColisoes::setJog1(Jogador* pJg1) {
	if (pJg1) {
		pJog1 = pJg1;
	}
}
void GerenciadorColisoes::tocandoChao() {
	if (pJog1->gety() + pJog1->vely < 200 - 50) {
		pJog1->podePular = true;
		pJog1->vely = 0;
		pJog1->setPosition(pJog1->getx(), 200);
	}
}
