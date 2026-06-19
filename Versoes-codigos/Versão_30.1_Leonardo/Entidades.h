#pragma once

#include "Ente.h"
#include <iostream>

namespace Personagens {
	class Dragao;
}

namespace Entidades {

	class Entidade : public Ente {
	protected:
		float x;
		float y;

		float sizex;
		float sizey;

        float vely;
		float velx;

		ostream buffer;
		bool ehObstaculo;

		static const float gravidade;

	public:
		Entidade();
		virtual ~Entidade();

		virtual void executar() = 0;
		virtual void salvar() = 0;
		float getx();
		float gety();
		float getSizex();
		float getSizey();
		float getvelx();
		float getvely();
		void setvelx(float x);
		void setvely(float y);
		void setPosition(float x, float y);
		virtual const int getPontos();
		virtual bool getJogador();
		void gravitar();
		virtual const int getVidas() = 0;
		const bool getObs();
		ostream& getBuffer();
		std::ostream& getConteudoBuffer();

		virtual std::string getTipo() = 0;

	protected:
		void salvarDataBuffer();
		void setBuffer(std::streambuf* sb);

	};

    class Projetil : public Entidade{
    protected:
        bool ativo;
        Dragao* pDragao;

    public:
        Projetil();
		Projetil(Dragao* pDrag, float velx, float vely, float x, float y, float sx, float sy);
        Projetil(Dragao* pDragao);
        ~Projetil();

        void executar();
        void salvar();
        const int getVidas();
        void desativar();
		float arrasto();
		Dragao* getDragao();
		void setSprite();
		std::string getTipo();
    };
}
