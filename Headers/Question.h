
//
// Created by edson on 31/03/18.
//

#ifndef TRABALHO_ED2_QUESTION_H
#define TRABALHO_ED2_QUESTION_H

#include <iostream>
#include <string>

using namespace std;

class Question {
private:
    unsigned int questionId;
    unsigned int userId;
    int score;
    string date;
    string title;
public:
    Question() = default;
    Question(string* question);
    ~Question();
    void printComponents ();
    int getQuestionId() const;
    void setQuestionId(unsigned int questionId);

    bool operator<(const Question &rhs) const;
    bool operator>(const Question &rhs) const;
    bool operator<=(const Question &rhs) const;
    bool operator>=(const Question &rhs) const;
    friend ostream& operator <<(ostream &o, const Question &q);

    bool operator==(const Question &rhs) const;
    bool operator==(const int &rhs) const;


    bool operator!=(const Question &rhs) const;
    bool operator!=(const int &rhs) const;

    unsigned int getUserId() const;

};


#endif //TRABALHO_ED2_QUESTION_H
