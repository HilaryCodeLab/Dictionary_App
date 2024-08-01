// Dictionary_App.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Soong_10591936.cpp : This file contains the 'main' function. Program execution begins and ends there.
// author: Hilary See Ting Soong 
// student ID: 10591936
// created on: 18/04/2023
//

#include <iostream>
#include <cstdio>
#include<fstream>
#include<string>
#include <regex>
#include <stdio.h>
#include <format>
#include "Word.h"
#include "Dictionary.h"
#include "ExtendedDictionary.h"

using namespace std;

using std::cout;
using std::cin;

// template for the menu for the beginning of the program
void intro() {
    string menuInstruction = "Please type a number of task from the options below: ";
    string op1 = "[1] : Load and Parse dictionary file";
    string op2 = "[2] : Search a word";
    string op3 = "[3] : Find all words that contains more than 3 'z' characters";
    string op4 = "[4] : Add a word to the dictionary";
    string op5 = "[5] : Palindromes";
    string op6 = "[6] : Rhyming Words";
    string op7 = "[7] : Guess the forth word";
    string op8 = "[8] : Searchdle";
    string op0 = "[0] : exit";
    cout << menuInstruction << endl;
    cout << op1 << endl;
    cout << op2 << endl;
    cout << op3 << endl;
    cout << op4 << endl;
    cout << op5 << endl;
    cout << op6 << endl;
    cout << op7 << endl;
    cout << op8 << endl;
    cout << op0 << endl;
}

// display menu option and prompt user to enter task to performm
void selectMenuOption() {
    string defaultFile = "dictionary_2023S1.txt";
    char input;
    auto* userInput = &input;
    Word newWord;
    vector<Word>dictionary;
    string fileOption;
    string userFile;
    //Dictionary dict;
    ExtendedDictionary dict;
    intro();

    // prompt user to make a choice from the menu
    cin >> *userInput;

    // using while loop to keep menu option appearred each time a task is finished
    while (true) {
        switch (*userInput) {
        case '1':
            //dict.displayDictionary();
            dict.loadAndParseFile();
            break;

        case '2':
            // this function allow user to find word from dictionary 
            dict.searchWord();
            break;

        case '3':
            cout << "Find all words that has 3 z" << endl;
            // this function will find all the words with has three or more z.
            dict.findThreeZ();
            break;

        case '4':
            // this function will allow user to add new word to dictionary file 
            dict.addNewWord(dictionary);
            break;

        case '5':
            dict.listPalindromes();
            break;

        case '6':
            dict.rhymingWords();
            break;

        case '7':
            cout << "************************ Welcome to Guess the Fourth Word! ************************" << endl;
            dict.guessFourthWord();
            break;

        case '8':
            dict.searchdle();
            break;

        case '0':
            //this allow user to exit the program
            system("pause");
            break;

        default:
            // this display error if input is incorrect
            cout << "Invalid Input. Must be 1-4" << endl;

        }

        // keep menu display all the time
        intro();

        // keep prompting user what they wish to do from the menu
        cin >> *userInput;

    }

}

int main()
{
    selectMenuOption();


}





