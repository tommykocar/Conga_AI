

//File: Main.cpp - Main function implementation
//
// This is the main cpp which holds the main function and all the other methods/functions we have created to run the code.
// We have two players of the game Conga which will be MAX and MIN players. MAX is our AI agent that evaluates the moves possible
// and picks the best one according to our evaluation function. Min is our Random agent that will just look at the possible moves
// and pick a random moves from them. The max player uses black pieces and the min player uses white pieces. So when the board is displayed
// it will shows the number of seeds with a "b" or "w" next to them to signify the color of the seeds. This is how you know whos pieces are what
//
//
//
// Author:    Thomas Kocar and Andrew Fox, University of Toledo
// Date:      November 1, 2020



#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Conga.h"

using namespace std;

// This function is here to copy the board we start with so then when we are traveling down the tree for MINIMAX
void copyboard(struct CELL CopiedBoard[4][4], struct CELL board[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			CopiedBoard[i][j].player = board[i][j].player;			//copies the player from the original board to the copy of the board
			CopiedBoard[i][j].value = board[i][j].value;			//copies the value from the original board to the copy of the board
		}
	}
}

// This prints out the board with the move we have made.
// This allows everyone to see what move you made that turn and make sure that it is a valid move according to the rules
void PRINTBoard(struct CELL board[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << board[i][j].value;					// prints the value at the cell we are at
			if (board[i][j].player == MAX) {
				cout << "b | ";							// prints b for black player which is the MAX player(AI AGENT)
			}
			else if (board[i][j].player == MIN) {
				cout << "w | ";							// prints w for whith player which is the MIN player(random AGENT)
			}
			else {
				cout << "  | ";							// prints just a line with a space as it is an opensquare so there is no content in it
			}


		}
		cout << endl;
		if (i < 3)cout << "--------------------" << endl;
	}
}


