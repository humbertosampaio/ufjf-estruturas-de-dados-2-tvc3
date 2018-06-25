#ifndef TRABALHO_3_CHARFREQUENCYPAIR_H
#define TRABALHO_3_CHARFREQUENCYPAIR_H

#include <string>

using namespace std;

class CharPathPair
{
	public:
	CharPathPair(char c);
	CharPathPair(char c, string path);
	string getPath();
	char getChar();

	bool operator<(const CharPathPair &rhs) const;

	private:
	char c;
	string p;
};

#endif