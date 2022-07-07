//------------------
//Implementation: 1D
//------------------

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <ctime>
#include <Windows.h>
using namespace std;

//initializes all positions to empty and unchosen
void startFunction(char grid[9], bool chosen_grid[9]);
//for selecting and assigning symbol to user and computer
void chooseSymbol(char* user_symbol, char* computer_symbol);
//takes input from the user
void user_input(bool chosen_grid[9], int* row, int* column, int* position);
//displays countdown
void display_countdown();
//takes input from the computer
void computer_input(bool chosen_grid[9], int* row, int* column, int* position);
//displays the grid
void display_array(char grid[9]);
//updates array after taking input
void update_array(char grid[9], bool chosen_grid[9], char* user_symbol, char* computer_symbol, bool* turn, int* position);
//checks if there is a winner or if the game is drawn
void is_there_a_winner(char grid[9], bool chosen_grid[9], bool* gameOver, bool* gameWon, bool* gameDrawn, char* user_symbol, char* computer_symbol, bool* user_won);

int main()
{
	char grid[9];

	bool chosen_grid[9];			//stores information: if a position is already chosen or not

	char user_symbol;
	char computer_symbol;

	bool gameOver;
	bool gameWon;
	bool gameDrawn;

	int chosen_row, chosen_column;

	int position;

	bool user_turn;				//true if user's turn; false if computer's turn

	bool user_won;				//true if user won; false if computer won or draw

	char repeat;

	do
	{
		startFunction(grid, chosen_grid);		//initializes all positions to empty and unchosen

		gameOver = false;
		gameWon = false;
		gameDrawn = false;

		bool user_turn = true;
		bool user_won = false;

		display_array(grid);

		chooseSymbol(&user_symbol, &computer_symbol);

		do
		{
			if (user_turn == true)
			{
				cout << "\n\t\t\t\t\t       -----Your Turn-----\n";

				user_input(chosen_grid, &chosen_row, &chosen_column, &position);	//takes input

				update_array(grid, chosen_grid, &user_symbol, &computer_symbol, &user_turn, &position);	//updates array

				display_array(grid);	//displayes updated array
			}
			else
			{
				cout << "\n";

				display_countdown();			//displays countdown

				cout << "\n\t\t\t\t\t     -----Computers Turn-----\n\n";

				Sleep(500);

				computer_input(chosen_grid, &chosen_row, &chosen_column, &position);	//takes input

				update_array(grid, chosen_grid, &user_symbol, &computer_symbol, &user_turn, &position);		//updates array

				display_array(grid);		//displayes updated array

				Sleep(500);
			}

			if (user_turn == true)				//changes turn
			{
				user_turn = false;
			}
			else
			{
				user_turn = true;
			}

			//checks if someone won or if it is a draw
			is_there_a_winner(grid, chosen_grid, &gameOver, &gameWon, &gameDrawn, &user_symbol, &computer_symbol, &user_won);

		} while (gameOver == false);

		if (user_won == true && gameDrawn == false)
		{
			cout << "\n---------------";
			cout << "\n    You won    ";
			cout << "\n---------------";
		}
		else if (user_won == false && gameDrawn == false)
		{
			cout << "\n---------------";
			cout << "\n Computer won ";
			cout << "\n---------------";
		}
		else
		{
			cout << "\n---------------";
			cout << "\n  It's a Draw  ";
			cout << "\n---------------\n";
		}

		cout << "\nDo you want to play again?(y/n): ";

		do		//makes sure that the entries are right
		{
			cout << "\n>> ";
			cin >> repeat;

			if (repeat != 'y' && repeat != 'Y' && repeat != 'n' && repeat != 'N')
			{
				cout << "---Invalid Input-Enter Again---";
			}
		} while (repeat != 'y' && repeat != 'Y' && repeat != 'n' && repeat != 'N');

		cout << "\n";

	} while (repeat == 'y' || repeat == 'Y');

	//goodbye message
	cout << "\n-------------------------";
	cout << "\n  Thank you for Playing";
	cout << "\n        Goodbye!";
	cout << "\n-------------------------";

	return 0;
}

