#include "Dictionary.h"


/**
 * .
 * load dictionary file
 * \param file
 * \param dictionary
 * \return
 * \author Hilary Soong
 * \date   7 May 2023
 */
void Dictionary::loadAndParseFile() {

    string data; // to keep some texts of the files e.g <word>,</word>, and the first two lines of the texts
    ifstream dictFile;
    string fileOption;
    string defaultFile = "dictionary_2023S1.txt";
    string userFile;
    Word record;
    string name = record.getName();
    string defo = record.getDefinition();
    string type = record.getType();

    // prompt user to decide how to load default file or their own file
    cout << "You have two options : " << endl;
    cout << "enter [1] - run default file" << endl;
    cout << "enter [2] - to type in your file name" << endl;
    // get user response on file option           
    cin >> fileOption;
    //if user chose 1, run default file
    if (fileOption == "1") {

        dictFile.open(defaultFile);
        string trash;

        // check if file is open, if not open print error status
        if (dictFile.is_open()) {
            //read the file until the end

            while (!dictFile.eof()) {
                getline(dictFile, data); // This will be <word>
                //read line by line
                if (data != "<word>") {
                    getline(dictFile, trash); //The trash stays where it belongs. 
                    continue;
                }

                //add the lines to struct vector accordingly
                getline(dictFile, name); // this will be line for name
                getline(dictFile, defo); //this will be line for definition
                getline(dictFile, type); //this will be line for type
                getline(dictFile, data);// this will be line for </word>
                record = Word(name, type, defo);
                dictionary.push_back(record); // add the right data into dictionary vector 
                //this->dictionary.push_back(record); // add the right data into dictionary vector


            }
            //close the text file after finish reading        
            dictFile.close();
            cout << "Dictionary successfully loaded. " << dictionary.size() << " entry." << endl;

        }
        // display error if failed to open file
        else {
            cout << "Unable to open file" << endl;
        }
    }
    //if user chose 2, ask them to enter name of the file
    else if (fileOption == "2") {
        cout << "please enter the name of your file: " << endl;
        getline(cin >> ws, userFile);
        string userFileName = userFile + ".txt";

        dictFile.open(userFileName);
        string trash;
        Word record;
        // check if file is open, if not open print error status
        if (dictFile.is_open()) {
            //read the file until the end

            while (!dictFile.eof()) {
                getline(dictFile, data); // This will be <word>
                //read line by line
                if (data != "<word>") {
                    getline(dictFile, trash); //The trash stays where it belongs. 
                    continue;
                }
                //add the lines to struct vector accordingly
                getline(dictFile, name); // this will be line for name
                getline(dictFile, defo); //this will be line for definition
                getline(dictFile, type); //this will be line for type
                getline(dictFile, data);// this will be line for </word>
                record = Word(name, type, defo);
                dictionary.push_back(record); // add the right data into dictionary vector 
                //this->dictionary.push_back(record); // add the right data into dictionary vector 

            }
            //close the text file after finish reading        
            dictFile.close();

        }
        // display error if failed to open file
        else {
            cout << "Unable to load dictionary." << endl;
        }
    }
    // print error if user failed to put in correct input
    else {
        cout << "invalid input. Must be from 1 - 2" << endl;
    }

}


//display dictionary on console after load and parser the dictionary file

/**
 * .
 *
 * \param dictionary
 * \author Hilary Soong
 * \date   6 May 2023
 */
void Dictionary::displayDictionary() {
    loadAndParseFile();
    for (auto it = this->dictionary.begin(); it != this->dictionary.end(); it++) {

        cout << "name: " << it->getName() << endl;
        cout << "definition: " << it->getDefinition() << endl;
        cout << "type: " << it->getType() << endl;
    }
}

void Dictionary::searchWord() {
    string filename = "dictionary_2023S1.txt";

    fstream current_file;
    string word;
    bool isFound = true;
    Word theWord;

    //current_file.open(filename);
    // check if the file can be opened in the beginning before proceeding further
    /*if (current_file.fail()) {
        cout << "error: fail to open file" << endl;
        return;
    }*/

    cout << "Enter a word to search: " << endl;
    // prompt user to put in search word
    cin >> word;

    // convert word to lower case 
    transform(word.begin(), word.end(), word.begin(), ::tolower);

    for (auto el : this->dictionary) {

        if (word == el.getName()) {
            theWord = el;
            isFound = true;
            break;

        }
        else {
            isFound = false;

        }

    }
    // if the word is found then print out the name, definition and type of the word on the console
    if (isFound) {
        cout << "Name: " << theWord.getName() << endl;
        cout << "Definition: " << theWord.getDefinition() << endl;
        string type = theWord.getType();
        // set the word type to a new variable called theWordType
        string theWordType = type;

        //check the kind of type of the word and set the word type accordingly as follows
        if (type == "n") {
            theWordType = "[noun]";
        }
        else if (type == "v") {
            theWordType = "[verb]";
        }
        else if (type == "adv") {
            theWordType = "[adverb]";
        }
        else if (type == "adj") {
            theWordType = "[adjective]";
        }
        else if (type == "prep") {
            theWordType = "[preposition]";
        }
        else if (type == "misc") {
            theWordType = "[miscellaneous]";
        }
        else if (type == "pn") {
            theWordType = "[proper noun]";
        }
        else if (type == "n_and_v") {
            theWordType = "[noun and verb]";
        }
        else {
            theWordType = "N/A";
        }
        cout << "Type: " << theWordType << endl;



    }
    // print out error if word not found
    else {
        cout << "word not found" << endl;
    }


}

