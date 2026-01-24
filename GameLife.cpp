#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <windows.h>

char** create_two_dim_array(int rows, int cols);
void fill_two_dim_array(char** arr, int* arrR, int rows, int cols, int cnt1);
void print_two_dim_array(char** arr, int rows, int cols, int& generationCnt, int cnt1);
void delete_two_dim_array(char** arr, int rows, int cols);
int generation_two_dim_array(char** arr, int* arrR, int rows, int cols);
int compare_two_two_dim_array(char** arr, int* arrR, int* arrC, int rows, int cols, int generationCnt, int cnt1);

int main()
{
	int generationCnt{ 1 };
	int rows{}, cols{};

	std::ifstream ifile1("GL.txt");
	if (ifile1.is_open()) {
		ifile1 >> rows >> cols;
	}
	ifile1.close();

	int num, cnt1{ 0 };
	int const size = rows * cols;
	int* arrR = new int[size * 2];
	int* arrC = new int[size * 2];

	std::ifstream ifile2("GL.txt");	
	if (ifile2.is_open()) {
		ifile2 >> rows >> cols;
		while (ifile2 >> num) {
			arrR[cnt1] = num;
			arrC[cnt1] = num;
			cnt1++;
		}
	}
	ifile2.close();
	


	char** arr = create_two_dim_array(rows, cols);
	fill_two_dim_array(arr, arrR, rows, cols, cnt1);
	print_two_dim_array(arr, rows, cols, generationCnt, cnt1);
	while (true)
	{
		Sleep(2000);
		cnt1 = generation_two_dim_array(arr, arrR, rows, cols);
		if (compare_two_two_dim_array(arr, arrR, arrC, rows, cols, generationCnt, cnt1) == 1) break;
		for (int i = 0; i < cnt1 * 2; i++)
		{
			arrC[i] = arrR[i];
		}
		std::system("cls");
		print_two_dim_array(arr, rows, cols, generationCnt, cnt1);
	}
	delete_two_dim_array(arr, rows, cols);
	delete[] arrR;
	delete[] arrC;

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
	for (int k = 0; k < cnt1; k += 2) {
		int row = arrR[k];
		int col = arrR[k + 1];
		arr[row][col] = '*';
	}

}

void print_two_dim_array(char** arr, int rows, int cols, int& generationCnt, int cnt1)
{
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			std::cout << arr[i][j] << ' ';
		}
		std::cout << '\n';
	}
	std::cout << "Generation: " << generationCnt << " Alive cells: " << cnt1/2 << '\n';
	generationCnt++;
}

void delete_two_dim_array(char** arr, int rows, int cols)
{
	for (int i = 0; i < rows; ++i)
	{
		delete[] arr[i];
	}
	delete[] arr;
}

int generation_two_dim_array(char** arr, int* arrR, int rows, int cols)
{
	char** arrJ = create_two_dim_array(rows, cols);
	int cntR = 0; 
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			int cnt = 0;
			for (int k = -1; k <= 1; ++k)
			{
				for (int m = -1; m <= 1; ++m)
				{
					if (k == 0 && m == 0) continue;
					int r = i + k;
					int c = j + m;

					if (r >= 0 && r < rows && c >= 0 && c < cols)
					{
						if (arr[r][c] == '*') {
							cnt++;
						}
					}
				}
			}
			if (arr[i][j] == '-' && cnt == 3) {
				arrJ[i][j] = '*';
			}
			else if (arr[i][j] == '*' && (cnt == 2 || cnt == 3)) {
				arrJ[i][j] = '*';
			}
			else {
				arrJ[i][j] = '-';
			}
			if (arrJ[i][j] == '*') {
				arrR[cntR++] = i;
				arrR[cntR++] = j;
			}
		}
	}

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			arr[i][j] = arrJ[i][j];
		}
	}
	delete_two_dim_array(arrJ, rows, cols);
	return cntR;
}

int compare_two_two_dim_array(char** arr, int* arrR, int* arrC, int rows, int cols, int generationCnt, int cnt1) {
	if (cnt1 == 0) {
		print_two_dim_array(arr, rows, cols, generationCnt, cnt1);
		std::cout << "All cells are dead. Game over." << '\n';
		return 1;
	}
	bool flag = true;
	int i = 0;
	for (int i = 0; i < cnt1; i++)
	{
		if (arrR[i] != arrC[i])
		{
			flag = false;
			break;
		}
	}
	if (flag == true)
	{
		print_two_dim_array(arr, rows, cols, generationCnt, cnt1);
		std::cout << "The world has stagnated. Game over." << '\n';
		return 1;
	}

	return 0;
	
}
