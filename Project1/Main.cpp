


// File: Main.cpp - Main function implementation
//
// This is the main cpp which holds the main function and all the other methods/functions we have created to run the code.
// We have two players of the game Conga which will be MAX and MIN players. MAX is our AI agent that evaluates the moves possible
// and picks the best one according to our evaluation function. Min is our Random agent that will just look at the possible moves
// and pick a random moves from them. The max player uses black pieces and the min player uses white pieces. So when the board is displayed
// it will shows the number of seeds with a "b" or "w" next to them to signify the color of the seeds. This is how you know whos pieces are what
//
//
// Author:    Thomas Kocar and Andrew Fox, University of Toledo
// Date:      November 1, 2020



#include <stdio.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include "Conga.h"

using namespace std;

// This function is here to copy the board we start with so then when we are traveling down the tree for MINIMAX
void copyboard(struct CELL CopiedBoard[4][4], struct CELL board[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			CopiedBoard[i][j].player = board[i][j].player;	//copies the player from the original board to the copy of the board
			CopiedBoard[i][j].count = board[i][j].count;	//copies the count from the original board to the copy of the board
		}
	}
}

// This prints out the board to the console with the move we have made.
// This allows everyone to see what move you made that turn and make sure that it is a valid move according to the rules
void DisplayCongaBoard(struct CELL board[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << board[i][j].count;				// prints the count at the cell we are at
			if (board[i][j].player == MAX) {
				cout << "b | ";						// prints b for black player which is the MAX player(AI AGENT)
			}
			else if (board[i][j].player == MIN) {
				cout << "w | ";						// prints w for whith player which is the MIN player(random AGENT)
			}
			else {
				cout << "  | ";						// prints just a line with a space as it is an opensquare so there is no content in it
			}
		}
		cout << endl;
		if (i < 3) cout << "--------------------" << endl;
	}
	cout << endl;	//added additional line break to separate (put an empty line) moves
}

/*
	This function controls which evaluation function MAX will use. This is necessary to choose between different evaluation
	functions tested without having to constantly change the name of the each evaluation function
*/
int (*evaluationFunction)(struct CELL[4][4]);	// intialize function pointer to evaluationFunction()
void chooseEvaluationFunction(int evalFunc(struct CELL[4][4])) {
	evaluationFunction = evalFunc;	// set evaluationFunction() for MAX to use from the inputted evalFunc
};

// This right here is one of our evaluation function of how we find the best move to make for the AI Agent. 
// This evaluation function counts up the cells occupied by MAX(black) and subtracts it against the number of cells occupied by MIN(white).
// This helps us figure out the cell diferential between the two players. The more cells black controls, the higher the probability is that white is losing (though not necessarily)
int evaluationFunctionCellDifferential(struct CELL board[4][4]) {

	int numofMAXSpaces = 0, numofMINSpaces = 0;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (board[i][j].player == MAX) {
				numofMAXSpaces++;	// adds to count as the cell we visited from the board has the MAX player in it
			}
			else if (board[i][j].player == MIN) {
				numofMINSpaces++;	// adds to count as the cell we visited from the board has the MAX player in it
			}

		}
	}

	return numofMAXSpaces - numofMINSpaces;
}


