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
		const int getVidas();
		virtual void operator--();

	};

	class Jogador : public Personagem {
	protected:
		int pontos;
		sf::Clock relogioDano;
		float tempoInvencivel;

	public:
		float vely;
		float velx;
		bool podePular;
		float forca_pulo;

	public:
		Jogador();
		Jogador(bool del);
		~Jogador();

		void colidir();
		void executar();
		void salvar();
		void mover(float velx, float vely);
		void setPosition(float x, float y);
		void operator--();
		void operator++();
		const int getPontos();
	};

	class Inimigo : public Personagem {
	protected:
		int nivel_maldade;
		float velx;

	public:
		Inimigo();
		~Inimigo();

		void salvarDataBuffer();
		virtual void executar() = 0;
		virtual void danificar(Jogador* p) = 0;
		virtual void salvar() = 0;

		float getVelx();
		void setVelx(float velx);
	};

	//Inimigo facil
	class Goomba : public Inimigo {
	private:
		float raio;
		

	public:
		float x_inic;
		float x_atual;

	public:
		Goomba();
		~Goomba();

		void danificar(Jogador* p);
		void executar();
		void salvar();
		void mover(float velx, float vely);
	};

}