// This right here is our evaluation function of how we find the best move to make for the AI Agent. Our evaluation function counts up the cells
// that the MAX player is filling up and subtracts it against the possible moves the MIN player can make. This helps us figure out how many cells we
// can move to, in order for them to not have as many or any cells to move to making us the winner of the game
int evaluationFunction(struct CELL board[4][4]) {


	int numofMAXseeds = 0, numofMINmoves = 0;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (board[i][j].player == MAX) {
				numofMAXseeds++;								// adds to count as the cell we visited from the board has the MAX player in it
			}
			else if (board[i][j].player == MIN) {


				// These if statements are exactly like the ones in move list. As we want to see how many moves are available to the MIN player
				// from that cell so the if statements are all based on the specific cell they are in so we don't have to go through 8 if statements everytime.
				// This will allow us to see how many moves the white player will have left if we make this move allowing us to block as many cells as possible.
				if (j == 0) {
					if (i == 0) {
						if (board[i][j + 1].player == MIN || board[i][j + 1].player == openSquare) numofMINmoves++;

						if (board[i + 1][j + 1].player == MIN || board[i + 1][j + 1].player == openSquare) numofMINmoves++;

						if (board[i + 1][j].player == MIN || board[i + 1][j].player == openSquare)numofMINmoves++;
					}
					else if (i == 3) {
						if (board[i][j + 1].player == MIN || board[i][j + 1].player == openSquare) numofMINmoves++;

						if (board[i - 1][j + 1].player == MIN || board[i - 1][j + 1].player == openSquare) numofMINmoves++;

						if (board[i - 1][j].player == MIN || board[i - 1][j].player == openSquare) numofMINmoves++;

					}
					else {
						if (board[i + 1][j].player == MIN || board[i + 1][j].player == openSquare) numofMINmoves++;
						if (board[i + 1][j + 1].player == MIN || board[i + 1][j + 1].player == openSquare) numofMINmoves++;
						if (board[i][j + 1].player == MIN || board[i][j + 1].player == openSquare) numofMINmoves++;
						if (board[i - 1][j + 1].player == MIN || board[i - 1][j + 1].player == openSquare) numofMINmoves++;
						if (board[i - 1][j].player == MIN || board[i - 1][j].player == openSquare) numofMINmoves++;
					}
				}
				else if (j == 1 || j == 2) {
					if (i == 0) {
						if (board[i][j + 1].player == MIN || board[i][j + 1].player == openSquare) numofMINmoves++;

						if (board[i + 1][j + 1].player == MIN || board[i + 1][j + 1].player == openSquare) numofMINmoves++;

						if (board[i + 1][j].player == MIN || board[i + 1][j].player == openSquare) numofMINmoves++;

						if (board[i + 1][j - 1].player == MIN || board[i + 1][j - 1].player == openSquare) numofMINmoves++;

						if (board[i][j - 1].player == MIN || board[i][j - 1].player == openSquare) numofMINmoves++;
					}
					else if (i == 3) {
						if (board[i][j - 1].player == MIN || board[i][j - 1].player == openSquare) numofMINmoves++;

						if (board[i - 1][j - 1].player == MIN || board[i - 1][j - 1].player == openSquare) numofMINmoves++;

						if (board[i - 1][j].player == MIN || board[i - 1][j].player == openSquare) numofMINmoves++;
						if (board[i - 1][j + 1].player == MIN || board[i - 1][j + 1].player == openSquare) numofMINmoves++;
						if (board[i][j + 1].player == MIN || board[i][j + 1].player == openSquare) numofMINmoves++;
					}
					else {
						if (board[i + 1][j].player == MIN || board[i + 1][j].player == openSquare) numofMINmoves++;
						if (board[i + 1][j + 1].player == MIN || board[i + 1][j + 1].player == openSquare) numofMINmoves++;
						if (board[i][j + 1].player == MIN || board[i][j + 1].player == openSquare) numofMINmoves++;
						if (board[i - 1][j + 1].player == MIN || board[i - 1][j + 1].player == openSquare) numofMINmoves++;
						if (board[i - 1][j].player == MIN || board[i - 1][j].player == openSquare) numofMINmoves++;
						if (board[i - 1][j - 1].player == MIN || board[i - 1][j - 1].player == openSquare) numofMINmoves++;
						if (board[i + 1][j - 1].player == MIN || board[i + 1][j - 1].player == openSquare) numofMINmoves++;
						if (board[i][j - 1].player == MIN || board[i][j - 1].player == openSquare) numofMINmoves++;
					}
				}
				else if (j == 3) {
					if (i == 0) {
						if (board[i][j - 1].player == MIN || board[i][j - 1].player == openSquare) numofMINmoves++;

						if (board[i + 1][j - 1].player == MIN || board[i + 1][j - 1].player == openSquare) numofMINmoves++;

						if (board[i + 1][j].player == MIN || board[i + 1][j].player == openSquare) numofMINmoves++;
					}
					else if (i == 3) {
						if (board[i][j - 1].player == MIN || board[i][j - 1].player == openSquare) numofMINmoves++;

						if (board[i - 1][j - 1].player == MIN || board[i - 1][j - 1].player == openSquare) numofMINmoves++;

						if (board[i - 1][j].player == MIN || board[i - 1][j].player == openSquare) numofMINmoves++;
					}
					else {
						if (board[i + 1][j].player == MIN || board[i + 1][j].player == openSquare) numofMINmoves++;
						if (board[i - 1][j].player == MIN || board[i - 1][j].player == openSquare) numofMINmoves++;
						if (board[i - 1][j - 1].player == MIN || board[i - 1][j - 1].player == openSquare) numofMINmoves++;
						if (board[i + 1][j - 1].player == MIN || board[i + 1][j - 1].player == openSquare) numofMINmoves++;
						if (board[i][j - 1].player == MIN || board[i][j - 1].player == openSquare) numofMINmoves++;
					}
				}

			}
		}
	}


	if (numofMINmoves++ == 0) {
		return 50;					// returns a very large value to signify that this move allowed us to win so this is the move that is the best and no one can beat it
	}

	else {
		return numofMAXseeds - numofMINmoves++;		// Gives us the value to fill us in if this is a good move or a bad move for the AI agent
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
					if (board[i][j + 1].player == player || board[i][j + 1].player == openSquare) moveList.push_back(PossibleMoves(i, j, 0, 1, true));

					if (board[i + 1][j + 1].player == player || board[i + 1][j + 1].player == openSquare) moveList.push_back(PossibleMoves(i, j, 1, 1, true));

					if (board[i + 1][j].player == player || board[i + 1][j].player == openSquare) moveList.push_back(PossibleMoves(i, j, 1, 0, true));
				}
				else if (i == 3) {
					if (board[i][j + 1].player == player || board[i][j + 1].player == openSquare) moveList.push_back(PossibleMoves(i, j, 0, 1, true));

					if (board[i - 1][j + 1].player == player || board[i - 1][j + 1].player == openSquare) moveList.push_back(PossibleMoves(i, j, -1, 1, true));

					if (board[i - 1][j].player == player || board[i - 1][j].player == openSquare) moveList.push_back(PossibleMoves(i, j, -1, 0, true));

				}
				else {
					if (board[i + 1][j].player == player || board[i + 1][j].player == openSquare) moveList.push_back(PossibleMoves(i, j, 1, 0, true));
					if (board[i + 1][j + 1].player == player || board[i + 1][j + 1].player == openSquare) moveList.push_back(PossibleMoves(i, j, 1, 1, true));
					if (board[i][j + 1].player == player || board[i][j + 1].player == openSquare) moveList.push_back(PossibleMoves(i, j, 0, 1, true));
					if (board[i - 1][j + 1].player == player || board[i - 1][j + 1].player == openSquare) moveList.push_back(PossibleMoves(i, j, -1, 1, true));
					if (board[i - 1][j].player == player || board[i - 1][j].player == openSquare) moveList.push_back(PossibleMoves(i, j, -1, 0, true));
				}
			}
			else if (j == 1 || j == 2) {
				if (i == 0) {
					if (board[i][j + 1].player == player || board[i][j + 1].player == openSquare) moveList.push_back(PossibleMoves(i, j, 0, 1, true));

					if (board[i + 1][j + 1].player == player || board[i + 1][j + 1].player == openSquare) moveList.push_back(PossibleMoves(i, j, 1, 1, true));

					if (board[i + 1][j].player == player || board[i + 1][j].player == openSquare) moveList.push_back(PossibleMoves(i, j, 1, 0, true));

					if (board[i + 1][j - 1].player == player || board[i + 1][j - 1].player == openSquare) moveList.push_back(PossibleMoves(i, j, 1, -1, true));

					if (board[i][j - 1].player == player || board[i][j - 1].player == openSquare) moveList.push_back(PossibleMoves(i, j, 0, -1, true));
				}
				else if (i == 3) {
					if (board[i][j - 1].player == player || board[i][j - 1].player == openSquare) moveList.push_back(PossibleMoves(i, j, 0, -1, true));

					if (board[i - 1][j - 1].player == player || board[i - 1][j - 1].player == openSquare) moveList.push_back(PossibleMoves(i, j, -1, -1, true));

					if (board[i - 1][j].player == player || board[i - 1][j].player == openSquare) moveList.push_back(PossibleMoves(i, j, -1, 0, true));
					if (board[i - 1][j + 1].player == player || board[i - 1][j + 1].player == openSquare) moveList.push_back(PossibleMoves(i, j, -1, 1, true));
					if (board[i][j + 1].player == player || board[i][j + 1].player == openSquare) moveList.push_back(PossibleMoves(i, j, 0, 1, true));
				}
				else {
					if (board[i + 1][j].player == player || board[i + 1][j].player == openSquare) moveList.push_back(PossibleMoves(i, j, 1, 0, true));
					if (board[i + 1][j + 1].player == player || board[i + 1][j + 1].player == openSquare) moveList.push_back(PossibleMoves(i, j, 1, 1, true));
					if (board[i][j + 1].player == player || board[i][j + 1].player == openSquare) moveList.push_back(PossibleMoves(i, j, 0, 1, true));
					if (board[i - 1][j + 1].player == player || board[i - 1][j + 1].player == openSquare) moveList.push_back(PossibleMoves(i, j, -1, 1, true));
					if (board[i - 1][j].player == player || board[i - 1][j].player == openSquare) moveList.push_back(PossibleMoves(i, j, -1, 0, true));
					if (board[i - 1][j - 1].player == player || board[i - 1][j - 1].player == openSquare) moveList.push_back(PossibleMoves(i, j, -1, -1, true));
					if (board[i + 1][j - 1].player == player || board[i + 1][j - 1].player == openSquare) moveList.push_back(PossibleMoves(i, j, 1, -1, true));
					if (board[i][j - 1].player == player || board[i][j - 1].player == openSquare) moveList.push_back(PossibleMoves(i, j, 0, -1, true));
				}
			}
			else if (j == 3) {
				if (i == 0) {
					if (board[i][j - 1].player == player || board[i][j - 1].player == openSquare) moveList.push_back(PossibleMoves(i, j, 0, -1, true));

					if (board[i + 1][j - 1].player == player || board[i + 1][j - 1].player == openSquare) moveList.push_back(PossibleMoves(i, j, 1, -1, true));

					if (board[i + 1][j].player == player || board[i + 1][j].player == openSquare) moveList.push_back(PossibleMoves(i, j, 1, 0, true));
				}
				else if (i == 3) {
					if (board[i][j - 1].player == player || board[i][j - 1].player == openSquare) moveList.push_back(PossibleMoves(i, j, 0, -1, true));

					if (board[i - 1][j - 1].player == player || board[i - 1][j - 1].player == openSquare) moveList.push_back(PossibleMoves(i, j, -1, -1, true));

					if (board[i - 1][j].player == player || board[i - 1][j].player == openSquare) moveList.push_back(PossibleMoves(i, j, -1, 0, true));
				}
				else {
					if (board[i + 1][j].player == player || board[i + 1][j].player == openSquare) moveList.push_back(PossibleMoves(i, j, 1, 0, true));
					if (board[i - 1][j].player == player || board[i - 1][j].player == openSquare) moveList.push_back(PossibleMoves(i, j, -1, 0, true));
					if (board[i - 1][j - 1].player == player || board[i - 1][j - 1].player == openSquare) moveList.push_back(PossibleMoves(i, j, -1, -1, true));
					if (board[i + 1][j - 1].player == player || board[i + 1][j - 1].player == openSquare) moveList.push_back(PossibleMoves(i, j, 1, -1, true));
					if (board[i][j - 1].player == player || board[i][j - 1].player == openSquare) moveList.push_back(PossibleMoves(i, j, 0, -1, true));
				}
			}

		}
	}
	return moveList;
}

