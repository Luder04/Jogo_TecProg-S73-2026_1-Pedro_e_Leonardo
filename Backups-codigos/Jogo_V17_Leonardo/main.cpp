//Versao 17
//Adicionado obstáculo médio (lama, deixa o jogador lento)
//O inimigo fácil agora é um círculo (já que o tamanho dele é definido como um raio). Classe ente foi ajustada para permitir isso.
//Ajustadas fórmulas de spawn dos inimigos e obstáculos (o obstáculo 1 pode ser paredes verticais ou plataformas aéreas horizontais)
//O GC, quando detecta colisão entre jogador e obstáculo, agora chama a função obstaculizar do obstáculo, a qual trata do que deve ser feito quando essa colisão ocorre
//Adicionada função destrutora do menu (deleta todos os submenus e botões criados dinamicamente)
//É possível voltar ao menu apertando esc
//Pontuação do jogador é resetada ao voltar ao menu (por morte ou apertando esc).

#include "Principal.h"

int main()
{
    Jogo jogo;
    jogo.executar();

    return 0;
}