// This right here is our evaluation function of how we find the best move to make for the AI Agent. Our evaluation function counts up the cells
// that the MAX player is filling up and subtracts it against the possible moves the MIN player can make. This helps us figure out how many cells we
// can move to, in order for them to not have as many or any cells to move to making us the winner of the game
int evaluationFunctionOG(struct CELL board[4][4]) {

	int numofMAXseeds = 0, numofMINmoves = 0;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (board[i][j].player == MAX) {
				numofMAXseeds++;	// adds to count as the cell we visited from the board has the MAX player in it
			}
			else if (board[i][j].player == MIN) {

				// These if statements are exactly like the ones in move list. As we want to see how many moves are available to the MIN player
				// from that cell so the if statements are all based on the specific cell they are in so we don't have to go through 8 if statements everytime.
				// This will allow us to see how many moves the white player will have left if we make this move allowing us to block as many cells as possible.
				if (j == 0) {
					if (i == 0) {
						if (board[i][j + 1].player == MIN || board[i][j + 1].player == openSquare)		numofMINmoves++;

						if (board[i + 1][j + 1].player == MIN || board[i + 1][j + 1].player == openSquare)	numofMINmoves++;

						if (board[i + 1][j].player == MIN || board[i + 1][j].player == openSquare)		numofMINmoves++;
					}
					else if (i == 3) {
						if (board[i][j + 1].player == MIN || board[i][j + 1].player == openSquare)		numofMINmoves++;

						if (board[i - 1][j + 1].player == MIN || board[i - 1][j + 1].player == openSquare)	numofMINmoves++;

						if (board[i - 1][j].player == MIN || board[i - 1][j].player == openSquare)		numofMINmoves++;

					}
					else {
						if (board[i + 1][j].player == MIN || board[i + 1][j].player == openSquare)		numofMINmoves++;
						if (board[i + 1][j + 1].player == MIN || board[i + 1][j + 1].player == openSquare)	numofMINmoves++;
						if (board[i][j + 1].player == MIN || board[i][j + 1].player == openSquare)		numofMINmoves++;
						if (board[i - 1][j + 1].player == MIN || board[i - 1][j + 1].player == openSquare)	numofMINmoves++;
						if (board[i - 1][j].player == MIN || board[i - 1][j].player == openSquare)		numofMINmoves++;
					}
				}
				else if (j == 1 || j == 2) {
					if (i == 0) {
						if (board[i][j + 1].player == MIN || board[i][j + 1].player == openSquare)		numofMINmoves++;

						if (board[i + 1][j + 1].player == MIN || board[i + 1][j + 1].player == openSquare)	numofMINmoves++;

						if (board[i + 1][j].player == MIN || board[i + 1][j].player == openSquare)		numofMINmoves++;

						if (board[i + 1][j - 1].player == MIN || board[i + 1][j - 1].player == openSquare)	numofMINmoves++;

						if (board[i][j - 1].player == MIN || board[i][j - 1].player == openSquare)		numofMINmoves++;
					}
					else if (i == 3) {
						if (board[i][j - 1].player == MIN || board[i][j - 1].player == openSquare)		numofMINmoves++;

						if (board[i - 1][j - 1].player == MIN || board[i - 1][j - 1].player == openSquare)	numofMINmoves++;

						if (board[i - 1][j].player == MIN || board[i - 1][j].player == openSquare)		numofMINmoves++;
						if (board[i - 1][j + 1].player == MIN || board[i - 1][j + 1].player == openSquare)	numofMINmoves++;
						if (board[i][j + 1].player == MIN || board[i][j + 1].player == openSquare)		numofMINmoves++;
					}
					else {
						if (board[i + 1][j].player == MIN || board[i + 1][j].player == openSquare)		numofMINmoves++;
						if (board[i + 1][j + 1].player == MIN || board[i + 1][j + 1].player == openSquare)	numofMINmoves++;
						if (board[i][j + 1].player == MIN || board[i][j + 1].player == openSquare)		numofMINmoves++;
						if (board[i - 1][j + 1].player == MIN || board[i - 1][j + 1].player == openSquare)	numofMINmoves++;
						if (board[i - 1][j].player == MIN || board[i - 1][j].player == openSquare)		numofMINmoves++;
						if (board[i - 1][j - 1].player == MIN || board[i - 1][j - 1].player == openSquare)	numofMINmoves++;
						if (board[i + 1][j - 1].player == MIN || board[i + 1][j - 1].player == openSquare)	numofMINmoves++;
						if (board[i][j - 1].player == MIN || board[i][j - 1].player == openSquare)		numofMINmoves++;
					}
				}
				else if (j == 3) {
					if (i == 0) {
						if (board[i][j - 1].player == MIN || board[i][j - 1].player == openSquare)		numofMINmoves++;

						if (board[i + 1][j - 1].player == MIN || board[i + 1][j - 1].player == openSquare)	numofMINmoves++;

						if (board[i + 1][j].player == MIN || board[i + 1][j].player == openSquare)		numofMINmoves++;
					}
					else if (i == 3) {
						if (board[i][j - 1].player == MIN || board[i][j - 1].player == openSquare)		numofMINmoves++;

						if (board[i - 1][j - 1].player == MIN || board[i - 1][j - 1].player == openSquare)	numofMINmoves++;

						if (board[i - 1][j].player == MIN || board[i - 1][j].player == openSquare)		numofMINmoves++;
					}
					else {
						if (board[i + 1][j].player == MIN || board[i + 1][j].player == openSquare)		numofMINmoves++;
						if (board[i - 1][j].player == MIN || board[i - 1][j].player == openSquare)		numofMINmoves++;
						if (board[i - 1][j - 1].player == MIN || board[i - 1][j - 1].player == openSquare)	numofMINmoves++;
						if (board[i + 1][j - 1].player == MIN || board[i + 1][j - 1].player == openSquare)	numofMINmoves++;
						if (board[i][j - 1].player == MIN || board[i][j - 1].player == openSquare)		numofMINmoves++;
					}
				}
			}
		}
	}

	if (numofMINmoves++ == 0) {
		return 50;	// returns a very large value to signify that this move allowed us to win so this is the move that is the best and no one can beat it
	}
	else {
		return numofMAXseeds - numofMINmoves++;	// Gives us the value to fill us in if this is a good move or a bad move for the AI agent
	}
}

