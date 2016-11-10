//BlockGame.h

#ifndef BLOCKGAME
#define BLOCKGAME

#include<iostream>
#include <string>

using namespace std;


class Block{
    public:
        int x;
        int y;
        int length= 0;
        char direction;
};

class BlockGame {
    public:
        BlockGame();
        //Initilizes the block num to 0 and state to an empty board condition

        BlockGame(Block blocks[], int blockNumber);
        //Sets the blockNum to blockNumber and creates an initial state

        void printBoard(char board[][6]);
        //Prints the board

        string boardToState(char board[][6]);
        //Converts the board to a state and returns it

        string output(string allStates);
        //Returns the output version of the solution

        string actions(string state);
        //Checks all the possible states from the given state and adds them
        //together. It returns it as one long string

        string fillBoard(Block blocks[], int blockNum);
        //Fills the board and returns it as a state string

        string move(string way, int target, Block blocks[], int blockNum);
        //Checks a single block's movements to a single direction. If the
        //block's move is legal, it returns the new state. If not, it returns "0"

        string getInitialState();
        //returns the initialState

        bool checkWin(string state);
        //Checks if the game is over. Returns true if it is, false if it's not

        void printPossibleStates(string possibleStates);
        //Print the possible states in a readable way.

        int distanceToStart(string state);
        //returns g(n) for the a* algorithm

        int distanceToFinish(string state);
        //returns h(n) for the a* algorithm

    private:
        string initialState;
        int blockNum;
};

#endif
