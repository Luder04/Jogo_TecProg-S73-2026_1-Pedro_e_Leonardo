#pragma once

#include "Ente.h"
#include "Gerenciadores.h"
#include "Personagens.h"
#include "Listas.h"

class Jogo;

namespace Personagens {
	class Chefao;
}

namespace Fases {

	class Fase : public Ente {
	public:
		Jogador* pJog1;
		Jogador* pJog2;
		Jogo* pJogo;
		static const int maxRatos;
		static const int maxPlataformas;
	protected:
		Listas::ListaEntidades lista_ents;
		Gerenciadores::GerenciadorColisoes GC;
		sf::Texture texCeu;
		sf::Texture texChao;
		//float gravidade;
	public:
		static sf::Sprite chao;
		static sf::Sprite ceu;

	public:
		Fase();
		~Fase();

		void setJogo(Jogo* j);
		virtual void executar();
		virtual void limpar();
		void setJogadores(Jogador* pJog1_in,Jogador* pJog2_in);
		void salvarEntidades(std::ofstream& arquivo);
		bool gameOver();

	protected:
		void criarRatos();
		void criarPlataformas();
		void criarCenario();
		virtual void criarInimigos() = 0;
		virtual void criarObstaculo() = 0;

	};


	class FasePrimeira : public Fase {
	private:
		const int maxAguias;
		const int maxLamas;

	public:
		FasePrimeira();
		~FasePrimeira();
		void executar();

	protected:
		void criarInimigos();
		void criarObstaculo();
		void criarAguias();
		void criarLamas();
	};


	class FaseSegunda : public Fase {
	private:
		const int maxChefoes;
		const int maxLavas;
		vector<Chefao*> lista_chefoes;

	public:
		FaseSegunda();
		~FaseSegunda();
		void executar();
		void limpar() override;

	protected:
		void criarInimigos();
		void criarObstaculo();
		void criarChefoes();
		void criarLavas();
		void criarProjeteis(Chefao* pChefe);
	};

}
