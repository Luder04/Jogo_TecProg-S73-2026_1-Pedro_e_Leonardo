#pragma once

namespace Listas {
    template <typename TL>
    class Lista{
    private:
        *Elemento<TL> pPrimeiro;
        *Elemento<TL> pUltimo;
    private:
        template <typename TE>
        class Elemento {
        private:
            *Elemento<TE> pProx;
            *TE pinfo;
        public:
            Elemento();
            ~Elemento();
            void incluir(*TE p);
            void setProx(*Elemento<TE> pE);
            const *Elemento<TE> getProximo();

        };

    protected:

    public:
        Lista();
        ~Lista();
        void incluir(TL* p);
        void limpar();
    };

    class ListaEntidades{
    private:
        lista<Entidade> LEs;

    public:
        ListaEntidades();
        ~ListaEntidades();
        void incluir(*Entidade pE);
        void percorrer();
    };
}

