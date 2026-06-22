#pragma once
#include "Gerenciadores.h"
using namespace Gerenciadores;

#include <iostream>
using namespace std;

class Ente {
private:
	static int cont_id;

protected:
	int id;
	static GerenciadorGrafico* pGG;
	sf::Shape* pFig;
	sf::Texture* pTexture;
	sf::Sprite* pSprite;

public:
	bool direcao;

public:
	Ente();
	virtual ~Ente();

	virtual void executar() = 0;
	void desenhar();
	static void setGG(GerenciadorGrafico* pG);
	sf::Shape& getFig();
    sf::Sprite& getSprite();
	void setTexture(const std::string& arquivo);
	virtual void setSprite();
	int getId() const;
};
