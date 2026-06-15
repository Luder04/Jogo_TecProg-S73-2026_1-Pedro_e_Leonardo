#include "Fases.h"
#include "Principal.h"
#include "Obstaculos.h"

using namespace Obstaculos;
using namespace Fases;

//FASE ABSTRATA
const int Fase::maxRatos = 6;
const int Fase::maxPlataformas = 6;
sf::Sprite Fases::Fase::chao;
sf::Sprite Fases::Fase::ceu;

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
        //lista_ents.setJoRatosgador(pJog1_in);
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
    criarCenario();

    lista_ents.percorrer();

    GC.executar();

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
void Fase::criarRatos() {
    int n = maxRatos-rand() % 4;
    int i;
    Rato* inim = NULL;

    for (i = 0; i < n; i++) {
        inim = new Rato();
        lista_ents.incluir(static_cast<Entidade*>(inim));
        GC.incluirInimigo(static_cast<Inimigo*>(inim));

    }

}
void Fase::criarPlataformas() {
    int n=maxPlataformas-rand()%4;

    for (int i = 0; i < n; i++) {
        Plataforma* plat = new Plataforma();
        GC.incluirObstaculo(static_cast<Obstaculo*>(plat));
        lista_ents.incluir(static_cast<Entidade*>(plat));
    }

}
void Fase::criarCenario() {
    texCeu.loadFromFile("ceu.png");
    ceu.setTexture(texCeu);
    ceu.setRotation(180.f);
    ceu.setScale(1.4f, 1.2f);
    ceu.setPosition(1300.f, 740.f);

    texChao.loadFromFile("chao.png");
    chao.setTexture(texChao);
    chao.setTextureRect(sf::IntRect({ 0, 50 }, { 1000, 200 }));
    chao.setRotation(180.f);
    chao.setScale(2.f, 2.1f);
    chao.setPosition(1600.f, 200.f);
}
void Fase::limpar() {
    lista_ents.limpar();
    GC.limparListas();
}

//FASE PRIMEIRA
FasePrimeira::FasePrimeira() : maxAguias(4), maxLamas(4) {

}
FasePrimeira::~FasePrimeira() {

}
void FasePrimeira::executar() {
    pJog1->setPosition(100, 200);
    criarObstaculo();
    criarInimigos();

    ceu.setColor(sf::Color(255, 255, 255));

    while (Ente::pGG->isOpen() && pJogo->proxFase == 1) {
        Ente::pGG->atualizarEventos();
        Ente::pGG->clear();
        Ente::pGG->desenharFundo(0x68ADEDFF, 0x8F7B5DFF);//a cor é definida pelo código hexadecimal, escrever na forma: 0x"Codigo"FF
        Fase::pGG->desenharVidas(pJog1);

        Fase::executar();

        //código para passar para a fase 2: (provisoriamente é só ir para o canto direito do cenário)
        if (pJog1->getx() > 1250) {
            pJogo->proxFase = 2;
            pJog1->podePular = true;
            limpar();
            return;
        }
    }
}

void FasePrimeira::criarInimigos() {
    criarRatos();
    criarAguias();
}
void FasePrimeira::criarObstaculo() {
    criarPlataformas();
    criarLamas();
}
void FasePrimeira::criarAguias() {
    int i;
    Aguia* inim = NULL;

    int n=maxAguias-rand()%2;

    for (i = 0; i < n; i++) {
        inim = new Aguia();
        lista_ents.incluir(static_cast<Entidade*>(inim));
        GC.incluirInimigo(static_cast<Inimigo*>(inim));
    }
}
void FasePrimeira::criarLamas() {
    int n=maxLamas-rand()%2;

    for (int i = 0; i < n; i++) {
        Lama* lama = new Lama();
        GC.incluirObstaculo(static_cast<Obstaculo*>(lama));
        lista_ents.incluir(static_cast<Entidade*>(lama));
    }

}


//FASE SEGUNDA
FaseSegunda::FaseSegunda() : maxChefoes(4), maxLavas(6) {

}
FaseSegunda::~FaseSegunda() {

}
void FaseSegunda::executar() {
    pJog1->setPosition(100, 200);
    criarInimigos();
    criarObstaculo();

    ceu.setColor(sf::Color(150, 100, 100));

    while (Ente::pGG->isOpen() && pJogo->proxFase == 2) {
        Ente::pGG->atualizarEventos();
        Ente::pGG->clear();
        Ente::pGG->desenharFundo(0xC1B891FF, 0xB5785AFF);//EFE4B0 B97A57
        Fase::pGG->desenharVidas(pJog1);
        for(int i=0;i<lista_chefoes.size();i++){
            if(lista_chefoes[i]!=NULL){
                if (lista_chefoes[i]->getAtirar()==true && lista_chefoes[i]->getProj()){
                    criarProjeteis(lista_chefoes[i]);
                }
                if (lista_chefoes[i]->getVidas()==0){
                    lista_chefoes.erase(lista_chefoes.begin() + i);
                }
            }
        }
        Fase::executar();
        //código para completar o jogo fase 2: (provisoriamente é só ir para o canto direito do cenário)
        if (pJog1->getx() > 1250 && (lista_chefoes.empty())) {
            pJogo->menu_principal.vitoria(pJog1->getPontos()+pJog1->getVidas());
            pJog1->reset();
            pJogo->proxFase = 0;
            limpar();
        }
    }
}

void FaseSegunda::criarInimigos() {
    criarRatos();
    criarChefoes();
}
void FaseSegunda::criarObstaculo() {
    criarPlataformas();
    criarLavas();
}
void FaseSegunda::criarChefoes() {
    int i;
    Chefao* inim = NULL;
    int n=maxChefoes-rand()%2;

    for (i = 0; i < n; i++) {
        inim = new Chefao();
        lista_ents.incluir(static_cast<Entidade*>(inim));
        GC.incluirInimigo(static_cast<Inimigo*>(inim));
        lista_chefoes.push_back(inim);
    }
}
void FaseSegunda::criarLavas() {
    int n=maxLavas-rand()%4;
    for (int i = 0; i < n; i++) {
        Lava* lava = new Lava();
        GC.incluirObstaculo(static_cast<Obstaculo*>(lava));
        lista_ents.incluir(static_cast<Entidade*>(lava));
    }

}
void FaseSegunda::criarProjeteis(Chefao* pChefao) {
    Projetil* pj = new Projetil(pChefao);
    GC.incluirProjetil(pj);
    lista_ents.incluir(static_cast<Entidade*>(pj));
}

void FaseSegunda::limpar() {
    lista_chefoes.clear();
    Fase::limpar();
}
