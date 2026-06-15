//Versão 25
//Adicionado jogador 2
//adicionado novos submenus para poder jogar com 1 ou 2 jogadores
//Jogadores são adicionados quando a fase é iniciada (não pela classe jogo)
//limpar lista de entidades agora tira também o jogador (só não desaloca ele--isto é feito no menu)
//gerenciadores, fases, etc foram todos ajustados para permitir dois jogadores

#include "Principal.h"

int main()
{
    Jogo jogo;
    jogo.executar();

    return 0;
}
//PARA FAZER:
//SAVES!
