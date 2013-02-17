#include "maze.h"
#include<math.h>
#include<iostream>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<iomanip>
#include<algorithm>



double Maze::getNodeUtil(int x, int y, int origX, int origY)
{
	if (x<0 || x >= mazeVector.size() || y < 0 || y >= mazeVector[0].size() || mazeVector[x][y].isWall())
	{
		return mazeVector[origX][origY].getUtility(); 
	}
	return mazeVector[x][y].getUtility();

};

double RMS()
{
	
};

double Maze::getNextQ(int x, int y, int action)
{
	int newRow = x;
	int newColumn = y;
	int rowSize = mazeVector.size();
	int columnSize = mazeVector[0].size();

	if (action == 0)				//up
	{
		newRow = std::max(newRow - 1, 0); 
	}
	if (action == 1)					//left
	{	
		newColumn =  std::max(newColumn - 1, 0);
	}
	if (action == 2)				//down
	{
		newRow = std::min(newRow+1, rowSize-1);
	}
	if (action == 3)				//right
	{
		newColumn = std::min(newColumn+1, columnSize-1);
	}


	if (mazeVector[newRow][newColumn].isWall())
	{
		return mazeVector[x][y].getUtility();
	}
	
	return mazeVector[newRow][newColumn].getUtility();
};

int randomAction()
{
	return rand() % 4;
};

int Maze::randomRow()
{
	return rand() % 4;
};

int Maze::randomColumn()
{
	return rand() % 6;
};

void Maze::populateMaze()
{	
	for (int i = 0; i < 4; i++)
	{
		std::vector<Node> interVector;
		for (int j = 0; j < 6; j++)
		{
			if (i == 0 && j == 0)
			{
				Node newNode = Node(false, 0);
				newNode.setStart();
				interVector.push_back(newNode);

			}
			else if (i == 1 && j == 1 || i == 2 && j == 1 || i == 0 && j == 2 || i == 2 && j == 4)
			{	
				Node newNode = Node(true, 0);
				interVector.push_back(newNode);
				wallList.push_back(newNode);
			}
			else if (i == 0 && j == 5)
			{
				Node newNode = Node(false, 1);
				interVector.push_back(newNode);
				terminalPos.first = i;
				terminalPos.second = j;
			}
			else if (i == 1 && j == 5)
			{
				Node newNode = Node(false, 2);
				interVector.push_back(newNode);
				terminalNeg.first = i;
				terminalNeg.second = j;
			}
			else
			{
				Node newNode = Node(false, 0);
				interVector.push_back(newNode);
			}
	
		}
		mazeVector.push_back(interVector);
	}
};

void Maze::printMaze()
{
	for (int i = 0; i < mazeVector.size(); i++)
	{
		for (int j = 0; j < mazeVector[i].size(); j++)
		{
			std::cout <<"[ " <<  mazeVector[i][j].getChar() << " ]";
		}
		std::cout << "\n";
	}
	
};

void Maze::valueIterate(int nTimes)
{
for (int times = 0; times < nTimes; times++)
{
	for (int i = 0; i < mazeVector.size(); i++)
	{
		for (int j = 0; j < mazeVector[i].size(); j++)
		{
			if (!mazeVector[i][j].isTerminal())
			{
				double up = getNodeUtil (i-1, j, i, j);
				double left = getNodeUtil (i, j-1, i, j);
				double down = getNodeUtil (i+1, j, i, j);
				double right = getNodeUtil (i, j+1, i, j);

				double upUtility = (up*forwardProb + left*leftRightProb + right*leftRightProb)*discountDoubleCheck + mazeVector[i][j].getReward();
				double leftUtility = (left*forwardProb + up*leftRightProb + down*leftRightProb)*discountDoubleCheck + mazeVector[i][j].getReward();
				double downUtility = (down*forwardProb + left*leftRightProb + right*leftRightProb)*discountDoubleCheck + mazeVector[i][j].getReward();
				double rightUtility = (right*forwardProb + up*leftRightProb + down*leftRightProb)*discountDoubleCheck + mazeVector[i][j].getReward();
	
				double maxUtility = std::max( std::max(leftUtility,rightUtility), std::max(upUtility,downUtility));
	

				mazeVector[i][j].setUtility(maxUtility);
			
				if (maxUtility == upUtility)
				{
					mazeVector[i][j].setDirection(0);
				}
				if (maxUtility == leftUtility)
				{
					mazeVector[i][j].setDirection(1);
				}
				if (maxUtility == downUtility)
				{
					mazeVector[i][j].setDirection(2);
				}
				if (maxUtility == rightUtility)
				{
					mazeVector[i][j].setDirection(3);
				}
			}
		}
	}
}
};

void Maze::printUtilities()
{
	for (int i = 0; i < mazeVector.size(); i++)
	{
		for (int j = 0; j < mazeVector[i].size(); j++)
		{
			std::cout << "[ " << std::setprecision(3) << mazeVector[i][j].getUtility() << " ]        "; 
		}
		std::cout << "\n";
	}

};

void Maze::utilityList()
{
	for (int i = 0; i < mazeVector[0].size(); i++)
	{
		for (int j = 0 ; j < mazeVector.size(); j++)
		{
		//		std::cout << "("<<i<<" , "<<j<<"): " << mazeVector[j][i].getUtility();
				std::cout << mazeVector[i][j].getUtility() << ",";
		}
	}
};

void Maze::QLearning(int n)
{

	int t = 1;
	for (int times = 0; times < n; times++)
	{
		srand(time(NULL));
		double alpha = (double) 60/(double)(t+59);
		int action = randomAction();
		int i = randomRow();
		int j = randomColumn();

		//std::cout << "Action chosen is : " << action << "\n";
		//std::cout << "Cell is : [" << i << "][" << j << "]\n";
		
		if (mazeVector[i][j].isTerminal() == false)
		{
		 	t++;
		//	std::cout << "t is: " << t << "\n";
			double upQ = getNextQ(i, j, 0);
			double leftQ = getNextQ(i, j, 1);
			double downQ = getNextQ(i, j, 2);
			double rightQ = getNextQ(i, j, 3);
		//	std::cout << "UP LEFT DOWN RIGHT : " << upQ << "  " << leftQ << "  " << downQ << "  " << rightQ << "\n";
		
			double Q_Maximum = std::max( std::max(upQ, downQ), std::max(leftQ, rightQ));


	
			if (upQ == Q_Maximum)
			{
		//		std::cout << "Up selected!\n";
				mazeVector[i][j].setDirection(0);
			}
			if (leftQ == Q_Maximum)
			{
		//		std::cout << "Left selected!\n";
				mazeVector[i][j].setDirection(1);
			}
			if (downQ == Q_Maximum)
			{
		//		std::cout << "Down selected!\n";
				mazeVector[i][j].setDirection(2);
			}
			if (rightQ == Q_Maximum)
			{
		//		std::cout << "Right selected!\n";
				mazeVector[i][j].setDirection(3);
			}

			mazeVector[i][j].setActionQ(action, mazeVector[i][j].getActionQ(action) + alpha*(mazeVector[i][j].getReward() + discountDoubleCheck*(Q_Maximum-mazeVector[i][j].getActionQ(action))));

			double utilityMake = std::max( std::max(mazeVector[i][j].getActionQ(1), mazeVector[i][j].getActionQ(3)), std::max(mazeVector[i][j].getActionQ(0),mazeVector[i][j].getActionQ(2)));

		//	std::cout << "UTILITY SET AS : " << utilityMake << std::endl;
			mazeVector[i][j].setUtility(utilityMake);
		

		}

	}

};

