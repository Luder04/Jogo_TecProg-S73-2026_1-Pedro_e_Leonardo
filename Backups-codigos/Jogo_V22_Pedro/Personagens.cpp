#include "Personagens.h"

using namespace Personagens;

Personagem::Personagem() : Entidade(), num_vidas(1) {
}
Personagem::~Personagem() {
	num_vidas = 0;
}
void Personagem::operator--(int dano) {
	num_vidas -= dano;
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
Jogador::Jogador() : Personagem(), pontos(0), forca_pulo(16), forca_andar(5), max_vidas(30), podePular(true), tempoInvencivel(0.2f), salvo(false) {
	num_vidas=max_vidas;
	sizex = 25.0f;
	sizey = 50.0f;

	sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(sizex, sizey));
	shape->setFillColor(sf::Color::Green);

	pFig = shape;
}

Jogador::~Jogador() {}

void Jogador::colidir() {}
void Jogador::executar() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && podePular == true) {
        vely = forca_pulo;
        podePular = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		velx = forca_andar;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		velx = -forca_andar;
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
			setPosition(100, 200);
			podePular = true;
		}
		relogioDano.restart();
	}
	else {
		std::cout << "Dano ignorado! Jogador invencivel por mais: " << (tempoInvencivel - relogioDano.getElapsedTime().asSeconds()) << "s" << std::endl;
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
Goomba::Goomba() : Inimigo(), raio(10) {
	x = 300+200*(rand()%5)+rand()%60;
	y = 200;
	velx=3 + 2*nivel_maldade/100.0;


	num_vidas = 1;
	sf::CircleShape* shape = new sf::CircleShape(raio);
	//sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(sizex, sizey));
	shape->setFillColor(sf::Color(0x54270DFF));
	shape->setPosition(x, y);

	pFig = shape;
}
Goomba::~Goomba() {

}

void Goomba::danificar(Jogador* pJog) {
    pJog->operator--(1);
}

void Goomba::executar() {
	if (x < 200 && velx < 0) {
		velx = -velx;
	}
	if (x > 1150 && velx > 0) {
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
void Goomba::salvar() {
	Inimigo::salvarDataBuffer();
}
void Goomba::mover(float velx, float vely) {
    x += velx;
	y += vely;
	pFig->move(velx, vely);
}

//INIMIGO MEDIO
Inim_Medio::Inim_Medio() : Inimigo(), tamanho(0) {

    tamanho=10+rand()%6;
	x = 200+rand()%950;
	y = 300+rand()%100;
	velx=2+ 5*nivel_maldade/100.0;

	num_vidas = 1;
	sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(tamanho, 4*tamanho));
	//sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(sizex, sizey));
	shape->setFillColor(sf::Color(0xFF7F27FF));
	shape->setPosition(x, y);

	pFig = shape;
}
Inim_Medio::~Inim_Medio() {

}

void Inim_Medio::danificar(Jogador* pJog) {
    pJog->operator--(1 + (rand()%5) );
}

void Inim_Medio::executar() {
	if (x < 200 && velx < 0) {
		velx = -velx;
	}
	if (x > 1150 && velx > 0) {
		velx = -velx;
	}

	x = pFig->getPosition().x;

	gravitar();
	baterAsas();
	mover(velx, vely);

	if (num_vidas > 0) {
		//desenhar();
	}
}
void Inim_Medio::salvar() {
	Inimigo::salvarDataBuffer();
}
void Inim_Medio::mover(float velx, float vely) {
	pFig->move(velx, vely);
}
void Inim_Medio::baterAsas() {
	vely += 1;
}




//CHEFAO
Chefao::Chefao() : Inimigo(), forca(0), atirar(false), timer(0), pProj(NULL) {

    forca=2+rand()%3;
	x = 600+rand()%500;
	y = 280+rand()%80;
	velx=0.4+ 0.9*nivel_maldade/100.0;

	num_vidas = forca;

	sizex = 30;
	sizey = 50;

	sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(sizex,sizey));
	//sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(sizex, sizey));
	shape->setFillColor(sf::Color(0x6D9EFFFF));
	shape->setPosition(x, y);

	pFig = shape;
}
Chefao::~Chefao() {
	removeProj();
}

void Chefao::danificar(Jogador* pJog) {
	int dano = forca;
    pJog->operator--(forca * nivel_maldade / 10);
}

void Chefao::executar() {
    //timer para voltar para a cor normal, se o chefão recebeu dano recentemente
    if(timer==1){
        pFig->setFillColor(sf::Color(0x6D9EFFFF));
        timer=0;
    }
    if(timer>0){
        timer--;
    }

    if(rand()%200==0){
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
void Chefao::salvar() {
	Inimigo::salvarDataBuffer();
}
void Chefao::mover(float velx, float vely) {
	pFig->move(velx, vely);
}
bool Chefao::getAtirar(){
    return atirar;
}
void Chefao::operator--(int dano) {
	num_vidas--;
	pFig->setFillColor(sf::Color(0xFFADADFF));
	timer=5;
}
void Chefao::baterAsas() {
	vely += 1;
}
void Chefao::setProj(Projetil* pPj) {
	pProj = pPj;
}
void Chefao::removeProj() {
	pProj = NULL;
}
bool Chefao::getProj() {
	if (pProj != NULL) {
		return false;
	}
	return true;
}
