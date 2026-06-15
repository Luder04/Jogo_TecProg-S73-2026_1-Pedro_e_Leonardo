#include "Gerenciadores.h"
#include <iostream>
#include "Ente.h"
#include "Entidades.h"
#include "Personagens.h"
#include "Obstaculos.h"
#include "Fases.h"

using namespace std;
using namespace Gerenciadores;
using namespace Obstaculos;

//GRAFICO
GerenciadorGrafico::GerenciadorGrafico() : obj(sf::VideoMode({ 1280, 720 }), "Jogo"), digitando(false), nome_jogador("") {
	sf::View view;
	view.setCenter(sf::Vector2f(640.f, 360.f));
	view.setSize(sf::Vector2f(1280.f, -720.f));
	obj.setView(view);

	obj.setFramerateLimit(60);
}
GerenciadorGrafico::~GerenciadorGrafico() { obj.close(); }
void GerenciadorGrafico::desenharEnte(Ente* pE) {
	pE->setSprite();

	obj.draw(pE->getFig()); //Remover para tirar retângulo da hitbox do desenho
	obj.draw(pE->getSprite());
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

	obj.draw(Fases::Fase::ceu);
	obj.draw(Fases::Fase::chao);
}
void GerenciadorGrafico::desenharVidas(Jogador* pJog1,Jogador* pJog2) {
	sf::Font font;
	if (!font.loadFromFile("BAUHS93.TTF"))
		return;

    std::string textoVidas;
	if(pJog2==NULL){
        textoVidas = "Vidas: " + std::to_string(pJog1->getVidas());
	} else {
        textoVidas = "Vidas: " + std::to_string(pJog1->getVidas()) + " / " + std::to_string(pJog2->getVidas());
	}


	sf::Text vidas(textoVidas, font);
	vidas.setCharacterSize(45);
	vidas.setScale({ 1.f, -1.f });
	vidas.setPosition({ 1000, 720 });

	std::string textoPontos;
    if(pJog2==NULL){
        textoPontos = "Pontos: " + std::to_string(pJog1->getPontos());
    } else {
        textoPontos = "Pontos: " + std::to_string(pJog1->getPontos()) + " / " + std::to_string(pJog2->getPontos());
    }
	sf::Text pontos(textoPontos, font);
	pontos.setCharacterSize(45);
	pontos.setScale({ 1.f, -1.f });
	pontos.setPosition({ 700, 720 });

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
		if (evento.type == sf::Event::TextEntered && digitando) {
            // backspace para apagar a última letra
            if (evento.text.unicode == 8) {
                if (!nome_jogador.empty()) {
                    nome_jogador.pop_back();
                }
            } else if (evento.text.unicode < 128) {
                if (nome_jogador.size() < 15) { //tamanho máximo de 15 caracteres
                    nome_jogador += static_cast<char>(evento.text.unicode);
                }
            }
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
std::string GerenciadorGrafico::getNomeJogador(){
    return nome_jogador;
}
void GerenciadorGrafico::limparNomeJogador(){
    nome_jogador = "";
}
void GerenciadorGrafico::setDigitando(bool digitando_in){
    digitando=digitando_in;
}

//COLISOES
GerenciadorColisoes::GerenciadorColisoes() : pJog1(NULL), pJog2(NULL), LI(), LO() {

}
GerenciadorColisoes::~GerenciadorColisoes() {}
void GerenciadorColisoes::setJog1(Jogador* pJg1) {
	if (pJg1) {
		pJog1 = pJg1;
	}
}
void GerenciadorColisoes::setJog2(Jogador* pJg2) {
	if (pJg2) {
		pJog2 = pJg2;
	}
}
void GerenciadorColisoes::tocandoChao() {
    if(pJog1!=NULL){
        if (pJog1->gety() + pJog1->getvely() < 200) {
            pJog1->podePular = true;
            pJog1->setvely(0);
            pJog1->setPosition(pJog1->getx(), 200);
        }
    }
    if(pJog2!=NULL){
        if (pJog2->gety() + pJog2->getvely() < 200) {
            pJog2->podePular = true;
            pJog2->setvely(0);
            pJog2->setPosition(pJog2->getx(), 200);
        }
    }
}

bool GerenciadorColisoes::verificarColisao(Entidade* pe1, Entidade* pe2) const {
	if (pe1 == nullptr || pe2 == nullptr) return false;
    sf::FloatRect bounds1 = pe1->getFig().getGlobalBounds();
    sf::FloatRect bounds2 = pe2->getFig().getGlobalBounds();
    if(pJog1!=NULL){
        if (pe1 == static_cast<Entidade*>(pJog1)) {
            bounds1.top += pJog1->getvely();
        }
        else if (pe2 == static_cast<Entidade*>(pJog1)) {
            bounds2.top += pJog1->getvely();
        }
    }
    if(pJog2!=NULL){
        if (pe1 == static_cast<Entidade*>(pJog2)) {
            bounds1.top += pJog2->getvely();
        }
        else if (pe2 == static_cast<Entidade*>(pJog2)) {
            bounds2.top += pJog2->getvely();
        }
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
    LP.clear();
}

void GerenciadorColisoes::executar(){
    tocandoChao();

    tratarColisoesJogsInimigos();

    tratarColisoesJogsObstaculo();

    tratarColisoesInimObstaculo();

    //printf("b");
    tratarColisoesProjObstaculo();
    //printf("c");
    tratarColisoesJogsProjeteis();
    //printf("d");
    tratarColisoesProjChao();
    //printf("e");
}

void GerenciadorColisoes::tratarColisoesJogsInimigos() {
	int i;

	for (i = 0; i < (int)LI.size(); i++) {
		if (LI[i] != NULL) {
            int aux=0;
            if(pJog1!=NULL){
                if (verificarColisao(static_cast<Entidade*>(pJog1), static_cast<Entidade*>(LI[i]))) {
                    sf::FloatRect boundsInimigo = LI[i]->getFig().getGlobalBounds();
                    sf::FloatRect boundsJogador = pJog1->getFig().getGlobalBounds();

                    sf::FloatRect proxPos_Y = boundsJogador;
                    proxPos_Y.top += pJog1->getvely();

                    if (proxPos_Y.intersects(boundsInimigo)) {
                        pJog1->colidir(LI[i]);
                        if(LI[i]->getVidas()<1){ //se a colisão eliminou o inimigo, remove ele da lista
                            LI.erase(LI.begin() + i);
                            i--;
                            aux=1; //se mata o inimigo, o jogador 2 não precisa checar colisão
                        }
                    }
                }
            }
            if(pJog2!=NULL && aux==0){
                if (verificarColisao(static_cast<Entidade*>(pJog2), static_cast<Entidade*>(LI[i]))) {
                    sf::FloatRect boundsInimigo = LI[i]->getFig().getGlobalBounds();
                    sf::FloatRect boundsJogador = pJog2->getFig().getGlobalBounds();

                    sf::FloatRect proxPos_Y = boundsJogador;
                    proxPos_Y.top += pJog2->getvely();

                    if (proxPos_Y.intersects(boundsInimigo)) {
                        pJog2->colidir(LI[i]);
                        if(LI[i]->getVidas()<1){ //se a colisão eliminou o inimigo, remove ele da lista
                            LI.erase(LI.begin() + i);
                            i--;
                        }
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

            if(pJog1!=NULL){
                if (verificarColisao(static_cast<Entidade*>(pJog1), static_cast<Entidade*>(pObs))) {
                    pObs->obstaculizar(pJog1);
                }
            }
            if(pJog2!=NULL){
                if (verificarColisao(static_cast<Entidade*>(pJog2), static_cast<Entidade*>(pObs))) {
                    pObs->obstaculizar(pJog2);
                }
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
                            pObs->obstaculizar(LI[i]);
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

void GerenciadorColisoes::tratarColisoesJogsProjeteis(){
    if (!LP.empty()) {
        std::set<Projetil*>::iterator it2;

        for (it2 = LP.begin(); it2 != LP.end(); ) {
            Projetil* pProj = *it2;
            if (pProj != NULL) {

                if(pJog1!=NULL){
                    if (verificarColisao(static_cast<Entidade*>(pJog1), static_cast<Entidade*>(pProj))) {
                        pProj->getChefao()->danificar(pJog1);
                        pProj->desativar();
                        it2=LP.erase(it2);
                    } else if(pJog2!=NULL){
                        if (verificarColisao(static_cast<Entidade*>(pJog2), static_cast<Entidade*>(pProj))) {
                            pProj->getChefao()->danificar(pJog2);
                            pProj->desativar();
                            it2=LP.erase(it2);
                        } else {
                            it2++;
                        }
                    } else {
                        it2++;
                    }
                }
            }
        }
    }
}

void GerenciadorColisoes::tratarColisoesProjChao(){
    if (!LP.empty()) {
        std::set<Projetil*>::iterator it2;

        for (it2 = LP.begin(); it2 != LP.end(); ) {
            Projetil* pProj = *it2;
            if (pProj->gety() + pProj->getvely() <= 200 ) {
                pProj->desativar();
                it2=LP.erase(it2);
            } else {
                it2++;
            }
        }
    }
}

void GerenciadorColisoes::tratarColisoesProjObstaculo(){
    if (!LP.empty()) {
        std::list<Obstaculo*>::iterator it;
        std::set<Projetil*>::iterator it2;

        for (it = LO.begin(); it != LO.end(); it++) {
            Obstaculo* pObs = *it;
            if (pObs != NULL) {
                if(typeid(*pObs) == typeid(Plataforma)){
                    for (it2 = LP.begin(); it2 != LP.end(); ) {
                        Projetil* pProj = *it2;
                        if (verificarColisao(static_cast<Entidade*>(pObs), static_cast<Entidade*>(pProj))) {
                                pProj->desativar();
                                it2=LP.erase(it2);
                        } else {
                            it2++;
                        }
                    }
                }
            }
        }
    }
}
