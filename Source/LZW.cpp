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
        dictionary.insere(s);
    }
}

string LZW::compressText(string text)
{
    string str, strRet;
    str.push_back(text[0]);
    unsigned long int dictionaryId;
    for (auto i = text.begin()+1; i != text.end(); ++i)
    {
        dictionaryId = dictionary.busca(str+(*i));
        if (dictionaryId) {
            str.push_back(*i);
            continue;
        }
        else {
            strRet += to_string(dictionary.busca(str)) + " ";
            str.push_back(*i);
            dictionary.insere(str);
            str.clear();
            str.push_back(*i);
        }
    }
    return strRet;
}

void LZW::compressQuestions(vector<Question> questionList, string savePath)
{
    ofstream a;
    a.open(savePath, ios_base::app);
    for (int i = 0; i < questionList.size(); ++i)
    {
        a << compressText(questionList[i].getBody());
        if (i%1000 == 0)
            cout << i << endl;
    }
    a.close();
}
