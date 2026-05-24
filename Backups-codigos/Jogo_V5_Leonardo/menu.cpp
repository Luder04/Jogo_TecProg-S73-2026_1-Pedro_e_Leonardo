// ALTERAÇÔES
// Uso do setScale(1, -1) par inverter o eixy y, visto que a tela foi invertida para ajustar o entendimento da gravidade
// Uso de sf::Vector2f mousePosF = Ente::pGG->getJanela().mapPixelToCoords(mousePos); ao invés de mousePos, pois como a tela foi invertida
// as coordenadas também foram, logo foi necessário pegar a s coordenadas direto da view usando a nova função.

#include "menu.h"
#include <optional>
#include <iostream>

Menu::Menu() : pJog(NULL) {
}

Menu::~Menu() {
    pJog = NULL;
}

void Menu::setJogo(Jogo* j) {
    pJog = j;
}

void Menu::executar() {

    /*if(pJog!=NULL){
        GC.setJog1(pJog->getJogador1());
    }*/

    sf::Font font;
    if (!font.loadFromFile("BAUHS93.TTF"))
        return;
    sf::Text titulo("Super Duper Mairo", font);
    titulo.setCharacterSize(110);
    titulo.setScale({ 1.f, -1.f });
    titulo.setPosition({ 180, 620 });

    //poderíamos adicionar um objeto botão para evitar de duplicar esses códigos
    //precisa de um código melhor para centralizar os textos
    sf::RectangleShape jogar1_botao;
    jogar1_botao.setSize(sf::Vector2f(350, 100));
    jogar1_botao.setScale({ 1.f, -1.f });
    jogar1_botao.setPosition({ 490, 425 });
    jogar1_botao.setFillColor(sf::Color(230, 120, 20));
    jogar1_botao.setOutlineThickness(5);
    jogar1_botao.setOutlineColor(sf::Color::Black);

    sf::RectangleShape jogar2_botao;
    jogar2_botao.setSize(sf::Vector2f(350, 100));
    jogar2_botao.setScale({ 1.f, -1.f });
    jogar2_botao.setPosition({ 490, 325 });
    jogar2_botao.setFillColor(sf::Color(230, 120, 20));
    jogar2_botao.setOutlineThickness(5);
    jogar2_botao.setOutlineColor(sf::Color::Black);


    sf::Text jogar1_txt("JOGAR FASE 1", font);
    jogar1_txt.setCharacterSize(75);
    jogar1_txt.setScale({ 1.f, -1.f });
    jogar1_txt.setPosition({ 555, 425 });

    sf::Text jogar2_txt("JOGAR FASE 2", font);
    jogar2_txt.setCharacterSize(75);
    jogar2_txt.setScale({ 1.f, -1.f });
    jogar2_txt.setPosition({ 555, 325 });


    while (Ente::pGG->isOpen()) {
        Ente::pGG->atualizarEventos();
        Ente::pGG->clear();
        Ente::pGG->desenharFundo(0x68ADEDFF,0x68ADEDFF);
        //GC.tocandoChao();

        sf::Vector2i mousePos = sf::Mouse::getPosition(Ente::pGG->getJanela());

        // Converter a posição do mouse para Float (necessário para colisão no SFML)
        //sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        sf::Vector2f mousePosF = Ente::pGG->getJanela().mapPixelToCoords(mousePos);

        // Pegar os limites do botão
        sf::FloatRect botao1Bordas = jogar1_botao.getGlobalBounds();
        sf::FloatRect botao2Bordas = jogar2_botao.getGlobalBounds();

        if (botao1Bordas.contains(mousePosF))
        {
            jogar2_botao.setFillColor(sf::Color(230, 120, 20));
            jogar1_botao.setFillColor(sf::Color(150, 50, 5));

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                pJog->proxFase=1;
                return;
                //jogar1_botao.setFillColor(sf::Color(230, 170, 150));
            }
        }
        else {
            jogar1_botao.setFillColor(sf::Color(230, 120, 20));
            if (botao2Bordas.contains(mousePosF)){
                jogar2_botao.setFillColor(sf::Color(150, 50, 5));
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                {
                    pJog->proxFase=2;
                    return;
                    //jogar1_botao.setFillColor(sf::Color(230, 170, 150));
                }
            }
        }

        pGG->getJanela().draw(titulo);
        pGG->getJanela().draw(jogar1_botao);
        pGG->getJanela().draw(jogar1_txt);
        pGG->getJanela().draw(jogar2_botao);
        pGG->getJanela().draw(jogar2_txt);

        Ente::pGG->display();
    }
}
