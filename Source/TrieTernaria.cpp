#include "../Headers/TrieTernaria.h"

unsigned long int No_Ter::dicionarioCounter = 0;

TrieTernaria::TrieTernaria()
{
    raiz = NULL;
}
unsigned long int TrieTernaria::busca(string palavra){
    //cout << "Buscando a palavra " << palavra<< "... ";
    unsigned long int achou = buscaAux(raiz, palavra);
    /*
    if(achou){
        cout << "encontrado!" << endl;
    }else{
        cout << "NAO encontrado!" << endl;
    }
     */
    return achou;
}
unsigned long int TrieTernaria::buscaAux(No_Ter* no, string palavra){
    if(no == NULL) return false;
    char caractere = palavra.at(0);

    if(caractere == no->getChar()){
        if(palavra.size() == 1){
            if(no->getChave()){
                return no->getChaveDicionario();
            }else{
                return false;
            }
        }else{
            return buscaAux(no->getMeio(),palavra.substr(1,palavra.size()));
        }
    }else{
        if(caractere > no->getChar()){
            return buscaAux(no->getDir(),palavra);
        }else{
            return buscaAux(no->getEsq(),palavra);
        }
    }
}
void TrieTernaria::insere(string palavra){
    raiz = insereAux(raiz,palavra);
}
No_Ter* TrieTernaria::insereAux(No_Ter* no, string palavra){
    char caractere = palavra.at(0);
    if(no == NULL){
        no = new No_Ter();
        no->setChar(caractere);
    }
    if(caractere > no->getChar()){
        no->setDir(insereAux(no->getDir(),palavra));
    }else if(caractere < no->getChar()){
        no->setEsq(insereAux(no->getEsq(),palavra));
    }else{
        if(palavra.size() == 1){
            no->setChave(true);
            no->setDicionario();
        }else{
            no->setMeio(insereAux(no->getMeio(),palavra.substr(1,palavra.size())));
        }
    }
    return no;
}
void TrieTernaria::imprime(){
    imprimeAux(raiz,"");
}
void TrieTernaria::imprimeAux(No_Ter* no, string palavra){
    if(no == NULL) return;
    if(no->getChave() && no->getChaveDicionario() > 255){
        cout << palavra << no->getChar() << "\t" << no->getChaveDicionario() << endl;
    }
    imprimeAux(no->getEsq(),palavra);
    imprimeAux(no->getMeio(),(palavra+no->getChar()));
    imprimeAux(no->getDir(),palavra);
}
void TrieTernaria::remover(string palavra){
    if(palavra.empty()) return;
    removerAux(palavra, raiz);
}
bool TrieTernaria::removerAux(string palavra, No_Ter* no){
    if(no == NULL) return true;
    char caractere = palavra.at(0);
    if(palavra.size() > 1){
        if(caractere == no->getChar()){
            if(removerAux(palavra.substr(1,palavra.size()),no->getMeio())){
                no->setMeio(NULL);
            }
        }else if (caractere > no->getChar()){
            if(removerAux(palavra,no->getDir())){
                no->setDir(NULL);
            }
        }else{
            if(removerAux(palavra,no->getEsq())){
                no->setEsq(NULL);
            }
        }
    }else{
        if(no->getChave()){
            if(caractere == no->getChar()){
                // encontrou a palavra
                no->setChave(false);
            }
        }
    }
    if(no->getChave() == false &&
       no->getEsq() == NULL &&
       no->getDir() == NULL &&
       no->getMeio() == NULL){
        delete no;
        return true;
    }else{
        return false;
    }
}
No_Ter** TrieTernaria::getRaiz(){

    return &raiz;

}
TrieTernaria::~TrieTernaria(){
    if(raiz == NULL) return;
    deletaArvore(raiz);
}
void TrieTernaria::deletaArvore(No_Ter* no){
    if(no->getEsq() != NULL) deletaArvore(no->getEsq());
    if(no->getDir() != NULL) deletaArvore(no->getDir());
    if(no->getMeio()!= NULL) deletaArvore(no->getMeio());
    delete no;
}