// This funtion is here to find the moves possible for which ever players turn it is.
// I have written it where it has specific if statments for each spot so it will
// check the surronding cells of the cell we have a seed at and not look at more then it needs too
vector<PossibleMoves> findMoves(struct CELL board[4][4], Player player) {
	vector<PossibleMoves> moveList;			// a vector to hold the moves that are possible


	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {

			if (board[i][j].player != player) continue;		// it starts with checking if the space has the player whos turn we are looking for so then
															// if it makes it past this statement without continuing then we know that the spot has the player
															// whos turn it is as looks to see if it can make any possible moves from that spot.

			// For these if statments it finds the spot on the board that it is at and then it looks at the surronding cells it could possible travel to.
			// Then if it can move that direction to a certain cell it pushs the i(row), j(column), directioni(row we are traveling to) and directionj( column we are traveling to) the move list vector.
			// This data will allow us to know which direction we are going to and then later if we deem it the move we make, we know the direction of cells to check
			// to see if they are open to know how many seeds to move to what cell, and how many cells we are able to move.
			if (j == 0) {
				if (i == 0) {
					if (board[i][j + 1].player == player || board[i][j + 1].player == openSquare)		moveList.push_back(PossibleMoves(i, j, 0, 1, true));

					if (board[i + 1][j + 1].player == player || board[i + 1][j + 1].player == openSquare)	moveList.push_back(PossibleMoves(i, j, 1, 1, true));

					if (board[i + 1][j].player == player || board[i + 1][j].player == openSquare)		moveList.push_back(PossibleMoves(i, j, 1, 0, true));
				}
				else if (i == 3) {
					if (board[i][j + 1].player == player || board[i][j + 1].player == openSquare)		moveList.push_back(PossibleMoves(i, j, 0, 1, true));

					if (board[i - 1][j + 1].player == player || board[i - 1][j + 1].player == openSquare)	moveList.push_back(PossibleMoves(i, j, -1, 1, true));

					if (board[i - 1][j].player == player || board[i - 1][j].player == openSquare)		moveList.push_back(PossibleMoves(i, j, -1, 0, true));

				}
				else {
					if (board[i + 1][j].player == player || board[i + 1][j].player == openSquare)		moveList.push_back(PossibleMoves(i, j, 1, 0, true));
					if (board[i + 1][j + 1].player == player || board[i + 1][j + 1].player == openSquare)	moveList.push_back(PossibleMoves(i, j, 1, 1, true));
					if (board[i][j + 1].player == player || board[i][j + 1].player == openSquare)		moveList.push_back(PossibleMoves(i, j, 0, 1, true));
					if (board[i - 1][j + 1].player == player || board[i - 1][j + 1].player == openSquare)	moveList.push_back(PossibleMoves(i, j, -1, 1, true));
					if (board[i - 1][j].player == player || board[i - 1][j].player == openSquare)		moveList.push_back(PossibleMoves(i, j, -1, 0, true));
				}
			}
			else if (j == 1 || j == 2) {
				if (i == 0) {
					if (board[i][j + 1].player == player || board[i][j + 1].player == openSquare)		moveList.push_back(PossibleMoves(i, j, 0, 1, true));

					if (board[i + 1][j + 1].player == player || board[i + 1][j + 1].player == openSquare)	moveList.push_back(PossibleMoves(i, j, 1, 1, true));

					if (board[i + 1][j].player == player || board[i + 1][j].player == openSquare)		moveList.push_back(PossibleMoves(i, j, 1, 0, true));

					if (board[i + 1][j - 1].player == player || board[i + 1][j - 1].player == openSquare)	moveList.push_back(PossibleMoves(i, j, 1, -1, true));

					if (board[i][j - 1].player == player || board[i][j - 1].player == openSquare)		moveList.push_back(PossibleMoves(i, j, 0, -1, true));
				}
				else if (i == 3) {
					if (board[i][j - 1].player == player || board[i][j - 1].player == openSquare)		moveList.push_back(PossibleMoves(i, j, 0, -1, true));

					if (board[i - 1][j - 1].player == player || board[i - 1][j - 1].player == openSquare)	moveList.push_back(PossibleMoves(i, j, -1, -1, true));

					if (board[i - 1][j].player == player || board[i - 1][j].player == openSquare)		moveList.push_back(PossibleMoves(i, j, -1, 0, true));
					if (board[i - 1][j + 1].player == player || board[i - 1][j + 1].player == openSquare)	moveList.push_back(PossibleMoves(i, j, -1, 1, true));
					if (board[i][j + 1].player == player || board[i][j + 1].player == openSquare)		moveList.push_back(PossibleMoves(i, j, 0, 1, true));
				}
				else {
					if (board[i + 1][j].player == player || board[i + 1][j].player == openSquare)		moveList.push_back(PossibleMoves(i, j, 1, 0, true));
					if (board[i + 1][j + 1].player == player || board[i + 1][j + 1].player == openSquare)	moveList.push_back(PossibleMoves(i, j, 1, 1, true));
					if (board[i][j + 1].player == player || board[i][j + 1].player == openSquare)		moveList.push_back(PossibleMoves(i, j, 0, 1, true));
					if (board[i - 1][j + 1].player == player || board[i - 1][j + 1].player == openSquare)	moveList.push_back(PossibleMoves(i, j, -1, 1, true));
					if (board[i - 1][j].player == player || board[i - 1][j].player == openSquare)		moveList.push_back(PossibleMoves(i, j, -1, 0, true));
					if (board[i - 1][j - 1].player == player || board[i - 1][j - 1].player == openSquare)	moveList.push_back(PossibleMoves(i, j, -1, -1, true));
					if (board[i + 1][j - 1].player == player || board[i + 1][j - 1].player == openSquare)	moveList.push_back(PossibleMoves(i, j, 1, -1, true));
					if (board[i][j - 1].player == player || board[i][j - 1].player == openSquare)		moveList.push_back(PossibleMoves(i, j, 0, -1, true));
				}
			}
			else if (j == 3) {
				if (i == 0) {
					if (board[i][j - 1].player == player || board[i][j - 1].player == openSquare)		moveList.push_back(PossibleMoves(i, j, 0, -1, true));

					if (board[i + 1][j - 1].player == player || board[i + 1][j - 1].player == openSquare)	moveList.push_back(PossibleMoves(i, j, 1, -1, true));

					if (board[i + 1][j].player == player || board[i + 1][j].player == openSquare)		moveList.push_back(PossibleMoves(i, j, 1, 0, true));
				}
				else if (i == 3) {
					if (board[i][j - 1].player == player || board[i][j - 1].player == openSquare)		moveList.push_back(PossibleMoves(i, j, 0, -1, true));

					if (board[i - 1][j - 1].player == player || board[i - 1][j - 1].player == openSquare)	moveList.push_back(PossibleMoves(i, j, -1, -1, true));

					if (board[i - 1][j].player == player || board[i - 1][j].player == openSquare)		moveList.push_back(PossibleMoves(i, j, -1, 0, true));
				}
				else {
					if (board[i + 1][j].player == player || board[i + 1][j].player == openSquare)		moveList.push_back(PossibleMoves(i, j, 1, 0, true));
					if (board[i - 1][j].player == player || board[i - 1][j].player == openSquare)		moveList.push_back(PossibleMoves(i, j, -1, 0, true));
					if (board[i - 1][j - 1].player == player || board[i - 1][j - 1].player == openSquare)	moveList.push_back(PossibleMoves(i, j, -1, -1, true));
					if (board[i + 1][j - 1].player == player || board[i + 1][j - 1].player == openSquare)	moveList.push_back(PossibleMoves(i, j, 1, -1, true));
					if (board[i][j - 1].player == player || board[i][j - 1].player == openSquare)		moveList.push_back(PossibleMoves(i, j, 0, -1, true));
				}
			}
		}
	}
	// randomly shuffle moveList to prevent the same moves to always be checked first (this hopefully prevents loops)
	// Note: We still look through list for "best" move, this only affects the order when there are multiple "best" moves
	//		 since we always save the first "best" move found
	random_shuffle(moveList.begin(), moveList.end());
	return moveList;
}

