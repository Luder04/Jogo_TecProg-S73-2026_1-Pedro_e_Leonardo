#include "menu.h"
#include <optional>
#include <iostream>
#include "Principal.h"

Menu::Menu() : Ente(), pJog(NULL), submenu_ativo(0), mouse_pressionado(false) {
}

Menu::~Menu() {
    pJog = NULL;
}

void Menu::setJogo(Jogo* j) {
    pJog = j;
}

void Menu::criarTitulo(const char* nome_titulo){
    titulo.setString(nome_titulo);
    titulo.setFont(fonte);
    titulo.setCharacterSize(110);
    titulo.setScale({ 1.f, -1.f });

    sf::FloatRect limitesTexto = titulo.getLocalBounds();
    titulo.setOrigin(limitesTexto.left + limitesTexto.width / 2.0f, limitesTexto.top + limitesTexto.height / 2.0f);
    titulo.setPosition({ 640, 600 });
}

void Menu::criarSubTitulo(int id_submenu,const char* nome_subtitulo){
    lista_submenus[id_submenu]->subtitulo.setString(nome_subtitulo);
    lista_submenus[id_submenu]->subtitulo.setFont(fonte);
    lista_submenus[id_submenu]->subtitulo.setCharacterSize(60);
    lista_submenus[id_submenu]->subtitulo.setScale({ 1.f, -1.f });
    lista_submenus[id_submenu]->subtitulo.setFillColor(sf::Color::Black);

    sf::FloatRect limitesTexto = lista_submenus[id_submenu]->subtitulo.getLocalBounds();
    lista_submenus[id_submenu]->subtitulo.setOrigin(limitesTexto.left + limitesTexto.width / 2.0f, limitesTexto.top + limitesTexto.height / 2.0f);
    lista_submenus[id_submenu]->subtitulo.setPosition({ 640, 500 });
}

void Menu::criarBotao(int id_submenu,const char* nome_botao,std::function<bool()> acao_botao){
    Botao *novo_botao = new Botao();
    lista_submenus[id_submenu]->lista_botoes.push_back(novo_botao);
    novo_botao->setNome(nome_botao);
    novo_botao->setId((int)lista_submenus[id_submenu]->lista_botoes.size());
    novo_botao->acao=acao_botao;

    int altura=70;
    novo_botao->retangulo.setSize(sf::Vector2f(350, (float)altura));

    sf::Vector2f tamanho = novo_botao->retangulo.getSize();
    novo_botao->retangulo.setOrigin(tamanho.x / 2.0f, tamanho.y / 2.0f);

    novo_botao->retangulo.setScale({ 1.f, -1.f });
    novo_botao->retangulo.setPosition({ 640.0f, 425.0f - (altura+5.0f)*novo_botao->getId()});//altura+5 porque tem 5 pixels de borda
    novo_botao->retangulo.setFillColor(sf::Color(230, 120, 20));
    novo_botao->retangulo.setOutlineThickness(5);
    novo_botao->retangulo.setOutlineColor(sf::Color::Black);

    novo_botao->borda = novo_botao->retangulo.getGlobalBounds();

    novo_botao->texto.setString(nome_botao);
    novo_botao->texto.setFont(fonte);
    novo_botao->texto.setCharacterSize(50);
    novo_botao->texto.setScale({ 1.f, -1.f });
    sf::FloatRect limitesTexto = novo_botao->texto.getLocalBounds();
    novo_botao->texto.setOrigin(limitesTexto.left + limitesTexto.width / 2.0f, limitesTexto.top + limitesTexto.height / 2.0f);
    novo_botao->texto.setPosition(novo_botao->retangulo.getPosition());
}

void Menu::criarSubMenu(int id_submenu){
    SubMenu *novo_submenu = new SubMenu();
    novo_submenu->setId(id_submenu);
    lista_submenus.push_back(novo_submenu);
}

void Menu::executar() {

    if (!fonte.loadFromFile("BAUHS93.TTF"))
        return;
    criarTitulo("Super Duper Mairo");

    criarSubMenu(0);
    criarSubMenu(1);
    criarSubMenu(2);
    criarSubTitulo(1,"NOVO JOGO");
    criarSubTitulo(2,"RANKINGS");

    //return true quando vai sair do menu, return false quando continua no menu
    criarBotao(0,"NOVO JOGO",[this]() {submenu_ativo=1; return false;} );
    criarBotao(1,"JOGAR FASE 1", [this]() { pJog->proxFase = 1; return true;} );
    criarBotao(1,"JOGAR FASE 2", [this]() { pJog->proxFase = 2; return true;} );
    criarBotao(1,"VOLTAR",[this]() {submenu_ativo=0; return false;} );
    criarBotao(0,"CONTINUAR", [this]() { return false;} );
    criarBotao(0,"RANKINGS",[this]() {submenu_ativo = 2; return false;} );
    criarBotao(2,"VOLTAR",[this]() {submenu_ativo=0; return false;} );

    while (Ente::pGG->isOpen()) {
        Ente::pGG->atualizarEventos();
        Ente::pGG->clear();
        Ente::pGG->desenharFundo(0x68ADEDFF, 0x68ADEDFF);

        sf::Vector2i mousePos = sf::Mouse::getPosition(Ente::pGG->getJanela());
        sf::Vector2f mousePosF = Ente::pGG->getJanela().mapPixelToCoords(mousePos);

        for(int i=0;i<lista_submenus[submenu_ativo]->lista_botoes.size();i++){
            lista_submenus[submenu_ativo]->lista_botoes[i]->retangulo.setFillColor(sf::Color(230, 120, 20));//primeiro pinta todos os botões na cor padrão
        }
        for(int i=0;i<lista_submenus[submenu_ativo]->lista_botoes.size();i++){
            if(lista_submenus[submenu_ativo]->lista_botoes[i]->borda.contains(mousePosF)){
                lista_submenus[submenu_ativo]->lista_botoes[i]->retangulo.setFillColor(sf::Color(150, 50, 5));//se detecta que o mouse está em um botão, pinta ele de outra cor
                if (mouse_pressionado && !sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){//executa ao soltar o botão do mouse

                    if (lista_submenus[submenu_ativo]->lista_botoes[i]->executar_acao() == true) {
                        return;
                    }
                }
                break;//break para não selecionar dois botões ao mesmo tempo (se o mouse ficar bem na borda entre eles)
            }
        }
        mouse_pressionado=sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        for(int i=0;i<lista_submenus[submenu_ativo]->lista_botoes.size();i++){
            pGG->getJanela().draw(lista_submenus[submenu_ativo]->lista_botoes[i]->retangulo);
            pGG->getJanela().draw(lista_submenus[submenu_ativo]->lista_botoes[i]->texto);
        }
        pGG->getJanela().draw(titulo);
        pGG->getJanela().draw(lista_submenus[submenu_ativo]->subtitulo);

        Ente::pGG->display();
    }
}
