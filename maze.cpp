#include "maze.h"
#include<math.h>
#include<iostream>
#include<iomanip>



double Maze::getNodeUtil(int x, int y, int origX, int origY)
{
	if (x<0 || x >= mazeVector.size() || y < 0 || y >= mazeVector[0].size() || mazeVector[x][y].isWall())
	{
		return mazeVector[origX][origY].getUtility(); 
	}
	return mazeVector[x][y].getUtility();

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
				std::cout << "("<<i<<" , "<<j<<"): " << mazeVector[j][i].getUtility() << std::endl;
		}
	}
};
