#pragma once
#include "Entidades.h"
using namespace Entidades;

namespace Personagens {
	
	class Personagem : public Entidade {
	protected:
		int num_vidas;

	public:
		Personagem();
		~Personagem();

		void salvarDataBuffer();

		virtual void executar() = 0;
		virtual void salvar() = 0;
		virtual void mover(float velx, float vely) = 0;
		
	};

	class Jogador : public Personagem {
	protected:
		int pontos;

	public:
		float vely;
		bool podePular;

	public:
		Jogador();
		~Jogador();

		void colidir();
		void executar();
		void salvar();
		void mover(float velx, float vely);
		void setPosition(int x, int y);
	};

}
