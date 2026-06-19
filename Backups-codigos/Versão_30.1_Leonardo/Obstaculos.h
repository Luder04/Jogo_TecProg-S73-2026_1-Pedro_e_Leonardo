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
		const int getVidas();
		virtual void executar() = 0;
		virtual void salvar() = 0;
		virtual void obstaculizar(Jogador* p) = 0;
		virtual void obstaculizar(Inimigo* p)=0;
		void setSprite();
		virtual std::string getTipo() = 0;
	};

	class Plataforma : public Obstaculo {
	private:
		float altura;
		float largura;
		static int qtd_plats;
		bool movel;

	public:
		Plataforma();
		Plataforma(float x, float y, float sx, float sy);
		~Plataforma();

		void executar();
		void salvar();
		void obstaculizar(Jogador* p);
		void obstaculizar(Inimigo* p);
		void flutuar();
		void setSprite();
		void esmagar(Jogador* pJog);
		std::string getTipo();
	};

	class Lama : public Obstaculo {
	private:
		float largura;
		static int qtd_lamas;
		float viscosidade;
		float profundidade;

	public:
		Lama();
		Lama(float x, float y, float sx, float sy);
		~Lama();

		void executar();
		void afundar();
		void salvar();
		void obstaculizar(Jogador* pJog);
		void obstaculizar(Inimigo* p);
		void setSprite();
		std::string getTipo();
	};


	class Lava : public Obstaculo {
	private:
		float largura;
		static int qtd_lavas;
		short int danosidade;
		float temperatura;
		float dT;

	public:
		Lava();
		Lava(short int danosidade, float x, float y, float sx, float sy);
		~Lava();

		void executar();
		void salvar();
		void salvarDataBuffer();
		void obstaculizar(Jogador* pJog);
		void obstaculizar(Inimigo* p);
		void setSprite();
		std::string getTipo();
	};

}