// this function is here to make the move we deemed as the best possible move (for black player) 
void PlayersMoveMade(struct CELL board[4][4], int row, int col, int directionRow, int directionCol) {
	Player player = board[row][col].player;					// takes the player at the cell we are starting/moving from
	int value = board[row][col].count;						// takes the value at the cell we are starting/moving from
	int holdX = row, holdY = col, spacesPossible = 0;		// holds the x and y values to see how many possible cells are open or the cells that we can move 
														// by going toward the direction until there are no more cells that direction or there is the opponent blocking us from moving again

	// this for loop goes through 3 times as that is the most possible cells you can travel in one move.
	// It will only go 3 times if it doesn't break from either going over the array size on either row/column
	// or it will stop if their is an opponent in the way
	for (int i = 0; i < 3; i++)
	{
		holdX += directionRow;
		holdY += directionCol;
		if ((holdX + directionRow) > 3 || (holdX + directionRow) < 0 || (holdY + directionCol) > 3 || (holdY + directionCol) < 0 || board[holdX + directionRow][holdY + directionCol].player == (player == MAX ? MIN : MAX))
		{
			break;
		}
		else
		{
			spacesPossible++;	// adds up the total possible moves that can be traveled in that certain direction
		}
	}

	// these next three if statements will move the pieces to the designated cells based on their
	// values and possible moves they can make in the direction
	if ((value > 0 && value < 2) || spacesPossible == 0) {
		board[row + directionRow][col + directionCol].player = board[row][col].player;	// moves player into the first cell in that diretion
		board[row + directionRow][col + directionCol].count += board[row][col].count;	// adds the value of the cell we started at to the cell we are going
		board[row][col].player = openSquare;							// clears player or makes player open square if you will so then we know that the cell we started at is now open
		board[row][col].count = 0;										// clears the value at our starting cell so then 
	}
	else if ((value > 1 && value < 4) || spacesPossible == 1) {
		board[row + directionRow][col + directionCol].player = board[row][col].player;	// moves player from starting cell into cell we are traveling too
		board[row + directionRow][col + directionCol].count += 1;						// adds one to the cell we are headed to as it is moving more then one cell and first cell we travel to we always put 1 into
		board[row][col].count -= 1;														// subtracts one from the value in our starting cell


		board[row + directionRow + directionRow][col + directionCol + directionCol].player = board[row][col].player;	// moves player to second cell we are traveling too from the starting cell
		board[row + directionRow + directionRow][col + directionCol + directionCol].count += board[row][col].count;		// moves the rest of our remaining value to the second cell as that is the only number of spaces we can travel too


		board[row][col].player = openSquare;	// clears player (makes player openSquare) so we know that the cell we started at now has nothing in it
		board[row][col].count = 0;				// clears value as we haved moved our values to new cells
	}
	else {

		board[row + directionRow][col + directionCol].player = board[row][col].player;	// moves player from starting cell to the next cell we move to
		board[row + directionRow][col + directionCol].count += 1;						// adds 1 to the value already in the cell we are going too
		board[row][col].count -= 1;										// subtracts 1 from our value in the starting cell



		board[row + directionRow + directionRow][col + directionCol + directionCol].player = board[row][col].player;	// moves player from startin cell to the second cell we move to
		board[row + directionRow + directionRow][col + directionCol + directionCol].count += 2;						// adds 2 to the second cell as we have more then 3 and we are moving three cells so we put 2 in the cell we move to second
		board[row][col].count -= 2;														// subtracts 2 from the value at the starting cell as we just moved 2 into our the cell we move to second


		board[row + directionRow + directionRow + directionRow][col + directionCol + directionCol + directionCol].player = board[row][col].player;	// we move player from starting cell into the final cell we move to
		board[row + directionRow + directionRow + directionRow][col + directionCol + directionCol + directionCol].count += board[row][col].count;		// we move the remaining value we have from first cell into final cell we move to


		board[row][col].player = openSquare;	// we clear the player in the starting cell (making it openSquare) so we know it is open to be moved to
		board[row][col].count = 0;				// we clear value from the starting cell as there are no seeds there
	}
}

