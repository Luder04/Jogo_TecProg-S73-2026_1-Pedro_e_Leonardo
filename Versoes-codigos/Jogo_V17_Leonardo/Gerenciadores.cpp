#include "Gerenciadores.h"
#include <iostream>
#include "Ente.h"
#include "Entidades.h"
#include "Personagens.h"
#include "Obstaculos.h"

using namespace std;
using namespace Gerenciadores;
using namespace Obstaculos;

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
void GerenciadorGrafico::desenharFundo(int corCeuHex, int corChaoHex) {
	sf::RectangleShape ceu;
	ceu.setFillColor(sf::Color(corCeuHex));
	ceu.setPosition(0, 200);
	ceu.setSize({ 1280, 520 });
	obj.draw(ceu);

	sf::RectangleShape chao;
	chao.setFillColor(sf::Color(corChaoHex));
	chao.setPosition(0, 0);
	chao.setSize({ 1280, 200 });
	obj.draw(chao);
}
void GerenciadorGrafico::desenharVidas(Jogador* pJog) {
	sf::Font font;
	if (!font.loadFromFile("BAUHS93.TTF"))
		return;
	std::string textoVidas = "Vidas: " + std::to_string(pJog->getVidas());
	sf::Text vidas(textoVidas, font);
	vidas.setCharacterSize(50);
	vidas.setScale({ 1.f, -1.f });
	vidas.setPosition({ 1000, 700 });

	std::string textoPontos = "Pontos: " + std::to_string(pJog->getPontos());
	sf::Text pontos(textoPontos, font);
	pontos.setCharacterSize(50);
	pontos.setScale({ 1.f, -1.f });
	pontos.setPosition({ 700, 700 });

	obj.draw(vidas);
	obj.draw(pontos);
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
sf::RenderWindow& GerenciadorGrafico::getJanela() const {
	return const_cast<sf::RenderWindow&>(obj);
}

//COLISOES
GerenciadorColisoes::GerenciadorColisoes() : pJog1(NULL), LI(), LO() {

}
GerenciadorColisoes::~GerenciadorColisoes() {}
void GerenciadorColisoes::setJog1(Jogador* pJg1) {
	if (pJg1) {
		pJog1 = pJg1;
	}
}
void GerenciadorColisoes::tocandoChao() {
	if (pJog1->gety() + pJog1->getvely() < 200) {
		pJog1->podePular = true;
		pJog1->setvely(0);
		pJog1->setPosition(pJog1->getx(), 200);
	}
}

bool GerenciadorColisoes::verificarColisao(Entidade* pe1, Entidade* pe2) const {
	if (pe1 == nullptr || pe2 == nullptr) return false;
    sf::FloatRect bounds1 = pe1->getFig().getGlobalBounds();
    sf::FloatRect bounds2 = pe2->getFig().getGlobalBounds();
	if (pe1 == static_cast<Entidade*>(pJog1)) {
		bounds1.top += pJog1->getvely();
	}
	else if (pe2 == static_cast<Entidade*>(pJog1)) {
		bounds2.top += pJog1->getvely();
	}

    return bounds1.intersects(bounds2);
}

void GerenciadorColisoes::incluirInimigo(Inimigo *pI) {
	if (pI) {
		LI.push_back(pI);
	}
}

void GerenciadorColisoes::incluirObstaculo(Obstaculo *pO) {
	if (pO) {
		LO.push_back(pO);
	}
}

void GerenciadorColisoes::limparListas(){
    LI.clear();
    LO.clear();
}

void GerenciadorColisoes::tratarColisoesJogsInimigos() {
	int i;

	for (i = 0; i < (int)LI.size(); i++) {
		if (LI[i] != NULL) {
			if (verificarColisao(static_cast<Entidade*>(pJog1), static_cast<Entidade*>(LI[i]))) {
				sf::FloatRect boundsInimigo = LI[i]->getFig().getGlobalBounds();
				sf::FloatRect boundsJogador = pJog1->getFig().getGlobalBounds();

				sf::FloatRect proxPos_Y = boundsJogador;
				proxPos_Y.top += pJog1->getvely();

				if (proxPos_Y.intersects(boundsInimigo)) {
                    if(typeid(*LI[i]) == typeid(Goomba)){ //apenas goombas passam pelo check de colisao por cima (deve ter solução mais elegante que essa)
                        float cabecaInimigo = boundsInimigo.top + boundsInimigo.height;

                        if (pJog1->getvely() <= 0.0f && boundsJogador.top >= cabecaInimigo) {
                            //colisão por cima
                            LI[i]->operator--();
                            LI.erase(LI.begin() + i);
                            i--;

                            pJog1->setPosition(pJog1->getx(), cabecaInimigo);
                            pJog1->setvely(10.0); // Impulso para cima
                            pJog1->operator++();
                        }
                        else {
                            // Colisão lateral
                            LI[i]->danificar(pJog1);
                        }
                    } else {
                        LI[i]->danificar(pJog1);
                    }
                }
			}

		}
	}
}

void GerenciadorColisoes::tratarColisoesJogsObstaculo() {
    std::list<Obstaculo*>::iterator it;

	for (it = LO.begin(); it != LO.end(); it++) {
        Obstaculo* pObs = *it;

		if (pObs != NULL) {
			if (verificarColisao(static_cast<Entidade*>(pJog1), static_cast<Entidade*>(pObs))) {
                pObs->obstaculizar(pJog1);
			}
		}
	}
}

void GerenciadorColisoes::tratarColisoesInimObstaculo() {
	std::list<Obstaculo*>::iterator it;

	for (it = LO.begin(); it != LO.end(); it++) {
		Obstaculo* pObs = *it;
		if (pObs != NULL) {
            if(typeid(*pObs) == typeid(Plataforma)){ //inimigos só interagem com plataformas (deve ter solução mais elegante que essa)
                int i;

                for (i = 0; i < (int)LI.size(); i++) {
                    if (LI[i] != NULL) {

                        if (verificarColisao(static_cast<Entidade*>(pObs), static_cast<Entidade*>(LI[i]))) {
                            pObs->obstaculizarInimigo(LI[i]);
                        }

                    }
                }
            }
		}
	}
}

void GerenciadorColisoes::incluirProjetil(Projetil* pj) {
    LP.insert(pj);
}
