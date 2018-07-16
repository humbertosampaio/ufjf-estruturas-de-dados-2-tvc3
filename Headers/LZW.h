//
// Created by viniman on 6/26/18.
//

#ifndef TRABED2PART3_LZW_H
#define TRABED2PART3_LZW_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include "Question.h"
#include "TrieTernaria.h"

using namespace std;

class LZW {

public:
    LZW();
    ~LZW() = default;
    string compressText(string text);
    void compressQuestions(vector<Question> questionList);

private:
    unordered_map<string, unsigned int> dictionary;
    TrieTernaria _dictionary;
    unsigned int index;

};


#endif //TRABED2PART3_LZW_H
