#pragma once

#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>

class Ente;

namespace Personagens {
	class Jogador;
	class Inimigo;
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
		void desenharFundo(int corCeuHex, int corChaoHex);
		bool isOpen();
		void atualizarEventos();
		void clear();
		void display();
		sf::RenderWindow& getJanela() const;
	};

	class GerenciadorColisoes {
	private:
		Jogador* pJog1;
		std::vector<Inimigo*> LI;

	public:
		GerenciadorColisoes();
		~GerenciadorColisoes();

		void setJog1(Jogador* pJg1);
		void tocandoChao();

		void incluirInimigo(Inimigo* pI);
		int getQtdInimigosFacies();
	};

}