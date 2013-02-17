#include"node.h"
#include"maze.h"
#include<vector>
#include<iostream>
#include<math.h>


double RMS (std::vector<double> values, std::vector<double> estimates);

int main()
{

	Maze newMaze = Maze();
	newMaze.valueIterate(5000);
	newMaze.printMaze();
	newMaze.printUtilities();
	Maze qMaze = Maze(5000000);
	qMaze.QLearning(90000000);
	qMaze.printMaze();
	qMaze.printUtilities();

};

double RMS (std::vector<double> values, std::vector<double> estimates)
{
	double sum = 0;
	for (int i = 0; i<18; i++)
	{
		sum += (estimates[i] - values[i]);
	}
	
	sum = sum / 18;
	sum = sqrt(sum);
	
};
