//
// Created by viniman on 6/26/18.
//

#ifndef TRABED2PART3_LZ77_H
#define TRABED2PART3_LZ77_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Triple.h"

using namespace std;

class LZ77
{
private:
    unsigned int dictLength;
    unsigned int bufferLength;



public:
    LZ77(unsigned int dictLength, unsigned int bufferLength);
    ~LZ77();
    vector<Triple> compress(string &origText);
    string decompressText(string &textCompressed);
    string decompressText(vector<Triple> &palavra);
    string tripleToString(vector<Triple> &textCode);
    string saveFile(vector<Triple> &tripleVect, string fileName);

};
#endif //TRABED2PART3_LZ77_H