// this function is here to make the move we deemed as the best possible move (for black player) 
void PlayersMoveMade(int x, int y, int x_dir, int y_dir, struct CELL board[4][4]) {
	Player player = board[x][y].player;					// takes the player at the cell we are starting/moving from
	int value = board[x][y].value;						// takes the value at the cell we are starting/moving from
	int holdX = x, holdY = y, spacesPossible = 0;		// holds the x and y values to see how many possible cells are open or the cells that we can move 
														// by going toward the direction until there are no more cells that direction or there is the opponent blocking us from moving again
	
	// this for loop goes through 3 times as that is the most possible cells you can travel in one move.
	// It will only go 3 times if it doesn't break from either going over the array size on either row/column
	// or it will stop if their is an opponent in the way
	for (int i = 0; i < 3; i++)			
	{
		holdX += x_dir;
		holdY += y_dir;
		if((holdX + x_dir) > 3|| (holdX + x_dir) < 0 || (holdY + y_dir) > 3 || (holdY + y_dir) < 0 || board[holdX + x_dir][holdY + y_dir].player == (player == MAX ? MIN : MAX))
		{
			break;
		}
		else
		{
			spacesPossible++;						// adds up the total possible moves that can be traveled in that certain direction
		}
	}
	

	// these next three if statements will move the pieces to the designated cells based on their
	// values and possible moves they can make in the direction
	if ((value > 0 && value < 2) ||  spacesPossible == 0) {
		board[x + x_dir][y + y_dir].player = board[x][y].player;			// moves player into the first cell in that diretion
		board[x + x_dir][y + y_dir].value += board[x][y].value;				// adds the value of the cell we started at to the cell we are going
		board[x][y].player = openSquare;									// clears player or makes player open square if you will so then we know that the cell we started at is now open
		board[x][y].value = 0;												// clears the value at our starting cell so then 
	}
	else if ((value > 1 && value < 4) || spacesPossible == 1 ) {
		board[x + x_dir][y + y_dir].player = board[x][y].player;			// moves player from starting cell into cell we are traveling too
		board[x + x_dir][y + y_dir].value += 1;								// adds one to the cell we are headed to as it is moving more then one cell and first cell we travel to we always put 1 into
		board[x][y].value -= 1;												// subtracts one from the value in our starting cell

		
		board[x + x_dir + x_dir][y + y_dir + y_dir].player = board[x][y].player;		// moves player to second cell we are traveling too from the starting cell
		board[x + x_dir + x_dir][y + y_dir + y_dir].value += board[x][y].value;			// moves the rest of our remaining value to the second cell as that is the only number of spaces we can travel too
		

		board[x][y].player = openSquare;			// clears player (makes player openSquare) so we know that the cell we started at now has nothing in it
		board[x][y].value = 0;						// clears value as we haved moved our values to new cells
	}
	else {
		
		board[x + x_dir][y + y_dir].player = board[x][y].player;		// moves player from starting cell to the next cell we move to
		board[x + x_dir][y + y_dir].value += 1;							// adds 1 to the value already in the cell we are going too
		board[x][y].value -= 1;											// subtracts 1 from our value in the starting cell

		
		
		board[x + x_dir + x_dir][y + y_dir + y_dir].player = board[x][y].player;	// moves player from startin cell to the second cell we move to
		board[x + x_dir + x_dir][y + y_dir + y_dir].value += 2;						// adds 2 to the second cell as we have more then 3 and we are moving three cells so we put 2 in the cell we move to second
		board[x][y].value -= 2;														// subtracts 2 from the value at the starting cell as we just moved 2 into our the cell we move to second
		
		
			board[x + x_dir + x_dir + x_dir][y + y_dir + y_dir + y_dir].player = board[x][y].player;	// we move player from starting cell into the final cell we move to
			board[x + x_dir + x_dir + x_dir][y + y_dir + y_dir + y_dir].value += board[x][y].value;		// we move the remaining value we have from first cell into final cell we move to
		

		board[x][y].player = openSquare;				// we clear the player in the starting cell (making it openSquare) so we know it is open to be moved to
		board[x][y].value = 0;							// we clear value from the starting cell as there are no seeds there
	}
}