// This function is here to make the move when its whites turn. It will find the moves possible
// and then choose a random move from the availables moves. This will give us the random agent we want to play against.
struct PossibleMoves RandomAgentTurn(struct CELL board[4][4]) {
	vector<PossibleMoves> moveList = findMoves(board, MIN);	// calls findMoves function to get the available moves
	PossibleMoves move;


	srand(time(NULL));	// this uses the internal clock to control the choice of the move. Since time is always changing the move we choose will always be changing, hence random.


	if (moveList.size() == 0) {
		move.movesAccessible = false;	// if the movesList size is 0 means that we found no possible moves so moves available are false, since there are none.
		return move;	// return that as our random move
	}
	else {
		PossibleMoves randomMove = moveList[rand() % moveList.size()];	// this makes randomMove hold the random move we choose from the moves available
		PlayersMoveMade(board, randomMove.row, randomMove.col, randomMove.directionRow, randomMove.directionCol);	// this then makes the move that we just randomly chose
		return randomMove;
	}
}

// This function is here to traverse through the tree using MINIMAX and ALPHA-BETA PRUNNING. This is the function that we call multiple times to make the moves down the tree and then
// once we get to the depth we want we the return the value from the evaluation function for whatever node we are at and go back up to the tree
// bringing the values that are best for whoevers turn it is (MAX, MIN) to pick the best move possible if we were playing an optimal person
int TraverseTree(struct CELL board[4][4], struct PossibleMoves newMove, int numMove, Player player, int Alpha, int Beta) {
	vector<PossibleMoves> moveList;
	int bestMove, holder;
	Player nextPlayer;
	struct CELL PlayedBoard[4][4];	// creates a new Board 
	copyboard(PlayedBoard, board);	// makes the new Board identical to board to make it identical to the original board
	PlayersMoveMade(PlayedBoard, newMove.row, newMove.col, newMove.directionRow, newMove.directionCol);	// makes the move we sent in newMove in the new Board so then we can evaluate it later

	if (numMove == 4) {
		return evaluationFunction(PlayedBoard);	// it has reached the depth we want to evaluate from so it returns the value of the evaluation function
	}

	// finds the move of the next player to see if it has any moves available so then we make our next move to continue
	// down the tree toward the depth we want with the moves that are legal.
	moveList = findMoves(PlayedBoard, (player == MAX ? MIN : MAX));

	//This is here to see the move list of the next player, and if it is 0 then we return the evaluation function
	// as there is no more moves to make. This is really here to see if min player has 0 moves so then we have made
	// the correct move and probably will be the best move we make as there are no more moves for the opponent player
	if (moveList.size() == 0) {
		return evaluationFunction(PlayedBoard);		// returns evaluation function of this move as it has made it impossible for the opponent to move
	}

	// This is where we traverse the tree we put the prune at a high number to so then
	// the first node we evaluate it puts in as our new prunning value to prune the other values by.
	// Which we use to send to this function so we know when to prune and stop searching the other nodes.
	// Since it's not random order it is just based off of how I find them in the move list and we just go through starting
	// from the beginning of the list. In those terms I guess you could say they are random for thier values so still could
	// cause us to get the O(b^3h/4)
	bestMove = (player == MIN ? 5000 : -5000);
	nextPlayer = (player == MIN ? MAX : MIN);	// makes the next player for the next move
	holder = 0;									// uses to hold the value that is returned from the evaluation function to compare against the best move so far
	for (int i = 0; i < moveList.size(); i++) {

		// calls this function again but with the nexts players move list, numMoves made is 1 higher, the board is the
		// newBoard we made the move on, and the bestMove is now the prunning value for the next node we search
		holder = TraverseTree(PlayedBoard, moveList[i], numMove + 1, nextPlayer, Alpha, Beta);

		if (player == MIN) {
			// for the MIN node we set the beta whenever we find a move that bestMove from holder so then we can test if 
			// we need to prune or not by seeing it the new beta is less then or equal too alpha. This helps us prune to traverse tree faster
			// and expand less nodes
			if (holder < bestMove) {
				bestMove = holder;
				Beta = bestMove;
			}

			if (Alpha >= Beta) {

				return holder;	// returns holder as it is a worse move so we want to let the MAX node to stick with the move it has already found
			}
		}
		else {
			// This is the same thing as stated up by MIN node but for MAX node we set the alpha value for every best move we find and 
			// then check if alpha is greater then or equal too beta
			if (holder > bestMove) {
				bestMove = holder;	// places better move in our bestMove variable
				Alpha = bestMove;
			}

			if (Alpha >= Beta) {

				return holder;	// returns holder as it is a worse move so we want to let the MIN node to stick with the move it has found already
			}
		}
	}

	return bestMove;
}


