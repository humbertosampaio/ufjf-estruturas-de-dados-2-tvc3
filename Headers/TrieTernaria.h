#ifndef TRIETERNARIA_H
#define TRIETERNARIA_H
#include <string>
#include <iostream>
#include "No_Ter.h"

using namespace std;

class TrieTernaria
{
    public:
        TrieTernaria();
        void insere(string palavra);
        void imprime();
        unsigned long int busca(string palavra);
        void remover(string palavra);
        No_Ter **getRaiz();
        ~TrieTernaria();
    private:
        No_Ter *raiz;
        bool removerAux(string palavra, No_Ter* no);
        No_Ter* insereAux(No_Ter* no, string palavra);
        void imprimeAux(No_Ter* no, string palavra);
        unsigned long int buscaAux(No_Ter* no , string palavra);
        void deletaArvore(No_Ter* no);
};

#endif // TRIETERNARIA_H
