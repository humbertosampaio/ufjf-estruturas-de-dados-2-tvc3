//
// Created by viniman on 6/26/18.
//

#include <map>
#include "../Headers/LZW.h"

LZW::LZW()
{
    dictionary.reserve(100000000);
    string s;
    index = 0;
    for (index; index < 256; index++)
    {
        s = (char)index;
        dictionary.insert(pair<string, unsigned int>(s, index));
    }
}

string LZW::compressText(string text)
{
    string str, strRet;
    str.push_back(text[0]);
    unordered_map<string,unsigned int>::iterator it;
    for (auto i = text.begin()+1; i != text.end(); ++i)
    {
        //cout << str << endl;
        it = dictionary.find(str+(*i));
        if (it != dictionary.end()) {
            str.push_back(*i);
            continue;
        }
        else {
            //cout << str << " ";
            //strRet += str + " ";
            str.push_back(*i);
            cout << str << " " << index << " " << endl;
            dictionary.insert(pair<string,unsigned int>(str, index++));
            str.clear();
            str.push_back(*i);
        }
    }
    int i = 256;
    while (i < dictionary.size())
    {
        for (auto &it : dictionary)
        {
            if (it.second == i) {
                ++i;
                //cout << it.first << endl;
            }
        }
    }
    strRet += str + " ";
    //cout << strRet;
    return strRet;
}

void LZW::compressQuestions(vector<Question> questionList)
{

    for (int i = 0; i < 100; ++i)
    {
        compressText(questionList[i].getBody());
        cout << i;
    }
    cout << dictionary.size();
}
