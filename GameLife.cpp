#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

char** create_two_dim_array(int rows, int cols);
void fill_two_dim_array(char** arr, int* arrR, int rows, int cols, int cnt1);
void print_two_dim_array(char** arr, int rows, int cols);
void delete_two_dim_array(char** arr, int rows, int cols);

void generation_two_dim_array(char** arr, int rows, int cols);

int main()
{
	int rows{}, cols{};

	std::ifstream ifile1("GL.txt");
	if (ifile1.is_open()) {
		ifile1 >> rows >> cols;
	}
	ifile1.close();

	int num, cnt1{ 0 };
	int* arrR = new int[std::max(rows, cols)];

	std::ifstream ifile2("GL.txt");
	if (ifile2.is_open()) {
		ifile2 >> rows >> cols;
		while (ifile2 >> num) {
			arrR[cnt1] = num;
			cnt1 += 1;
		}
	}
	ifile2.close();

	char** arr = create_two_dim_array(rows, cols);
	fill_two_dim_array(arr, arrR, rows, cols, cnt1);
	generation_two_dim_array(arr, rows, cols);
	print_two_dim_array(arr, rows, cols);
	delete_two_dim_array(arr, rows, cols);
	delete[] arrR;

	return 0;
}

char** create_two_dim_array(int rows, int cols)
{
		char** arr = new char* [rows];
		for (int i = 0; i < rows; ++i)
		{
			arr[i] = new char[cols];
		}
		return arr;
}

void fill_two_dim_array(char** arr, int* arrR, int rows, int cols, int cnt1)
{

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			arr[i][j] = '-';
		}
	}
	for (int k = 0; k < cnt1-1; k += 2) {
		int row = arrR[k];
		int col = arrR[k + 1];
		arr[row][col] = '*';
	}

}

void print_two_dim_array(char** arr, int rows, int cols)
{
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			std::cout << arr[i][j] << ' ';
		}
		std::cout << '\n';
	}
}

void delete_two_dim_array(char** arr, int rows, int cols)
{
	for (int i = 0; i < rows; ++i)
	{
		delete[] arr[i];
	}
	delete[] arr;
}

void generation_two_dim_array(char** arr, int rows, int cols)
{
	for (int i = 1; i < rows-1; ++i)
	{
		for (int j = 1; j < cols-1; ++j)
		{
			std::string check_all = std::to_string(arr[i - 1][j - 1]) + std::to_string(arr[i - 1][j]) + std::to_string(arr[i][j - 1]) + std::to_string(arr[i + 1][j + 1]) + std::to_string(arr[i + 1][j]) + std::to_string(arr[i][j + 1]) + std::to_string(arr[i - 1][j + 1]) + std::to_string(arr[i + 1][j - 1]);
			int cnt = std::count(check_all.begin(), check_all.end(), '*');
			if (cnt == 3 && arr[i][j] == '-') {
				arr[i][j] = '*';
			}
			else if ((cnt == 3 || cnt == 2) && arr[i][j] == '*') {
				arr[i][j] = '*';
			}
			else {
				arr[i][j] = '-';
			}
		}
	}
	for (int i = 0; i < rows-1; ++i)//left col
	{
		int j = 0;
		std::string check_lt = std::to_string(arr[i + 1][j + 1]) + std::to_string(arr[i + 1][j]) + std::to_string(arr[i][j + 1]);
		int cnt = std::count(check_lt.begin(), check_lt.end(), '*');
		if (cnt == 3 && arr[i][j] == '-') {
			arr[i][j] = '*';
		}
		else if ((cnt == 3 || cnt == 2) && arr[i][j] == '*') {
			arr[i][j] = '*';
		}
		else {
			arr[i][j] = '-';
		}
	}
	for (int i = 0; i < rows-1; ++i)//right col
	{
		int j = cols;
		std::string check_rt = std::to_string(arr[i][j - 1]) + std::to_string(arr[i + 1][j-1]) + std::to_string(arr[i+1][j]);
		int cnt = std::count(check_rt.begin(), check_rt.end(), '*');
		if (cnt == 3 && arr[i][j] == '-') {
			arr[i][j] = '*';
		}
		else if ((cnt == 3 || cnt == 2) && arr[i][j] == '*') {
			arr[i][j] = '*';
		}
		else {
			arr[i][j] = '-';
		}
	}
	for (int j = 1; j < cols-1; ++j)//high col
	{
		int i = 0;
		std::string check_high = std::to_string(arr[i][j - 1]) + std::to_string(arr[i + 1][j-1]) + std::to_string(arr[i+1][j]) + std::to_string(arr[i + 1][j + 1]) + std::to_string(arr[i][j + 1]);
		int cnt = std::count(check_high.begin(), check_high.end(), '*');
		if (cnt == 3 && arr[i][j] == '-') {
			arr[i][j] = '*';
		}
		else if ((cnt == 3 || cnt == 2) && arr[i][j] == '*') {
			arr[i][j] = '*';
		}
		else {
			arr[i][j] = '-';
		}
	}
	for (int j = 1; j < cols-1; ++j)//low col
	{
		int i = rows;
		std::string check_low = std::to_string(arr[i][j - 1]) + std::to_string(arr[i - 1][j-1]) + std::to_string(arr[i-1][j]) + std::to_string(arr[i - 1][j + 1]) + std::to_string(arr[i][j + 1]);
		int cnt = std::count(check_low.begin(), check_low.end(), '*');
		if (cnt == 3 && arr[i][j] == '-') {
			arr[i][j] = '*';
		}
		else if ((cnt == 3 || cnt == 2) && arr[i][j] == '*') {
			arr[i][j] = '*';
		}
		else {
			arr[i][j] = '-';
		}
	}
}

