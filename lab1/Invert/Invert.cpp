#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <sstream>
#include <iomanip>

const int MATRIX_SIZE = 3;

using Matrix = std::array<std::array<double, MATRIX_SIZE>, MATRIX_SIZE>;

struct Args
{
	std::string file;
	std::string firstLine;
	std::string secondLine;
	std::string thirdLine;
};

void PrintHelp()
{
	std::cout << "Usage reference\n"
		<< "With arguments: <input file>\n"
		<< "If run without arguments: \n"
		<< "Example:\n1 2 3\n"
		<< "0 1 4\n"
		<< "5 6 0\n";
}

Args ParseArguments(int argc, char* argv[])
{
	Args args;
	if (argc == 1)
	{
		std::string str;
		std::getline(std::cin, str);
		args.firstLine = str;
		std::getline(std::cin, str);
		args.secondLine = str;
		std::getline(std::cin, str);
		args.thirdLine = str;
		
	}
	else if (argc == 2)
	{
		if (std::string(argv[1]) == "-h")
		{
			PrintHelp();
			exit(0);
		}
		else
		{
			args.file = argv[1];
		}
	}
	else
	{
		throw std::runtime_error("Invalid input format\n");
	}

	return args;
}

Matrix FillMatrixFromFile(const Args& args)
{
	Matrix matrix;

	std::ifstream inputFile(args.file);
	if (!inputFile)
	{
		throw std::runtime_error("Failed to read data from file\n");
	}

	std::vector<double> vector;
	std::string str;
	std::istringstream iss;
	double num;
	while (std::getline(inputFile, str))
	{
		std::istringstream iss(str);
		while (iss >> num)
		{
			vector.push_back(num);
		}
		if (iss.fail() && !iss.eof())
		{
			throw std::invalid_argument("Invalid matrix\n");
		}
		if (iss.bad())
		{
			throw std::runtime_error("Stream error while reading\n");
		}
	}

	if (inputFile.bad())
	{
		throw std::runtime_error("Error read data from input file\n");
	}

	if (vector.size() != MATRIX_SIZE * MATRIX_SIZE)
	{
		throw std::invalid_argument("Invalid matrix\n");
	}

	for (size_t i = 0; i < MATRIX_SIZE; i++)
	{
		for (size_t j = 0; j < MATRIX_SIZE; j++)
		{
			matrix[i][j] = vector[i * MATRIX_SIZE + j];
		}
	}

	return matrix;
}
// выделить функцию которая работает с потоками
Matrix FillMatrixFromInput(Args args)
{
	Matrix matrix;
	std::vector<double> vector;
	std::istringstream iss(args.firstLine);
	double num;
	while (iss >> num)
	{
		vector.push_back(num);
	}
	if (iss.fail() && !iss.eof())
	{
		throw std::invalid_argument("Invalid matrix\n");
	}
	if (iss.bad())
	{
		throw std::runtime_error("Stream error while reading first line\n");
	}
	iss.clear();
	iss.str(args.secondLine);
	while (iss >> num)
	{
		vector.push_back(num);
	}
	if (iss.fail() && !iss.eof())
	{
		throw std::invalid_argument("Invalid matrix\n");
	}
	if (iss.bad())
	{
		throw std::runtime_error("Stream error while reading first line\n");
	}
	iss.clear();
	iss.str(args.thirdLine);
	while (iss >> num)
	{
		vector.push_back(num);
	}
	if (iss.fail() && !iss.eof())
	{
		throw std::invalid_argument("Invalid matrix\n");
	}
	if (iss.bad())
	{
		throw std::runtime_error("Stream error while reading first line\n");
	}
	if (vector.size() != MATRIX_SIZE * MATRIX_SIZE)
	{
		throw std::invalid_argument("Invalid matrix\n");
	}

	for (size_t i = 0; i < MATRIX_SIZE; i++)
	{
		for (size_t j = 0; j < MATRIX_SIZE; j++)
		{
			matrix[i][j] =  vector[i * MATRIX_SIZE + j];
		}
	}
	return matrix;
}

