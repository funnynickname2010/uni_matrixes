#include <iostream>
#include <cmath>

#define FTYPE double

using namespace std;
void matrix_input(FTYPE** m, FTYPE** copy_m, int row, int col);
void matrix_print(FTYPE** m, int row, int col);
void gauss_method(FTYPE** m, int row, int col);
void row_swap(FTYPE*& row1, FTYPE*& row2);
void row_division(FTYPE*& row, FTYPE scalar, int row_length);
void row_substraction_row2_row1(FTYPE*& row1, FTYPE*& row2, int col);
void row_multiplication_true(FTYPE*& row, FTYPE scalar, int row_length);
FTYPE* row_multiplication_return(FTYPE* row, FTYPE scalar, int row_length);
void row_row1_plus_row2mult_by_scalar(FTYPE*& row1, FTYPE* row2, FTYPE scalar, int row_length);
void no_minus_zeros(FTYPE** m, int row, int col);
void matrix_solution_output(FTYPE** m, int row, int col);

int main()
{
	int row, col;
	FTYPE** m;
	FTYPE** copy_m;


	//input rows, columns

	cout << "Rows: \n";
	cin >> row;
	cout << "Columns: \n";
	cin >> col;
	cout << "\n";


	//memory allocation

	m = (new FTYPE * [row]());
	copy_m = (new FTYPE * [row]());

	for (int i = 0; i < row; i++)
	{
		m[i] = (new FTYPE[col]());
		copy_m[i] = (new FTYPE[col]());
	}

	//input matrix

	matrix_input(m, copy_m, row, col);
	cout << "\n";

	//doing whatever

	gauss_method(m, row, col);

	//printing matrix 

	no_minus_zeros(m, row, col);
	matrix_print(m, row, col);

	//printing solution

	matrix_solution_output(m, row, col);

	return 0;
}

void gauss_method(FTYPE** m, int row, int col)
{
	int rows_done_first = 0; //Number of rows that don't need any procedures anymore(?)

	for (int j = 0; j < col; j++) //col = m
	{
		for (int i = rows_done_first; i < row; i++) //row = n
		{
			if (m[i][j] != 0)
			{
				row_division(m[i], m[i][j], col);

				for (int k = i + 1; k < row; k++)
				{
					if (m[k][j] != 0)
					{
						row_row1_plus_row2mult_by_scalar(m[k], m[i], -m[k][j], col);
					}
				}

				row_swap(m[i], m[rows_done_first]);
				rows_done_first += 1;
				break;
			}
		}
	}

	//Reverse part

	int rows_done_second = 0;

	for (int j = col - 2; j >= 0; j--)
	{
		for (int i = row - 1 - rows_done_second; i >= 0; i--)
		{
			if (m[i][j] == 0)
			{
				rows_done_second++;
			}
			else
			{
				for (int k = i - 1; k >= 0; k--)
				{
					if (m[k][j] != 0)
					{
						row_row1_plus_row2mult_by_scalar(m[k], m[i], -m[k][j], col);
					}
				}
				break;
			}
		}
	}
}

void matrix_input(FTYPE** m, FTYPE** copy_m, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cin >> m[i][j];
			**copy_m = m[i][j];
		}
	}
}

void matrix_print(FTYPE** m, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << m[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

void row_swap(FTYPE*& row1, FTYPE*& row2)
{
	FTYPE* buffer = row1;

	row1 = row2;
	row2 = buffer;
}

void row_division(FTYPE*& row, FTYPE scalar, int row_length)
{
	for (int i = 0; i < row_length; i++)
	{
		row[i] = row[i] / scalar;
	}
}

void row_multiplication_true(FTYPE*& row, FTYPE scalar, int row_length)
{
	for (int i = 0; i < row_length; i++)
	{
		row[i] = row[i] * scalar;
	}
}

FTYPE* row_multiplication_return(FTYPE* row, FTYPE scalar, int row_length)
{
	for (int i = 0; i < row_length; i++)
	{
		row[i] = row[i] * scalar;
	}
	return row;
}

void row_row1_plus_row2mult_by_scalar(FTYPE*& row1, FTYPE* row2, FTYPE scalar, int row_length)
{
	for (int i = 0; i < row_length; i++)
	{
		row1[i] += row2[i] * scalar;
	}
}

void row_substraction_row2_row1(FTYPE*& row1, FTYPE*& row2, int col)
{
	for (int i = 0; i < col; i++)
	{
		row2[i] = row2[i] - row1[i];
	}
}

void no_minus_zeros(FTYPE** m, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (abs(m[i][j]) < 0.0000001)
			{
				m[i][j] = 0.0;
			}
		}
	}
}

void matrix_solution_output(FTYPE** m, int row, int col)
{
	bool matrix_solvable = 1;

	for (int i = 0; i < row; i++)
	{
		bool row_solvable = 0;

		for (int j = 0; j < col - 1; j++)
		{
			if (m[i][j] != 0)
			{
				row_solvable = 1;
				break;
			}
		}

		if (row_solvable == 0 && m[i][col - 1] != 0)
		{
		matrix_solvable = 0;
		break;
		}
	}

	if (matrix_solvable == 1)
	{
		for (int i = 0; i < row; i++)
		{
			FTYPE x_scalar;

			for (int j = 0; j < col - 1; j++)
			{
				if (m[i][j] != 0)
				{
					cout << "\nx" << j + 1 << " = " << m[i][col - 1] / m[i][j];
					x_scalar = m[i][j];

					for (int k = 0; k < col - 1; k++)
					{
						if (m[i][k] != 0 && m[i][k] > 0 && m[i][k] != m[i][j])
						{
							cout << " - " << m[i][k] / x_scalar << " * x" << k + 1;
						}
						else if (m[i][k] != 0 && m[i][k] < 0 && m[i][k] != m[i][j])
						{
							cout << " + " << m[i][k] / x_scalar << " * x" << k + 1;
						}
					}
				}
			}
		}

		for (int j = 0; j < col; j++)
		{
			bool any_number = 1;
			
			for (int i = 0; i < row; i++)
			{
				if (m[i][j] != 0)
				{
					any_number = 0;
					break;
				}
			}

			if (any_number == 1)
			{
				cout << "\nx" << j + 1 << " = any number\n";
			}
		}
	}
	else
	{
		cout << "No solutions.\n";
	}
}