// This function is here to make the move when its whites turn. It will find the moves possible
// and then choose a random move from the availables moves. This will give us the random agent we want to play against.
struct PossibleMoves RandomAgentturn(struct CELL board[4][4]) {
	vector<PossibleMoves> moveList = findMoves(board, MIN);		// calls findMoves function to get the available moves
	PossibleMoves move;


	srand(time(NULL));		// this uses the internal clock to control the choice of the move. Since time is always changing the move we choose will always be changing, hence random.

	
	if (moveList.size() == 0) {
		move.movesAccessible = false;				// if the movesList size is 0 means that we found no possible moves so moves available are false, since there are none.
		return move;							// return that as our random move
	}
	else {
		PossibleMoves randomMove = moveList[rand() % moveList.size()];											// this makes randomMove hold the random move we choose from the moves available
		PlayersMoveMade(randomMove.i, randomMove.j, randomMove.directionI, randomMove.directionJ, board);		// this then makes the move that we just randomly chose
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
	struct CELL PlayedBoard[4][4];																	// creates a newBoard 
	copyboard(PlayedBoard, board);																	// makes the newBoard identical to board to make it identical to the original board
	PlayersMoveMade(newMove.i, newMove.j, newMove.directionI, newMove.directionJ, PlayedBoard);	// makes the move we sent in newMove in the newBoard so then we can evaluate it later
	
	
	if (numMove == 4) {
		
		return evaluationFunction(PlayedBoard);					// it has reached the depth we want to evaluate from so it returns the value of the evaluation function
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
	nextPlayer = (player == MIN ? MAX : MIN);				// makes the next player for the next move
	holder = 0;												// uses to hold the value that is returned from the evaluation function to compare against the best move so far
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

				return holder;			// returns holder as it is a worse move so we want to let the MAX node to stick with the move it has already found
			}
		}
		else {
			// This is the same thing as stated up by MIN node but for MAX node we set the alpha value for every best move we find and 
			// then check if alpha is greater then or equal too beta
			if (holder > bestMove) {
				bestMove = holder;			// places better move in our bestMove variable
				Alpha = bestMove;
			}
			
			if (Alpha >= Beta) {

				return holder;				// returns holder as it is a worse move so we want to let the MIN node to stick with the move it has found already
			}
		}
	}

	return bestMove;
}


