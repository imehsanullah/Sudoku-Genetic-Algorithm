#include<iostream>
#include<string>
#include<vector>
#include <stdio.h>
#include <stdlib.h>
#include <utility>

using namespace std;

int POP_SIZE = 15000;
int Select_rate = 25;
int Cross_rate = 50;
int Mutate_rate = 25;
int Precision_Mutate_rate = 0;

int Crossover1_start = (POP_SIZE * 0) / 100;
int Crossover1_end = (POP_SIZE * 50) / 100;
int Crossover2_start = (POP_SIZE * 0) / 100;
int Crossover2_end = (POP_SIZE * 70) / 100;

int Mutation_start = (POP_SIZE * 0) / 100;
int Mutation_end = (POP_SIZE * 50) / 100;


int Convergence_Select_rate = (POP_SIZE * 20) / 100;
int Convergence_Mutation_start = (POP_SIZE * 0) / 100;
int Convergence_Mutation_end = (POP_SIZE * 30) / 100;

int Convergence_newPopulation = (POP_SIZE * 50) / 100;


char* Board = 0;

char ConverttoString(int l)
{
	return '0' + l;
}

int ConverttoInt(char s)
{
	return s - '0';
}

char* Convert2DarraytoString(int arr[][9])
{
	char* word = new char[83];
	int size = 0;

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (arr[i][j] == -1)
			{
				word[size++] = ' ';
			}
			else
			{
				word[size++] = ConverttoString(arr[i][j]);
			}
		}

	}
	word[size] = '\0';
	return word;
}

//To Print the Sudoku form on Console
void PrintMatrix(int arr[9][9])
{
	for (int i = 0; i < 9; i++)
	{
		cout << " { ";
		for (int j = 0; j < 9; j++)
		{
			cout << arr[i][j];
			if (j != 8)
			{
				cout << ",";

			}
		}
		cout << " } " << endl;
	}

}

//To get the count of Duplicates in a row ,col or a Block
int getCount(int arr[], int size)
{
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (arr[i] > 1)
		{
			count += arr[i] - 1;
		}
	}
	return count;
}


//To help solve the Sudokus close to the best Solution
void GetDuplicatedigit(vector<pair<int, char>>& V, int arr[], int size, int side)
{

	for (int i = 1; i < size; i++)
	{
		if (arr[i] > 1)
		{
			for (int i = 1; i < arr[i]; i++)
			{
				V.push_back(make_pair(side, ConverttoString(i)));
			}
		}

	}

}

class Sudoku
{
	char* board;
	int fitness;
public:
	Sudoku(int n = 0)
	{
		if (n == 0)
		{
			board = new char[82];
			for (int i = 0; i <= 81; i++)
			{
				if (Board[i] != ' ') {
					board[i] = Board[i];
				}
				else
				{
					board[i] = ConverttoString(1 + (rand() % 9));
				}
			}
			board[81] = '\0';
			CalculateFitness();
		}
	}


