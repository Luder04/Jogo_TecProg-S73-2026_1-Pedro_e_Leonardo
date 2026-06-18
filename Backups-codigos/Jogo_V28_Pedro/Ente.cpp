#include "Ente.h"
int Ente::cont_id = 0;
GerenciadorGrafico* Ente::pGG;

Ente::Ente() : id(cont_id++), pFig(NULL), pTexture(NULL), pSprite(NULL), direcao(true) {
	pTexture = new sf::Texture();
	pSprite = new sf::Sprite();
}
Ente::~Ente() {
	delete pTexture;
	delete pSprite;
};

void Ente::desenhar() {
	pGG->desenharEnte(this);
}

void Ente::setGG(GerenciadorGrafico* pG) {
	if (!pG) { cout << "Gerenciador Gráfico não criado [Ente]" << endl; }
	if (!pGG){ pGG = pG; }
}

sf::Shape& Ente::getFig() {
	return *pFig;
}

sf::Sprite& Ente::getSprite() {
	return *pSprite;
}

void Ente::setTexture(const std::string& arquivo) {
	pTexture->loadFromFile(arquivo);
	std::cout << "pTexture = " << pTexture << std::endl;
}

void Ente::setSprite() {
}

int Ente::getId() const {
    return id;
}
