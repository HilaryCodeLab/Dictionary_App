//This is the header file, it contains class specification

#ifndef WORD_H
#define WORD_H

#include <iostream>
#include <cstdio>
#include<fstream>
#include<string>
#include <regex>
#include <stdio.h>
#include <format>
using namespace std;

using std::cout;
using std::cin;
class Word {

private:
    string name;
    string type;
    string definition;

public:
    Word() {

    }

    Word(string wName, string wType, string wDefinition)
    {
        name = wName;
        type = wType;
        definition = wDefinition;
    }
    string getName()
    {
        return this->name;
    }
    void setName(string wName)
    {
        this->name = wName;
    }
    string getType()
    {
        return this->type;
    }
    void setType(string wType)
    {
        this->type = wType;
    }
    string getDefinition()
    {
        return this->definition;
    }
    void setDefinition(string wDefinition)
    {
        this->definition = wDefinition;
    }



};

#endif 