#pragma once

// Para usar templates não foi possível separar o .h do .cpp. Estudar mais o porquê, pois já me esqueci

namespace Entidades {
    class Entidade;
}
using namespace Entidades;

namespace Listas {

    template <typename TL>
    class Lista {

    public:
        template <typename TE>
        class Elemento {
        private:
            Elemento<TE>* pProx;
            TE* pInfo;
        public:
            Elemento() : pProx(NULL), pInfo(NULL) {}
            ~Elemento() { pProx = NULL; pInfo = NULL; }
            void incluir(TE* p) { pInfo = p; }
            void setProx(Elemento<TE>* pE) { pProx = pE;  }
            const Elemento<TE>* getProximo() const { return pProx;  }
            TE* getInfo() const { return pInfo; }

        };

    private:
        Elemento<TL>* pPrimeiro;
        Elemento<TL>* pUltimo;

    public:
        Lista() : pPrimeiro(NULL), pUltimo() {}
        ~Lista() { limpar(); }
        void incluir(TL* p) {
            if (!p) return;
            Elemento<TL>* novoElemento = new Elemento<TL>();
            novoElemento->incluir(p);

            if (pPrimeiro == NULL) {
                pPrimeiro = novoElemento;
                pUltimo = novoElemento;
            }
            else {
                pUltimo->setProx(novoElemento);
                pUltimo = novoElemento;
            }
        }
        void limpar() {
            Elemento<TL>* atual = pPrimeiro;
            while (atual != NULL) {
                Elemento<TL>* proximo = const_cast<Elemento<TL>*>(atual->getProximo());
                delete atual;
                atual = proximo;
            }
            pPrimeiro = NULL;
            pUltimo = NULL;
        }
        void remover(TL* p) {
            if (p == NULL || pPrimeiro == NULL) return;

            Elemento<TL>* atual = pPrimeiro;
            Elemento<TL>* anterior = NULL;

            while (atual != NULL && atual->getInfo() != p) {
                anterior = atual;
                atual = const_cast<Elemento<TL>*>(atual->getProximo());
            }

            if (atual != NULL) {
                if (atual == pPrimeiro) {
                    pPrimeiro = const_cast<Elemento<TL>*>(atual->getProximo());
                }
                else {
                    anterior->setProx(const_cast<Elemento<TL>*>(atual->getProximo()));
                }

                if (atual == pUltimo) {
                    pUltimo = anterior;
                }

                delete p;
                delete atual;
            }
        }

        Elemento<TL>* getPrimeiro() { return pPrimeiro; }
    };

    class ListaEntidades {
    private:
        Lista<Entidade> LEs;
        Jogador* pJog1;

    public:
        ListaEntidades() : LEs(), pJog1(NULL) {}
        ~ListaEntidades() {}
        void incluir(Entidade* pE) { LEs.incluir(pE); }
        void setJogador(Jogador* pJ) { pJog1 = pJ; }
        void percorrer() {
            const Lista<Entidade>::Elemento<Entidade>* pAux = LEs.getPrimeiro();

            while (pAux != NULL) {
                const Lista<Entidade>::Elemento<Entidade>* pProximo = pAux->getProximo();

                Entidade* pEntidade = const_cast<Lista<Entidade>::Elemento<Entidade>*>(pAux)->getInfo();

                if (pEntidade != NULL) {
                    if (pEntidade->getVidas() > 0 ||  pEntidade->getObs() == true ) {
                        pEntidade->executar();
                    }
                    else if (pEntidade == pJog1) {
                        std::cout << "Jogador morreu! Telas de Game Over devem rodar aqui." << std::endl;
                    }
                    else {

                        std::cout << "Inimigo morto ignorado no desenho!" << std::endl;
                        LEs.remover(pEntidade);
                    }

                }
                pAux = pProximo;
            }
        }
        void desenhar() {
            const Lista<Entidade>::Elemento<Entidade>* pAux = LEs.getPrimeiro();

            while (pAux != NULL) {
                const Lista<Entidade>::Elemento<Entidade>* pProximo = pAux->getProximo();

                Entidade* pEntidade = const_cast<Lista<Entidade>::Elemento<Entidade>*>(pAux)->getInfo();

                if (pEntidade != NULL) {
                    if (pEntidade->getVidas() > 0 || pEntidade->getObs() == true) {
                        pEntidade->desenhar();
                    }

                }
                pAux = pProximo;
            }
        }
    };
}
