#include "ExtendedDictionary.h"
#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <sstream>
#include <numeric>
#include <list>

using namespace std;

/**
 * this function will return a list of palindromes found in the dictionary list.
 *
 * \return vector<string>
 * \author Hilary Soong
 * \date   7 May 2023
 */
vector<string> ExtendedDictionary::listPalindromes()
{
	vector<string> palindromeList;
	//Dictionary::loadAndParseFile_2(xDictionary.dictionary);
	//auto dictList = xDictionary.dictionary;
	if (dictionary.size() > 0) {
		for (auto item : dictionary) {

			auto copyItem = item.getName();

			reverse(copyItem.begin(), copyItem.end());
			if (item.getName() == copyItem) {
				palindromeList.push_back(copyItem);
			}
		}
		for (auto p : palindromeList) {
			cout << p << endl;
		}
	}
	else {
		cout << "List is empty. Uploading dictionary is neccessary" << endl;
	}


	return palindromeList;
}

/**
 * this function will return words that have similar last three letters as the user's word.
 *
 * \return vector <string>
 * \author Hilary Soong
 * \date   7 May 2023
 */
vector<string> ExtendedDictionary::rhymingWords()
{
	vector<string> rhymingWords;
	string userInput;
	cout << "enter a word: \n" << endl;
	//catch user word
	cin >> userInput;

	if (userInput.length() >= 3) {
		//check if the dictionary is loaded
		if (dictionary.size() > 0) {
			for (auto item : dictionary) {
				auto wordName = item.getName();
				//check the word length make sure to catch the word that has length more than 3
				if (wordName.length() >= 3) {
					//store the substring of last three letters of the dictionary word and the user input word
					string wn = wordName.substr(wordName.length() - 3);
					string ui = userInput.substr(userInput.length() - 3);
					// check if they match
					if (ui == wn) {
						// add the words that have same last 3 substrings to a vector
						rhymingWords.push_back(wordName);
					}

				}

			}
			if (rhymingWords.size() > 0) {
				for (auto r : rhymingWords) {
					cout << r << endl;
				}
			}
			else {
				cout << "no words found" << endl;
			}

		}
		else {
			cout << "List is empty. Uploading dictionary is neccessary" << endl;
		}



	}
	else {
		cout << "invalid input. please enter word that has at least 3 letters." << endl;
	}



	return rhymingWords;
}

/**
 * this function is designed for game that gets user to guess the fourth word of the word definition,
 * and keep the highest score to the program, user will be prompted with next question if answer correctly otherwise
 * it will display user's score and end the game then return to the main menu.
 *
 * \author Hilary Soong
 * \date   9 May 2023
 */
