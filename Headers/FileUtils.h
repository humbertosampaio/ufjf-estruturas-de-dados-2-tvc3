//
// Created by edson on 28/03/18.
//

#ifndef TRABALHO_ED2_FILEUTILS_H
#define TRABALHO_ED2_FILEUTILS_H

#include <iostream>
#include <fstream>
#include <exception>
#include <vector>
#include <ctime>
#include <string>
#include <iomanip>
#include <limits>
#include "Question.h"
#include <iostream>
#include <limits>
#include <random>
#include <chrono>

using namespace std;

class FileUtils
{
public:
    static void clearFileContent(string path);
    static vector<int> readInputFile(string path);
    static void readFileQuestion(string path, vector<Question> &questionList);
    static void writeToOutputFile(const string &outputFileName, const string &text, bool append);
    static void endProgram();
    static void pauseScreen(bool continuar);
    static void showTop();
};

#endif //TRABALHO_ED2_FILEUTILS_H
