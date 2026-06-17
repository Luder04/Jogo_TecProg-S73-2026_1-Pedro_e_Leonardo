#include "Personagens.h"

using namespace Personagens;

Personagem::Personagem() : Entidade(), num_vidas(1) {
}
Personagem::~Personagem() {
	num_vidas = 0;
}
void Personagem::operator--(int dano) {
	num_vidas -= dano;
	if(num_vidas<0){
        num_vidas=0;
	}
}
void Personagem::salvarDataBuffer() {
	Entidade::salvarDataBuffer();
}

const int Personagem::getVidas() {
	return num_vidas;
}
void Personagem::setVidas(int n){
    num_vidas=n;
}
Jogador::Jogador() : Personagem(), jogador2(false), pontos(0), forca_pulo(16), forca_andar(5), max_vidas(30), podePular(true), tempoInvencivel(0.2f), salvo(false) {
	num_vidas=max_vidas;
	sizex = 25.0f;
	sizey = 55.0f;
	atribuirBotoes();

	sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(sizex, sizey));
	shape->setFillColor(sf::Color::Green);

	pFig = shape;
	setTexture("jogador1.png");
	setSprite();
}
Jogador::Jogador(bool jog2) : Personagem(), jogador2(jog2), pontos(0), forca_pulo(16), forca_andar(5), max_vidas(30), podePular(true), tempoInvencivel(0.2f), salvo(false) {
	num_vidas=max_vidas;
	sizex = 25.0f;
	sizey = 55.0f;
    atribuirBotoes();

	sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(sizex, sizey));
	if(jogador2){
        shape->setFillColor(sf::Color(0x009900FF)); //pinta o jogador 2 de outra cor
	} else {
        shape->setFillColor(sf::Color::Green);
	}

	pFig = shape;
	if(jogador2){
        setTexture("jogador2.png");
	} else {
        setTexture("jogador1.png");
	}
	setSprite();
}

Jogador::~Jogador() {}

void Jogador::atribuirBotoes(){
    if(!jogador2){ //botões jogador 1:
        botao_pular=sf::Keyboard::Key::W;
        botao_esquerda=sf::Keyboard::Key::A;
        botao_direita=sf::Keyboard::Key::D;
    } else {       //botões jogador 2:
        botao_pular=sf::Keyboard::Key::Up;
        botao_esquerda=sf::Keyboard::Key::Left;
        botao_direita=sf::Keyboard::Key::Right;
    }
}

void Jogador::colidir() {}
void Jogador::executar() {
    if (sf::Keyboard::isKeyPressed(botao_pular) && podePular == true) {
        vely = forca_pulo;
        podePular = false;
    }

    if (sf::Keyboard::isKeyPressed(botao_direita) && !sf::Keyboard::isKeyPressed(botao_esquerda)) {
		velx = forca_andar;
		direcao=false;
    }
    else if (sf::Keyboard::isKeyPressed(botao_esquerda) && !sf::Keyboard::isKeyPressed(botao_direita)) {
		velx = -forca_andar;
		direcao=true;
    }

	gravitar();
	mover(velx, vely);
	forca_andar = 5;
	forca_pulo=16;
	velx=0;
	//desenhar();
}
void Jogador::salvar() {
	if (!salvo) {
		salvo = true;
		Personagem::salvarDataBuffer();
	}
}
void Jogador::mover(float velx, float vely) {
	x += velx;
	y += vely;
	pFig->move(velx, vely);
}

void Jogador::operator--(int dano) {
	if (relogioDano.getElapsedTime().asSeconds() >= tempoInvencivel) {
		if (num_vidas > 0) {
			Personagem::operator--(dano);
			moverParaSpawn();
			podePular = true;
		}
		relogioDano.restart();
	}
	else {
		std::cout << "Dano ignorado! Jogador invencivel por mais: " << (tempoInvencivel - relogioDano.getElapsedTime().asSeconds()) << "s" << std::endl;
	}
}
void Jogador::moverParaSpawn(){
    if(!jogador2){
        setPosition(100, 200);
    } else {
        setPosition(60, 200);
    }
}

void Jogador::operator++() {
	pontos++;
}

