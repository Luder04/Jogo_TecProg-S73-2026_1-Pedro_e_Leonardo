#include "Obstaculos.h"
#include "Personagens.h"

using namespace Personagens;
using namespace Obstaculos;

// Classe abstrata
Obstaculo::Obstaculo() : Entidades::Entidade(), danoso(false) {
    ehObstaculo = true;
}
Obstaculo::~Obstaculo() { danoso = false;  }
void Obstaculo::salvarDataBuffer() {
	Entidade::salvarDataBuffer();
}
const int Obstaculo::getVidas() { return 0; }

void Obstaculo::setSprite() {
    pSprite->setTexture(*pTexture);
    pSprite->setPosition(pFig->getPosition().x, pFig->getPosition().y);

    sf::Vector2u texSize = pTexture->getSize();

    float scaleX = sizex / texSize.x;
    float scaleY = sizey / texSize.y;

    pSprite->setScale(scaleX, scaleY);
}

// Plataforma
int Plataforma::qtd_plats = 0;

Plataforma::Plataforma() : Obstaculo(), altura(0), largura(0), movel(false) {
	qtd_plats++;

    x = rand() % 60 + (200.0f * qtd_plats);
    y=200;
    if(rand()%2 == 0){
        //plataforma horizontal alta
        y += 30 + rand() % 25;
        altura = (rand()%25 + 30.0f);
        largura = rand()%70 + 55.0f;
    } else{
        //plataforma vertical (50% de chance de ser movel)
        altura = rand()%30 + 85.0f;
        largura = rand()%30 + 35.0f;
        movel=rand()%2;
    }

    altura=altura-(int)altura%8; //altura e largura são múltiplos de 8, para a textura ficar alinhada
    largura=largura-(int)largura%8;

    sizex = largura;
    sizey = altura;

    sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(sizex, sizey));
    shape->setFillColor(sf::Color(0xEFEFEFFF));

	shape->setPosition(x, y);

	pFig = shape;
    setTexture("plataformamenor2.png");
    pTexture->setRepeated(true);
}
Plataforma::Plataforma(bool nmovel, float nvelx, float nvely, float nx, float ny, float sx, float sy) : Obstaculo(), altura(sy), largura(sx), movel(nmovel) {
    qtd_plats++;

    sizey = sy;
    sizex = sx;

    x = nx;
    y = ny;

    velx = nvelx;
    vely = nvely;

    sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(sizex, sizey));
    shape->setFillColor(sf::Color(0xEFEFEFFF));

    shape->setPosition(x, y);

    pFig = shape;
    setTexture("plataformamenor2.png");
    pTexture->setRepeated(true);
}
Plataforma::~Plataforma() {
	altura = 0.0f;
	qtd_plats = 0;
}

