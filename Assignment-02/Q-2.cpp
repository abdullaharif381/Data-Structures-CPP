#include <fstream>
#include <sstream>
#include<iostream>
#include<vector>
#include <windows.h>
using namespace std;
class Node
{
	friend class Maze;
public:
	int data;
	Node* up;
	Node* down;
	Node* right;
	Node* left;
	Node(int d = 0) :data(d), up(nullptr), down(nullptr), left(nullptr),
		right(nullptr)
	{
	}
};
class Maze
{
private:Node* head;
	Node* tail;
	Node* eliteNode;
	int rows;
	int cols;
	Node* getCell(int next_row = 1, int next_col = 1,
		int prev_row =
		1, int prev_col = 1,
		Node* curr = nullptr)
	{
		if (curr == nullptr)
		{
			curr = head;
		}
		if (next_col > prev_col)
		{
			for (int i = prev_col; i != next_col && curr->right; i++)
			{
				curr = curr->right;
			}
		}
		if (next_row > prev_row)
		{
			for (int j = prev_row; j != next_row && curr->down; j++)
			{
				curr = curr->down;
			}
		}
		if (next_col < prev_col)
		{
			for (int i = prev_col; i != next_col && curr->left; i--)
			{
				curr = curr->left;
			}
		}
		if (next_row < prev_row)
		{
			for (int j = prev_row; j != next_row && curr->up; j--)
			{
				curr = curr->up;
			}
		}
		else if ((next_row == prev_row) && (prev_col == next_col))
		{
			eliteNode = curr;
		}
		return curr;
	}
	int ClueRow(int data)
	{
		int sum = 0;
		int digit = data;
		while (digit > 0)
		{
			sum += digit % 10;
			digit /= 10;
		}
		int clue_row = (sum % rows) + 1;
		return clue_row;
	}
	int ClueColumn(int data)
	{
		int num_digits = 0;
		int digit = data;
		while (digit > 0)
		{
			digit /= 10;
			num_digits++;
		}
		int clue_col = num_digits;
		return clue_col;
	}
public:Maze()
{
	this->rows = 0;
	this->cols = 0;
	this->head = nullptr;
	this->tail = nullptr;
	this->eliteNode = nullptr;
}
	int getRow()
	{
		return rows;
	}
	int getCol()
	{
		return cols;
	}
	void Read(const string& filename)
	{
		ifstream inputFile(filename);
		if (!inputFile.is_open())
		{
			cerr << "\tError: Unable to open the file." << endl;
			return;
		}
		Node* prevNode = nullptr;
		string line;
		int row = 0;
		int col = 0;
		int nums = 0;
		while (getline(inputFile, line))
		{
			istringstream iss(line);
			string num;
			col = 0;
			row++;
			while (getline(iss, num, ','))
			{
				nums++;
				col++;
				int number;
				istringstream(num) >> number;
				Node* newNode = new Node(number);
				if (row == 1 && col == 1)
				{
					head = newNode;
				}
				if (col > 1)
				{
					prevNode = getCell(row, col - 1);
					newNode->left = prevNode;
					prevNode->right = newNode;
				}
				if (row > 1)
				{
					prevNode = getCell(row - 1, col);
					newNode->up = prevNode;
					prevNode->down = newNode;
				}
				tail = getCell(row, col);
			}
		}
		this->rows = row;
		this->cols = nums / row;
		inputFile.close();
	}
	void Print()
	{
		cout << "\n+--------+--------+--------+--------+--------+\n\n";
		Node* currentRow = head;
		while (currentRow != nullptr)
		{
			Node* currentNode = currentRow;
			cout << " +";
			for (int i = 0; i < cols; i++)
			{
				cout << "----+";
			}
			cout << endl;
			currentNode = currentRow;
			cout << " |";
			while (currentNode != nullptr)
			{
				int data = currentNode->data;
				int digits = 0;
				while (data > 0)
				{
					digits++;
					data /= 10;
				}
				switch (digits)
				{
				case 1:
					cout << " " << currentNode->data << "  |";
					break;
				case 2:
					cout << " " << currentNode->data << " |";
					break;
				case 3:
					cout << " " << currentNode->data << "|";
					break;
				case 4:
					cout << "" << currentNode->data << "|";
					break;
				}
				currentNode = currentNode->right;
			}
			cout << endl;
			currentNode = currentRow;
			currentRow = currentRow->down;
		}
		Node* lastRow = head->down;
		if (lastRow != nullptr)
		{
			Node* lastNode = lastRow;
			cout << " +";
			for (int i = 0; i < cols; i++)
			{
				cout << "----+";
			}
			cout << endl;
		}
	}
	friend ostream& operator << (ostream& os, Maze m)
	{
		m.Print();
		return os;
	}
	void visit()
	{
		cout << "\n+--------+--------+--------+--------+--------+\n";
		int size = rows * cols;
		vector < int >visited_node_data;
		Node* current_node = head;
		int next_row = 1;
		int next_col = 1;
		int prev_row = 1;
		int prev_col = 1;
		for (int i = 0;; i++)
		{
			Sleep(1000);
			prev_row = next_row;
			prev_col = next_col;
			if (i == 0)
				cout << "\nStarting from top left cell: " << head->data << endl;
			next_row = ClueRow(current_node->data);
			next_col = ClueColumn(current_node->data);
			cout << "\n\tRow Clue: " << next_row << endl;
			cout << "\tColumn Clue: " << next_col << endl;
			current_node =
				getCell(next_row, next_col, prev_row, prev_col, current_node);
			if ((prev_col == next_col) && (next_row == prev_row))
			{
				eliteNode = current_node;
				EliteNode(eliteNode);
				return;
			}
			cout << "\nVisited " << (i +
				1) << ": " << current_node->data << endl;
			visited_node_data.push_back(current_node->data);
			if (current_node != nullptr)
			{
				int target = current_node->data;
				for (int j = 0; j < visited_node_data.size() - 1; j++)
				{
					if (visited_node_data[j] == target)
					{
						EliteNode(current_node);
						return;
					}
					else if (visited_node_data.size() == size)
					{
						EliteNode(tail);
						return;
					}
				}
			}
		}
		return;
	}
	void EliteNode(Node* node)
	{
		cout << "\n+--------+--------+--------+--------+--------+";
		if (node == tail)
		{
			cout << "\n\n There is no Elite Node in the Maze.";
		}
		else if (node == eliteNode)
		{
			cout << "\n\n The Elite Node is " << node->data;
		}
		else
		{
			cout << "\n\n " << node->
				data <<
				" is the node visited for the second time, exiting the program... ";
		}
		cout << "\n\n+--------+--------+--------+--------+--------+\n\n\n";
	}
};
void
run()
{
	Maze maze;
	Sleep(100);
	cout <<
		"\n\t\tLuck is surely the second most important thing to reach what I am looking for. \n\t\t\tHard work and following the clues is the first."
		<<
		endl << endl << endl;
	maze.Read("maze_data.txt");
	Sleep(2000);
	cout << maze;
	Sleep(100);
	maze.visit();
	Sleep(50);
	cout << endl << endl << endl << endl << endl;
	return;
}
int
main()
{
	run();
	return 0;
}
