#ifndef __TOWERS__
#define __TOWERS__

#include <iostream>
#include <iomanip>		//Padding for prettyness
#include <windows.h>	//Console Handler
#include <vector>
#include <time.h>		//srand seed
#include <stdlib.h>		//srand/rand
#include <string>

//Public Error Codes
const int invalidMove = -5;
const int invalidDestination = -4;
const int invalidSource = -3;
const int noSpaceInDestination = -2;
const int noRingsInSource = -1;
const int successfulMove = 0;

class Towers {
	private:
		//Create a vector-array composed of integer-vector-arrays
		//--vectors = {vector_a, vector_b, vector_c};
		std::vector<std::vector<int>> towers = {};
		std::vector<std::vector<int>> solution = {};

		//Window handler
		const HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

		//Define Everything Else (Defaults)
		int towerCount = 3;
		int rings = 3;

		int towerColor = 15;
		int defaultColor = 15;
		int colorDepth = 14;

		int towerMarker = 15;
		char towerChar = '-';

		bool failFlag = false;
		int errorType = 0;

		//Error Codes
		int notEnoughTowers = 2;
		int tooManyRings = 3;
		int notEnoughRings = 4;
		int notEnoughTowers_tooManyRings = 6;
		int notEnoughTowers_notEnoughRings = 8;

		//Utilities
		//  Populate the board with towers
		bool populateTowers();

		//  Check The Current State of A Given Tower
		//  Return Codes:
		//	-2) Unkown Error
		//	-1) There is no space availble in the tower
		//	 0) Tower is empty
		//	 1) There is space available in the tower
		int towerState(std::vector<int>);

		//  Count the amount of rings on a given tower
		int countRings(std::vector<int>);

	public:
		//Initializer(s)
		//	Default Initializer
		Towers();

		//	Custom Amount of Towers
		Towers(int);

		//	Custom amount of towers with a custom amount of *rings (up to the color depth)
		Towers(int, int);

		//Deinitializer
		~Towers();

		//Getters
		//	Get the number of towers
		int getTowerCount();

		//	Get the size of each tower
		int getTowerSize();

		//	Get maximum amount of rings
		int getMaxRings();

		//	Return whether or not there was a failure
		bool fail();

		//	Get the exact error type of the fail flag
		int error();

		//	Return whether the game is solved or not
		bool isSolved();

		//Utilities
		//	Shuffle the towers
		bool shuffle();

		//	Move top-most item between source and destination towers
		//Return Codes:
		//	-5) Invalid Move
		//	-4) Invalid Destination
		//	-3) Invalid Source
		//	-2) Destination Has No Space
		//	-1) Source Has No Rings
		//	 0) Successful Move
		int move(int, int);

		//  Print the raw board -- Useful for debugging
		void printRaw();

		//  Draw the formatted board
		void draw();

		//Overloads
		//	Overload output stream for error reporting
		friend std::ostream& operator<<(std::ostream&, Towers&);
};

#endif
