//Versão 26
//terminei de renomear chefão como dragão
//textura da lama trocada
//textura da plataforma ajustada para não ficar esticada
//plataformas agora têm altura e largura como múltiplos de 8, para ficar alinhado com a textura
//textura dos ratos troca de sentido corretamente
//aumentada altura do jogador de 50 para 55 (para ficar mais coerente com a textura)
//trocada textura das águias (e a textura foi posicionada corretamente na hitbox)
//adicionada textura do dragão (com uma versão diferente para quando leva dano)
//hitbox do dragão foi ajustada
//adicionada textura do projétil

#include "Principal.h"

int main()
{
    Jogo jogo;
    jogo.executar();

    return 0;
}
/*PARA FAZER:
mudar a textura do menu. do jeito atual ele começa sem textura nenhuma, e quando sai de uma fase o menu fica com a textura daquela fase.

mover checagem de posição pela função gravitar() para o GC?

crash quando fica aberto por muito tempo?
malloc: mismatching next->prev_size (unsorted)
Aborted (core dumped)
SAVES!

revisar código para remover funções desnecessárias, remover códigos antigos comentados, etc

*/
