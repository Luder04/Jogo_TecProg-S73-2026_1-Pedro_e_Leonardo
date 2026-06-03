#pragma once

#include "Ente.h"
#include <iostream>

namespace Entidades {

	class Entidade : public Ente {
	protected:
		float x;
		float y;

		float sizex;
		float sizey;

		ostream buffer;
		bool ehObstaculo;

	public:
		Entidade();
		virtual ~Entidade();

		virtual void executar() = 0;
		virtual void salvar() = 0;
		float getx();
		float gety();
		float getSizex();
		float getSizey();
		virtual const int getVidas() = 0;
		const bool getObs();

	protected:
		void salvarDataBuffer();
	};


}
