// Versão 12
// Alterações em relação a V11 - Pontos, colisões com obstáculo (jogador e inimigo), obstáculos,
// correção de valores que estavam mudando de int->float, float->int, float->size_t e etc. (n causa erro, mas fica warning)
// alterações de variáveis de velocidade e posição no jogador para melhor funcionalidade das colisões
// lista_entes.percorrer agora foi separado em percorrer e desenhar, para melhor funcionamento das colisões

#include "Principal.h"

int main()
{
    Jogo jogo;
    jogo.executar();

    return 0;
}
