//Versao 20
//corrigido bug que fazia crashar na fase 2 (eu tinha esquecido de colocar para limpar a lista de projéteis)
//começo da implementação do ranking (por enquanto tem que digitar o nome pela janela de console)

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


Criar atributo voador nas entidades. Uma entidade voadora vai ter uma força igual à gravidade empurrando para cima.

Mover(x,y) pode ter sobrecarga como mover(x) (ideia)

*/