void ExtendedDictionary::guessFourthWord()
{
	int highestScore = 0;
	int playerScore = 0;
	//1.welcome player, print the current high score

	//check if there is existing score file
	string line;
	fstream scoreFile("highest_score.txt");
	if (scoreFile.is_open()) {
		while (getline(scoreFile, line)) {
			cout << line << endl;
		}
		scoreFile.close();
	}
	// if no score file is found, write one
	else
	{
		scoreFile.open("highest_score.txt");
		highestScore = 0;
		scoreFile << "current highest score is " + to_string(highestScore) << endl;
		scoreFile.close();

	}

	vector<Word> defiList;
	string rand;
	string guess;
	string answer;
	bool gameOn = true;
	//2.choose a random word from dictionary that has more than four words in definition
	if (dictionary.size() > 0) {
		for (auto el : dictionary) {
			auto wordName = el.getName();
			auto wordDefi = el.getDefinition();
			auto lenDefi = wordDefi.size();
			int words = 0;
			for (int i = 0; i < lenDefi; i++) {
				//if there is a space in word definition, it means another word is forming
				if (wordDefi[i] == ' ') {
					words++;
				}
			}
			words += 1;
			if (words > 4) {
				//wNameList.push_back(wordName);
				defiList.push_back(el);
			}
		}
		while (gameOn) {
			//pick a random definition from the definition list
			random_device rd;
			mt19937 gen{ rd() };

			for (int i{}; i != 1; ++i) {
				shuffle(defiList.begin(), defiList.end(), gen);

				//print out word and definition on the console
				cout << defiList[i].getName() << endl;
				rand = defiList[i].getDefinition();
			}

			//3.print the word and definition in which the fourth word is replaced by underscores.

			string str;
			vector<string> definition;
			stringstream ss(rand);
			//split the string into individual strings 
			while (getline(ss, str, ' ')) {

				definition.push_back(str);
			}
			//change the fourth words to underscores.
			answer = definition[3];
			definition[3] = "___";
			ostringstream result_stream;
			ostream_iterator< std::string > oit(result_stream, " ");
			copy(definition.begin(), definition.end(), oit);

			string strDefi = result_stream.str();
			cout << strDefi << endl;
			cout << "your guess? \n" << endl;

			cin >> guess;

			//4.if player guess the missing word, print 'congrats' then continue the guessing game with new word.

			if (guess == answer) {

				cout << "Congratulations! Your answer is correct!" << endl;
				// add 10 points to each correct answer
				playerScore += 10;



			}
			//4a.if player guess incorrectly, print the player score and game finishes.
			else {
				cout << "Wrong answer. Your score is " + to_string(playerScore) << endl;
				gameOn = false;


			}

		}
		//update the score if there is new high score
		//program save the current highest scores to a file
		if (playerScore > highestScore) {
			ofstream updateFile;
			highestScore = playerScore;
			updateFile.open("highest_score.txt");
			updateFile << "current highest score is " + to_string(highestScore) << endl;
			updateFile.close();

		}


	}
	else {
		cout << "List is empty. Uploading dictionary is neccessary" << endl;
	}


}

/**
 * This function will allow user to cheat at searchdle by looking up words
 * that contains a set of the game rules for the mystery word.
 *
 * \author Hilary Soong
 * \date   14 May 2023
 */
