#pragma once

#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>
#include <list>
#include <set>

class Ente;
namespace Entidades {
	class Entidade;
	class Projetil;
}
namespace Personagens {
	class Jogador;
	class Inimigo;
}
namespace Obstaculos {
	class Obstaculo;
}
using namespace Personagens;
using namespace Obstaculos;
using namespace Entidades;

namespace Gerenciadores {

	class GerenciadorGrafico {
	private:
		sf::RenderWindow obj;

	public:
		GerenciadorGrafico();
		~GerenciadorGrafico();

		void desenharEnte(Ente* pE);
		void desenharFundo(int corCeuHex, int corChaoHex);
		void desenharVidas(Jogador* pJog);
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
		std::list<Obstaculo*> LO;
		std::set<Projetil*> LP;
	public:
		GerenciadorColisoes();
		~GerenciadorColisoes();

		bool verificarColisao(Entidade* pe1, Entidade* pe2) const;

		void setJog1(Jogador* pJg1);
		void tocandoChao();

		void tratarColisoesJogsInimigos();
		void tratarColisoesJogsObstaculo();
		void tratarColisoesInimObstaculo();

		void incluirInimigo(Inimigo* pI);
		void incluirObstaculo(Obstaculo* pO);
		void limparListas();
		void incluirProjetil(Projetil* pj);

	};

}