	Sudoku(const Sudoku & obj)
	{
		board = new char[82];
		for (int i = 0; i <= 81; i++)
		{
			board[i] = obj.board[i];
		}
		board[81] = '\0';
		fitness = obj.fitness;
	}
	Sudoku& operator=(const Sudoku & obj)
	{
		board = new char[82];
		for (int i = 0; i <= 81; i++)
		{
			board[i] = obj.board[i];
		}
		board[81] = '\0';
		fitness = obj.fitness;
	}
	int CalculateFitness()
	{
		int count = 0;
		//Counting Dups in rows
		for (int i = 0; i < 81; i += 9)
		{
			int arr[10] = { 0,0,0,0, 0,0, 0,0, 0,0 };
			for (int j = 0; j < 9; j++)
			{
				if (board[i + j] != ' ')
				{
					arr[ConverttoInt(board[i + j])] = arr[ConverttoInt(board[i + j])] + 1;

				}
			}
			count += getCount(arr, 10);
		}

		//Counting Dups in Cols  for (int i = 0; i < 81; i += 9)
		for (int j = 0; j < 9; j++)
		{
			int arr[10] = { 0,0,0,0, 0,0, 0,0, 0,0 };
			for (int i = 0; i < 81; i += 9)
			{
				if (board[i + j] != ' ')
				{
					arr[ConverttoInt(board[i + j])] = arr[ConverttoInt(board[i + j])] + 1;

				}
			}
			count += getCount(arr, 10);
		}
		//Counting Dups in Blocks
		for (int i = 0; i < 81; i += 27)
		{
			for (int j = 0; j < 9; j += 3)
			{
				int arr[10] = { 0,0,0,0, 0,0, 0,0, 0,0 };
				for (int k = 0; k < 27; k += 9)
				{
					for (int l = 0; l < 3; l++)
					{
						arr[ConverttoInt(board[i + j + k + l])] = arr[ConverttoInt(board[i + j + k + l])] + 1;

					}
				}
				count += getCount(arr, 10);
			}

		}

		fitness = count;
		return count;
	}
	int FindDuplicates()
	{
		int count = 0;
		//Counting Dups in rows
		for (int i = 0; i < 81; i += 9)
		{
			int arr[10] = { 0,0,0,0, 0,0, 0,0, 0,0 };
			for (int j = 0; j < 9; j++)
			{
				if (board[i + j] != ' ')
				{
					arr[ConverttoInt(board[i + j])] = arr[ConverttoInt(board[i + j])] + 1;

				}
			}
			int num = getCount(arr, 10);
			if (num > 0)
			{
				cout << "in row : " << (i / 9) << endl;
			}
			count += num;
		}

		//Counting Dups in Cols  
		for (int j = 0; j < 9; j++)
		{
			int arr[10] = { 0,0,0,0, 0,0, 0,0, 0,0 };
			for (int i = 0; i < 81; i += 9)
			{
				if (board[i + j] != ' ')
				{
					arr[ConverttoInt(board[i + j])] = arr[ConverttoInt(board[i + j])] + 1;

				}
			}
			int num = getCount(arr, 10);
			if (num > 0)
			{
				cout << "in Coloum :" << (j) << endl;
			}

			count += num;
		}
		//Counting Dups in Blocks
		for (int i = 0; i < 81; i += 27)
		{
			for (int j = 0; j < 9; j += 3)
			{
				int arr[10] = { 0,0,0,0, 0,0, 0,0, 0,0 };
				for (int k = 0; k < 27; k += 9)
				{
					for (int l = 0; l < 3; l++)
					{
						arr[ConverttoInt(board[i + j + k + l])] = arr[ConverttoInt(board[i + j + k + l])] + 1;

					}
				}
				int num = getCount(arr, 10);
				if (num > 0)
				{
					cout << "in Block :" << (i / 9) + j / 3 << endl;
				}
				count += num;
			}

		}


		return count;
	}

	//To take Crossover of 2 Chromosomes/Individuals
	Sudoku* Crossover(const Sudoku & obj)
	{
		Sudoku* nobj = new Sudoku(1);
		nobj->board = new char[83];
		int P1 = rand() % 81;
		int P2 = P1 + (rand() % (80 - P1 + 1));

		for (int i = 0; i < P1; i++)
		{
			nobj->board[i] = this->board[i];
		}

		for (int i = P1; i < P2; i++)
		{
			nobj->board[i] = obj.board[i];
		}
		for (int i = P2; i <= 80; i++)
		{
			nobj->board[i] = this->board[i];
		}
		nobj->board[81] = '\0';
		nobj->CalculateFitness();
		return nobj;
	}

	//To Mutate a Chromosome
	Sudoku* Mutate()
	{
		Sudoku* nobj = new Sudoku(1);
		nobj->board = new char[83];
		int P1 = rand() % 81;
		int P2 = P1 + (rand() % (80 - P1 + 1));

		for (int i = 0; i < P1; i++)
		{
			nobj->board[i] = this->board[i];
		}

		for (int i = P1; i <= P2; i++)
		{
			nobj->board[i] = ConverttoString(1 + (rand() % 9));
		}
		for (int i = P2 + 1; i <= 80; i++)
		{
			nobj->board[i] = this->board[i];
		}
		nobj->board[81] = '\0';
		nobj->CalculateFitness();
		return nobj;
	}

