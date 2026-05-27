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
		virtual void executar() = 0;
		virtual void salvar() = 0;
		virtual void obstaculizar(Jogador* p) = 0;
	};

	class Plataforma : public Obstaculo {
	private:
		int altura;

	public:
		Plataforma();
		~Plataforma();

		void executar();
		void salvar();
		void obstaculizar(Jogador* p);
	};
}
