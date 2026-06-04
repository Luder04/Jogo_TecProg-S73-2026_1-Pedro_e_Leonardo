// Versão 15
// Colisões alteradas para utilizar o "verificarColisão"
// Sistema de save exporta os arquivos corretamente (ainda n tem opção de obter o save, continuar no caso)
// Melhorias no sistema de delete de entidades: fase1 deleta ao entrar na fase 2, ambas fases deletam ao sair do jogo, e prints mais específicos sobre o que foi deletado
// Prints sobre qual ente foi criado e seu respectivo Id
// Print relativo aos saves (sem muita descrição)

#include "Principal.h"

int main()
{
    Jogo jogo;
    jogo.executar();

    return 0;
}
