#include "Fases.h"
#include "Principal.h"
#include "Obstaculos.h"

using namespace Obstaculos;
using namespace Fases;

//FASE ABSTRATA
Fase::Fase() : Ente(), pJog1(NULL), pJogo(NULL) {

}
Fase::~Fase() {

}
void Fase::setJogadores(Jogador* pJog1_in/*,Jogador* pJog2_in*/) {
    if (pJog1_in != NULL) {
        pJog1 = pJog1_in;
        GC.setJog1(pJog1);
        lista_ents.incluir(static_cast<Entidade*>(pJog1));
        lista_ents.setJogador(pJog1);
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

    lista_ents.desenhar();

    Ente::pGG->display();
}
void Fase::criarInimFaceis() {
    int max_qtd_inim_facil = 1;//3 + rand() % 8;
    int i;
    Goomba* inim = NULL;

    for (i = 0; i < max_qtd_inim_facil; i++) {
        inim = new Goomba();
        GC.incluirInimigo(static_cast<Inimigo*>(inim));
        lista_ents.incluir(static_cast<Entidade*>(inim));

    }

}
void Fase::criarPlataformas() {
    int max = 3;

    for (int i = 0; i < max; i++) {
        Plataforma* plat = new Plataforma();
        GC.incluirObstaculo(static_cast<Obstaculo*>(plat));
        lista_ents.incluir(static_cast<Entidade*>(plat));
    }
    
}
void Fase::criarCenario() {

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

    while (Ente::pGG->isOpen()) {
        Ente::pGG->atualizarEventos();
        Ente::pGG->clear();
        Ente::pGG->desenharFundo(0x68ADEDFF, 0x8F7B5DFF);//a cor é definida pelo código hexadecimal, escrever na forma: 0x"Codigo"FF
        Fase::pGG->desenharVidas(pJog1);
        Fase::executar();

        //código para passar para a fase 2: (provisoriamente é só ir para o canto direito do cenário)
        if (pJog1->getx() > 1200) {
            pJogo->proxFase = 2;
            return;
        }
    }
}

void FasePrimeira::criarInimigos() {
    criarInimFaceis();
}
void FasePrimeira::criarObstaculo() {
    criarPlataformas();
}
void FasePrimeira::criarInimMedios() {

}
void FasePrimeira::criarObstMedios() {

}

//FASE SEGUNDA
FaseSegunda::FaseSegunda() : maxChefoes(10) {

}
FaseSegunda::~FaseSegunda() {

}
void FaseSegunda::executar() {
    pJog1->setPosition(100, 200);
    while (Ente::pGG->isOpen()) {
        Ente::pGG->atualizarEventos();
        Ente::pGG->clear();
        Ente::pGG->desenharFundo(0xEFE4B0FF, 0xB97A57FF);
        Fase::executar();
    }
}

void FaseSegunda::criarInimigos() {

}
void FaseSegunda::criarObstaculo() {

}
void criarChefoes() {

}
void criarObstDificeis() {

}
void criarProjeteis() {

}