//check if string contains three z
bool Dictionary::hasThreeZ(string s) {
    return count(begin(s), end(s), 'z') >= 3;
}

// find words that have three z from the text file
void Dictionary::findThreeZ() {
    for (auto el : this->dictionary) {
        if (hasThreeZ(el.getName())) {
            cout << el.getName() << endl;
        }
    }
}

// display word type options for task 4 - adding a new word
void Dictionary::wordTypeOptions() {
    cout << "[1] Noun" << endl;
    cout << "[2] Verb" << endl;
    cout << "[3] Adverb" << endl;
    cout << "[4] Adjective" << endl;
    cout << "[5] Preposition" << endl;
    cout << "[6] Miscellaneous" << endl;
    cout << "[7] Proper Noun" << endl;
    cout << "[8] Noun and Verb" << endl;
}

//add new word to the dictionary vector by creating a new <word> instance, and save to new file
void Dictionary::addNewWord(vector<Word>dict) {
    string file = "dictionary_2023S1.txt";
    Word newWord;
    string newWordName;
    char newWordType;
    bool isValidType = false;
    string newFileName;
    string newFile;
    fstream current_file;
    string newWordDefo;

    //prompt user to enter the name, type and definition of a word
    cout << "enter name of the new word: " << endl;
    cin >> newWordName;
    //check if the word exists in the dictionary
    for (auto element : this->dictionary) {
        if (newWordName != element.getName()) {
            newWord.setName(newWordName);
            //wordName = newWordName;
            cout << "please enter the number for type of new word from the following options: " << endl;
            //display word type
            wordTypeOptions();

            //prompt user to enter number for their word type
            cin >> newWordType;

            //add new word into dictionary given valid type is enterred
            switch (newWordType) {
            case '1':

                newWord.setType("n");
                isValidType = true;
                break;
            case '2':
                newWord.setType("v");
                isValidType = true;
                break;
            case '3':
                newWord.setType("adv");
                isValidType = true;
                break;
            case '4':
                newWord.setType("n");
                isValidType = true;
                break;
            case '5':
                newWord.setType("prep");
                isValidType = true;
                break;
            case '6':
                newWord.setType("misc");
                isValidType = true;
                break;
            case '7':
                newWord.setType("pn");
                isValidType = true;
                break;
            case '8':
                newWord.setType("n_and_v");
                isValidType = true;
                break;
                // print out error if incorrect input is entered
            default:
                cout << "Invalid option. Must be 1 - 8" << endl;
                isValidType = false;
            }
            // if valid type is correct, proceed further
            if (isValidType) {
                cout << "please enter definition of the new word: " << endl;
                //ask user for new word definition

                //getline(cin >> ws, newWord.setDefinition(ws));
                getline(cin >> ws, newWordDefo);
                newWord.setDefinition(newWordDefo);
                //instatiate word object and add it to dictionary vector
                dict = this->dictionary;
                dict.push_back(newWord);
                cout << "new word successfully added. Saving to a new file. Please enter name for new file: " << endl;

                // prompt user to enter file name
                getline(cin >> ws, newFileName);

                // combine file name with file extension
                newFile = newFileName + ".txt";

                // write the Dictionary to a new file
                ofstream file(newFile);

                // loop thru dict vector and save into the new file with following values  
                for (int i = 0; i < dict.size(); i++) {
                    file << "<word>" << endl;
                    file << dict[i].getName() << endl;
                    file << dict[i].getDefinition() << endl;
                    file << dict[i].getType() << endl;
                    file << "</word>" << endl;
                }
                file.close();
                cout << newFile << " created" << endl;
                return;
            }
        }
        // print error if word exists
        else {
            cout << "error: word exists, elevated privileges required to edit existing words" << endl;
            return;

        }
    }
}

