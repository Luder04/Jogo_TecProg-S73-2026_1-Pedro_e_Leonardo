//Versao 21
//Criada função gravitar e implementada em todas as entidades
//Criada associação bidirecional entre chefe e projetil (ATENÇÃO, agora um chefe só pode atiarr 1 projétil por vez. Alterar UML para associação 1 pra 1)
//ObstaculizarInimigo alterado para sobrecarga de Obstaculizar
//Danificar de cada inimigo agora é único. Rato dá 1 de dano, Águia dá 1 + (rand()%5 de dano, 
//e o projetil chama o danificar de Chefao, que dá forca * nivel_maldade de dano / 10
//Nota: acho q será melhor mudar os nomes DEPOPIS de pegar os sprites, caso a gente n ache sprite de águia, rato e etc


#include "Principal.h"

int main()
{
    Jogo jogo;
    jogo.executar();

    return 0;
}

/*
PARA FAZER:
renomar classes de inimigos e obstáculos:
Rato
Voador
Chefao

Plataforma
Lama
Lava

*/