const int Jogador::getPontos() {
	return pontos;
}
void Jogador::reset(){
    num_vidas=max_vidas;
    pontos=0;
    podePular=true;
}
void Jogador::colidir(Inimigo* pIn){
    if(typeid(*pIn)==typeid(Aguia)){
        pIn->danificar(this);
    } else if(typeid(*pIn)==typeid(Rato) || typeid(*pIn)==typeid(Dragao)) {

                sf::FloatRect boundsInimigo = pIn->getFig().getGlobalBounds();
                sf::FloatRect boundsJogador = getFig().getGlobalBounds();

                if (boundsJogador.left + boundsJogador.width > boundsInimigo.left + 5.0f &&
                            boundsJogador.left < boundsInimigo.left + boundsInimigo.width - 5.0f && getvely()!=0) {

                    // De cima para baixo
                    if (getvely() <= 0.0f) {
                        pIn->operator--(1);
                        float cabecaInimigo = boundsInimigo.top + boundsInimigo.height;
                        setPosition(getx(), cabecaInimigo);
                        podePular = true;
                        setvely(10.0); // Impulso para cima
                        operator++();  // jogador ganha um ponto
                    }
                    // De baixo para cima
                    else if (getvely() > 0.0f) {
                        pIn->operator--(1);
                        float peInimigo = boundsInimigo.top - boundsJogador.height;
                        setPosition(getx(), peInimigo);
                        setvely(-5.0f); // Para a subida e começa a cair
                        operator++();  // jogador ganha um ponto
                    }
                } else {
                    // Colisão lateral
                    pIn->danificar(this);
                }
    }
}

void Jogador::setSprite() {
	pSprite->setTexture(*pTexture);
	pSprite->setTextureRect(sf::IntRect({ 0, 0 }, { 16, 16 }));
	pSprite->setPosition(pFig->getPosition().x, pFig->getPosition().y);

	sf::Vector2u texSize = pTexture->getSize();

	pSprite->setRotation(180.0f);

	if (direcao) {
		pSprite->setOrigin(12.5f, 16.f);
		pSprite->setScale(3, 4);
	}
	else {
		pSprite->setOrigin(4.f, 16.f);
		pSprite->setScale(-3, 4);
	}
}

// Inimigo
Inimigo::Inimigo() : Personagem(), nivel_maldade(rand() % 100 + 1) {

}
Inimigo::~Inimigo() {
	nivel_maldade = 0;
}

void Inimigo::salvarDataBuffer() {
	Personagem::salvarDataBuffer();
}

float Inimigo::getVelx() {
	return velx;
}
void Inimigo::setVelx(float newVelx) {
	velx = newVelx;
}
float Inimigo::getVely() {
	return vely;
}
void Inimigo::setVely(float newVely) {
	velx = newVely;
}

//INIMIGO FACIL
Rato::Rato() : Inimigo(), raio(10) {
	x = 300+200*(rand()%5)+rand()%60;
	y = 200;
	velx=3 + 2*nivel_maldade/100.0;


	num_vidas = 1;
	sf::CircleShape* shape = new sf::CircleShape(raio);
	//sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(sizex, sizey));
	shape->setFillColor(sf::Color(0x54270DFF));
	shape->setPosition(x, y);

	pFig = shape;

	setTexture("rat.png");
}
Rato::~Rato() {
	delete pFig;
}

void Rato::danificar(Jogador* pJog) {
    pJog->operator--(3);
}

void Rato::executar() {
	if (x < 200 && velx < 0) {
        direcao=!direcao;
		velx = -velx;
	}
	if (x > 1150 && velx > 0) {
	    direcao=!direcao;
		velx = -velx;
	}
	if (rand() % 100 == 0) { //pulinho aleatório
		vely = 5;
	}
	//x = pFig->getPosition().x;
	gravitar();
	mover(velx,vely);
	//pFig->move(velx, 0);

	/*if (num_vidas > 0) {
		desenhar();
	}*/
}
void Rato::salvar() {
	Inimigo::salvarDataBuffer();
}
void Rato::mover(float velx, float vely) {
    x += velx;
	y += vely;
	pFig->move(velx, vely);
}

void Rato::setSprite() {
	float scala = 1.2f;

	pSprite->setTexture(*pTexture);
	pSprite->setTextureRect(sf::IntRect({ 0, 96 }, { 32, 32 }));
	pSprite->setPosition(pFig->getPosition().x, pFig->getPosition().y);

	pSprite->setRotation(180.0f);

	if (direcao) {
		pSprite->setScale(scala, scala);
		pSprite->setOrigin(24.f, 32.f);
	}
	else {
		pSprite->setScale(-scala, scala);
		pSprite->setOrigin(8.f, 32.f);
	}
}


//INIMIGO MEDIO
Aguia::Aguia() : Inimigo(), tamanho(0) {

    tamanho=10+rand()%6;
	x = 200+rand()%950;
	y = 300+rand()%100;
	sizex = 6 * tamanho;
	sizey = 3 * tamanho;
	velx=2+ 5*nivel_maldade/100.0;

	num_vidas = 1;
	sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(sizex, sizey));
	//sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(sizex, sizey));
	shape->setFillColor(sf::Color(0xFF7F27FF));
	shape->setPosition(x, y);

	pFig = shape;
	setTexture("aguianova2.png");
}
Aguia::~Aguia() {

}

