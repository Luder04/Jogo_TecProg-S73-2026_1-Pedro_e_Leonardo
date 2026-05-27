#pragma once

#include "Ente.h"
#include <iostream>

namespace Entidades {

	class Entidade : public Ente {
	protected:
		int x;
		int y;

		ostream buffer;

	public:
		Entidade();
		~Entidade();

		virtual void executar() = 0;
		virtual void salvar() = 0;
		int getx();
		int gety();

	protected:
		void salvarDataBuffer();
	};


}