void startFunction(char grid[9], bool chosen_grid[9])	//initializes all positions to empty and unchosen
{
	for (int i = 0; i < 9; i++)							//initializes all positions to empty
	{
		grid[i] = ' ';
	}

	for (int i = 0; i < 9; i++)							//initializes all positions to false(unchosen)
	{
		chosen_grid[i] = false;
	}
}

void chooseSymbol(char* user_symbol, char* computer_symbol)		//for selecting and assigning symbol to user and computer
{
	char chosen;

	cout << "Please choose your symbol";
	cout << "\n. X";
	cout << "\n. O";
	cout << "\n-------------------------";

	do		//makes sure that the entries are right
	{
		cout << "\n>> ";
		cin >> chosen;

		if ((chosen != 'x') && (chosen != 'X') && (chosen != 'o') && (chosen != 'O'))
		{
			cout << "---Invalid Input-Enter Again---";
		}

	} while ((chosen != 'x') && (chosen != 'X') && (chosen != 'o') && (chosen != 'O'));

	cout << "-------------------------\n";

	if ((chosen == 'x') || (chosen == 'X'))
	{
		*user_symbol = 'X';
		*computer_symbol = 'O';
	}
	else
	{
		*user_symbol = 'O';
		*computer_symbol = 'X';
	}

}

void user_input(bool chosen_grid[9], int* row, int* column, int* position)
{
	bool chosen = false;

	do
	{
		cout << "\nChoose your position";
		cout << "\n--------------------";

		do					//makes sure that user enters input within range
		{
			cout << "\nRow:  ";
			cin >> *row;

			if ((*row < 1) || (*row > 3))
			{
				cout << "---Invalid Input-Enter Again---";
			}

		} while ((*row < 1) || (*row > 3));

		do					//makes sure that user enters input within range
		{
			cout << "Column: ";
			cin >> *column;

			if ((*column < 1) || (*column > 3))
			{
				cout << "---Invalid Input-Enter Again---\n";
			}

		} while ((*column < 1) || (*column > 3));

		cout << "--------------------\n";

		switch (*row)			//determines the position selected (in 1 - 9)
		{
		case 1:
			switch (*column)
			{
			case 1:
				*position = 1;
				break;
			case 2:
				*position = 2;
				break;
			case 3:
				*position = 3;
				break;
			}
			break;
		case 2:
			switch (*column)
			{
			case 1:
				*position = 4;
				break;
			case 2:
				*position = 5;
				break;
			case 3:
				*position = 6;
				break;
			}
			break;
		case 3:
			switch (*column)
			{
			case 1:
				*position = 7;
				break;
			case 2:
				*position = 8;
				break;
			case 3:
				*position = 9;
				break;
			}
			break;
		}

		if (chosen_grid[*position - 1] == false)		//checks if the selected position is already chosen or not
		{
			chosen = true;
		}
		else
		{
			cout << "\nPosition is already chosen. Please choose again.\n";
		}

	} while (chosen == false);		//repeats if the position selected by the user was already chosen

}

void display_countdown()		//displays five second countdown
{
	int seconds = 5;

	cout << endl;

	while (seconds >= 0)
	{
		cout << "\rWait for Computer's Turn: " << seconds;
		Sleep(1000);
		seconds--;
	}

	cout << endl;
}

