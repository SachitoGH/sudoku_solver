#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

#define N 9
#define CYAN	"\e[0;36m"
#define RESET	"\033[0m"

bool	is_legal(int sudoku_grid[N][N], int row, int col, int num)
{
	int	block_size;
	int	sub_row;
	int	sub_col;

	if (num > N)
		return (false);
	// Check column
	for (int i = 0; i < N; i++)
		if (sudoku_grid[i][col] == num)
			return (false);

	// Check row
	for (int i = 0; i < N; i++)
		if (sudoku_grid[row][i] == num)
			return (false);

	// Check subgrid
	block_size = (int)sqrt(N);
	sub_row = row - (row % block_size);
	sub_col = col - (col % block_size);
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

bool fill_grid(int sudoku_grid[N][N], bool is_fixed[N][N], char *str)
{
	int	num;
	int	i;

	i = 0;
	for (int j = 0; j < N && str[i]; j++)
	{
		for (int k = 0; k < N && str[i]; k++)
		{
			while (str[i] && str[i] != '.' && (str[i] < '0' || str[i] > '9'))
				i++;
			if (str[i] && str[i] >= '0' && str[i] <= '9')
			{
				num = str[i] - '0';
				if (num && is_legal(sudoku_grid, j, k, num))
				{
					sudoku_grid[j][k] = num;
					is_fixed[j][k] = true;	
				}
				else if (num)
					return (false);
			}
			if (str[i])
				i++;
		}
	}
	if (str[i] && (str[i] == '.' || (str[i] >= '0' && str[i] <= '9')))
		return (false);
	return (true);
}

void	print_grid(int sudoku_grid[N][N], bool (*is_fixed)[N])
{
	int	block_size;

	block_size = (int)sqrt(N);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (is_fixed && is_fixed[i][j])
				printf("%s%d %s", CYAN, sudoku_grid[i][j], RESET);
			else
				printf("%d ", sudoku_grid[i][j]);
			if ((j + 1) % block_size == 0 && j < N - 1)
				printf(" ");
		}
		if ((i + 1) % block_size == 0 && i < N - 1)
			printf("\n");
		printf("\n");
	}
}

int	main(int argc, char *argv[])
{
	int		sudoku_grid[N][N] = {0};
	bool	is_fixed[N][N] = {false};

	if (argc > 2)
	{
		printf("Usage: ./sudoku_solver [sudoku input in 1 arg]\n");
		return (1);
	}
	if (argc == 2 && !fill_grid(sudoku_grid, is_fixed, argv[1]))  // only for sudoku up to 9x9
	{
		printf("Invalid sudoku input!\n");
		return (2);
	}
	if (!solve(sudoku_grid, 0, 0))
	{
		printf("There is no solution for this sudoku!\n");
		return (3);
	}
	print_grid(sudoku_grid, is_fixed);
	return (0);
}