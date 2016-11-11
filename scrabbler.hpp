/**
 * \file scrabbler.hpp
 *
 * \author Ashley Gould
 *
 * \brief Provides scrabbler, a class for checking possible words against a given 
 *          dictionary using unordered_set
 */

#ifndef SCRABBLER_HPP_INCLUDED
#define SCRABBLER_HPP_INCLUDED 1
 

#include <cstddef>
#include <string>
#include <iostream>
#include <unordered_set>


using std::string;
using std::cout;
using std::endl;
using std::cerr;
using std::unordered_set;


/**
 * \class Scrabbler 
 *
 * \brief Implements a class for checking text against a given dictionary
 * 
 * \remarks Uses unordered_set to structure the dictionary
 */
class Scrabbler {

public:


    ///< Constructor
    Scrabbler() = default;

    ///<Parameterized Constructor
    Scrabbler(const string& dictfile);

    ///< Disable copy constructor
    Scrabbler(const Scrabbler& rhs) = delete;

    ///< Disable assignment operator
    Scrabbler operator=(const Scrabbler& rhs) = delete;

    ///< Destructor
    ~Scrabbler()= default;

    /**  
     * \brief This function uses the hash function to see if the word exists 
     *          in the dictionary hash table
     *
     * \param word, a string
     *
     * \details This function  
     */
    bool existsInDict(const string& word) const;

    /**  
     * \brief This function clears the options_ for new tile sets
     */
    void clearOptions();   

    /**  
     * \brief This function uses the dictionary to find all valid 
     *          permutations of a given set of tiles
     *
     * \param tiles, a 7-character string
     *
     * \details 
     */
    void tileChecker(const string& tiles);

    /**  
     * \brief This function uses the dictionary to find all valid 
     *          permutations of a given set of tiles for all tiles in a given file
     *
     * \param tilefile, the name of a file of tile sets
     *
     * \details 
     */
    void multiTileChecker(const string& tilefile);

private:
    unordered_set<string> dictionary_; // The unordered_set storing our dictionary
    unordered_set<string> output_; // The unordered_set to collect all the possibilities

    /**  
     * \brief This function uses the existsInDict function to check word validity 
     *          and add valid words to output_
     *
     * \param word, a string
     *
     * \details 
     */
    void checkAndAdd(const string& word);

    /**  
     * \brief This function handles blank tiles by substituting in each of the 
     *          letters of the alphabet 
     *       
     * \param phrase, a string representing the current root
     * \param tiles, a string representing the current tile set
     * \param used, a boolean array indicating which tiles are currently in use
     *
     * \details 
     *  
     */
    void blankTiler(const string& phrase, const string& tiles, bool used[]);

    /**  
     * \brief This function recursively combines tiles and then uses checkAndAdd 
     *          to add valid options to the output
     *       
     *
     * \param phrase, a string representing the current root
     * \param tiles, a string representing the current tile set
     * \param used, a boolean array indicating which tiles are currently in use
     *  
     */
    void nextLevel(const string& phrase, const string& tiles, bool used[]);

    /**  
     * \brief This function prints out the options in output_ to cout
     *
     * \details Unordered_set does not guarentee any order but will not produce duplicates.
     *  
     */
    void printOutput() const;


    /**  
     * \brief This function begins the recursive combination generation process
     *          and prints the output 
     *       
     *
     * \param word, a string 
     *
     * \details 
     *  
     */
    void comboGenerator(const string& tiles);

};

#endif