double CalculateDeterminant(Matrix matrix)
{
	double det = 1.0;
	for (size_t k = 0; k < MATRIX_SIZE; k++) 
	{
		if (matrix[k][k] == 0) 
		{
			size_t swapRow = k + 1;
			while (swapRow < MATRIX_SIZE && matrix[swapRow][k] == 0) swapRow++;
			if (swapRow == MATRIX_SIZE) return 0.0; 
			std::swap(matrix[k], matrix[swapRow]); 
			det *= -1; 
		}
		det *= matrix[k][k]; 

		for (size_t i = k + 1; i < MATRIX_SIZE; i++) {
			double factor = matrix[i][k] / matrix[k][k];
			for (size_t j = k; j < MATRIX_SIZE; j++) 
			{
				matrix[i][j] -= factor * matrix[k][j];
			}
		}
	}
	return det;
}

double CalculateMinor(const Matrix& matrix, size_t excludedRow, size_t excludedCol)
{
	if (MATRIX_SIZE != 3) {
		return 0; 
	}

	size_t minorRow = 0, minorCol = 0;
	double minorMatrix[2][2];

	for (size_t i = 0; i < MATRIX_SIZE; i++) {
		if (i == excludedRow) continue;
		minorCol = 0;
		for (size_t j = 0; j < MATRIX_SIZE; j++) {
			if (j == excludedCol) continue;
			minorMatrix[minorRow][minorCol] = matrix[i][j];
			minorCol++;
		}
		minorRow++;
	}
	return minorMatrix[0][0] * minorMatrix[1][1] - minorMatrix[0][1] * minorMatrix[1][0];
}

Matrix TransponseTheMatrix(Matrix& matrix)
{
	Matrix transposed;
	for (size_t i = 0; i < MATRIX_SIZE; ++i) {
		for (size_t j = 0; j < MATRIX_SIZE; ++j) {
			transposed[i][j] = matrix[j][i];
		}
	}
	return transposed;
}

Matrix BuidAdjugateMatrix(Matrix& matrix)
{
	Matrix adjugateMatrix;
	for (size_t i = 0; i < MATRIX_SIZE; i++)
	{
		for (size_t j = 0; j < MATRIX_SIZE; j++)
		{
			double minor = CalculateMinor(matrix, i, j);
			adjugateMatrix[i][j] = (i + j) % 2 == 0 ? minor : -minor;
		}
	}
	return adjugateMatrix;
}

Matrix InvertMatrix(Matrix& matrix, double det)
{
	for (size_t i = 0; i < MATRIX_SIZE; i++)
	{
		for (size_t j = 0; j < MATRIX_SIZE; j++) 
		{
			matrix[i][j] /= det;
		}
	}
	return matrix;
}

void PrintMatrix(Matrix& matrix)
{
	std::cout << std::fixed << std::setprecision(3);
	for (size_t i = 0; i < MATRIX_SIZE; i++)
	{
		for (size_t j = 0; j < MATRIX_SIZE; j++) 
		{
			std::cout <<  matrix[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}

int main(int argc, char* argv[])
{
	try
	{
		Args args = ParseArguments(argc, argv);
		if (argc == 1)
		{
			Matrix matrix = FillMatrixFromInput(args);
			double det = CalculateDeterminant(matrix);
			if (det == 0)
			{
				throw std::runtime_error("Non-invertible\n");
			}
			matrix = BuidAdjugateMatrix(matrix);
			matrix = TransponseTheMatrix(matrix);
			InvertMatrix(matrix, det);
			PrintMatrix(matrix);
		}
		else
		{
			//убрать дублирование
			Matrix matrix = FillMatrixFromFile(args);
			double det = CalculateDeterminant(matrix);
			if (det == 0)
			{
				throw std::runtime_error("Non-invertible\n");
			}
			matrix = BuidAdjugateMatrix(matrix);
			matrix = TransponseTheMatrix(matrix);
			InvertMatrix(matrix, det);
			PrintMatrix(matrix);
		}
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
		return 1;
	}
	return 0;
}
