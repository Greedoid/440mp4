#ifndef __NODE_H
#define __NODE_H


#include <iostream>

class Node {

	private:
		int terminal;		//0 means normal space, 1 means +1 terminal, 2 means -1 terminal
		bool wall;
		bool start;
		double reward;
		int direction;		//0 - up, 1 - left, 2 - down, 3 - right
		double utility;
		double upQ;
		double leftQ;
		double downQ;
		double rightQ;
	
	public:
		Node(){};
		Node(bool wallFlag, int terminalSet)
		{
			upQ = leftQ = rightQ = downQ = 0;
			utility = 0;

			wall = wallFlag;
			terminal = terminalSet;
			start = false;
			reward = -.04;

			switch (terminalSet)
			{
				case(1):
				{
					reward = 1;
					utility = 1;
					break;
				}
				case(2):
				{
					reward = -1;
					utility = -1;
					break;
				}
				
			}
		};

		char getChar()
		{
			if (wall)
				return 'W';
			else if (terminal == 1)
				return '+';
			else if (terminal == 2)
				return '-';

			if (direction == 0)
				return '^';
			else if (direction == 1)
				return '<';
			else if (direction == 2)
				return 'v';
			else if (direction == 3)
				return '>';
			return ' ';
		};

		bool isTerminal()
		{
			return (wall || terminal > 0);
		};

		bool isWall()
		{
			return wall;
		};

		void setActionQ (int action, double Q)
		{
			if (action == 0)
				upQ = Q;
			if (action == 1)
				leftQ = Q;
			if (action == 2)
				downQ = Q;
			if (action == 3)
				rightQ = Q;

		}

		double getActionQ (int action)
		{
			if (action == 0)
				return upQ;
			if (action == 1)
				return leftQ;
			if (action == 2)
				return downQ;
				
			return rightQ;


		}

		void setUtility(double n)
		{
			utility = n;
		};
		
		double getUtility()
		{
			return utility;
		};
		void setDirection(int n)
		{
			direction = n;
		};

		void setStart()
		{
			start = true;
		};
		void setReward(double rewardSet)
		{
			reward = rewardSet;
		};
		double getReward()
		{
			return reward;
		};
};

#endif
