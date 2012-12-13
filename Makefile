all: markovMaze

markovMaze: main.o maze.o node.o
	g++ main.o maze.o node.o -o markovMaze

main.o: main.cpp
	g++ -c main.cpp

maze.o: maze.h maze.cpp
	g++ -c maze.h maze.cpp

node.o: node.h node.cpp
	g++ -c node.h node.cpp

clean:
	rm -rf *.gch *.o markovMaze
