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
		void setSprite();
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

	class Lama : public Obstaculo {
	private:
		float largura;
		static int qtd_lamas;

	public:
		Lama();
		~Lama();

		void executar();
		void salvar();
		void obstaculizar(Jogador* pJog);
		void obstaculizar(Inimigo* p);
	};


	class Lava : public Obstaculo {
	private:
		float largura;
		static int qtd_lavas;
		short int danosidade;
		float temperatura;
		float dT;

	public:
		Lava();
		~Lava();

		void executar();
		void salvar();
		void obstaculizar(Jogador* pJog);
		void obstaculizar(Inimigo* p);
	};

}
