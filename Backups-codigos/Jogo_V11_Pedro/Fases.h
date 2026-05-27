#pragma once

#include "Ente.h"
#include "Gerenciadores.h"
#include "Personagens.h"
#include "Listas.h"

class Jogo;

namespace Fases {

	class Fase : public Ente {
	public:
		Jogador* pJog1;
		Jogo* pJogo;
	protected:
		Listas::ListaEntidades lista_ents;
		Gerenciadores::GerenciadorColisoes GC;
		//float gravidade;

	public:
		Fase();
		~Fase();

		void setJogo(Jogo* j);
		virtual void executar();
		void setJogadores(Jogador* pJog1_in/*,Jogador* pJog2_in*/);
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

	public:
		FaseSegunda();
		~FaseSegunda();
		void executar();

	protected:
		void criarInimigos();
		void criarObstaculo();
		void criarChefoes();
		void criarObstDificeis();
		void criarProjeteis();
	};

}