void ExtendedDictionary::searchdle()
{
	vector <string> words;
	string str;
	int num_letter;
	string greyLetters;
	string orangeLetters;
	string greenLetters;
	vector<string>greys;
	string org;
	string grn;
	vector<string>oranges;
	vector<string>greens;

	//check if the dictionary is loaded
	if (dictionary.size() > 0) {
		//This function will help you cheat at Searchdle (see: https://wtfseo.com/searchdle/).
		//1a. check if the words from the list has same number of letters as mystery word.
		cout << "********************** Welcome to Searchdle **********************" << endl;
		cout << "You come to the right place if you want to cheat at the game :D" << endl;
		//ask user how many letters is the word
		//executes loop if the input fails, make sure user enter number
		while (std::cout << "How many letters in your word? \n" && !(std::cin >> num_letter)) {
			std::cin.clear(); //clear bad input flag
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
			std::cout << "Invalid input; please re-enter a number.\n";
		}
		//cin >> num_letter;
		// ask user what are the grey letters in the word
		cout << "what are the grey letters in your word? \n";
		cout << "*note: type all your letters in a line seperated by space.\n";
		getline(cin >> ws, greyLetters);
		stringstream ss(greyLetters);
		//split the string into individual strings 
		while (getline(ss, str, ' ')) {

			greys.push_back(str);
		}
		// ask user how many yellow/orange letters in the word
		cout << "what are the yellow/orange letters in your word? \n";
		cout << "*note: type all your letters in a line seperated by space.\n";
		getline(cin >> ws, orangeLetters);
		stringstream so(orangeLetters);
		//split the string into individual strings 
		while (getline(so, org, ' ')) {

			oranges.push_back(org);
		}
		// ask user for green letters and their positions
		int n;
		//ask user for number of green letters
		//executes loop if the input fails, make sure user enter number
		while (std::cout << "how many green letters in your word?\n" && !(std::cin >> n)) {
			std::cin.clear(); //clear bad input flag
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
			std::cout << "Invalid input; please re-enter a number.\n";
		}
		string a;
		string index;
		vector<string> v;
		int count = 0;
		int count_index = 0;
		string l;
		int idx;
		bool anyGreen;
		vector <int> greenIndexes;
		bool isString;
		int ind;
		vector<string> possibleAnswers;
		// loop through number of green letters
		for (int i = 0; i < n; i++)
		{
			cout << "letter: " << endl;
			cin >> a;
			//isString = false;
			isString = false;

			while (isString == false)
			{
				if (a.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_") != std::string::npos || isdigit(a[0])) {
					cout << "invalid input, please re-enter.\n";
					isString = false;
					cout << "letter: " << endl;
					cin >> a;
				}
				else {
					isString = true;

					//cout << "letter index: " << endl;
					//cin >> index;

					//executes loop if the input fails, make sure user enter number
					while (std::cout << "letter index: \n" && !(std::cin >> ind)) {
						std::cin.clear(); //clear bad input flag
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
						std::cout << "Invalid input; please re-enter a number.\n";
					}

					index = to_string(ind);
					v.push_back(a);
					v.push_back(index);
				}
			}


		}
		// check if any green letters
		if (n <= 0) {
			anyGreen = false;
		}
		else {
			anyGreen = true;
			for (auto p : v)
			{
				// to get green letters by acessing every second elements of vector list
				count += 1;
				if (count == 1) {
					//cout << p << " ";
					//count = 0;
					l = p;
				}


				if (count == 3) {
					//cout << p << " ";
					l += p;
					//cout << l << endl;
					count = 1;
				}

				//to get green letters indexes by acessing every second elements of vector list
				count_index += 1;
				if (count_index == 2) {
					//cout << p << " ";
					//convert index string to int
					idx = stoi(p);
					greenIndexes.push_back(idx);
					count_index = 0;
				}

			}

		}



		//1. search through the dictionary list that meets a set of parameters
		for (auto el : dictionary) {
			// access word name
			string word = el.getName();
			// check if the words from dictionary has the size indacated by user
			if (word.size() == num_letter) {
				bool hasGrey = false;
				//loop thru grey letters given by user
				for (auto grey : greys) {
					int found = word.find(grey);
					// if found is not -1 which means grey is found
					if (found != string::npos) {
						hasGrey = true;
						break;
					}

				}
				// catch only words that dont have greys.
				if (hasGrey == false) {
					bool hasAllOranges = true;
					//look for orange letters
					for (auto orange : oranges) {
						int found = word.find(orange);
						//if found is -1 which means no orange letter found
						if (found == string::npos) {
							hasAllOranges = false;
							break;
						}
					}
					// catch letter that have all orange letters
					if (hasAllOranges == true) {

						// catch green letters in this block of code
						if (anyGreen) {
							bool hasAllGreens = true;
							//loop through the green indexes caught earlier
							for (int i = 0; i < greenIndexes.size(); i++) {
								// get the individual index from the vector
								int index = greenIndexes[i];
								//compare the letter of the dictionary word at the green index with the uesr-specified letter  
								if (word.at(index) != l[i]) {
									hasAllGreens = false;
									break;
								}
							}

							//display all the letters that have green letters
							if (hasAllGreens) {
								possibleAnswers.push_back(word);

							}
							else {

								break;
							}


						}
						else {
							//only display words that do not contain green letters.							
							possibleAnswers.push_back(word);

						}


					}
				}

			}

		}
		if (possibleAnswers.size() > 0) {
			for (auto word : possibleAnswers) {
				cout << word << endl;
			}

		}
		else {
			cout << "no words found" << endl;
		}



	}
	else {
		cout << "List is empty. Uploading dictionary is neccessary" << endl;
	}



}



