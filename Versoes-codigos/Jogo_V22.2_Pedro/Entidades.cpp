#include "Entidades.h"
#include <fstream>

using namespace Entidades;

const float Entidade::gravidade = 1;
int Entidade::fase = 0;
Entidade::Entidade() : Ente(), x(-1), y(-1), sizex(0), sizey(0), vely(0), velx(0), buffer(NULL), ehObstaculo(false) {

}

Entidade::~Entidade() {
	x = -1;
	y = -1;
	sizex = 0;
	sizey = 0;
}

void Entidade::setBuffer(std::streambuf* sb) {
    buffer.rdbuf(sb);
}

void Entidade::salvarDataBuffer() {
    buffer << "Fase:" << fase << " "
        << typeid(*this).name() << " "
        << x << " "
        << y << " "
        << sizex << " "
        << sizey << "\n";
}

std::ostream& Entidade::getConteudoBuffer() {
    return buffer;
}

ostream& Entidade::getBuffer() { return buffer; }
float Entidade::getx() { return x; }
float Entidade::gety() { return y; }
float Entidade::getSizex() { return sizex; }
float Entidade::getSizey() { return sizey; }
float Entidade::getvelx() { return velx; }
float Entidade::getvely() { return vely; }
void Entidade::gravitar() {  
    vely -= gravidade;
    if (y + vely < 200) {
        vely = 0;
        setPosition(x, 200);
    }
}
const bool Entidade::getObs() { return ehObstaculo; }
void Entidade::setFase(int f) { fase = f; };
void Entidade::setPosition(float xNew, float yNew) {
	x = xNew;
	y = yNew;
	pFig->setPosition(xNew, yNew);
}
void Entidade::setvelx(float x){
    velx=x;
}
void Entidade::setvely(float y){
    vely=y;
}


//Projetil
Projetil::Projetil() : Entidade(), pChefe(NULL), ativo(false) {

}

Projetil::Projetil(float x_spawn, float y_spawn, Chefao* pChefao) : Entidade(), ativo(true), pChefe(pChefao) {
    x=x_spawn;
    y=y_spawn;
    velx=-(25+rand()%25);
    vely=10+rand()%10;
    sizex = 2.5;
    sizey = 2.5;
    sf::CircleShape* shape = new sf::CircleShape(sizex+ sizey);
    
	shape->setFillColor(sf::Color(0x54270DFF));
	shape->setPosition(x, y);
	pFig = shape;
}

Projetil::~Projetil(){
    ativo=false;
}

void Projetil::executar(){
    x += velx;
    y += vely;

    gravitar();
    velx += arrasto();
	pFig->move(velx, vely);
}
void Projetil::salvar(){

}
const int Projetil::getVidas() {
    return (int)ativo;
}

void Projetil::setAtivo(bool a){
    ativo=a;
}
float Projetil::arrasto() {
    float coeficiente = 0.02f;
    float massaEspecifica = 0.0787f;
    float area = sizex * sizey;
    float forcaArrasto = (1.0f/ 2.0f) * coeficiente * massaEspecifica * area * (velx*velx);

    if (velx > 0)
        return -forcaArrasto;
    else
        return forcaArrasto;
}
