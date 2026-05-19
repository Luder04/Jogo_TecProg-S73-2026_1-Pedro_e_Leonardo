#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>

using namespace sf;
using namespace std;

int main()
{
    bool jogando = false;

    RenderWindow window(VideoMode({ 1280, 720 }), "Jogo"); //Abre janela

    RectangleShape chao;
    chao.setSize(Vector2f(1280, 200));
    chao.setPosition({0, 520 });
    chao.setFillColor(Color(200, 170, 80));

    RectangleShape ceu;
    ceu.setSize(Vector2f(1280, 520));
    ceu.setPosition({ 0, 0 });
    ceu.setFillColor(Color(70, 120, 200));

    const Font font("BAUHS93.ttf");
    Text titulo(font, "Super Duper Mairo");
    titulo.setCharacterSize(110);
    titulo.setPosition({ 180, 50 });

    RectangleShape jogar_but;
    jogar_but.setSize(Vector2f(350, 100));
    jogar_but.setPosition({ 490, 225 });
    jogar_but.setFillColor(Color(230, 120, 20));
    jogar_but.setOutlineThickness(5);
    jogar_but.setOutlineColor(Color::Black);

    Text jogar_txt(font, "JOGAR");
    jogar_txt.setCharacterSize(75);
    jogar_txt.setPosition({ 555, 225 });

    RectangleShape jog1;
    jog1.setSize(Vector2f(50, 100));
    jog1.setPosition({ 50, 420 });
    jog1.setFillColor(Color(20, 20, 200));
    float velocidade = 5;
    float pulo = 0;
    bool podePular = true;

    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        // Pegar a posição atual do mouse em relação à janela
        Vector2i mousePos = Mouse::getPosition(window);

        // Converter a posição do mouse para Float (necessário para colisão no SFML)
        Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        // Pegar os limites do botão
        FloatRect botaoBordas = jogar_but.getGlobalBounds();

        if (botaoBordas.contains(mousePosF))
        {
            jogar_but.setFillColor(Color(150, 50, 5));

            if (Mouse::isButtonPressed(Mouse::Button::Left))
            {
                jogar_but.setFillColor(Color(230, 170, 150));
            }
        }
        else {
            jogar_but.setFillColor(Color(230, 120, 20));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && jogando) {
            
            jog1.move({ velocidade, 0 });
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && jogando)
        {
            jog1.move({ -velocidade, 0 });
        }

        if (jog1.getPosition().y > 420) {
            jog1.setPosition({ jog1.getPosition().x, 420 });
            pulo = 0;
            podePular = true;
        }

        if (pulo < 10) {
            jog1.setPosition({ jog1.getPosition().x, jog1.getPosition().y + pulo });
            pulo = pulo + 0.2;
        }

        while (const optional event = window.pollEvent()) // O pollEvent realiza "uma ação por vez", enqto o loop principal roda incessantemente*
        {
            if (event->is<Event::Closed>())
                window.close();

            if (event->is<Event::MouseButtonPressed>())
            {
                if (Mouse::isButtonPressed(Mouse::Button::Left))
                {
                    if (botaoBordas.contains(mousePosF))
                    {
                        jogando = true;
                    }
                }
            }  

            if (event->is<Event::KeyPressed>()) {
                if (Keyboard::isKeyPressed(Keyboard::Key::W) && podePular) {
                    pulo = -5;
                    podePular = false;
                    cout << "pulou" << endl;
                }
            }
        }

        window.clear();

        window.draw(chao);
        window.draw(ceu);
        
        if (jogando == false) {
            window.draw(titulo);

            window.draw(jogar_but);
            window.draw(jogar_txt);
        }
        else {
            window.draw(jog1);
        }

        window.display();
    }

    return 0;
}