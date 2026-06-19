//Versão 30
//Sistema de save implementado (Salva APENAS se fechar com o X da janela)

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
