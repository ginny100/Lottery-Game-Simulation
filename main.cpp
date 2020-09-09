//Khue Dang
//Lab6out
//A lottery game simulation

#include <iostream>
#include "graph1.h"
#include "Lottery.h"
#include <ctime>
#include <iomanip>

using namespace std;

int main()
{
	//Display Graphics
	displayGraphics();

	//Variable Declaration/Initialization
	int no_balls = 0;
	int num = 0;
	int matches = 0;
	int winnings = 0;
	char repeat = 'y';
	Lottery lottery;

	do
	{
		//Prompt for the number of lottery balls
		do
		{
			cout << "How many lottery balls do you want to play: ";
			cin >> no_balls;

		} while (!lottery.setNoBalls(no_balls));

		//Prompt for the lottery number
		for (int i = 0; i < no_balls; i++)
		{
			do 
			{
				cout << "Enter lottery # " << i + 1 << " (between 1 and 40): ";
				cin >> num;
			} while (!lottery.addNumber(num, i));
		}
		lottery.selectionSort();
		lottery.displayYourNumbers();
		lottery.processWinningNumbers();

		//Display lottery balls
		gout << setPos(40, 440) << "Your Numbers" << endg;

		//Display winning numbers
		gout << setPos(40, 220) << "Winning Numbers" << endg;
		
		//Compute winnings
		matches = lottery.computeWinnings();
		winnings = pow(10.0, (double)matches);

		//Display the # of balls played, the # of matches, and the winnings 
		gout << setPos(20, 20) << "Number of Balls played: " << no_balls << endg;
		gout << setPos(20, 30) << "Number of Matches: " << matches << endg;
		gout << setPos(20, 40) << "Your Payout: $" << setPrecision(2) << winnings << endg;
		
		//Prompts repeat
		cout << "Repeat program? (y/n) ";
		cin >> repeat;
		cout << endl;
		
		//Clears the Graphics and Console
		clearGraphics();
		system("cls");
	} while (repeat == 'Y' || repeat == 'y');

	return 0;
}