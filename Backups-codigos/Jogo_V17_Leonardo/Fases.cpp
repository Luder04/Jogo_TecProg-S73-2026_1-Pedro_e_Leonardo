#include "Fases.h"
#include "Principal.h"
#include "Obstaculos.h"

using namespace Obstaculos;
using namespace Fases;

//FASE ABSTRATA
Fase::Fase() : Ente(), pJog1(NULL), pJogo(NULL), lista_ents(), GC() {
    cout << "Fase de Id: " << getId() << " criado no Jogo" << endl;
}
Fase::~Fase() {
}
void Fase::salvarEntidades(std::ofstream& arquivo) {
    lista_ents.salvar(arquivo);
}
void Fase::setJogadores(Jogador* pJog1_in/*,Jogador* pJog2_in*/) {
    if (pJog1_in != NULL) {
        pJog1 = pJog1_in;
        //lista_ents.setJogador(pJog1_in);
        GC.setJog1(pJog1);

        lista_ents.incluir(static_cast<Entidade*>(pJog1));

    }

    /*if(pJog2_in!=NULL){
        pJog2=pJog2_in;
        GC.setJog2(pJog2_in);
    }*/
}
void Fase::setJogo(Jogo* j) {
    pJogo = j;
}
void Fase::executar() {
    //comandos comuns a ambas as fases:
    lista_ents.percorrer();

    GC.tocandoChao();
    GC.tratarColisoesJogsInimigos();
    GC.tratarColisoesJogsObstaculo();
    GC.tratarColisoesInimObstaculo();

    lista_ents.desenhar(); //desenhar voltar a estar aqui

    Ente::pGG->display();

    //se morreu ou apertou esc, volta para o menu:
    if (pJog1->getVidas()<1 || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
            cout<<"Voltando para o menu..."<<endl;
            pJog1->reset();
            pJogo->proxFase = 0;
            limpar();
    }
}
void Fase::criarInimFaceis() {
    int max_qtd_inim_facil = 3;//3 + rand() % 8;
    int i;
    Goomba* inim = NULL;

    for (i = 0; i < max_qtd_inim_facil; i++) {
        inim = new Goomba();
        lista_ents.incluir(static_cast<Entidade*>(inim));
        GC.incluirInimigo(static_cast<Inimigo*>(inim));

    }

}
void Fase::criarPlataformas() {
    int max = 10;

    for (int i = 0; i < max; i++) {
        Plataforma* plat = new Plataforma();
        GC.incluirObstaculo(static_cast<Obstaculo*>(plat));
        lista_ents.incluir(static_cast<Entidade*>(plat));
    }

}
void Fase::criarCenario() {

}
void Fase::limpar() {
    lista_ents.limpar();
    GC.limparListas();
}

//FASE PRIMEIRA
FasePrimeira::FasePrimeira() : maxInimMedios(10) {

}
FasePrimeira::~FasePrimeira() {

}
void FasePrimeira::executar() {
    pJog1->setPosition(100, 200);
    criarInimigos();
    criarObstaculo();

    while (Ente::pGG->isOpen() && pJogo->proxFase == 1) {
        Ente::pGG->atualizarEventos();
        Ente::pGG->clear();
        Ente::pGG->desenharFundo(0x68ADEDFF, 0x8F7B5DFF);//a cor é definida pelo código hexadecimal, escrever na forma: 0x"Codigo"FF
        Fase::pGG->desenharVidas(pJog1);

        Fase::executar();

        //código para passar para a fase 2: (provisoriamente é só ir para o canto direito do cenário)
        if (pJog1->getx() > 1200) {
            pJogo->proxFase = 2;
            limpar();
            return;
        }
    }
}

void FasePrimeira::criarInimigos() {
    criarInimFaceis();
}
void FasePrimeira::criarObstaculo() {
    criarPlataformas();
    criarObstMedios();
}
void FasePrimeira::criarInimMedios() {

}
void FasePrimeira::criarObstMedios() {
    int max = 3;

    for (int i = 0; i < max; i++) {
        Obst_Medio* lama = new Obst_Medio();
        GC.incluirObstaculo(static_cast<Obstaculo*>(lama));
        lista_ents.incluir(static_cast<Entidade*>(lama));
    }

}


//FASE SEGUNDA
FaseSegunda::FaseSegunda() : maxChefoes(10) {

}
FaseSegunda::~FaseSegunda() {

}
void FaseSegunda::executar() {
    pJog1->setPosition(100, 200);
    criarInimigos();
    criarObstaculo();

    while (Ente::pGG->isOpen() && pJogo->proxFase == 2) {
        Ente::pGG->atualizarEventos();
        Ente::pGG->clear();
        Ente::pGG->desenharFundo(0xEFE4B0FF, 0xB97A57FF);
        Fase::pGG->desenharVidas(pJog1);
        Fase::executar();
    }
}

void FaseSegunda::criarInimigos() {

}
void FaseSegunda::criarObstaculo() {
    criarPlataformas();
}
void criarChefoes() {

}
void criarObstDificeis() {

}
void criarProjeteis() {

}
