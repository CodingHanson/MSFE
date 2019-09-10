/*
 *  sudoku.h
 *  Sudoku
 *  Created by Prof. Ramavarapu Sreenivas
 *  Inspired by: http://web.eecs.utk.edu/courses/spring2012/cs140/Notes/Sudoku/index.html
*/
#include <vector>
#include <fstream>
#include <iostream>
using std::vector;
using namespace std;
class Sudoku
{
	// Private
	int puzzle[9][9];
	int count = 0;
	// Private member function that checks if the named row is valid
	bool row_valid(int row, int val)
	{
		// write code that checks if "row" is valid
		std::vector<int> jud_arr;
		for (int i = 1; i <= 9; i++)
		{
			jud_arr.push_back(i);
		}
		// create a judge vector to decide whether accept the input value
		for (int k = 0; k < 9; k++)
		{
			for (int m = 0; m < jud_arr.size(); m++)
			{
				if ( puzzle[row][k] == jud_arr[m])
				{
					jud_arr.erase(jud_arr.begin() + m);
				}
			}
		}
		if ( find(jud_arr.begin(), jud_arr.end(), val) != jud_arr.end() )
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// Private member function that checks if the named column is valid
	bool col_valid(int col, int val)
	{
		// check validity of "col" 
		std::vector<int> jud_arr;
		for (int i = 1; i <= 9; i++)
		{
			jud_arr.push_back(i);
		}
		// create a judge vector to decide whether accept the input value
		for (int k = 0; k < 9; k++)
		{
			for (int m = 0; m < jud_arr.size(); m++)
			{
				if ( puzzle[k][col] == jud_arr[m])
				{
					jud_arr.erase(jud_arr.begin() + m);
				}
			}
		}
		if ( find(jud_arr.begin(), jud_arr.end(), val) != jud_arr.end())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// Private member function that checks if the named 3x3 block is valid
	bool block_valid(int row, int col, int val)
	{
		// check 3 x 3 block validity 
		//put the input data into the specific block

		int block_row = row - row % 3;
		int block_col = col - col % 3;
		std::vector<int> jud_arr;
		for (int i = 1; i <= 9; i++)
		{
			jud_arr.push_back(i);
		}
		// create a judge vector to decide whether accept the input value
		for (int k = 0; k < 3; k++)
		{
			for (int l = 0; l < 3; l++)
			{
				for (int m = 0; m < jud_arr.size(); m++)
				{
					//monitor the number in that block
					if (puzzle[k + block_row][l + block_col] == jud_arr[m])
					{
						jud_arr.erase(jud_arr.begin() + m);
					}
				}
			}
		}
		if (find(jud_arr.begin(), jud_arr.end(), val) != jud_arr.end())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

public:
	// Public member function that reads the incomplete puzzle
	// we are not doing any checks on the input puzzle -- that is,
	// we are assuming they are indeed valid
	void read_puzzle(int argc, char* const argv[])
	{
		// write code that reads the input puzzle using the 
		// guidelines of figure 23 of the bootcamp material
		// Third command line variable is an input Filename, that I use
	// later
		ifstream input_file(argv[1]);


		if (input_file.is_open()) // If "Data.txt" exists in the local directory
		{
			for (int i = 0; i < 9; i++)
				for (int j = 0; j < 9; j++)
					input_file >> puzzle[i][j];
			input_file.close();
		}
		else
			cout << "Input file Data.txt does not exist in PWD" << endl;
	}

	// Public member function that prints the puzzle when called
	void print_puzzle()
	{

		std::cout << std::endl << "Board Position" << std::endl;
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				// check if we have a legitimate integer between 1 and 9
				if ((puzzle[i][j] >= 1) && (puzzle[i][j] <= 9))
				{
					// printing initial value of the puzzle with some formatting
					std::cout << puzzle[i][j] << " ";
				}
				else {
					// printing initial value of the puzzle with some formatting
					std::cout << "X ";
				}
			}
			std::cout << std::endl;
		}
	}
	// search the next available space to input a num
	bool find_next_available_space(int &row, int &col)
	{
		for (row=0; row < 9; row++)
		{
			for (col=0; col < 9; col++)
			{
				if (puzzle[row][col] == 0)
					return true;
			}
		}
		return false;  // after exhautive search, there is no more availa
	}
	// Public member function that (recursively) implements the brute-force 
	// search for possible solutions to the incomplete Sudoku puzzle
	bool Solve(int row, int col)
	{
		// this part of the code identifies the row and col number of the 
		// first incomplete (i.e. 0) entry in the puzzle.  If the puzzle has
		// no zeros, the variable row will be 9 => the puzzle is done, as 
		// each entry is row-, col- and block-valid...

		// use the pseudo code of figure 3 of the description
		if (9 == row)
		{
			return true; //the puzzle has been solved
		}
		
		if (find_next_available_space(row, col))
		{
	
			for (int k = 1; k <= 9; k++)
			{
				bool flag1 = false;
				bool flag2 = false;
				bool flag3 = false;
				if (row_valid(row, k))
				{
					flag1 = true;
				}
				if (col_valid(col, k))
				{
					flag2 = true;
				}
				if (block_valid(row, col, k))
				{
					flag3 = true;
				}
				if ( flag1==true && flag2==true &&  flag3 == true)        
				{
					puzzle[row][col] = k;  //make experimental input	
					if (Solve(row, col))
						return true;       //return if success
					puzzle[row][col] = 0; // failure, then try again
				}
			}
			return false; // triggers backtracking
		}
		else
			return true;
	}

	bool alternate_Solve(int row, int col)
	{
		if (!find_next_available_space(row, col))   //To ensure all the possiblities have been considered
		{
			cout << "Solution #" << ++count << endl;
			print_puzzle();
			return true; //the puzzle has been solved
		}
		else
		{

				for (int k = 1; k <= 9; k++)
				{
					bool flag1 = false;
					bool flag2 = false;
					bool flag3 = false;
					if (row_valid(row, k))
					{
						flag1 = true;
					}
					if (col_valid(col, k))
					{
						flag2 = true;
					}
					if (block_valid(row, col, k))
					{
						flag3 = true;
					}
					if (flag1 == true && flag2 == true && flag3 == true)
					{
						puzzle[row][col] = k;  //make experimental input	
						alternate_Solve(row, col);
						puzzle[row][col] = 0; // failure, then try again
					}
				}
			}
			return true;
	}


	};

#include <iostream>

	// Soduku Solver using Brute-Force Search implemted using 
	// recursion.
	// Written for IE523: Financial Computation by Prof. Sreenivas
	// and GE523: Discrete Event Systems
	//


	int main(int argc, char* const argv[])
	{
		Sudoku x;
		cout<<"please input the Suduku Puzzle" << endl;
		x.read_puzzle(argc, argv);
		x.print_puzzle();
		//x.Solve(0, 0);
		x.alternate_Solve(0, 0);
		//x.print_puzzle();
		std::cout << "My name is Han Wang" << std::endl;
		std::cout << "My NetID is: 'hanw8'" << std::endl;
		std::cout << "I hereby certify that I have read the University policy on Academic Integrity and that I am not in violation." << std::endl;
		return 0;
	}
