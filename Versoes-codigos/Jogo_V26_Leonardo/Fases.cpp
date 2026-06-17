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

Fase::Fase() : Ente(), pJog1(NULL), pJog2(NULL), pJogo(NULL), lista_ents(), GC() {
    cout << "Fase de Id: " << getId() << " criado no Jogo" << endl;
}
Fase::~Fase() {
}
void Fase::salvarEntidades(std::ofstream& arquivo) {
    lista_ents.salvar(arquivo);
}
void Fase::setJogadores(Jogador* pJog1_in,Jogador* pJog2_in) {
    if (pJog1_in != NULL) {
        pJog1 = pJog1_in;
        //lista_ents.setJoRatosgador(pJog1_in);
        GC.setJog1(pJog1);
        lista_ents.incluir(static_cast<Entidade*>(pJog1));
    }
    if (pJog2_in != NULL) {
        pJog2 = pJog2_in;
        //lista_ents.setJoRatosgador(pJog1_in);
        GC.setJog2(pJog2);

        lista_ents.incluir(static_cast<Entidade*>(pJog2));
    }
}
void Fase::setJogo(Jogo* j) {
    pJogo = j;
}

bool Fase::gameOver(){
    if(pJog2==NULL){ //se for singleplayer
        if(pJog1->getVidas()<1){
            return true;
        }
    } else { //se for multiplayer
        if(pJog1->getVidas()<1 && pJog2->getVidas()<1){
            return true;
        }
    }
    return false;
}
void Fase::executar() {
    //comandos comuns a ambas as fases:
    criarCenario();

    lista_ents.percorrer();

    GC.executar();

    lista_ents.desenhar(); //desenhar voltar a estar aqui

    Ente::pGG->display();

    //se morreu ou apertou esc, volta para o menu:
    if (gameOver() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
            if(gameOver()){
                cout<<"Jogador(es) perdeu todas as vidas! Voltando para o menu..."<<endl;
                pJogo->menu_principal.gameOver();
            } else {
                cout<<"Jogador saiu do jogo! Voltando para o menu..."<<endl;
            }
            pJog1->reset();
            if(pJog2!=NULL) {
                pJog2->reset();
            }
            pJogo->proxFase = 0;
            limpar();
    }
}
void Fase::criarRatos() {
    int n = maxRatos-rand()%(maxRatos-2); //isso garante que o número de ratos é sempre maior ou igual a 3 e menor ou igual ao valor máximo
    int i;
    Rato* inim = NULL;

    for (i = 0; i < n; i++) {
        inim = new Rato();
        lista_ents.incluir(static_cast<Entidade*>(inim));
        GC.incluirInimigo(static_cast<Inimigo*>(inim));
    }

}
void Fase::criarPlataformas() {
    int n=maxPlataformas-rand()%(maxPlataformas-2);

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
    pJog1=NULL;
    pJog2=NULL;
    lista_ents.limpar();
    GC.limparListas();
}

