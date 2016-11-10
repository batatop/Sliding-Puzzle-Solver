//BlockGame.cpp

#include <iostream>
#include <string>
#include <stdlib.h>
#include "BlockGame.h"

using namespace std;

BlockGame::BlockGame(){
    initialState= "000000000000000000000000000000000000";
    blockNum= 0;
}

BlockGame::BlockGame(Block allBlocks[], int blockNumber){
    blockNum= blockNumber;
    Block blocks[blockNum];
    for(int i=0; i<blockNum; i++){
        blocks[i]= allBlocks[i];
    }
    initialState= fillBoard(blocks, blockNum);
}

void BlockGame::printBoard(char board[][6]){
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            cout<<board[i][j];
        }
        cout<<""<<endl;
    }
}

string BlockGame::boardToState(char board[][6]){
    string state="";
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            state+= board[i][j];
        }
    }
    return state;
}

string BlockGame::output(string allStates){
    string state= "";
    string solution= "";
    int tempBoard[6][6];
    int counter= 0;
    int blockNum= 0;
    int index= 0;
    while(index<allStates.length()){
        state= allStates.substr(index, 36);
        for(int i=0; i<6; i++){
            for(int j=0; j<6; j++){
                tempBoard[i][j]= state[counter] - '0';
                counter++;
            }
        }
        counter= 0;

        blockNum=0;
        char charBlockNum= blockNum+'0';
        for(int i=0; i<36; i++){
            if(state[i]>charBlockNum){
                charBlockNum= state[i];
            }
        }
        blockNum= charBlockNum-'0';

        Block blocks[blockNum];
        int tempBlockNum= 0;
        for(int i=0; i<6; i++){
            for(int j=0; j<6; j++){
                if(tempBoard[i][j]!=0){
                    tempBlockNum= tempBoard[i][j];
                    if(tempBoard[i+1][j]==tempBlockNum){
                        blocks[tempBlockNum-1].direction= 'v';
                    }
                    else if(tempBoard[i][j+1]==tempBlockNum){
                        blocks[tempBlockNum-1].direction= 'h';
                    }
                    blocks[tempBlockNum-1].length++;
                    if(blocks[tempBlockNum-1].direction== 'h'){
                        if(tempBoard[i][j]!=tempBoard[i][j-1]){
                            blocks[tempBlockNum-1].x= i;
                            blocks[tempBlockNum-1].y= j;
                        }
                    }
                    else if(blocks[tempBlockNum-1].direction== 'v'){
                        for(int k=0; k<6; k++){
                            for(int l=0; l<6; l++){
                                if(tempBoard[k][l]== tempBlockNum){
                                    blocks[tempBlockNum-1].x= i;
                                    blocks[tempBlockNum-1].y= j;
                                }
                            }
                        }
                    }
                }
            }
        }
        index+= 36;

        for(int i=0; i<blockNum; i++){
            solution+= to_string((blocks[i].x+1))+" "+to_string((blocks[i].y+1))+" "+to_string(blocks[i].length)+" "+blocks[i].direction+"\n";
        }
        solution+="\n";
    }

    return solution;
}

string BlockGame::actions(string state){
    string allPossibleActions= "";
    char tempBoard[6][6];
    int counter= 0;
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            tempBoard[i][j]= state[counter];
            counter++;
        }
    }

    blockNum=0;
    char charBlockNum= blockNum+'0';
    for(int i=0; i<36; i++){
        if(state[i]>charBlockNum){
            charBlockNum= state[i];
        }
    }
    blockNum= charBlockNum-'0';

    Block blocks[blockNum];
    int tempBlockNum= 0;
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            if(tempBoard[i][j]!='0'){
                tempBlockNum= tempBoard[i][j]-'0';
                if(tempBoard[i+1][j]==tempBlockNum+'0'){
                    blocks[tempBlockNum-1].direction= 'v';
                }
                else if(tempBoard[i][j+1]==tempBlockNum+'0'){
                    blocks[tempBlockNum-1].direction= 'h';
                }
                blocks[tempBlockNum-1].length++;
                if(blocks[tempBlockNum-1].direction== 'h'){
                    if(tempBoard[i][j]!=tempBoard[i][j-1]){
                        blocks[tempBlockNum-1].x= i;
                        blocks[tempBlockNum-1].y= j;
                    }
                }
                else if(blocks[tempBlockNum-1].direction== 'v'){
                    for(int k=0; k<6; k++){
                        for(int l=0; l<6; l++){
                            if(tempBoard[k][l]== tempBlockNum+'0'){
                                blocks[tempBlockNum-1].x= i;
                                blocks[tempBlockNum-1].y= j;
                            }
                        }
                    }
                }
            }
        }
    }

    for(int i=0; i<blockNum; i++){
        if(blocks[i].direction== 'h'){
            if(move("left", i, blocks, blockNum)!= "0"){
                allPossibleActions+= move("left", i, blocks, blockNum);
            }
            if(move("right", i, blocks, blockNum)!= "0"){
                allPossibleActions+= move("right", i, blocks, blockNum);
            }
        }
        else if(blocks[i].direction== 'v'){
            if(move("up", i, blocks, blockNum)!= "0"){
                allPossibleActions+= move("up", i, blocks, blockNum);
            }
            if(move("down", i, blocks, blockNum)!= "0"){
                allPossibleActions+= move("down", i, blocks, blockNum);
            }
        }
    }

    return allPossibleActions;
}

