#include "Principal.h"

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;

void Jogo::randomizar() {
	srand(static_cast<unsigned int>(time(NULL)));
}

Jogo::Jogo() : pJog1(NULL), pJog2(NULL), proxFase(0), fase1(), fase2(), menu_principal() {
	randomizar();
	pJog1 = new Jogador();
	GC.setJog1(pJog1);
}

Jogo::~Jogo() {
	ofstream arquivoFisico("save.txt");

	cout << "Caminho do save: "
		<< filesystem::absolute("save.txt") << endl;

	if (arquivoFisico.is_open()) {

		cout << "Salvando... " << endl;

		fase1.salvarEntidades(arquivoFisico);
		fase2.salvarEntidades(arquivoFisico);

		arquivoFisico.close();

		cout << "Jogo salvo! " << endl;
	}
	else {
		cout << "Erro ao abrir o arquivo de save para escrita." << endl;
	}

	cout << "Limpando jogo... " << endl;

	fase1.limpar();
	fase2.limpar();

    cout << "Deletando Jogador de Id: " << pJog1->getId() << " Tipo: " << typeid(*pJog1).name() << "... ";
    delete pJog1;
    cout << "Deletado" << endl;
    pJog1=NULL;
}

Jogador* Jogo::getJogador1() {
	return pJog1;
}

void Jogo::executar() {

	Ente::setGG(&GG);

	menu_principal.setJogo(this);

	fase1.setJogadores(pJog1);
	fase1.setJogo(this);

	fase2.setJogadores(pJog1);
	fase2.setJogo(this);

	menu_principal.executar();
	if (proxFase == 1) {
		Entidade::setFase(1);
		fase1.executar();
	}
	if (proxFase == 2) {
		Entidade::setFase(2);
		fase2.executar();
	}
}
