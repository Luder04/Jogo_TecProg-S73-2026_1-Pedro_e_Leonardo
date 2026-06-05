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

Plataforma::Plataforma() : Obstaculo(), altura(0), largura(0) {
	qtd_plats++;

    x = rand() % 70 + (190.0f * qtd_plats);
    y=200;
    if(rand()%2 == 0){
        //plataforma horizontal alta
        y += 30 + rand() % 25;
        altura = rand()%25 + 25.0f;
        largura = rand()%70 + 50.0f;
    } else{
        //plataforma vertical no chão
        altura = rand()%30 + 80.0f;
        largura = rand()%30 + 30.0f;
    }

    sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(largura, altura));
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
void Plataforma::obstaculizar(Jogador* pJog) {
    sf::FloatRect boundsObs = (this)->getFig().getGlobalBounds();
    sf::FloatRect boundsJogador = pJog->getFig().getGlobalBounds();

    if (!boundsJogador.intersects(boundsObs)) return;

    // Colisão vertical
    if (boundsJogador.left + boundsJogador.width > boundsObs.left + 5.0f &&
        boundsJogador.left < boundsObs.left + boundsObs.width - 5.0f) {

        // De cima para baixo
        if (pJog->vely <= 0.0f) {
            float topoObs = boundsObs.top + boundsObs.height;
            pJog->setPosition(pJog->getx(), topoObs);
            pJog->vely = 0;
            pJog->podePular = true;
        }
        // De baixo para cima
        else if (pJog->vely > 0.0f) {
            float fundoObs = boundsObs.top - boundsJogador.height;
            pJog->setPosition(pJog->getx(), fundoObs);
            pJog->vely = -1.0f; // Para a subida e começa a cair
        }
    }

    // Colisão lateral
    else {
        if (boundsJogador.left + boundsJogador.width / 2.0f < boundsObs.left + boundsObs.width / 2.0f) {
            pJog->setPosition(boundsObs.left - boundsJogador.width, pJog->gety());
        }
        else {
            pJog->setPosition(boundsObs.left + boundsObs.width, pJog->gety());
        }
        pJog->velx = 0.0f;
    }
}

// Obstaculo Medio
int Obst_Medio::qtd_obstMedio = 0;

Obst_Medio::Obst_Medio() : Obstaculo(), largura(0), altura(10) {
	qtd_obstMedio++;

	x = 200*qtd_obstMedio + rand()%100;
	y = 201-altura;
	largura = rand()%30 + 60.0f;

    sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(largura, altura));
	shape->setFillColor(sf::Color(0x964B00FF));

	shape->setPosition(x, y);

	pFig = shape;
}

Obst_Medio::~Obst_Medio() {
	largura = 0.0f;
	qtd_obstMedio = 0;
}

void Obst_Medio::salvar() {
	Obstaculo::salvarDataBuffer();
}
void Obst_Medio::executar() {
    //desenhar();
}
void Obst_Medio::obstaculizar(Jogador* pJog) {
    //pJog->podePular=false;
    pJog->forca_pulo=0.4*pJog->forca_pulo;
    pJog->forca_andar=0.4*pJog->forca_andar;
}