void Aguia::danificar(Jogador* pJog) {
    pJog->operator--(2 + (tamanho/5) );
}

void Aguia::executar() {
	if (x < 200 && velx < 0) {
		velx = -velx;
		direcao=!direcao;
	}
	if (x > 1150 && velx > 0) {
		velx = -velx;
		direcao=!direcao;
	}

	x = pFig->getPosition().x;

	gravitar();
	baterAsas();
	mover(velx, vely);

	if (num_vidas > 0) {
		//desenhar();
	}
}
void Aguia::salvar() {
	Inimigo::salvarDataBuffer();
}
void Aguia::mover(float velx, float vely) {
	pFig->move(velx, vely);
}
void Aguia::baterAsas() {
	vely += 1;
}
void Aguia::setSprite() {
	float scaleX = sizex / 35.f;
	float scaleY = sizey / 20.f;
    //pSprite->setScale(scaleX, scaleY);
	pSprite->setTexture(*pTexture);
	//pSprite->setPosition(pFig->getPosition().x - sizex*0.20, pFig->getPosition().y - sizey*0.1);

	if (direcao) {
		pSprite->setScale(scaleX, scaleY);
		pSprite->setPosition(pFig->getPosition().x - sizex*0.20, pFig->getPosition().y - sizey*0.1);
		//pSprite->setOrigin(sizex / 2, sizey/2);
		//pSprite->setTextureRect(sf::IntRect({ 0, 0 }, { 42, 21 }));
	}
	else {
		pSprite->setScale(-scaleX, scaleY);
		pSprite->setPosition(pFig->getPosition().x + sizex*1.20, pFig->getPosition().y - sizey*0.1);
		//pSprite->setTextureRect(sf::IntRect({ 42, 0 }, { 42, 21 }));
		//pSprite->setOrigin(sizex / 42.f, sizey/2);
	}
}




//CHEFAO
Dragao::Dragao() : Inimigo(), forca(0), atirar(false), timer(0), pProj(NULL) {

    forca=3+rand()%3;
	x = 600+rand()%500;
	y = 280+rand()%80;
	velx=0.4+ 0.9*nivel_maldade/100.0;

	num_vidas = forca;

	sizex = 50;
	sizey = 40;

	sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(sizex,sizey));
	//sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(sizex, sizey));
	shape->setFillColor(sf::Color(0x6D9EFFFF));
	shape->setPosition(x, y);

	pFig = shape;
	setTexture("dragao.png");
}
Dragao::~Dragao() {
	removeProj();
}

void Dragao::danificar(Jogador* pJog) {
	//int dano = forca;
    pJog->operator--(3+ forca + nivel_maldade / 20);
}

void Dragao::executar() {
    //timer para voltar para a cor normal, se o chefão recebeu dano recentemente
    if(timer==1){
        setTexture("dragao.png");
        pFig->setFillColor(sf::Color(0x6D9EFFFF));
        timer=0;
    }
    if(timer>0){
        timer--;
    }

    if(rand()%200==0){ //chance de atirar
        atirar=true;
    } else {
        atirar=false;
    }
	if (x < 550 && velx < 0) {
		velx = -velx;
	}
	if (x > 1150 && velx > 0) {
		velx = -velx;
	}

	x = pFig->getPosition().x;
	baterAsas();
	gravitar();
	mover(velx, vely);

	if (num_vidas > 0) {
		//desenhar();
	}
}
void Dragao::salvar() {
	Inimigo::salvarDataBuffer();
}
void Dragao::mover(float velx, float vely) {
	pFig->move(velx, vely);
}
bool Dragao::getAtirar(){
    return atirar;
}
void Dragao::operator--(int dano) {
	num_vidas--;
	setTexture("dragaodano.png");
	pFig->setFillColor(sf::Color(0xFFADADFF));
	timer=5;
}
void Dragao::baterAsas() {
	vely += 1;
}
void Dragao::setProj(Projetil* pPj) {
	pProj = pPj;
}
void Dragao::removeProj() {
	pProj = NULL;
}
bool Dragao::getProj() {
	if (pProj != NULL) {
		return false;
	}
	return true;
}

void Dragao::setSprite() {
	float scaleX = sizex / 70.f;
	float scaleY = sizey / 50.f;
	pSprite->setTexture(*pTexture);
    pSprite->setScale(scaleX, scaleY);
    pSprite->setPosition(pFig->getPosition().x - sizex*0.20, pFig->getPosition().y - sizey*0.3);
}