	//Precision Mutation which is used to help when we have reached closed to the Desired Solution
	Sudoku* PrecisionMutate()
	{

		Sudoku* nobj = new Sudoku(1);
		nobj->board = new char[83];
		for (int i = 0; i <= 81; i++)
		{
			nobj->board[i] = board[i];
		}

		int count = 0;


		//Counting Dups in rows
		vector<pair<int, char>> rows;
		for (int i = 0; i < 81; i += 9)
		{
			int arr[10] = { 0,0,0,0, 0,0, 0,0, 0,0 };
			for (int j = 0; j < 9; j++)
			{
				if (board[i + j] != ' ')
				{
					arr[ConverttoInt(board[i + j])] = arr[ConverttoInt(board[i + j])] + 1;

				}
			}
			int num = getCount(arr, 10);
			if (num > 0)
			{
				GetDuplicatedigit(rows, arr, 10, (i / 9));
			}
			count += num;
		}
		for (int i = 0; i < rows.size(); i++)
		{
			pair<int, char>p = rows[i];
			int r = p.first * 9;
			for (int j = 0; j < 9; j++)
			{
				if (nobj->board[r + j] == p.second && Board[r + j] == ' ')
				{
					nobj->board[r + j] = ConverttoString(1 + (rand() % 9));
					break;
				}
			}
		}

		vector<pair<int, char>> cols;
		//Counting Dups in Cols  for (int i = 0; i < 81; i += 9)
		for (int j = 0; j < 9; j++)
		{
			int arr[10] = { 0,0,0,0, 0,0, 0,0, 0,0 };
			for (int i = 0; i < 81; i += 9)
			{
				if (board[i + j] != ' ')
				{
					arr[ConverttoInt(board[i + j])] = arr[ConverttoInt(board[i + j])] + 1;

				}
			}
			int num = getCount(arr, 10);
			if (num > 0)
			{
				GetDuplicatedigit(cols, arr, 10, (j));
			}

			count += num;
		}
		for (int i = 0; i < cols.size(); i++)
		{
			pair<int, char>p = cols[i];
			int r = p.first;
			for (int j = 0; j < 81; j += 9)
			{
				if (nobj->board[r + j] == p.second && Board[r + j] == ' ')
				{
					nobj->board[r + j] = ConverttoString(1 + (rand() % 9));
					break;
				}
			}
		}
		vector<pair<int, char>> blocks;
		//Counting Dups in Blocks
		for (int i = 0; i < 81; i += 27)
		{
			for (int j = 0; j < 9; j += 3)
			{
				int arr[10] = { 0,0,0,0, 0,0, 0,0, 0,0 };
				for (int k = 0; k < 27; k += 9)
				{
					for (int l = 0; l < 3; l++)
					{
						arr[ConverttoInt(board[i + j + k + l])] = arr[ConverttoInt(board[i + j + k + l])] + 1;

					}
				}
				int num = getCount(arr, 10);
				if (num > 0)
				{
					GetDuplicatedigit(blocks, arr, 10, ((i / 9) + j / 3));

				}
				count += num;
			}

		}

		for (int i = 0; i < blocks.size(); i++)
		{
			pair<int, char>p = blocks[i];
			int r = ((p.first) / 3) * 27 + ((p.first) % 3) * 3;
			for (int k = 0; k < 27; k += 9)
			{
				for (int l = 0; l < 3; l++)
				{

					if (nobj->board[r + k + l] == p.second && Board[r + k + l] == ' ')
					{
						nobj->board[r + k + l] = ConverttoString(1 + (rand() % 9));
						break;
					}
				}
			}
		}

		nobj->board[81] = '\0';
		nobj->CalculateFitness();
		return nobj;
	}
	void Print()
	{
		for (int i = 0; i < 81; i += 9)
		{
			cout << "{";
			for (int j = 0; j < 9; j++)
			{
				cout << board[i + j];
				if (j != 8)
				{
					cout << " ,";
				}
			}
			cout << "}" << endl;
		}
	}

	int getfitness()
	{
		return fitness;
	}
	~Sudoku()
	{
		delete[]board;
	}
};


void Sort(Sudoku * *&arr, int size)
{

	vector<Sudoku*>* hash = new vector<Sudoku*>[220];
	for (int i = 0; i < POP_SIZE; i++)
	{
		hash[arr[i]->getfitness()].push_back(arr[i]);
	}
	int s = 0;
	for (int i = 0; i < 220; i++)
	{
		if (!hash[i].empty())
		{
			for (int j = 0; j < hash[i].size(); j++)
			{
				arr[s++] = hash[i][j];
			}
		}
	}
	delete[]hash;
}


int getanumbw(int a, int b)
{

	return a + (rand() % (b - a + 1));
}

