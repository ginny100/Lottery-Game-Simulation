#include <iostream>
#include "graph1.h"
#include "Lottery.h"
#include <ctime>

Lottery::Lottery()
{
	//Implement the default Constructor
	no_balls = 0;
	yourNumbers = NULL;
	winningNumbers = NULL;
	matches = 0;
}

Lottery::~Lottery()
{
	delete[] yourNumbers;
	delete[] winningNumbers;
}

int Lottery::getNoBalls()
{
	return no_balls;
}

bool Lottery::setNoBalls(int no_balls)
{
	if (no_balls < 3 || no_balls > 10)
	{
		cout << "Invalid Input. Value must be between 3 and 10 inclusively." << endl;
		return false;
	}
	else
	{
		yourNumbers = new int[no_balls];
		winningNumbers = new int[no_balls];
		this->no_balls = no_balls;

		return true;
	}
} 


bool Lottery::addNumber(int number, int index)
{
	if ((number < 1 || number > 40)) //check for duplicates as well
	{
		return false;
	}

	for (int i = 0; i < no_balls; i++)
	{
		if (yourNumbers[i] == number)
		{
			return false;
		}
	}

	yourNumbers[index] = number;
	return true;

}

void Lottery::displayYourNumbers()
{
	string fn;
	for (int i = 0; i < no_balls; i++)
	{
		fn = to_string(yourNumbers[i]) + ".bmp";
		displayBMP(fn, 40 +(i * 60), 440);
	}
}

void Lottery::processWinningNumbers()
{
	string fn;
	bool duplicate = false;

	//Generate the winning numbers
	for (int i = 0; i < no_balls; i++)
	{
		winningNumbers[i] = rand() % 40 + 1;
		do
		{
			duplicate = false;
			for (int j = 0; j < i; j++)
			{
				if (winningNumbers[i] == winningNumbers[j])
				{
					winningNumbers[j] = rand() % 40 + 1;
					duplicate = true;
					break;
				}
			}
		} while (duplicate);
	}
	
	//Display the winning numbers
	for (int i = 0; i < getNoBalls(); i++)
	{
		fn = to_string(winningNumbers[i]) + ".bmp";
		displayBMP(fn, 40 + i * 60, 220);
		Sleep(1000);
	}

	insertionSort();

	//Display the winning numbers
	for (int i = 0; i < getNoBalls(); i++)
	{
		fn = to_string(winningNumbers[i]) + ".bmp";
		displayBMP(fn, 40 + i * 60, 220);
	}
}

void Lottery::selectionSort()
{
	
	//Variable Declaration/Initialization 
	int n = 0;
	int k = 0;
	int sm_index = 0;
	int smallest = 0;
	int temp1 = 0;
	int temp2 = 0;

	for (k = 0; k < no_balls - 1; k++)	       // size-1 = number of passes
	{
		smallest = yourNumbers[k];
		sm_index = k;

		for (n = k + 1; n < no_balls; n++)    // size = # elem. to look at
		{
			if (yourNumbers[n] < smallest)
			{
				smallest = yourNumbers[n];
				sm_index = n;
			}
		}

		if (smallest < yourNumbers[k])
		{
			temp1 = yourNumbers[k];
			yourNumbers[k] = yourNumbers[sm_index];
			yourNumbers[sm_index] = temp1;
		}
	}
}

void Lottery::insertionSort()
{
	
	int i, j, v;
	// For each element after the first:
	for (i = 1; i < no_balls; i++)
	{	
		v = winningNumbers[i];
		for (j = i - 1; j >= 0 && winningNumbers[j] > v; j--)
			winningNumbers[j + 1] = winningNumbers[j];
		winningNumbers[j + 1] = v;
	}
}

int Lottery::getMatches()
{
	return matches;
}

int Lottery::binarySearch(int target)
{
	int high = no_balls;
	int low = 0;
	int middle;
	bool found = false;
	int i;
	for (i = 0; i < no_balls; i++)
	{
		while ((low <= high) && (!found))
		{
				middle = (low + high) / 2;

				if (winningNumbers[middle] == target)
					found = true;
				else if (target > winningNumbers[middle])
					low = middle + 1;
				else
					high = middle - 1;
		}
		if (found)
		{
			return i;
		}
		else
		{
			return -1;
		}
	}
}

int Lottery::computeWinnings()
{
	matches = 0;
	for (int i = 0; i < no_balls; i++)
	{
		if (binarySearch(yourNumbers[i]) != -1)
			matches++;
	}
	return matches;
}