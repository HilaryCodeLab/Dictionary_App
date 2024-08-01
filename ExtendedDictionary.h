#pragma once
#ifndef EXTENDEDDICTIONARY_H
#define EXTENDEDDICTIONARY_H
#include "Dictionary.h"
#include <iostream>




class ExtendedDictionary :public Dictionary
{
public:
	Dictionary xDictionary;
	vector<string> listPalindromes();
	vector<string> rhymingWords();
	void guessFourthWord();
	void searchdle();



};


#endif // !ExtendedDictionary.h



