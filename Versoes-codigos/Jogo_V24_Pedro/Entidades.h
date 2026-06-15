#pragma once

#include "Ente.h"
#include <iostream>

namespace Personagens {
	class Chefao;
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

		static int fase;
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
		void gravitar();
		virtual const int getVidas() = 0;
		const bool getObs();
		ostream& getBuffer();
		std::ostream& getConteudoBuffer();

		static void setFase(int f);

	protected:
		void salvarDataBuffer();
		void setBuffer(std::streambuf* sb);

	};

    class Projetil : public Entidade{
    protected:
        bool ativo;
        Chefao* pChefe;

    public:
        Projetil();
        Projetil(Chefao* pChefao);
        ~Projetil();

        void executar();
        void salvar();
        const int getVidas();
        void desativar();
		float arrasto();
		Chefao* getChefao();
    };
}
