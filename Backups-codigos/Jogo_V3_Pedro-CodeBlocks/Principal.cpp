#include "Principal.h"
#include "Ente.h"

Jogo::Jogo() : pJog1(NULL), pJog2(NULL) {
	pJog1 = new Jogador();
	GC.setJog1(pJog1);
}

Jogo::~Jogo() {
	delete pJog1;
	pJog1 = NULL;
}

void Jogo::executar() {
	Ente::setGG(&GG);

	while (GG.isOpen()) {
		GG.atualizarEventos();
		GG.clear();
		GG.desenharFundo();
		GC.tocandoChao();

		if (!pJog1->podePular) {
			pJog1->mover(0, pJog1->vely);
			pJog1->vely -= 0.1;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && pJog1->podePular == true) {
			pJog1->vely = 5;
			pJog1->podePular = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			pJog1->mover(5, 0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			pJog1->mover(-5, 0);
		}
		else {
			pJog1->desenhar();
		}

		GG.display();
	}
}