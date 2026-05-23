#pragma once

#include <SFML/Graphics.hpp>
#include <optional>

class Ente;

namespace Personagens {
	class Jogador;
}
using namespace Personagens;

namespace Gerenciadores {

	class GerenciadorGrafico {
	private:
		sf::RenderWindow obj;

	public:
		GerenciadorGrafico();
		~GerenciadorGrafico();

		void desenharEnte(Ente* pE);
		void desenharFundo();
		bool isOpen();
		void atualizarEventos();
		void clear();
		void display();
	};

	class GerenciadorColisoes {
	private:
		Jogador* pJog1;

	public:
		GerenciadorColisoes();
		~GerenciadorColisoes();

		void setJog1(Jogador* pJg1);
		void tocandoChao();
	};

}
