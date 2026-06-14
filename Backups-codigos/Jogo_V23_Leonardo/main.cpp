//Versao 22
//a construtora de projétil não recebe mais as coordenadas do chefão, uma vez que o projétil possui ponteiro para o chefão (a sobrecarga de construtora é mantida já que a construtora de projétil inclui o ponteiro do chefão agora)
//fase segunda não possui mais as variáveis de x e y do projétil
//ponteiro do chefão em projétil é protected (para respeitar o modelo uml)
//adicionado executar() do GC, funções de tratar colisão viraram privadas
//nomes de inimigos e obstáculos alterados. inimigo fácil=rato, inimigo médio=água, obstáculo médio=lama, obstáculo difícil=lava
//adicionada função colidir na classe jogador
//rebalanceados alguns danos de inimigos e obstáculos
//implementado o submenu para escrever o nome no ranking (não é mais na janela de console)
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
Chefao

criar função criarCenario() na fase abstrata

adicionar representações gráficas únicas

jogador 2
*/
