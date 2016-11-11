/**
 * \file scrabbler.cpp
 * \author Ashley Gould, 
 *
 * \brief Hash function for strings
 */

#include "scrabbler.hpp"
#include <fstream>

//Parameterized Constructor
Scrabbler::Scrabbler(const string& dictfile) {

    // Attempt to read in dictionary
    std::ifstream inFile(dictfile);
    if (!inFile) {
        cerr << "Couldn't find dictionary: " << dictfile << endl;
        exit(1);
    }

    // Read data from the file, one item per line
    string line;
    while(inFile.good()) {
        getline(inFile, line);
        if (inFile.fail())
            break;
        dictionary_.insert(line);
    }
}


bool Scrabbler::existsInDict(const string& word) const {

    //using the HashSet exists, checks if the word exists
    return dictionary_.count(word);
}

void Scrabbler::clearOptions() {
    output_.clear();
}

void Scrabbler::checkAndAdd(const string& word) {
    // If this set of tiles is a valid word
    if (existsInDict(word)) {
        // add it to the list of possiblities
        output_.insert(word);
    }
}

void Scrabbler::blankTiler(const string& phrase, const string& tiles, bool used[]) {
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    // for all the possibilities of the blank tile
    for (size_t i = 0; i < 26; ++i) {
        string newPhrase = phrase + alphabet[i];
        checkAndAdd(newPhrase);

        // continue with nextLevel if we have not hit the end
        if (newPhrase.length() < tiles.length()) {
            nextLevel(newPhrase, tiles, used);
        }
    }
}

void Scrabbler::nextLevel(const string& phrase, const string& tiles, bool used[]) {
    for (size_t i = 0; i < tiles.length(); ++i) {
        // check if we can use this tile
        if (used[i] == false) {
            used[i] = true;

            //check if this tile is a blank tile (*)
            if (tiles[i] == '*') {
                blankTiler(phrase, tiles, used);
            }

            else { // new tile is not a blank tile
                // add the tile to the phrase
                string newPhrase = phrase + tiles[i];
                checkAndAdd(newPhrase);

                // recurse if we have not hit the end
                if (newPhrase.length() < tiles.length()) {
                    nextLevel(newPhrase, tiles, used);
                }
            }

            // free the tile to be used again
            used[i] = false;
        }
    }
}

void Scrabbler::printOutput() const {
    for (auto i = output_.begin(); i != output_.end(); ++i) {
        cout << " " << *i;
    }
    cout << endl;
}


void Scrabbler::comboGenerator(const string& tiles) {

    bool used[7] = {false, false, false, false, false, false, false};
    string noStem = "";
    nextLevel(noStem, tiles, used);
    
    // Print out all of our options
    cout << "Options for " + tiles + ":" << endl;
    printOutput();
} 


void Scrabbler::tileChecker(const string& tiles) {
    // check that the number of tiles is correct
    if (tiles.length() == 7) {
        comboGenerator(tiles);
    }
    else {
        cerr << "Invalid number of tiles: " << tiles << endl;
        exit(1);
    }
}

void Scrabbler::multiTileChecker(const string& tilefile) {
    // Attempt to read in tile file
    std::ifstream inFile(tilefile);
    if (!inFile) {
        cerr << "Couldn't find tile file: " << tilefile << endl;
        exit(1);
    }

    // Read data from the file, one item per line
    string line;
    while(inFile.good()) {
        getline(inFile, line);
        if (inFile.fail())
            break;
        clearOptions();
        tileChecker(line);
    }
}