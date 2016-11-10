tester: prog.o BlockGame.o SearchAlgorithms.o
	g++ -std=c++11 prog.o BlockGame.o SearchAlgorithms.o -o prog

prog.o: prog.cpp BlockGame.h SearchAlgorithms.h
	g++ -c -std=c++11 prog.cpp

BlockGame.o: BlockGame.cpp BlockGame.h
	g++ -c -std=c++11 BlockGame.cpp

SearchAlgorithms.o: SearchAlgorithms.cpp SearchAlgorithms.h
	g++ -c -std=c++11 SearchAlgorithms.cpp

clean:
	rm -f *.o prog solution.txt