struct PossibleMoves MaxTurn(struct CELL board[4][4]) {
	PossibleMoves move;
	int Alpha = -5000, Beta = 5000, holder, highestRatedMove;	// to start the prunning value off with this number
	vector<PossibleMoves> moveList = findMoves(board, MAX);		// finds available moves for the black player	

	// Goes through all the possible moves from the MAX player to see which move is the best one 
	// for it to win the game. It stores the bestMove in bestMove and stores the value in evaluation
	// so then we can keep comparing that value against the other moves values to see if they are better or not.
	for (int i = 0; i < moveList.size(); i++) {
		holder = TraverseTree(board, moveList[i], 0, MAX, Alpha, Beta);		//evaluates the moves with our MINIMAX, Prunning and evaluation function
		if (holder > Alpha) {
			highestRatedMove = i;	// bestMove is not whatever move is at that spot in the vector moveList
			Alpha = holder;			// stores value in evaluation to compare against others moves against it
		}
	}

	// we call this function to make the move we found to be the best move
	PlayersMoveMade(board, moveList[highestRatedMove].row, moveList[highestRatedMove].col, moveList[highestRatedMove].directionRow, moveList[highestRatedMove].directionCol);

	move = moveList[highestRatedMove];
	return move;
}

int main() {
	struct CELL board[4][4];

	// this sets the board to be filled with nothing besides zeros and the opensquare player
	// to signify that the spots are open to move to.
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			board[i][j].player = openSquare;
			board[i][j].count = 0;
		}
	}

	// sets the two players at their starting positions
	// initially, MAX has ten black stones in the top left and MIN has ten white stones in the bottom right
	board[0][0].player = MAX;
	board[0][0].count = 10;
	board[3][3].player = MIN;
	board[3][3].count = 10;

	cout << "CONGA" << endl;

	// choose which evaluation function for the AI agent (MAX) to use. 
	// this allows us to easily change the evalulation function in use to easily compare them
	chooseEvaluationFunction(evaluationFunctionOG);	// seems like this is somehow increased moves played but not sure, might be anecdotal evidence

	// MAX and MIN take turns making moves based on the rules of Conga
	struct PossibleMoves maxTurn, minTurn;
	int movesPlayed = 0;
	while (true)
	{
		maxTurn = MaxTurn(board);	// returns move made on board for MAX player (AI Agent)
		//cout << "MAX moved: x=" <<turn.row << ", y=" << turn.col << endl;		// displays what cell/seed/piece the MAX player moved
		if (maxTurn.movesAccessible == true) {
			cout << "MAX moved (" << maxTurn.row << ", " << maxTurn.col << ") dirRow: " << maxTurn.directionRow << " dirCol: " << maxTurn.directionCol << endl;
			DisplayCongaBoard(board);
			movesPlayed++;
		}
		else {
			cout << "MIN won!!" << endl;
			cout << "GAME OVER - MOVE COUNT: " << movesPlayed << endl;	// displays move count as game is over and MAX player has won
			break;
		}
		minTurn = RandomAgentTurn(board);	// returns move made on board for MIN Player (random Agent)
		if (minTurn.movesAccessible == true) {
			//cout << "MIN moved: x=" << turn.row << ", y=" << turn.col << endl;	// displays what cell/seed/piece the MIN player moved
			cout << "MIN moved (" << minTurn.row << ", " << minTurn.col << ") dirRow: " << minTurn.directionRow << " dirCol: " << minTurn.directionCol << endl; // displays what cell/seed/piece the MIN player moved where
			movesPlayed++;
			DisplayCongaBoard(board);
		}
		else {
			cout << "MAX won!!" << endl;
			cout << "GAME OVER - MOVE COUNT: " << movesPlayed << endl;	// displays move count as game is over and MAX player has won
			break;
		}
	}
	return 0;
}