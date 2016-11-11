/**
 * \file mytiles.cpp
 *
 * \author Ashley Gould
 *
 * \brief Implements the UI for the tile combination suggester
 */

#include <string>
#include <iostream>
#include <stdexcept>

#include "scrabbler.hpp"

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::cerr;


/**
 * \brief Process input from cin and compares against the dictionary.
 *        Of the tiles, valid word options from the dictionary are
 *        output to cout.
 *
 * \param dictfile Name of dictionary file.
 *
 */
void singleOptionsCheck(const string& dictfile)
{
    Scrabbler dictionary(dictfile);
    string tiles;
    cout << "Please enter the seven tiles as a string, using * for blank tiles:" << endl;
    cin >> tiles;
    dictionary.tileChecker(tiles);

    // Seeing as we have a processed dictionary, we can use it again.
    while (true) {
    	string yesOrNo;
    	cout << "Would you like to submit another set of tiles? (y/n)" << endl;
    	cin >> yesOrNo;

    	// Want to continue
    	if (yesOrNo == "y") {
    		cout << "Please enter the seven tiles, with no separation:" << endl;
    		cin >> tiles;
    		dictionary.clearOptions();
    		dictionary.tileChecker(tiles);
    	}
    	// Don't want to continue
    	else {
    		break;
    	}
    }
}

/**
 * \brief Process input from cin and compares against the dictionary.
 *        Of the tiles, valid word options from the dictionary are
 *        output to cout.
 *
 * \param dictfile, name of dictionary file.
 * \param tilefile, name of tile sets file
 *
 */
void multiOptionsCheck(const string& dictfile, const string& tilefile)
{
    Scrabbler dictionary(dictfile);
	dictionary.multiTileChecker(tilefile);

	// Seeing as we have a processed dictionary, we can use it again.
    while (true) {
    	string yesOrNo;
    	cout << "Would you like to submit another file of tiles? (y/n)" << endl;
    	cin >> yesOrNo;

    	// Want to continue
    	if (yesOrNo == "y") {
    		string newfile;
    		cout << "Please enter the tile file name:" << endl;
    		cin >> newfile;
    		dictionary.multiTileChecker(newfile);
    	}
    	// Don't want to continue
    	else {
    		break;
    	}
    }
}

/// Main function, processes inputs and runs optionsCheck or multiOptionsCheck as appropriate
int main(int argc, const char** argv)
{
    // Process command-line options
    --argc; // Skip past 0th arg (program name)
    ++argv;
    bool file = false;

    if (argc == 2) {
        --argc;
        file = true;
    }

    if (argc != 1) {
        cerr << "Usage: ./mytiles dictionary tiles" << endl;
        exit(2);
    }

    // Tiles are input by file
    if (file) {
    	// Parse out the names of the two files
    	string dictfile = argv[0];
    	++argv;
    	string tilefile = argv[0];
    	try {
    		multiOptionsCheck(dictfile, tilefile);
    	} catch (std::runtime_error err) {
	        cerr << err.what() << endl;
	        return 1;
	    }
    }
    // Tiles are input manually
    else {
	    // Check those tiles!
	    try {
	        singleOptionsCheck(argv[0]);
	    } catch (std::runtime_error err) {
	        cerr << err.what() << endl;
	        return 1;
	    }
	}

    return 0;
}