void Plataforma::salvar() {
    buffer << getTipo() << " "
           << movel << " "
           << velx << " "
           << vely << " ";
    Obstaculo::salvarDataBuffer();
}
void Plataforma::executar() {
    gravitar();
    flutuar();
    pFig->setPosition(x, y);
    y += vely;
}
void Plataforma::obstaculizar(Jogador* pJog) {
    sf::FloatRect boundsObs = (this)->getFig().getGlobalBounds();
    sf::FloatRect boundsJogador = pJog->getFig().getGlobalBounds();

    if (!boundsJogador.intersects(boundsObs)) return;

    // Colisão vertical
    if (boundsJogador.left + boundsJogador.width > boundsObs.left + 5.0f &&
        boundsJogador.left < boundsObs.left + boundsObs.width - 5.0f) {

        // De cima para baixo
        if (pJog->getvely() < 0.0f) {
            float topoObs = boundsObs.top + boundsObs.height;
            pJog->setPosition(pJog->getx(), topoObs);
            pJog->setvely(0);
            pJog->podePular = true;
        }
        // De baixo para cima
        else if (pJog->getvely() > 0.0f) {
            float fundoObs = boundsObs.top - boundsJogador.height;
            pJog->setPosition(pJog->getx(), fundoObs);
            pJog->setvely(-1.0f); // Para a subida e começa a cair
        } else if(pJog->getvely()==0){
            esmagar(pJog);
        }
    }

    // Colisão lateral
    else {
        if (boundsJogador.left + boundsJogador.width / 2.0f < boundsObs.left + boundsObs.width / 2.0f) {
            pJog->setPosition(boundsObs.left - boundsJogador.width, pJog->gety());
        }
        else {
            pJog->setPosition(boundsObs.left + boundsObs.width, pJog->gety());
        }
        pJog->setvelx(0.0f);
    }
}
void Plataforma::obstaculizar(Inimigo* pInim){
    sf::FloatRect boundsObs = (this)->getFig().getGlobalBounds();
    sf::FloatRect boundsInimigo = pInim->getFig().getGlobalBounds();

    if (!boundsInimigo.intersects(boundsObs)) return;

    // Colisão vertical
    if (boundsInimigo.left + boundsInimigo.width > boundsObs.left + 5.0f &&
        boundsInimigo.left < boundsObs.left + boundsObs.width - 5.0f) {

        // De cima para baixo
        if (pInim->getvely() <= 0.0f) {
            float topoObs = boundsObs.top + boundsObs.height;
            pInim->setPosition(pInim->getx()+pInim->getvelx(), topoObs);
            pInim->setvely(0);
        }
        // De baixo para cima
        else if (pInim->getvely() > 0.0f) {
            float fundoObs = boundsObs.top - boundsInimigo.height;
            pInim->setPosition(pInim->getx(), fundoObs);
            pInim->setvely(-1.0f); // Para a subida e começa a cair
        }
    }

    // Colisão lateral
    else {
        if (boundsInimigo.left + boundsInimigo.width / 2.0f < boundsObs.left + boundsObs.width / 2.0f) {
            pInim->setPosition(boundsObs.left - boundsInimigo.width, pInim->gety());
        }
        else {
            pInim->setPosition(boundsObs.left + boundsObs.width, pInim->gety());
        }
        pInim->setvelx(-pInim->getvelx());
        if (pInim->direcao == true) pInim->direcao = false; else pInim->direcao = true;
    }
}

void Plataforma::esmagar(Jogador* pJog){
    pJog->operator--(altura*largura/1000);//dano da plataforma depende da área dela
    pJog->setPosition(getx()-pJog->getSizex(), pJog->gety());
}
void Plataforma::flutuar() {
    if(movel){
        if (y < 290) {
            vely += 1.05;
        }
        else if (y > 200) {
            vely += -1.05;
        }
    } else {
        if(vely<0){
            vely += 1;
        }
    }
}

void Plataforma::setSprite(){
    pSprite->setTexture(*pTexture);
	pSprite->setPosition(pFig->getPosition().x, pFig->getPosition().y);
	pSprite->setTextureRect(sf::IntRect({ 0, 0 }, { (int)getSizex(), (int)getSizey() }));
}

std::string Plataforma::getTipo() {
    return "Plataforma";
}

// Obstaculo Medio
int Lama::qtd_lamas = 0;

Lama::Lama() : Obstaculo(), largura(0), viscosidade(.7), profundidade(.01) {
	qtd_lamas++;

    sizey=10;

	x = 205*qtd_lamas + rand()%90;
	y = 201- sizey;
	largura = rand()%30 + 60.0f;
    sizex = largura;

    profundidade=(rand()%5)/1000.0+0.007;

    sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(sizex, sizey));
	shape->setFillColor(sf::Color(0x964B00FF));

	shape->setPosition(x, y);

	pFig = shape;
    setTexture("lama2.png");
}

Lama::Lama(float nx, float ny, float sx, float sy) : Obstaculo(), largura(sx), viscosidade(.7), profundidade(.01) {
    qtd_lamas++;

    sizex = sx;
    sizey = sy;

    x = nx;
    y = ny;

    sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(sizex, sizey));
    shape->setFillColor(sf::Color(0x964B00FF));

    shape->setPosition(x, y);

    pFig = shape;
    setTexture("lama2.png");
}

Lama::~Lama() {
	largura = 0.0f;
	qtd_lamas = 0;
}

