//Versão 25.1
//adicionada textura única para o jogador 2, ajustada textura do jogador 1 (um pouco menos escura)
//textura do jogo vira quando o jogador muda de sentido
//lava fica escura quando não é danosa

#include "Principal.h"

int main()
{
    Jogo jogo;
    jogo.executar();

    return 0;
}
/*PARA FAZER:
melhorar textura e hitbox da águia
melhorar textura da lama?
adicionar textura do chefão
dar um nome para o chefão
mudar a textura do menu. do jeito atual ele começa sem textura nenhuma, e quando sai de uma fase o menu fica com a textura daquela fase.

mover checagem de posição pela função gravitar() para o GC?

crash quando fica aberto por muito tempo?
malloc: mismatching next->prev_size (unsorted)
Aborted (core dumped)
SAVES!*/
