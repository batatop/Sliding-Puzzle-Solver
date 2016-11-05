//SearchAlgorithms.cpp

#include <iostream>
#include <queue>
#include <set>
#include <string>
#include "SearchAlgorithms.h"

using namespace std;

SearchAlgorithms::SearchAlgorithms(){
    root= NULL;
}

string SearchAlgorithms::breadthFirstSearch(BlockGame problem){
    Node* node= new Node();
    node->state= problem.getInitialState();
    node->parent= NULL;
    root= node;
    if(problem.checkWin(node->state)){
        return solution(node);
    }
    queue<Node*> frontier;
    frontier.push(node);
    set<string> explored;
    bool is_in;

    bool reached= false;
    string action="";
    int i=0;
    int x= 0;
    while(!reached){
        if(frontier.empty()){
            //cout<<"burda"<<endl;
            return "There is no solution.";
        }
        node= frontier.front();
        frontier.pop();
        //cout<<frontier.size()<<endl;
        explored.insert(node->state);
        action= problem.actions(node->state);
        //cout<<action.length()<<endl;
        while(i<action.length()){
            x++;
            //cout<<x<<endl;
            //cout<<i<<endl;
            //cout<<action.length()<<endl;
            Node* child= new Node();
            child->state= action.substr(i, 36);
            child->parent= node;
            is_in= explored.find(child->state) != explored.end();
            //cout<<is_in<<endl;
            if(!is_in){
                if(problem.checkWin(child->state)){
                    //cout<<"bitti mi lo"<<endl;
                    return solution(child);
                }
                //cout<<"pust"<<endl;
                frontier.push(child);
                //cout<<frontier.size()<<endl;
                //cout<<(frontier.front())->state<<endl;
                action= action.substr(i, action.length()-36);
            }
            i+=36;
        }
        i=0;
        action="";
    }

}

string SearchAlgorithms::solution(Node* node){
    Node* tempNode= node;
    int index= 0;
    int steps= 0;
    string solution="";
    //cout<<root->state<<endl;
    //cout<<node->state<<endl;
    while(tempNode->state!= root->state){
        steps++;
        tempNode= tempNode->parent;
    }
    cout<<"Solved with "<<steps<<" steps. You can find the steps in the 'solution.txt' file."<<endl;

    string stepStates[steps];
    tempNode= node;
    index= steps-1;
    while(tempNode->state!= root->state){
        stepStates[index]= tempNode->state;
        tempNode= tempNode->parent;
        index--;
    }

/*
    index=0;
    for(int i=0; i<steps; i++){
        while(index<stepStates[i].length()){
            cout<<stepStates[i].substr(index, 6)<<endl;
            index+= 6;
        }
        cout<<""<<endl;
        index= 0;
    }
    */
    for(int i=0; i<steps; i++){
            solution+= stepStates[i];
    }
    //cout<<solution<<endl;

    return solution;
}
