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
		Jogo* pJogo;
		static const int maxRatos;
		static const int maxPlataformas;
	protected:
		Listas::ListaEntidades lista_ents;
		Gerenciadores::GerenciadorColisoes GC;
		//float gravidade;

	public:
		Fase();
		~Fase();

		void setJogo(Jogo* j);
		virtual void executar();
		virtual void limpar();
		void setJogadores(Jogador* pJog1_in/*,Jogador* pJog2_in*/);
		void salvarEntidades(std::ofstream& arquivo);

	protected:
		void criarInimFaceis();
		void criarPlataformas();
		void criarCenario();
		virtual void criarInimigos() = 0;
		virtual void criarObstaculo() = 0;

	};


	class FasePrimeira : public Fase {
	private:
		const int maxInimMedios;
		const int maxLamas;

	public:
		FasePrimeira();
		~FasePrimeira();
		void executar();

	protected:
		void criarInimigos();
		void criarObstaculo();
		void criarInimMedios();
		void criarObstMedios();
	};


	class FaseSegunda : public Fase {
	private:
		const int maxChefoes;
		const int maxLavas;
		vector<Chefao*> lista_chefoes;
		float x_projetil;
		float y_projetil;

	public:
		FaseSegunda();
		~FaseSegunda();
		void executar();
		void limpar() override;

	protected:
		void criarInimigos();
		void criarObstaculo();
		void criarChefoes();
		void criarObstDificeis();
		void criarProjeteis(Chefao* pChefe);
	};

}
