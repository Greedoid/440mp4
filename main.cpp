#include"node.h"
#include"maze.h"

#include<iostream>


int main()
{

	Maze newMaze = Maze();
	newMaze.valueIterate(200);
	newMaze.utilityList();
};
