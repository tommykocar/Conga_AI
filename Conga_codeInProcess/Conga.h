#pragma once

//File: Kruskal.h
// Author:    Thomas Kocar and Andrew Fox, University of Toledo
// Date:     November 1 , 2020

/*This file is here just to initialize our structs we will use for data to keep them together like
the players playing, the cells/spaces on the board, the possible moves that are available, and the move data that you keep*/

using namespace std;


enum Player { MAX, MIN, openSquare };	// three different players which we will use to tell the difference between an open square, AI agent and Random agent


struct CELL {
	int value;								// the value at that square
	Player player;							// along with the player/color of the seeds at that sq
};

struct PossibleMoves {
	int i;					// row number
	int j;					// column number
	int directionI;			// direction of row it is going to, if any as it could stay in row so it could be 0 for direction
	int directionJ;			// same as row but for column
	bool movesAccessible;	// number of possible moves

	PossibleMoves() {}
	PossibleMoves(int i, int j, int directionI, int directionJ, bool movesAccessible) : i(i), j(j), directionI(directionI), directionJ(directionJ), movesAccessible(movesAccessible) {
		// initializes the move/data of move to be able to push all information at once to the vector
	}


};

/*struct playersMove {
	bool moveAvailable;							// says whether there is moves even avaiable
	struct PossibleMoves turn;					// possible turns you could do
};*/

