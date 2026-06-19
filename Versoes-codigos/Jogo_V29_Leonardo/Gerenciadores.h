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
		//para digitar o nome do jogador para ranking:
		std::string nome_jogador;
		bool digitando;

	public:
		GerenciadorGrafico();
		~GerenciadorGrafico();

		void desenharEnte(Ente* pE);
		void desenharFundo(int corCeuHex, int corChaoHex);
		void desenharVidas(Jogador* pJog1,Jogador* pJog2);
		bool isOpen();
		void atualizarEventos();
		void clear();
		void display();
		sf::RenderWindow& getJanela() const;

		std::string getNomeJogador();
		void limparNomeJogador();
		void setDigitando(bool digitando_in);

	};

	class GerenciadorColisoes {
	private:
		Jogador* pJog1;
		Jogador* pJog2;
		std::vector<Inimigo*> LI;
		std::list<Obstaculo*> LO;
		std::set<Projetil*> LP;
    private:
        bool verificarColisao(Entidade* pe1, Entidade* pe2) const;
        void tratarColisoesJogsChao();
        void tratarColisoesJogsInimigos();
        void tratarColisoesJogsObstaculo();
        void tratarColisoesInimObstaculo();
        void tratarColisoesInimChao();
        void tratarColisoesObstaculoChao();
        void tratarColisoesProjObstaculo();
        void tratarColisoesJogsProjeteis();
        void tratarColisoesProjChao();
	public:
		GerenciadorColisoes();
		~GerenciadorColisoes();
		void setJog1(Jogador* pJg1);
		void setJog2(Jogador* pJg2);

		void executar();
		void incluirInimigo(Inimigo* pI);
		void incluirObstaculo(Obstaculo* pO);
		void incluirProjetil(Projetil* pj);
		void limparListas();

	};

}
