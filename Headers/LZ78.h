#ifndef TRABED2PART3_LZ78_H
#define TRABED2PART3_LZ78_H

#include <unordered_map>

using namespace std;

class LZ78
{
	public:
	LZ78() = default;
	~LZ78() = default;
	string compress(string &text);
	string decompress(string &encodedText);
	
	private:
	unordered_map<string, unsigned int> compressDictionary;
	string getEncodedSequence(string tempString, string nextChar);
	unsigned int lastCompressDicIndex;

	unordered_map<unsigned int, string> decompressDictionary;
	string getDecodedSequence(string strDictionaryCode, string nextCharSequence);
	unsigned int lastDecompressDicIndex;

	const string NUMERIC_SEPARATOR = "~¨";
	const int MAX_DICTIONARY_SIZE = 58132624; // Tamanho máximo que o arquivo Questions.csv ocupa
	bool isNumeric(char c);
	bool isNumeric(string s);
	unsigned int toUnsignedInt(string number);
};


#endif //TRABED2PART3_LZ78_H
