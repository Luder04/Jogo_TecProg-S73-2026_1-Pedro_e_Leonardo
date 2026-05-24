#pragma once

#include "Ente.h"
#include "Principal.h"

class Menu : public Ente {
private:
    Jogo* pJog;
    Gerenciadores::GerenciadorColisoes GC;

public:
    Menu();
    ~Menu();

    void setJogo(Jogo* j);
    void executar();

};

