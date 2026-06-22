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

int Jogo::proxFase = 0;
Jogo::Jogo() : pJog1(NULL), pJog2(NULL), fase1(), fase2(), menu_principal(), multiplayer(0) {
	randomizar();
	pJog1 = new Jogador();
	pJog2 = new Jogador(1);

	recuperaRank();
}

Jogo::~Jogo() {

	if (proxFase != -1) {
		ofstream arquivoFisico("save.txt");

		if (arquivoFisico.is_open()) {
			cout << "Salvando... " << endl;
			arquivoFisico << "Fase:" << proxFase << "\n";
			arquivoFisico << "Multiplayer:" << multiplayer << "\n";
			arquivoFisico << "Pontos1:" << pJog1->getPontos() << "\n";
			arquivoFisico << "Pontos2:" << pJog2->getPontos() << "\n";
			fase1.salvarEntidades(arquivoFisico);
			fase2.salvarEntidades(arquivoFisico);

			arquivoFisico.close();

			cout << "Jogo salvo! " << endl;
		}
		else {
			cout << "Erro ao abrir o arquivo de save para escrita." << endl;
		}
	}

	ofstream arquivoRank("rank.txt");

	if (arquivoRank.is_open()) {
		for (int i = 0; i < 3; i++) {
			arquivoRank << "Ranking " << menu_principal.getRankNome(i) << " "
				<< menu_principal.getRanking(i) << "\n";
		}

		arquivoRank.close();
	}
	else {
		cout << "Erro ao abrir o arquivo de save Rank para escrita." << endl;
	}

	cout << "Limpando jogo... " << endl;

	fase1.limpar();
	fase2.limpar();

    cout << "Deletando Jogador de Id: " << pJog1->getId() << " Tipo: " << typeid(*pJog1).name() << "... ";
    delete pJog1;
    cout << "Deletado" << endl;
    pJog1=NULL;

    cout << "Deletando Jogador de Id: " << pJog2->getId() << " Tipo: " << typeid(*pJog2).name() << "... ";
    delete pJog2;
    cout << "Deletado" << endl;
    pJog2=NULL;
}

Jogador* Jogo::getJogador1() {
	return pJog1;
}
Jogador* Jogo::getJogador2() {
	return pJog2;
}
void Jogo::executar() {

	Ente::setGG(&GG);

	menu_principal.setJogo(this);

	fase1.setJogo(this);

	fase2.setJogo(this);

	while(GG.isOpen() && proxFase >=0){
        switch (proxFase) {
            case 0:
                menu_principal.executar();
                printf("Saindo do menu, para fase %d\n",proxFase);
                break;
            case 1:
                if(multiplayer==false){
                    fase1.setJogadores(pJog1,NULL);
                } else {
                    fase1.setJogadores(pJog1,pJog2);
                }
                fase1.executar();
                break;
            case 2:
                if(multiplayer==false){
                    fase2.setJogadores(pJog1,NULL);
                } else {
                    fase2.setJogadores(pJog1,pJog2);
                }
                fase2.executar();
                break;
        }
	}
}

void Jogo::recuperar() {
	Fase::recuperado = true;

	ifstream arquivo("save.txt");
	
	std::string linha;
	std::getline(arquivo, linha);
	int fase = std::stoi(linha.substr(5));
	if (fase == -1) { fase = 0; }

	std::getline(arquivo, linha);
	multiplayer = std::stoi(linha.substr(12));

	std::getline(arquivo, linha);
	pJog1->setPontos(std::stoi(linha.substr(8)));

	std::getline(arquivo, linha);
	pJog2->setPontos(std::stoi(linha.substr(8)));

	int qtd_jogs_recuperados = 0;
	bool jog1_rec = false, jog2_rec = false;

	std::string tipo;
	while (arquivo >> tipo)
	{
		if (tipo == "Jogador")
		{
			
			float x, y, sx, sy;
			bool jog2;
			int pontos, vids;

			arquivo >> pontos >> vids >> jog2 >> x >> y >> sx >> sy;

			if (jog2) {
				delete pJog2;

				pJog2 = new Jogador(pontos, vids, jog2, x, y, sx, sy);	
				jog2_rec = true;
			}
			else {
				delete pJog1;

				pJog1 = new Jogador(pontos, vids, jog2, x, y, sx, sy);
				jog1_rec = true;
			}

			qtd_jogs_recuperados++;
		}
	}

	if (multiplayer == 1 && qtd_jogs_recuperados < 2) {
		if (jog1_rec) {
			pJog2->setVidas(0);
		}
		else if (jog2_rec) {
			pJog1->setVidas(0);
		}
	}

	proxFase = fase;
}

void Jogo::recuperaRank() {
	ifstream arquivo("rank.txt");
	int rank_pos = 0;

	std::string tipo;
	while (arquivo >> tipo)
	{
		if (tipo == "Ranking")
		{
			int pontuacao;
			std::string nome;

			arquivo >> nome >> pontuacao;

			menu_principal.editarRanking(2, rank_pos, pontuacao, nome);
			rank_pos++;
		}
	}
}