void A3()
{
	int arr[9][9] = { {5, 3, -1, -1, 7, -1, -1, -1, -1},{6, -1, -1, 1, 9, 5, -1, -1, -1}, {-1, 9, 8, -1, -1, -1, -1, 6, -1}, {8, -1, -1, -1, 6, -1, -1, -1, 3}, {4, -1, -1, 8, -1, 3, -1, -1, 1}, {7, -1, -1, -1, 2, -1, -1, -1, 6}, {-1, 6, -1, -1, -1, -1, 2, 8, -1}, {-1, -1, -1, 4, 1, 9, -1, -1, 5}, {-1, -1, -1, -1, 8, -1, -1, 7, 9} };

	//Convertinf the Matrix to a String
	Board = Convert2DarraytoString(arr);
	Sudoku** Population = new Sudoku * [POP_SIZE];
	for (int i = 0; i < POP_SIZE; i++)
	{
		Population[i] = new Sudoku();
	}
	Sort(Population, POP_SIZE);//Sorting in O(n)

	int itr = 0;
	bool flag = true;

	int Prevgen = -1;
	int newgen = -2;
	int convergence = 0;
	while (itr < 150 && Population[0]->getfitness() != 0)
	{
		cout << "Best value in Generation " << itr << " is " << Population[0]->getfitness() << endl;
		Sudoku** newPopulation = new Sudoku * [POP_SIZE];
		int npsize = 0;

		newgen = Population[0]->getfitness();
		//To handle Pre-Mature Convergence
		if (newgen == Prevgen)
		{
			convergence++;
		}
		else
		{
			convergence = 0;
		}
		if (convergence <= 8)
		{
			//Precision Mutation Activated when we have reached 10 units near to desired fitness
			if (Population[0]->getfitness() < 10 && flag == true)
			{
				Cross_rate -= 10;
				Precision_Mutate_rate += 10;
				flag = false;
			}

			//Selection Using Elitism (tried the Roulette wheel was n't that effective for me)
			for (int i = 0; i < (POP_SIZE * Select_rate) / 100; i++)
			{
				newPopulation[npsize++] = Population[i];
			}

			//CrossOver
			for (int i = 0; i < (POP_SIZE * Cross_rate) / 100; i++)
			{
				int ind1 = getanumbw(Crossover1_start, Crossover1_end);
				int ind2 = getanumbw(Crossover2_start, Crossover2_end);

				Sudoku* sudo = Population[ind1]->Crossover(*Population[ind2]);
				newPopulation[npsize++] = sudo;
			}

			//Mutate
			for (int i = 0; i < (POP_SIZE * Mutate_rate) / 100; i++)
			{
				int ind = getanumbw(Mutation_start, Mutation_end);
				Sudoku* sudo = Population[ind]->Mutate();
				newPopulation[npsize++] = sudo;

			}

			//Only Done when reached close to Solution
			for (int i = 0; i < (POP_SIZE * Precision_Mutate_rate) / 100; i++)
			{
				int ind = getanumbw(0, (POP_SIZE * 5) / 100);
				Sudoku * sudo = Population[ind]->PrecisionMutate();
				newPopulation[npsize++] = sudo;

			}

			for (int i = (POP_SIZE * Select_rate) / 100; i < POP_SIZE; i++)
			{
				delete Population[i];

			}
			delete[]Population;

		}
		else
		{
			//Including new Chromsomes in the Population when population has converged
			convergence = 0;
			for (int i = 0; i < Convergence_Select_rate; i++)
			{
				newPopulation[npsize++] = Population[i];
			}
			for (int i = Convergence_Mutation_start; i < Convergence_Mutation_end; i++)
			{
				newPopulation[npsize++] = Population[i]->Mutate();
			}
			for (int i = Convergence_newPopulation; i < POP_SIZE; i++)
			{
				newPopulation[npsize++] = new Sudoku();
			}
			for (int i = Convergence_Select_rate; i < POP_SIZE; i++)
			{
				delete Population[i];

			}
			delete[]Population;

		}


		Prevgen = newgen;

		Population = 0;
		Population = newPopulation;
		Sort(Population, POP_SIZE);
		itr++;
	}
	cout << "Best value in Generation " << itr << " is " << Population[0]->getfitness() << endl;
	cout << "The Solution of the Given Matrix to the Genetic Algorithm is" << endl;
	Population[0]->Print();

	cout << "Duplicates if any in the Solution are :"<<endl;
	Population[0]->FindDuplicates();
	cout << "Fitness Value of the Solution is";
	cout << Population[0]->getfitness();
}

int main()
{
	A3();
}