string BlockGame::fillBoard(Block blocks[], int blockNum){
    char tempBoard[6][6];
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            tempBoard[i][j]= '0';
        }
    }
    for(int i=0; i<blockNum; i++){
        if(blocks[i].x>6 || blocks[i].y>6){
            return "0";
        }
        else if(tempBoard[blocks[i].x][blocks[i].y]!='0'){
            return "0";
        }
    }

    int blockCounter= 1;
    for(int i=0; i<blockNum; i++){
        if(blocks[i].direction=='v'){
            for(int j=0; j<blocks[i].length; j++){
                if(tempBoard[(blocks[i].x)-j][blocks[i].y]!='0'){
                    return "0";
                }
                else if((blocks[i].x-j)>5 || (blocks[i].x-j)<0){
                    return "0";
                }
                else{
                    tempBoard[blocks[i].x-j][blocks[i].y]=blockCounter+'0';
                }
            }
            blockCounter++;
        }
        else if(blocks[i].direction=='h'){
            for(int j=0; j<blocks[i].length; j++){
                if(tempBoard[blocks[i].x][(blocks[i].y+j)]!='0'){
                    return "0";
                }
                else if((blocks[i].y+j)>5 || (blocks[i].y+j)<0){
                    return "0";
                }
                else{
                    tempBoard[blocks[i].x][blocks[i].y+j]=blockCounter+'0';
                }
            }
            blockCounter++;
        }
    }

    return boardToState(tempBoard);
}

string BlockGame::move(string way, int target, Block blocks[], int blockNum){
    Block tempBlocks[blockNum];
    for(int i=0; i<blockNum; i++){
        tempBlocks[i]= blocks[i];
    }

    if(way== "up"){
        tempBlocks[target].x--;
    }
    else if(way== "down"){
        tempBlocks[target].x++;
    }
    else if(way== "left"){
        tempBlocks[target].y--;
    }
    else if(way== "right"){
        tempBlocks[target].y++;
    }


    if(fillBoard(tempBlocks, blockNum)!="0"){
        return fillBoard(tempBlocks, blockNum);
    }

    return "0";
}

string BlockGame::getInitialState(){
    return initialState;
}

bool BlockGame::checkWin(string state){
    if(state[17]=='1'){
        return true;
    }
    return false;
}

void BlockGame::printPossibleStates(string possibleStates){
    int index= 0;
    int indexTwo= 0;
    string tempString;

    cout<<"Possible Moves: "<<(possibleStates.length())/36<<endl;
    cout<<""<<endl;

    while(index<possibleStates.length()){
        tempString= possibleStates.substr(index, 36);
        while(indexTwo<tempString.length()){
            cout<<tempString.substr(indexTwo, 6)<<endl;
            indexTwo+= 6;
        }
        cout<<""<<endl;
        index+= 36;
        indexTwo= 0;
    }
}

int BlockGame::distanceToStart(string state){
    string checkingState= initialState;
    int distance= 0;
    char tempBoard[6][6];

    bool found= false;
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            if(!found && checkingState[(i*6)+j]=='1'){
                distance= j;
                found= true;
            }
        }
    }

    checkingState= state;
    found= false;
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            if(!found && checkingState[(i*6)+j]=='1'){
                distance= j - distance;
                found= true;
            }
        }
    }

    return abs(distance);
}

int BlockGame::distanceToFinish(string state){
    int distance= 0;
    char tempBoard[6][6];

    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            if(state[(i*6)+j]=='1'){
                distance= 5 - j;
            }
        }
    }

    return abs(distance);
}
