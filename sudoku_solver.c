#include <stdio.h>

int	sudoku_grid[9][9] = {
	2,1,0, 0,0,0, 0,6,5,
	0,0,4, 0,5,0, 0,0,0,
	8,0,0, 0,4,6, 1,7,0,

	0,0,0, 0,0,0, 2,0,0,
	7,0,8, 3,1,0, 0,0,0,
	0,0,0, 8,0,4, 9,0,0,

	6,0,0, 0,0,5, 0,0,0,
	0,5,0, 0,8,0, 0,0,0,
	0,0,0, 0,9,1, 8,0,3,
};


int	is_legal(int row, int col, int num)
{
	int	sub_row;
	int	sub_col;

	// Check column
	for (int i = 0; i < 9; i++)
		if (sudoku_grid[i][col] == num)
			return (0);

	// Check row
	for (int i = 0; i < 9; i++)
		if (sudoku_grid[row][i] == num)
			return (0);

	// Check subgrid

	// Find the top-left corner (start) of the 3×3 subgrid
	sub_row = row - (row % 3);
	sub_col = col - (col % 3);

	// Check all cells in the 3×3 subgrid
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (sudoku_grid[sub_row + i][sub_col + j] == num)
				return (0);
	return (1);
}

int	solve(int row, int col)
{
	if (row == 9)
		return (1);
	if (col == 9)
		return (solve(row + 1, 0));
	if (sudoku_grid[row][col])
		return (solve(row, col + 1));
	for (int num = 1; num < 10; num++)
	{
		if (is_legal(row, col, num))
		{
			sudoku_grid[row][col] = num;
			if (solve(row, col + 1))
				return (1);	
			sudoku_grid[row][col] = 0;
		}
	}
	return (0);
}

void	print_grid(void)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			printf("%d ", sudoku_grid[i][j]);
			if ((j + 1) % 3 == 0)
				printf(" ");
		}
		if ((i + 1) % 3 == 0)
			printf("\n");
		printf("\n");
	}
}

int	main(void)
{
	if (!solve(0, 0))
	{
		printf("There is no solution for this sudoku !\n");
		return (1);
	}
	print_grid();
	return (0);
}