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
		void setVidas(int n);
		virtual void operator--();

	};

	class Jogador : public Personagem {
	protected:
		int pontos;
		sf::Clock relogioDano;
		float tempoInvencivel;
		bool salvo;
		int max_vidas;

	public:
		bool podePular;
		float forca_pulo;
		float forca_andar;

	public:
		Jogador();
		~Jogador();

		void colidir();
		void executar();
		void salvar();
		void mover(float velx, float vely);
		//void setPosition(float x, float y);
		void operator--();
		void operator++();
		const int getPontos();
		void reset();
	};

	class Inimigo : public Personagem {
	protected:
		int nivel_maldade;

	public:
		Inimigo();
		~Inimigo();

		void salvarDataBuffer();
		virtual void executar() = 0;
		virtual void danificar(Jogador* pJog) = 0;
		virtual void salvar() = 0;

		float getVelx();
		void setVelx(float velx);
		float getVely();
		void setVely(float vely);
	};

	//Inimigo facil
	class Goomba : public Inimigo {
	private:
		float raio;

	public:
		Goomba();
		~Goomba();

		void danificar(Jogador* p);
		void executar();
		void salvar();
		void mover(float velx, float vely);
	};

	class Inim_Medio : public Inimigo {
	private:
		int tamanho;

	public:
		Inim_Medio();
		~Inim_Medio();

		void danificar(Jogador* p);
		void executar();
		void salvar();
		void mover(float velx, float vely);
	};

	class Chefao : public Inimigo {
	private:
		short int forca;
		bool atirar;
		int timer;

	public:
		Chefao();
		~Chefao();

		void danificar(Jogador* p);
		void executar();
		void salvar();
		void mover(float velx, float vely);
		bool getAtirar();
		void operator--();
	};
}
