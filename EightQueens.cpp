#include<iostream>
#include <time.h>¡¡

int count = 0;

class Board
{

private:
	int size;
	int** chess_board;
	// count = 0;

	// private member function:  returns 'false' if
	// the (row, col) position is not safe.
	bool is_this_position_safe(int row, int col)
	{
		bool flag = true;
		int i, j ,k= 0;
		// whether the col is dangerous
		for (j = 0; j < size; j++)
		{
			if(row>=j)  //this part is the most important part,I spend my whole night to figure it out
			{
				if (*(*(chess_board + row - j) + col) != 0)  // determine whether this line has a queen
				{
					flag = false;
					break;
				}
			}
		}
			// whether the top left diagonal is dangerous 
			for (i = row, k = col; i >= 0 && k >= 0; i--, k--)
			{
				if (*(*(chess_board + i) + k) != 0)
				{
					flag = false;
					break;
				}
			}
			// whether the top right diagonal is dangerous 
			for (i = row, k = col; i >= 0 && k < size; i--, k++)
			{
				if (*(*(chess_board + i) + k) != 0)
				{
					flag = false;
					break;
				}
			}
			// whether the bottom right diagonal is dangerous 
			for (i = row, k = col; i < size && k < size; i++, k++)
			{
				if (*(*(chess_board + i) + k) != 0)
				{
					flag = false;
					break;
				}
			}
			// whether the bottom left diagonal is dangerous 
			for (i = row, k = col; i < size && k >= 0; i++, k--)
			{
				if (*(*(chess_board + i) + k) != 0)
				{
					flag = false;
					break;
				}
			}
		if (flag)
			return true;
		else
			return false;

		
		// write the appropriate code on your own that returns
		// "true" if the (row,col) position is safe.  If it is
		// unsafe (i.e. some other queen can threaten this position)
		// return "false"

	}

	// private member function: initializes the (n x n) chessboard
	void initialize(int n)
	{
		size = n; // giving the number input to private sector
		int** chess_board_oper = new int* [size]; // if I define chess_board here it could be a redefine issue( many bugs told me)
		for (int m = 0; m < size; m++)
			chess_board_oper[m] = new int[size];

		chess_board = chess_board_oper;   // in this way, we can allocate memory to the pointer

		for( int i = 0; i < size ; i++)
		{
			for (int j = 0; j < size; j++)
			{
				*(*(chess_board + i) + j) = 0;   //
			}

		}
		// write the appropriate code that uses the pointer-to-pointer
		// method to initialize the (n x n) chessboard.  Once initialized,
		// put zeros in all entries.  Later on, if you placed a queen in
		// the (i,j)-th position, then chessboard[i][j] will be 1.
	}

	// private member function: prints the board position
	void print_board()
	{
		std::cout << size << "-Queens Problem Solution" << std::endl;
		//std::cout << "No." << count + 1 << "Solution of" << size << "Queen Problem" << std::endl;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				std::cout << *(*(chess_board + i) + j) ;
			}
			std::cout << " " << std::endl;
		}
		count++;
		// write the appropriate code here to print out the solved
		// board as shown in the assignment description

	}

	// private member function: recursive backtracking
	
	bool solve(int row)
	{
		if (row == size)
			print_board();

		else
		{
			for (int j = 0; j < size; j++)
			{
				if (is_this_position_safe(row, j))
				{
					*(*(chess_board + row) + j) = 1;
					//chess_board[row][j] = 1;

					if (solve(row + 1))
						return true;
					else
						*(*(chess_board + row) + j) = 0;
						//chess_board[row][j] = 0;
				}
			}
		}
		return false; // pay attention to this end 
		              //struggle to find out
	}
		// implement the recursive backtracking procedure described in
		// pseudocode format in figure 1 of the description of the first
		// programming assignment
public:
	// Solves the n-Queens problem by (recursive) backtracking
	void nQueens(int n)
	{
		initialize(n);      //initialze the chess_board
		if (!solve(0))
		{
			std::cout << "Backtracking is finished. Here comes the result" << std::endl;
		}
			
		else
			std::cout << "There is no solution to the " << n << "-Queens Problem" << std::endl;
	}
};

int main(int argc, char* const argv[])
{
	clock_t start, end;
	start = clock();
	Board x;

	int board_size;
	std::cout << "please input the value of N:";
	sscanf_s(argv[1], "%d", &board_size);
	//std::cin >> board_size;
	if (board_size <= 3)
	{
		std::cout << "Wrong Input" << std::endl;
		return 0;
	}
	x.nQueens(board_size);
	std::cout << "Finally, there are " << count << " solutions"<<std::endl;
	end = clock();   //end
	std::cout << "Running time = " << double(end - start) / CLOCKS_PER_SEC << "s" << std::endl;  //print the time
	std :: cout << "My name is Han Wang"<<std::endl;
	std::cout << "My NetID is: 'hanw8'" << std::endl;
	std::cout << "I hereby certify that I have read the University policy on Academic Integrity and that I am not in violation." << std::endl;
	return 0;

}