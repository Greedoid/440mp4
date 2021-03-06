#ifndef __MAZE_H
#define __MAZE_H

#include <iostream>
#include <vector>
#include <utility>
#include "node.h"

class Maze {

	private:	
		std::vector< std::vector<Node> > mazeVector;		//Main vector, contains the maze (2d vector of nodes)
		double forwardProb;
		double leftRightProb;
		double discountDoubleCheck;
		std::vector<Node> wallList;
		std::pair<int, int> terminalPos;
		std::pair<int, int> terminalNeg;
		std::vector<double> utilVector;


	public:
		Maze()
		{
			discountDoubleCheck = .99;
			forwardProb = .8;
			leftRightProb = .1;
			populateMaze();
		};
		Maze(int n)
		{
			discountDoubleCheck = .99;
			populateMaze();
			
		};
		void populateMaze();
		void printMaze();
		void printUtilities();
		void utilityList();
		void mazeMove(int x, int y);
		void valueIterate(int ntimes);
		void QLearning(int ntimes);
		double getNodeUtil(int x, int y, int origX, int origY);
		double getNextQ(int x, int y, int action);

		int randomRow();
		int randomColumn();

		
		Node getNode(int x, int y)
		{
			return mazeVector[x][y];
		};
		
};

#endif