void Lama::salvar() {
    buffer << getTipo() << " ";
	Obstaculo::salvarDataBuffer();
}
void Lama::executar() {
    gravitar();
    pFig->setPosition(x, y - 9);
    y += vely;
    afundar();
}
void Lama::obstaculizar(Jogador* pJog) {
    pJog->forca_pulo=(1-viscosidade)*pJog->forca_pulo;
    pJog->forca_andar=(1-viscosidade)*pJog->forca_andar;
}

void Lama::obstaculizar(Inimigo* p){
}

void Lama::afundar() {
    if (viscosidade >= 0.8) {
        profundidade = -profundidade;
    }
    if (viscosidade < 0.3) {
        profundidade = -profundidade;
    }

    viscosidade += profundidade;
}

void Lama::setSprite(){
    pSprite->setTexture(*pTexture);
    int altura_sprite=sizey*viscosidade*0.5+6;
	pSprite->setPosition(x, y-altura_sprite+2); //desenha a lama um pouco acima do chão
	pSprite->setTextureRect(sf::IntRect({ 0, 0 }, { (int)sizex, altura_sprite }));
}

std::string Lama::getTipo() {
    return "Lama";
}

// Obstaculo dificil
int Lava::qtd_lavas = 0;

Lava::Lava() : Obstaculo(), danosidade(0), largura(0), temperatura(0), dT(2) {
	qtd_lavas++;

    float altura=10;
    danosidade=rand()%100;

	x = 205*qtd_lavas + rand()%90;
	y = 201-altura;
	largura = rand()%40 + 85.0f;

    sizex = largura;
    sizey = altura;

    sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(sizex, sizey));
	shape->setPosition(x, y);

	pFig = shape;
    setTexture("lavaonoff.png");
    pTexture->setRepeated(true);
    setSprite();
}

Lava::Lava(short int danosidade, float nx, float ny, float sx, float sy) : Obstaculo(), danosidade(danosidade), largura(sx), temperatura(0), dT(2) {
    qtd_lavas++;

    x = nx;
    y = ny;

    sizex = sx;
    sizey = sy;

    sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(sizex, sizey));
    shape->setPosition(x, y);

    pFig = shape;
    setTexture("lavaonoff.png");
    pTexture->setRepeated(true);
    setSprite();
}

Lava::~Lava() {
	largura = 0.0f;
	danosidade=0;
	qtd_lavas = 0;
}

void Lava::salvarDataBuffer() {
    Obstaculo::salvarDataBuffer();
}

void Lava::salvar() {
    buffer  << getTipo() << " "
            << danosidade << " ";
	salvarDataBuffer();
}

void Lava::executar() {
    //a lava vira danosa quando atinge uma certa temperatura (a qual depende da danosidade)
    if(temperatura>100-danosidade){
        danoso=true;
        pFig->setFillColor(sf::Color(255, 17, 17));
    } else {
        danoso=false;
        pFig->setFillColor(sf::Color(100, 17, 17));
    }

    temperatura+=dT;
    if(temperatura>100 || temperatura<0){
        dT=-dT;
    }

    gravitar();
    pFig->setPosition(x, y - 9);
    y += vely;
}
void Lava::obstaculizar(Jogador* pJog) {
    if(danoso){
        pJog->operator--(2+danosidade/20);
    }
    pJog->forca_andar=0.8*pJog->forca_andar;
}
void Lava::obstaculizar(Inimigo* p){
}

void Lava::setSprite(){
    pSprite->setTexture(*pTexture);
	pSprite->setPosition(x, y-sizey+2);

	if (danoso) {
        pSprite->setTextureRect(sf::IntRect({ 0, 0 }, { (int)getSizex(), (int)getSizey() })); //se danoso, pega a parte de cima da imagem de textura (a parte clara)
	}
	else {
	    pSprite->setTextureRect(sf::IntRect({ 0, 16 }, { (int)getSizex(), (int)getSizey() }));//se não danoso, pega a parte de baixo (parte escura)
	}
}

std::string Lava::getTipo() {
    return "Lava";
}
