//prog.cpp

//COMPILATION
//To compile, run makefile
//Then run ./prog <fileName> <sortingType> <depth(if DLS)>

//Example commands for Breadth-First-Search
//make
//./prog input.txt

//Example commands for Depth-Limited-Search. Default depth limit is 9.
//make
//./prog input.txt 9

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include "BlockGame.h"
#include "SearchAlgorithms.h"

using namespace std;

int main(int argc, const char *argv[]){
    ifstream inFile(argv[1]);
    ofstream printFile ("solution.txt");
    string oneLine;
    string solution= "";
    SearchAlgorithms algorithms;
    int depth= 9;

    if(argv[1]==NULL){
        cout<<"You didn't enter an input name."<<endl;
        return 0;
    }

    if(argv[2]==NULL){
        cout<<"You didn't specify the sorting method."<<endl;
        return 0;
    }

    string sortingName= argv[2];
    if(sortingName!="bfs" && sortingName!="dfs" && sortingName!="dls" && sortingName!="a*"){
        cout<<"You entered a wrong sorting algorithm name."<<endl;
        return 0;
    }

    if(argv[3]!=NULL){
        string::size_type sz;
        depth= stoi(argv[3], &sz);
    }
    if(argv[3]==NULL){
        if(sortingName=="dfs" ||  sortingName=="dls"){
            cout<<"You didn't specify the depth. The default depth is 9."<<endl;
        }
    }

    //To measure time
    //clock_t t;
    //t= clock();
    //t= clock()-t;
    //cout<<(float)t/CLOCKS_PER_SEC<<endl;

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
        solution+= game->getInitialState();

        if(sortingName=="bfs"){
            solution+=algorithms.breadthFirstSearch(*game);
        }
        else if(sortingName=="dfs" || sortingName=="dls"){
            solution+= algorithms.depthLimitedSearch(*game, depth);
        }
        else if(sortingName=="a*"){
            solution+= algorithms.aStarAlgorithm(*game);
        }

        if (printFile.is_open()){
            string checkCutoff= game->getInitialState()+"cutoff";
            string checkFailure= game->getInitialState()+"failure";
            if(solution!=checkCutoff && solution!=checkFailure){
                printFile<<game->output(solution)<<endl;
            }
            else if(solution==checkCutoff){
                cout<<"Algorithm reached the limit."<<endl;
            }
            else{
                cout<<"There is no solution."<<endl;
            }
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
