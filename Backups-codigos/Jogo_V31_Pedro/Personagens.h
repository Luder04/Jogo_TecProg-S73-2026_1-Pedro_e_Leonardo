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
		virtual const int getPontos();
		virtual bool getJogador();
		void setVidas(int n);
		virtual void operator--(int dano);
		virtual std::string getTipo() = 0;

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
		Jogador(int pontos, int num_vid, bool jog2, float x, float y, float sx, float sy);
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
		bool getJogador();
		void reset();
		void colidir(Inimigo* pIn);
		void moverParaSpawn();
		void setSprite();
		std::string getTipo();
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

		virtual std::string getTipo() = 0;
	};

	//Inimigo facil
	class Rato : public Inimigo {
	private:
		float raio;

	public:
		Rato();
		Rato(float x, float y, float sx, float sy);
		~Rato();

		void danificar(Jogador* p);
		void executar();
		void salvar();
		void mover(float velx, float vely);
		void setSprite();
		void pular();
		std::string getTipo();
	};

	class Aguia : public Inimigo {
	private:
		int tamanho;
		float altitude;

	public:
		Aguia();
		Aguia(float alt, float x, float y, float sx, float sy);
		~Aguia();

		void danificar(Jogador* p);
		void executar();
		void salvar();
		void mover(float velx, float vely);
		void baterAsas();
		void setSprite();
		std::string getTipo();
	};

	class Dragao : public Inimigo {
	private:
		short int forca;
		bool atirar;
		int timer;
		Projetil* pProj;

	public:
		Dragao();
		Dragao(int id, int vidas, short int nforca, float x, float y, float sx, float sy);
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
		std::string getTipo();
	};
}
