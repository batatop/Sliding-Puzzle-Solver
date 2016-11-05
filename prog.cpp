//prog.cpp

#include <iostream>
#include <fstream>
#include <string>
#include "BlockGame.h"
#include "SearchAlgorithms.h"

using namespace std;

int main(){
    ifstream inFile("input.txt");
    ofstream printFile ("solution.txt");
    string oneLine;
    string solution= "";
    SearchAlgorithms bfs;
    int blockNum= 0;
    char board[6][6];
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            board[i][j]= '0';
        }
    }
    int counter=0;


    if(inFile.is_open()){
        while(getline(inFile, oneLine)){
            if(oneLine!=""){
                blockNum++;
            }
        }
        inFile.clear();
        inFile.seekg(0, inFile.beg);
        Block blocks[blockNum];
        while(getline(inFile, oneLine)){
            blocks[counter].x= (oneLine[0]-'0')-1;
            blocks[counter].y= (oneLine[2]-'0')-1;
            blocks[counter].length= oneLine[4]-'0';
            blocks[counter].direction= oneLine[6];
            counter++;
        }
        inFile.close();

        BlockGame *game= new BlockGame(blocks, blockNum);
        //cout<<game->getInitialState()<<endl;
        solution+= game->getInitialState();
        //cout<<game->actions(game->getInitialState())<<endl;
        //game->printPossibleStates(game->actions(game->getInitialState()));
        solution+=bfs.breadthFirstSearch(*game);
        //cout<<game->output(solution)<<endl;

        if (printFile.is_open()){
            printFile<<game->output(solution)<<endl;
            printFile.close();
        }
        else{
            cout<<"Unable to open the file."<<endl;
        }

    }
    else{
        cout<<"Unable to read the file."<<endl;
    }

    return 0;

}