//FASE PRIMEIRA
FasePrimeira::FasePrimeira() : maxAguias(4), maxLamas(4) {

}
FasePrimeira::~FasePrimeira() {

}
void FasePrimeira::executar() {
    pJog1->moverParaSpawn();
    if(pJog2!=NULL){
        pJog2->moverParaSpawn();
    }
    criarObstaculo();
    criarInimigos();

    ceu.setColor(sf::Color(255, 255, 255));

    while (Ente::pGG->isOpen() && pJogo->proxFase == 1) {
        Ente::pGG->atualizarEventos();
        Ente::pGG->clear();
        Ente::pGG->desenharFundo(0x68ADEDFF, 0x8F7B5DFF);//a cor é definida pelo código hexadecimal, escrever na forma: 0x"Codigo"FF
        Fase::pGG->desenharVidas(pJog1,pJog2);

        Fase::executar();
        //código para passar para a fase 2: (ambos os jogadores, ou apenas o que estiver vivo, devem ir para o canto direito do cenário)
        if(pJogo->proxFase!=0){ //não executar quando o fase::executar deu gameover
            if(pJog2==NULL){ //se for single player
                if (pJog1->getx() > 1250) {
                    pJogo->proxFase = 2;
                    pJog1->podePular = true;
                    limpar();
                    return;
                }
            } else { //se for multiplayer

                if( (pJog1->getVidas()<1 && pJog2->getx() > 1250) || (pJog2->getVidas()<1 && pJog1->getx() > 1250) || (pJog1->getx() > 1250 && pJog2->getx() > 1250) ){
                    pJogo->proxFase = 2;
                    pJog1->podePular = true;
                    pJog2->podePular = true;
                    limpar();
                    return;
                }
            }
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

    int n=maxAguias-rand()%(maxAguias-2);

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
FaseSegunda::FaseSegunda() : maxDragoes(4), maxLavas(6) {

}
FaseSegunda::~FaseSegunda() {

}
void FaseSegunda::executar() {
    pJog1->moverParaSpawn();
    if(pJog2!=NULL){
        pJog2->moverParaSpawn();
    }
    criarInimigos();
    criarObstaculo();

    ceu.setColor(sf::Color(150, 100, 100));

    while (Ente::pGG->isOpen() && pJogo->proxFase == 2) {
        Ente::pGG->atualizarEventos();
        Ente::pGG->clear();
        Ente::pGG->desenharFundo(0xC1B891FF, 0xB5785AFF);//EFE4B0 B97A57
        Fase::pGG->desenharVidas(pJog1,pJog2);
        for(int i=0;i<lista_dragoes.size();i++){
            if(lista_dragoes[i]!=NULL){
                if (lista_dragoes[i]->getAtirar()==true && lista_dragoes[i]->getProj()){
                    criarProjeteis(lista_dragoes[i]);
                }
                if (lista_dragoes[i]->getVidas()==0){
                    lista_dragoes.erase(lista_dragoes.begin() + i);
                }
            }
        }
        Fase::executar();

        //código para completar o jogo: (todos os bosses devem estar mortos e ambos os jogadores, ou o que estiver vivo, devem ir para o canto direito do cenário)
        if(pJogo->proxFase!=0){
            if(pJog2==NULL){ //se for singleplayer
                if (pJog1->getx() > 1250 && (lista_dragoes.empty())) {
                    pJogo->menu_principal.vitoria(pJog1->getPontos()+pJog1->getVidas());
                    pJog1->reset();
                    pJogo->proxFase = 0;
                    limpar();
                }
            } else { //se for multiplayer

                if( (pJog1->getVidas()<1 && pJog2->getx() > 1250) || (pJog2->getVidas()<1 && pJog1->getx() > 1250) || (pJog1->getx() > 1250 && pJog2->getx() > 1250) ){
                    if(lista_dragoes.empty()){
                        pJogo->menu_principal.vitoria(pJog1->getPontos()+pJog2->getPontos()+(pJog1->getVidas()+pJog2->getVidas())/2 );
                        pJog1->reset();
                        pJogo->proxFase = 0;
                        limpar();
                    }
                }
            }
        }
    }
}

void FaseSegunda::criarInimigos() {
    criarRatos();
    criarDragoes();
}
void FaseSegunda::criarObstaculo() {
    criarPlataformas();
    criarLavas();
}
void FaseSegunda::criarDragoes() {
    int i;
    Dragao* inim = NULL;
    int n=maxDragoes-rand()%(maxDragoes-2);

    for (i = 0; i < n; i++) {
        inim = new Dragao();
        lista_ents.incluir(static_cast<Entidade*>(inim));
        GC.incluirInimigo(static_cast<Inimigo*>(inim));
        lista_dragoes.push_back(inim);
    }
}
void FaseSegunda::criarLavas() {
    int n=maxLavas-rand()%(maxLavas-2);
    for (int i = 0; i < n; i++) {
        Lava* lava = new Lava();
        GC.incluirObstaculo(static_cast<Obstaculo*>(lava));
        lista_ents.incluir(static_cast<Entidade*>(lava));
    }

}
void FaseSegunda::criarProjeteis(Dragao* pDragao) {
    Projetil* pj = new Projetil(pDragao);
    GC.incluirProjetil(pj);
    lista_ents.incluir(static_cast<Entidade*>(pj));
}

void FaseSegunda::limpar() {
    lista_dragoes.clear();
    Fase::limpar();
}
