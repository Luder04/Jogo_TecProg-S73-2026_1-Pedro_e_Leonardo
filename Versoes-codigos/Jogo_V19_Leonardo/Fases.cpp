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
    GC.tratarColisoesProjObstaculo();
    GC.tratarColisoesJogsProjeteis();
    GC.tratarColisoesProjChao();

    lista_ents.desenhar(); //desenhar voltar a estar aqui

    Ente::pGG->display();

    //se morreu ou apertou esc, volta para o menu:
    if (pJog1->getVidas()<1 || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){

            if(pJog1->getVidas()<1){
                cout<<"Jogador perdeu todas as vidas! Voltando para o menu..."<<endl;
                pJogo->menu_principal.gameOver();
            } else {
                cout<<"Jogador saiu do jogo! Voltando para o menu..."<<endl;
            }
            pJog1->reset();
            pJogo->proxFase = 0;

            limpar();
    }
}
void Fase::criarInimFaceis() {
    int max_qtd_inim_facil = 5;//3 + rand() % 8;
    int i;
    Goomba* inim = NULL;

    for (i = 0; i < max_qtd_inim_facil; i++) {
        inim = new Goomba();
        lista_ents.incluir(static_cast<Entidade*>(inim));
        GC.incluirInimigo(static_cast<Inimigo*>(inim));

    }

}
void Fase::criarPlataformas() {
    int max = 6;

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
FasePrimeira::FasePrimeira() : maxInimMedios(3) {

}
FasePrimeira::~FasePrimeira() {

}
void FasePrimeira::executar() {
    pJog1->setPosition(100, 200);
    criarObstaculo();
    criarInimigos();


    while (Ente::pGG->isOpen() && pJogo->proxFase == 1) {
        Ente::pGG->atualizarEventos();
        Ente::pGG->clear();
        Ente::pGG->desenharFundo(0x68ADEDFF, 0x8F7B5DFF);//a cor é definida pelo código hexadecimal, escrever na forma: 0x"Codigo"FF
        Fase::pGG->desenharVidas(pJog1);

        Fase::executar();

        //código para passar para a fase 2: (provisoriamente é só ir para o canto direito do cenário)
        if (pJog1->getx() > 1250) {
            pJogo->proxFase = 2;
            limpar();
            return;
        }
    }
}

void FasePrimeira::criarInimigos() {
    criarInimFaceis();
    criarInimMedios();
}
void FasePrimeira::criarObstaculo() {
    criarPlataformas();
    criarObstMedios();
}
void FasePrimeira::criarInimMedios() {
    int i;
    Inim_Medio* inim = NULL;

    for (i = 0; i < maxInimMedios; i++) {
        inim = new Inim_Medio();
        lista_ents.incluir(static_cast<Entidade*>(inim));
        GC.incluirInimigo(static_cast<Inimigo*>(inim));
    }
}
void FasePrimeira::criarObstMedios() {
    int max = 4;

    for (int i = 0; i < max; i++) {
        Obst_Medio* lama = new Obst_Medio();
        GC.incluirObstaculo(static_cast<Obstaculo*>(lama));
        lista_ents.incluir(static_cast<Entidade*>(lama));
    }

}


//FASE SEGUNDA
FaseSegunda::FaseSegunda() : maxChefoes(3) {

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
        Ente::pGG->desenharFundo(0xC1B891FF, 0xB5785AFF);//EFE4B0 B97A57
        Fase::pGG->desenharVidas(pJog1);

        for(int i=0;i<lista_chefoes.size();i++){
            if(lista_chefoes[i]!=NULL){
                if (lista_chefoes[i]->getAtirar()==true){
                    x_projetil=lista_chefoes[i]->getx();
                    y_projetil=lista_chefoes[i]->gety()+lista_chefoes[i]->getSizey();
                    criarProjeteis();
                }
                if (lista_chefoes[i]->getVidas()==0){
                    lista_chefoes.erase(lista_chefoes.begin() + i);
                }
            }
        }
        Fase::executar();

        //código para completar o jogo fase 2: (provisoriamente é só ir para o canto direito do cenário)
        if (pJog1->getx() > 1250 && (lista_chefoes.empty())) {
            pJogo->menu_principal.vitoria(pJog1->getPontos());
            pJog1->reset();
            pJogo->proxFase = 0;
            limpar();
        }
    }
}

void FaseSegunda::criarInimigos() {
    criarInimFaceis();
    criarChefoes();
}
void FaseSegunda::criarObstaculo() {
    criarPlataformas();
    criarObstDificeis();
}
void FaseSegunda::criarChefoes() {
    int i;
    Chefao* inim = NULL;

    for (i = 0; i < maxChefoes; i++) {
        inim = new Chefao();
        lista_ents.incluir(static_cast<Entidade*>(inim));
        GC.incluirInimigo(static_cast<Inimigo*>(inim));
        lista_chefoes.push_back(inim);
    }
}
void FaseSegunda::criarObstDificeis() {
    int max = 5;
    for (int i = 0; i < max; i++) {
        Obst_Dificil* lava = new Obst_Dificil();
        GC.incluirObstaculo(static_cast<Obstaculo*>(lava));
        lista_ents.incluir(static_cast<Entidade*>(lava));
    }

}
void FaseSegunda::criarProjeteis() {
    Projetil* pj = new Projetil(x_projetil,y_projetil);
    GC.incluirProjetil(pj);
    lista_ents.incluir(static_cast<Entidade*>(pj));
}

void FaseSegunda::limpar() {
    Fase::limpar();
    lista_chefoes.clear();
}
