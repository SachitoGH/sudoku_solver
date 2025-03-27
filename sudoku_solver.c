#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define N 9

bool	is_legal(int sudoku_grid[N][N], int row, int col, int num)
{
	int	block_size;
	int	sub_row;
	int	sub_col;

	block_size = (int)sqrt(N);
	sub_row = row - (row % block_size);
	sub_col = col - (col % block_size);

	// Check column
	for (int i = 0; i < N; i++)
		if (sudoku_grid[i][col] == num)
			return (false);

	// Check row
	for (int i = 0; i < N; i++)
		if (sudoku_grid[row][i] == num)
			return (false);

	// Check subgrid
	for (int i = 0; i < block_size; i++)
		for (int j = 0; j < block_size; j++)
			if (sudoku_grid[sub_row + i][sub_col + j] == num)
				return (false);
	return (true);
}

bool	solve(int sudoku_grid[N][N], int row, int col)
{
	if (row == N)
		return (true);
	if (col == N)
		return (solve(sudoku_grid, row + 1, 0));
	if (sudoku_grid[row][col])
		return (solve(sudoku_grid, row, col + 1));
	for (int num = 1; num < N + 1; num++)
	{
		if (is_legal(sudoku_grid, row, col, num))
		{
			sudoku_grid[row][col] = num;
			if (solve(sudoku_grid, row, col + 1))
				return (true);	
			sudoku_grid[row][col] = 0;
		}
	}
	return (false);
}

void	print_grid(int sudoku_grid[N][N])
{
	int	block_size;

	block_size = (int)sqrt(N);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("%d ", sudoku_grid[i][j]);
			if ((j + 1) % block_size == 0 && j < N - 1)
				printf(" ");
		}
		if ((i + 1) % block_size == 0 && i < N - 1)
			printf("\n");
		printf("\n");
	}
}

void fill_grid(int sudoku_grid[N][N], char *str)
{
	int	i;

	i = 0;
    for (int j = 0; j < N && str[i]; j++)
    {
        for (int k = 0; k < N && str[i]; k++)
        {
            while (str[i] && (str[i] < '0' || str[i] > '9'))
                i++;
            if (str[i] && str[i] >= '0' && str[i] <= '9')
                sudoku_grid[j][k] = str[i] - '0';
			if (str[i])
				i++;
        }
    }
}

int	main(int argc, char *argv[])
{
	int	sudoku_grid[N][N] = {0};

	// only for sudoku 9x9
	if (argc == 2)
		fill_grid(sudoku_grid, argv[1]);
	if (!solve(sudoku_grid, 0, 0))
	{
		printf("There is no solution for this sudoku !\n");
		return (1);
	}
	print_grid(sudoku_grid);
	return (0);
}