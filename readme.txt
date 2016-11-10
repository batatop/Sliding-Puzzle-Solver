INPUT FILE
The input file should be similar to the "output.txt" file that you provided. It should only 
have one state. For example for the "output.txt" file that you provided, the input should be:
3 2 2 h
4 1 2 v
6 1 2 v
5 2 2 v
6 3 2 h
3 4 3 v
3 5 2 v 

COMPILATION
To compile, run makefile
Then run ./prog <fileName> <sortingType> <depth(if DLS)>

Example commands for Breadth-first-search
make
./prog input.txt bfs

Example commands for Depth-limited-search. Default depth limit is 9.
make
./prog input.txt dfs 9
---or---
make
./prog input.txt dls 9

Example commands for A*-algorithm.
make
./prog input.txt a*