void computer_input(bool chosen_grid[9], int* row, int* column, int* position)	//takes input from the computer
{
	srand(time(NULL));

	bool chosen = false;

	do
	{
		*row = rand() % 3 + 1;			//generates random row number
		*column = rand() % 3 + 1;		//generates random column number

		switch (*row)					//determines the position selected (in 1 - 9)
		{
		case 1:
			switch (*column)
			{
			case 1:
				*position = 1;
				break;
			case 2:
				*position = 2;
				break;
			case 3:
				*position = 3;
				break;
			}
			break;
		case 2:
			switch (*column)
			{
			case 1:
				*position = 4;
				break;
			case 2:
				*position = 5;
				break;
			case 3:
				*position = 6;
				break;
			}
			break;
		case 3:
			switch (*column)
			{
			case 1:
				*position = 7;
				break;
			case 2:
				*position = 8;
				break;
			case 3:
				*position = 9;
				break;
			}
			break;
		}

		if (chosen_grid[*position - 1] == false)	//checks if the selected position is already chosen or not
		{
			chosen = true;
		}

	} while (chosen == false);		//repeats if the position selected by the computer was already chosen

}

void update_array(char grid[9], bool chosen_grid[9], char* user_symbol, char* computer_symbol, bool* turn, int* position)
{
	if (*turn == true)
	{
		grid[*position - 1] = *user_symbol;				//updates symbol on chosen position
		chosen_grid[*position - 1] = true;				//updates posotion status to chosen
	}
	else
	{
		grid[*position - 1] = *computer_symbol;			//updates symbol on chosen position
		chosen_grid[*position - 1] = true;				//updates posotion status to chosen
	}
}

void display_array(char grid[9])		//displays array
{
	cout << setw(65) << "     |     |     " << endl;
	cout << setw(50) << "   " << grid[0] << "  |  " << grid[1] << "  |  " << grid[2] << "   " << endl;
	cout << setw(65) << "_____|_____|_____" << endl;
	cout << setw(65) << "     |     |     " << endl;
	cout << setw(50) << "   " << grid[3] << "  |  " << grid[4] << "  |  " << grid[5] << "   " << endl;
	cout << setw(65) << "_____|_____|_____" << endl;
	cout << setw(65) << "     |     |     " << endl;
	cout << setw(50) << "   " << grid[6] << "  |  " << grid[7] << "  |  " << grid[8] << "   " << endl;
	cout << setw(65) << "     |     |     " << endl;
}

void is_there_a_winner(char grid[9], bool chosen_grid[9], bool* gameOver, bool* gameWon, bool* gameDrawn, char* user_symbol, char* computer_symbol, bool* user_won)
{
	*gameOver = false;
	*gameDrawn = false;
	*gameWon = false;

	int chosen_positions = 0;

	char symbol = '0';

	for (int i = 0; i < 9; i = i + 3)						//checks: if a column is same
	{
		if ((grid[i] == grid[i + 1] && grid[i + 1] == grid[i + 2]) && grid[i] != ' ')
		{
			*gameWon = true;
			symbol = grid[i];
			break;
		}
	}

	for (int i = 0; i < 3; i++)								//checks: if a row is same
	{
		if ((grid[i] == grid[i + 3] && grid[i + 3] == grid[i + 6]) && grid[i] != ' ')
		{
			*gameWon = true;
			symbol = grid[i];
			break;
		}
	}

	if ((grid[0] == grid[4] && grid[4] == grid[8]) && grid[4] != ' ')		//checks: if the main diagonal is same
	{
		*gameWon = true;
		symbol = grid[4];
	}

	if ((grid[2] == grid[4] && grid[4] == grid[6]) && grid[4] != ' ')		//checks: if the secondary diagonal is same
	{
		*gameWon = true;
		symbol = grid[4];
	}

	for (int i = 0; i < 9; i++)						//checks how many positions have been chosen
	{
		if (chosen_grid[i] == true)
		{
			chosen_positions++;
		}
	}

	if (*gameWon == false && chosen_positions == 9)	//game is drawn: if all positions are chosen and nobody has won
	{
		*gameDrawn = true;
	}

	if (*gameWon == true || *gameDrawn == true)		//game is over: if it is won by someone or it is a draw
	{
		*gameOver = true;
	}

	if (symbol == *user_symbol)
	{
		*user_won = true;
	}
}
