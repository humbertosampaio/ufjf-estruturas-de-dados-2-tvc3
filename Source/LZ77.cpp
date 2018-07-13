//
// Created by viniman on 6/26/18.
//

#include "../Headers/LZ77.h"



LZ77::LZ77(unsigned int dictLength, unsigned int bufferLength)
        : dictLength(dictLength), bufferLength(bufferLength) {}

LZ77::~LZ77() = default;


///Função que comprime um texto a partir de uma string e retorna uma vetor de triplas
vector<Triple> LZ77::compress(string &origText)
{
    /**
     * posDict: posicao relativa ao primeiro caracter da sequencia a codificar
     * size: quantidade de caracteres que a sequencia a codificar possui
     * Variaveis auxiliares de posDict e size para buscar a maior cadeia
     */
    vector<Triple> tripleVect;
    int posDictAux=0, posDict=0, size=0, sizeAux;
    for(int i = 0; i < origText.size(); ++i, posDictAux=posDict=size=0)
    {
        // Comprime a maior cadeia encontrada no dicionario
        // Para isso ele procura qual é essa cadeia
        while(i-posDictAux >= 0 && posDictAux <= this->dictLength)
        {
            sizeAux = 0;
            while(true)
            {
                // Se o tamanho do buffer tiver excedido, ou a proxima posicao a comparar difere
                // ou se a posicao do dicionario esta no inicio, sai do loop
                if(sizeAux > this->bufferLength || origText[i-posDictAux+sizeAux] != origText[i+sizeAux] || posDictAux == 0)
                    break;
                ++sizeAux;
            }

            // Tamanho da cadeia atual é maior que a anterior,
            // entao atualiza a posicao no dicionario e o tamanho da cadeia
            if(sizeAux > size)
            {
                posDict = posDictAux;
                size = sizeAux;
            }
            //enquanto o dicionario for grande o suficiente continua incrementando
            ++posDictAux;
        }

        // Atualiza o iterador da string, para o próximo caracter não codificado
        i += size;

        //Triple auxInserir(j, s, origText[i]);
        //tripleVect.push_back(auxInserir);
        tripleVect.emplace_back(posDict, size, origText[i]);
    }
    return tripleVect;
}


///Função que descomprime um texto a partir de uma string de códigos das triplas
/// caracter "|" usado para separar as triplas na string e arquivo
string LZ77::decompressText(string &textCompressed)
{
    string output;
    string aux;
    int triplaPosicao;
    int triplaTamanho;
    char triplaChar;
    int posOutput=0;
    for(int i = 0; i < textCompressed.size(); i++)
    {
        i++;
        aux = "";
        while(textCompressed[i] != ',')
            aux += textCompressed[i++];
        triplaPosicao = atoi(aux.c_str());
        i++;
        aux = "";
        while(textCompressed[i] != ',')
            aux += textCompressed[i++];
        triplaTamanho = atoi(aux.c_str());
        i++;
        triplaChar = i < textCompressed.size()-1 ? textCompressed[i++] : textCompressed[i];
        int posAux = posOutput-triplaPosicao;
        for (int j = 0; j < triplaTamanho; ++j)
        {
            output += output[posAux];
            ++posOutput;
            ++posAux;
        }
        output += triplaChar;
        ++posOutput;
    }
    return output;
}

///Função que descomprime um texto a partir de um vetor de triplas
string LZ77::decompressText(vector<Triple> &tripleVect)
{
    string output;
    int posOutput=0;
    for (auto &itTriple : tripleVect)
    {
        int posAux = posOutput - itTriple.p;
        for (int j = 0; j < itTriple.l; ++j)
        {
            output += output[posAux];
            ++posOutput;
            ++posAux;
        }
        output += itTriple.c;
        ++posOutput;
    }
    return output;
}


string LZ77::saveFile(vector<Triple> &tripleVect, string fileName)
{
    string str = tripleToString(tripleVect);
    ofstream outFile(fileName);
    if(outFile)
    {
        outFile << str;
        outFile.close();
    }
    return str;
}

string LZ77::tripleToString(vector<Triple> &textCode){
    string str;
    for (auto &it : textCode)
        str += "|" + to_string(it.p) + "," +  to_string(it.l) + "," + it.c + "|";
    return str;
}
