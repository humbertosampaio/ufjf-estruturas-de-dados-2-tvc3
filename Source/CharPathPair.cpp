#include "../Headers/CharPathPair.h"

bool CharPathPair::operator<(const CharPathPair &rhs) const
{
	return c < rhs.c;
}

CharPathPair::CharPathPair(char c)
{
	this->c = c;
	this->p = "";
}

CharPathPair::CharPathPair(char c, string path)
{
	this->c = c;
	this->p = path;
}

std::string CharPathPair::getPath()
{
	return p;
}

char CharPathPair::getChar()
{
	return c;
}
