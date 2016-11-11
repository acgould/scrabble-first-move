# scrabble-first-move

The purpose of this program is to solve for possible first moves in Scrabble. You have seven tiles, including possibly blank tiles, and want to know what words you could legally play. I will use an asterisk (*) to represent the blank tiles.

Assumptions:
* I assume that any number of duplicates are possible (up to all 7).
* I assume there are only 26 lowercase letters (a-z).
* I assume the same tile cannot be used twice in a single combination.
* I assume the order of the returned list is unimportant.

Simplest case:
7 letters, no wild cards, no duplicates

Special case:
All blank tiles (not possible in a real Scrabble game)

To input tile sets as lines of seven characters each in a text file:

  $ ./mytiles dictionary.txt tilefile.txt
  $ ./mytiles [dictionary file] [tile sets file]


To input tile sets manually via prompt:

  $ ./mytiles dictionary.txt
  $ ./mytiles [dictionary file] 

I have included in the repository two dictionary files, dictionary.txt and smalldict.txt, as well as a tilefile.txt for testing.

The main function exists in the mytiles.cpp file, which calls on either singleOptionsCheck or multiOptionsCheck, as appropriate, to create a Scrabbler object. The user can choose to include a “tile file” (a text file with tile sets of seven characters on each line, similar to the dictionary file) or not. If not, the user will be prompted to enter the seven character set. Both options ask the user if they wish to enter another tile file or tile set before closing the program.

The function multiOptionsCheck uses multiTileChecker to read in the tile sets one at a time from the tile file. Instead, singleOptionsCheck uses tileChecker to begin the process.

The first step is to generate the combinations of tiles. This is done by maintaining a boolean array called used to keep track of whether a particular tile has been used to create the current phrase. Beginning with a single tile, the phrase is checked against the dictionary and added to the unordered_set of strings called output_ if it is viable. Then nextLevel considers all possible (unused) second tiles for that root and checks the two character phrases starting with that same first tile. This then continues until all options with a particular root have been considered. If the permutations were organized as a tree, this would be a depth first search.

Blank tiles are taken into consideration with the addition of each new tile added to the current root phrase. If a blank tile is considered, the blankTiler function spawns 26 new branches of nextLevel, one for each of the possibilities of that blank tile.

Finally, after all permutations have been generated, considered, and saved if viable, the options for the given tile set are printed out. If one wished to save this information, it would be possible to alter the code so that these options are instead saved to a new file.

Currently, the code checks if the given tile set is exactly seven characters long. Invalid characters, such as numbers, are included in the tile set but will not be included in viable outcomes, as seen in the set 7777777 in the included tilefile.txt. Further restrictions on the tile sets could be implemented.

