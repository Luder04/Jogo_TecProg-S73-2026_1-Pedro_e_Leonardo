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
		virtual void operator--(int dano);

	};

	class Jogador : public Personagem {
	protected:
	    bool jogador2;
	    sf::Keyboard::Key botao_pular;
	    sf::Keyboard::Key botao_esquerda;
	    sf::Keyboard::Key botao_direita;
		int pontos;
		sf::Clock relogioDano;
		float tempoInvencivel;
		bool invulneravel;
		bool salvo;
		int max_vidas;

	public:
		bool podePular;
		float forca_pulo;
		float forca_andar;

	public:
		Jogador();
		Jogador(bool jog2);
		~Jogador();

		void atribuirBotoes();
		void colidir();
		void executar();
		void salvar();
		void mover(float velx, float vely);
		//void setPosition(float x, float y);
		void operator--(int dano);
		void operator++();
		const int getPontos();
		void reset();
		void colidir(Inimigo* pIn);
		void moverParaSpawn();
		void setSprite();
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
	class Rato : public Inimigo {
	private:
		float raio;

	public:
		Rato();
		~Rato();

		void danificar(Jogador* p);
		void executar();
		void salvar();
		void mover(float velx, float vely);
		void setSprite();
		void pular();
	};

	class Aguia : public Inimigo {
	private:
		int tamanho;
		float altitude;

	public:
		Aguia();
		~Aguia();

		void danificar(Jogador* p);
		void executar();
		void salvar();
		void mover(float velx, float vely);
		void baterAsas();
		void setSprite();
	};

	class Dragao : public Inimigo {
	private:
		short int forca;
		bool atirar;
		int timer;
		Projetil* pProj;

	public:
		Dragao();
		~Dragao();

		void danificar(Jogador* p);
		void executar();
		void salvar();
		void mover(float velx, float vely);
		bool getAtirar();
		void operator--(int dano);
		void baterAsas();
		void setProj(Projetil* pProj);
		void removeProj();
		bool getProj();
		void setSprite();
	};
}
