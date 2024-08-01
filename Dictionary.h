#pragma once
//Dictionary header file
#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "Word.h"
class Dictionary {
public:
    vector <Word> dictionary;

    //load dictionary file 
    void loadAndParseFile();
    void displayDictionary();
    void searchWord();
    bool hasThreeZ(string s);
    void findThreeZ();
    void wordTypeOptions();
    void addNewWord(vector<Word>dict);

};



#endif // !
