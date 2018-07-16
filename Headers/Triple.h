//
// Created by viniman on 7/13/18.
//

#ifndef TRABALHO_ED2_3_TRIPLE_H
#define TRABALHO_ED2_3_TRIPLE_H


class Triple
{
public:
    int p; // Posição do inicio da maior cadeia no dicionario (pos relativa a parte do texto que ja foi decodificado
    int l; // Comprimento da maior cadeia/sequencia encontrada no dicionario
    char c; // Primeiro caracter da janela futura após o fim da cadeia comprimida


    Triple(int p, int l, char c) : p(p), l(l), c(c) {}
    Triple() = default;
    ~Triple() = default;

};


#endif //TRABALHO_ED2_3_TRIPLE_H
