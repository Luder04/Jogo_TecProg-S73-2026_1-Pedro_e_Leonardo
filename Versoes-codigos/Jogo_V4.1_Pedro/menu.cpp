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

    sf::RectangleShape jogar_but;
    jogar_but.setSize(sf::Vector2f(350, 100));
    jogar_but.setScale({ 1.f, -1.f });
    jogar_but.setPosition({ 490, 425 });
    jogar_but.setFillColor(sf::Color(230, 120, 20));
    jogar_but.setOutlineThickness(5);
    jogar_but.setOutlineColor(sf::Color::Black);

    sf::Text jogar_txt("JOGAR", font);
    jogar_txt.setCharacterSize(75);
    jogar_txt.setScale({ 1.f, -1.f });
    jogar_txt.setPosition({ 555, 425 });


    while (Ente::pGG->isOpen()) {
        Ente::pGG->atualizarEventos();
        Ente::pGG->clear();
        Ente::pGG->desenharFundo();
        //GC.tocandoChao();

        sf::Vector2i mousePos = sf::Mouse::getPosition(Ente::pGG->getJanela());

        // Converter a posição do mouse para Float (necessário para colisão no SFML)
        //sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        sf::Vector2f mousePosF = Ente::pGG->getJanela().mapPixelToCoords(mousePos);

        // Pegar os limites do botão
        sf::FloatRect botaoBordas = jogar_but.getGlobalBounds();

        if (botaoBordas.contains(mousePosF))
        {
            jogar_but.setFillColor(sf::Color(150, 50, 5));

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                return;
                //jogar_but.setFillColor(sf::Color(230, 170, 150));
            }
        }
        else {
            jogar_but.setFillColor(sf::Color(230, 120, 20));
        }

        pGG->getJanela().draw(titulo);
        pGG->getJanela().draw(jogar_but);
        pGG->getJanela().draw(jogar_txt);


        /*if (!pJog->getJogador1()->podePular) {
            pJog->getJogador1()->mover(0, pJog->getJogador1()->vely);
            pJog->getJogador1()->vely -= 0.1;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && pJog->getJogador1()->podePular == true) {
            pJog->getJogador1()->vely = 5;
            pJog->getJogador1()->podePular = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            pJog->getJogador1()->mover(5, 0);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            pJog->getJogador1()->mover(-5, 0);
        }
        else {
            pJog->getJogador1()->desenhar();
        }*/

        Ente::pGG->display();
    }
}
