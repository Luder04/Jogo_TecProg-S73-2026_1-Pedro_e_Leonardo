#pragma once

#include "Entidades.h"

namespace Obstaculos {
	class Obstaculo : public Entidades::Entidade {
	protected:
		bool danoso;

	public:
		Obstaculo();
		~Obstaculo();

		void salvarDataBuffer();
		const int getVidas();
		virtual void executar() = 0;
		virtual void salvar() = 0;
		virtual void obstaculizar(Jogador* p) = 0;
		virtual void obstaculizar(Inimigo* p)=0;
	};

	class Plataforma : public Obstaculo {
	private:
		float altura;
		float largura;
		static int qtd_plats;

	public:
		Plataforma();
		~Plataforma();

		void executar();
		void salvar();
		void obstaculizar(Jogador* p);
		void obstaculizar(Inimigo* p);
		void flutuacao();
	};

	class Obst_Medio : public Obstaculo {
	private:
		float largura;
		static int qtd_obstMedio;

	public:
		Obst_Medio();
		~Obst_Medio();

		void executar();
		void salvar();
		void obstaculizar(Jogador* pJog);
		void obstaculizar(Inimigo* p);
	};


	class Obst_Dificil : public Obstaculo {
	private:
		float largura;
		static int qtd_obstDificil;
		short int danosidade;
		float temperatura;
		float dT;

	public:
		Obst_Dificil();
		~Obst_Dificil();

		void executar();
		void salvar();
		void obstaculizar(Jogador* pJog);
		void obstaculizar(Inimigo* p);
	};

}
