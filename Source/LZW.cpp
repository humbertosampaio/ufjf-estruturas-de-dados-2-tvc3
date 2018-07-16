//
// Created by viniman on 6/26/18.
//

#include <map>
#include "../Headers/LZW.h"

LZW::LZW()
{
    string s;
    index = 0;
    for (index; index < 256; index++)
    {
        s = (char)index;
        _dictionary.insere(s);
    }
}

void LZW::compressText(string text)
{
    string str, strRet;
    str.push_back(text[0]);
    unordered_map<string,unsigned int>::iterator it;
    unsigned long int dictionaryId;
    for (auto i = text.begin()+1; i != text.end(); ++i)
    {
        dictionaryId = _dictionary.busca(str+(*i));
        if (dictionaryId) {
            str.push_back(*i);
            continue;
        }
        else {
            strRet += to_string(_dictionary.busca(str)) + " ";
            str.push_back(*i);
            _dictionary.insere(str);
            str.clear();
            str.push_back(*i);
        }
    }
}

void LZW::compressQuestions(vector<Question> questionList)
{

    for (int i = 0; i < questionList.size(); ++i)
    {
        compressText(questionList[i].getBody());
        cout << i << endl;
    }
    cout << dictionary.size();
}
