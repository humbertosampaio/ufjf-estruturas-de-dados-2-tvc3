#include "../Headers/LZ78.h"
#include <iostream>
#include <string>
#include <chrono>

using namespace std;

string LZ78::compress(string &text)
{
	clock_t tStart = clock();

	this->lastCompressDicIndex = 1;
	this->compressDictionary.reserve(MAX_DICTIONARY_SIZE);
	char c;
	string tempStr, encodedStr;
	unsigned int strCode;

	int index = 0;

	auto strIt = text.begin();
	while (strIt != text.end())
	{
		c = (*strIt);
		auto dicIt = compressDictionary.find(tempStr + c);

		if (dicIt != compressDictionary.end()) // Já existe no Dicionário
		{
			tempStr += c;
		}
		else
		{
			encodedStr += getEncodedSequence(tempStr, string(1, c));
			compressDictionary.insert({(tempStr + c), lastCompressDicIndex++});
			tempStr.clear();
		}

		strIt++;

		++index;
		if (index % 1000000 == 0)
			cout << "Compactacao: " << index << " / " << text.length() << " caracteres processados\r";
	}

	if (tempStr != "")
	{
		encodedStr += getEncodedSequence(tempStr, "");
	}

	cout << endl << "Tempo gasto na compressao: " << (double)(clock() - tStart) / CLOCKS_PER_SEC << "s" << endl << endl;

	compressDictionary.clear();
	return encodedStr;
}

string LZ78::getEncodedSequence(string tempString, string nextChar)
{
	auto it = compressDictionary.find(tempString);
	unsigned int strCode = it == compressDictionary.end() ? 0 : (*it).second;
	
	if (isNumeric(nextChar))
		nextChar = NUMERIC_SEPARATOR + nextChar + NUMERIC_SEPARATOR;

	return (to_string(strCode) + nextChar);
}

string LZ78::decompress(string &encodedText)
{
	clock_t tStart = clock();

	this->lastDecompressDicIndex = 1;
	this->decompressDictionary.reserve(MAX_DICTIONARY_SIZE);
	auto strIt = encodedText.begin();
	string strDicCode, decodedString;
	string c;

	int index = 1;

	while (strIt != encodedText.end())
	{
		while (strIt != encodedText.end() && isNumeric(*strIt))
		{
			strDicCode += *strIt;
			strIt++;
		}

		while (strIt != encodedText.end() && !isNumeric(*strIt))
		{
			c += *strIt;
			strIt++;
		}

		if (c == NUMERIC_SEPARATOR)
		{
			c.clear();

			while (strIt != encodedText.end() && isNumeric(*strIt) && (*strIt) != NUMERIC_SEPARATOR[0])
			{
				c += *strIt;
				strIt++;
			}

			++strIt;
			++strIt;
		}

		decodedString += getDecodedSequence(strDicCode, c);

		strDicCode.clear();
		c.clear();

		++index;
		if (index % 1000000 == 0)
			cout << "Descompactacao: " << index << " / " << encodedText.length() << " caracteres processados\r";
	}

	cout << endl << "Tempo gasto na descompressao: " << (double)(clock() - tStart) / CLOCKS_PER_SEC << "s" << endl << endl;

	decompressDictionary.clear();
	return decodedString;
}

string LZ78::getDecodedSequence(string strDictionaryCode, string nextCharSequence)
{
	unsigned int key = toUnsignedInt(strDictionaryCode);
	string decodedString;
	if (key != 0) // Já existe no Dicionário
	{
		string value = (*decompressDictionary.find(key)).second;
		string newDicEntry = value + nextCharSequence;
		decompressDictionary.insert({lastDecompressDicIndex++, newDicEntry});
		return newDicEntry;
	}
	else
	{
		decodedString += nextCharSequence;
		decompressDictionary.insert({lastDecompressDicIndex++, nextCharSequence});
		return decodedString;
	}
}

bool LZ78::isNumeric(string s)
{
	if (s == "")
		return false;

	bool numeric = true;
	for (short i = 0; i < s.length(); ++i)
		if (!isNumeric(s[i]))
			return false;
	return numeric;
}

bool LZ78::isNumeric(char c)
{
	int ascii = (int)c;
	return ascii > 47 && ascii < 58;
}

unsigned int LZ78::toUnsignedInt(string number)
{
	int result = 0, temp = 0;
	for (int i = 0; i < number.size(); i++)
	{
		result *= 10;
		result += (int)((number[i]) - '0');
	}

	return result;
}
