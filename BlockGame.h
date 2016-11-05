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
        //Creates a board with 0 blocks in it

        BlockGame(Block blocks[], int blockNum);
        //Creates a board and places the blocks according to the parameter

        string fillBoard(Block blocks[], int blockNum);
        //Fills the board

        void printBoard(int board[][6]);
        //Prints the current state

        void printPossibleStates(string possibleStates);
        //Print the state in a pleasant way

        string boardToState(int board[][6]);
        //Converts the board to a state

        string actions(string state);
        //Moves the blocks

        string move(string way, int target, Block blocks[], int blockNum);
        //moves the blocks

        string getInitialState();
        //returns the initialState

        bool checkWin(string state);
        //Checks if the have been beate

        string output(string allStates);
        //prints the output version

    private:
        int board[6][6];
        string initialState;
        int blockNum;
};

#endif