struct PossibleMoves MAXturn(struct CELL board[4][4]) {	
	PossibleMoves move;
	int Alpha = -5000, Beta = 5000, holder, highestRatedMove;								// to start the prunning value off with this number
	vector<PossibleMoves> moveList = findMoves(board, MAX);		// finds available moves for the black player	

	

	// Goes through all the possible moves from the MAX player to see which move is the best one 
	// for it to win the game. It stores the bestMove in bestMove and stores the value in evaluation
	// so then we can keep comparing that value against the other moves values to see if they are better or not.
	for (int i = 0; i < moveList.size(); i++) {
		holder = TraverseTree(board, moveList[i], 0, MAX, Alpha, Beta);		//evaluates the moves with our MINIMAX, Prunning and evaluation function
		if (holder > Alpha) {
			highestRatedMove = i;					// bestMove is not whatever move is at that spot in the vector moveList
			Alpha = holder;					// stores value in evaluation to compare against others moves against it
		}
	}

	// we call this function to make the move we found to be the best move
	PlayersMoveMade(moveList[highestRatedMove].i, moveList[highestRatedMove].j, moveList[highestRatedMove].directionI, moveList[highestRatedMove].directionJ, board);

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
			board[i][j].value = 0;
		}
	}

	// sets the two players at their starting positions
	board[0][0].player = MAX;
	board[0][0].value = 10;
	board[3][3].player = MIN;
	board[3][3].value = 10;

	cout << "CONGA" << endl;

	// MAX and MIN take turns making moves based on the rules of Conga
	struct PossibleMoves turn;
	int movesPlayed = 0;
	while (true)
	{
		turn = MAXturn(board);		// returns move made on board for MAX player
		cout << "MAX moved: x=" <<turn.i << ", y=" << turn.j << endl;		// displays what cell/seed/piece the MAX player moved
		PRINTBoard(board);
		movesPlayed++;

		turn = RandomAgentturn(board);		// returns move made on board for MIN Player
		if (turn.movesAccessible == true) {
			cout << "MIN moved: x=" << turn.i << ", y=" << turn.j << endl;	// displays what cell/seed/piece the MIN player moved
			movesPlayed++;
			PRINTBoard(board);
		}
		else {
			cout << "MAX won!!" << endl;									
			cout << "GAME OVER - MOVE COUNT: " << movesPlayed << endl;		// displays move count as game is over and MAX player has won
			break;
		}
	
	}

	return 0;
}