#pragma once


// File: Conga.h
// Author:    Thomas Kocar and Andrew Fox, University of Toledo
// Date:     November 1 , 2020

/*This file is here just to initialize our structs we will use for data to keep them together like
the players playing, the cells/spaces on the board, the possible moves that are available, and the move data that you keep*/

using namespace std;

enum Player { MAX, MIN, openSquare };	// three different players which we will use to tell the difference between an open square, AI agent and Random agent


struct CELL {
	Player player;	// the current player/color who owns this square
	int count;		// the number of player's stones at this square
};

struct PossibleMoves {
	int row;				// row number
	int col;				// column number
	int directionRow;		// relative direction of row it is going to, if any as it could stay in row so it could be 0 for direction
	int directionCol;		// same as row but for column
	bool movesAccessible;	// bool for any accessible moves. FALSE for no moves available

	// initializes the move/data of move to be able to push all information at once to the vector
	PossibleMoves() {}

	PossibleMoves(int i, int j, int directionI, int directionJ, bool moves) {
		row = i;
		col = j;
		directionRow = directionI;
		directionCol = directionJ;
		movesAccessible = moves;
	}
};