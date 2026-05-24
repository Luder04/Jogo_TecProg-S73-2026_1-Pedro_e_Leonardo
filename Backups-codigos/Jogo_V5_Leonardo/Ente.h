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
	sf::RectangleShape* pFig;

public:
	Ente();
	virtual ~Ente();

	virtual void executar() = 0;
	void desenhar();

	static void setGG(GerenciadorGrafico* pG);
	sf::RectangleShape getFig();

};
