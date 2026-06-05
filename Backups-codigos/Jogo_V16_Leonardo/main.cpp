//Versao 16
//O percorrer da lista não desenha os objetos mais. Os objetos são desenhados por uma função desenhar, que é chamada após o GC no executar da fase. Isso corrige um bug visual do jogador atravessar outros objetos.
//Adicionado botão de fechar o jogo no menu.
//Fechar a janela do jogo agora fecha o programa.
//Na classe principal, foi adicionado suporte para voltar ao menu após fechar uma fase.
//Se o jogador perder todas as vidas, volta ao menu. É possível começar um novo jogo normalmente (foi muito trabalhoso corrigir todos os bugs para isso funcionar).
//Limpar fase agora limpa não só a lista de entidades, mas também as listas de inimigos e obstáculos no GC.
//Alterações diversas em menu, fases, listas para corrigir bugs...

#include "Principal.h"

int main()
{
    Jogo jogo;
    jogo.executar();

    return 0;
}
