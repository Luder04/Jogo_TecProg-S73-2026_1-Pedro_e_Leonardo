#pragma once

#include "Ente.h"
#include "Principal.h"
#include <string.h>
#include <functional>

class Menu : public Ente {

private:
    Jogo* pJog;
    sf::Font fonte;
    sf::Text titulo;

    class Botao {
        private:
            char nome[30];
            int id;

        public:
            sf::RectangleShape retangulo;
            sf::Text texto;
            sf::FloatRect borda;
            std::function<bool()> acao;

            Botao(){
            }
            ~Botao(){
            }
            void setNome(char* nome_botao){
                strcpy(nome,nome_botao);
            }
            void setId(int id_botao){
                id=id_botao;
            }
            char* getNome(){
                return nome;
            }
            int getId(){
                return id;
            }
            bool executar_acao() {
                if (acao)
                    return acao();
            }
    };

    class SubMenu{
        private:
            int id;

        public:
            vector<Botao*> lista_botoes;
            sf::Text subtitulo;
            SubMenu(){
            }
            ~SubMenu(){
            }
            void setId(int id_submenu){
                id=id_submenu;
            }
            int getId(){
                return id;
            }
            executar();
    };
    vector<SubMenu*> lista_submenus;
    int submenu_ativo;
    bool mouse_pressionado;

public:
    Menu();
    ~Menu();

    void setJogo(Jogo* j);
    void executar();

    void criarTitulo(char* nome_titulo);
    void criarSubTitulo(int id_submenu,char* nome_subtitulo);
    void criarBotao(int id_submenu,char* nome_botao,std::function<bool()> acao_botao);

    void criarSubMenu(int id_submenu);

};
