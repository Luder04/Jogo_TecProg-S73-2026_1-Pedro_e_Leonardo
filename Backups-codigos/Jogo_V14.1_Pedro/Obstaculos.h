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
	};

	class Plataforma : public Obstaculo {
	private:
		float altura;
		static int qtd_plats;
		float posy;

	public:
		Plataforma();
		~Plataforma();

		void executar();
		void salvar();
		void obstaculizar(Jogador* p);
	};
}
