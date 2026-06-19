//Versão 29
//Adicionada variável bool movel para plataformas. Plataformas verticais têm 50% de chance de serem móveis.
//Adicionada função esmagar jogador para plataformas (para caso o jogador ficar embaixo da plataforma movel)
//Adicionado parâmetro altitude nas águias. Se a plataforma empurrar a águia para cima, a águia volta para sua altitude original.
//Jogador fica com textura diferente quando recebe dano.
//Danificar do rato agora empurra o jogador para o lado certo (dependendo da direcao do rato).
//Textura da lama muda de tamanho conforme ela fica mais ou menos viscosa.
//checagem de colisão com o chão feito pelo GC agora (algumas novas funções adicionadas).

#include "Principal.h"

int main()
{
    Jogo jogo;
    jogo.executar();

    return 0;
}
/*PARA FAZER:
ratos (e raramente águias) vão para cima da plataforma quando colidem com ela por baixo. será que deve ficar assim?

mudar a textura do menu. do jeito atual ele começa sem textura nenhuma, e quando sai de uma fase o menu fica com a textura daquela fase.

crash quando fica aberto por muito tempo?
malloc: mismatching next->prev_size (unsorted)
Aborted (core dumped)
SAVES!

revisar código para remover funções desnecessárias, remover códigos antigos comentados, etc

*/
