#include <iostream>
#include <sstream>
#include <Windows.h>
#include <ctime>
#include <iomanip>
#include <string>
using namespace std;
class Node
{
public:
	Node* left;
	Node* right;
	Node* up;
	Node* down;
	Node() :left(nullptr), right(nullptr), up(nullptr), down(nullptr)
	{
	}
	~Node() {}
};
class Digit
{
	friend class Clock;
	Node* peg[6];
public:
	
	Digit(int digit = 8)
	{
		for (int i = 0; i < 6; i++)
			peg[i] = new Node;
		switch (digit)
		{
		case 0:
			peg[0]->right = peg[1];
			peg[4]->right = peg[5];
			peg[0]->down = peg[2];
			peg[1]->down = peg[3];
			peg[2]->down = peg[4];
			peg[3]->down = peg[5];
			peg[1]->left = peg[0];
			peg[5]->left = peg[4];
			peg[2]->up = peg[0];
			peg[3]->up = peg[1];
			peg[4]->up = peg[2];
			peg[5]->up = peg[3];
			break;
		case 1:
			peg[1]->down = peg[3];
			peg[3]->down = peg[5];
			peg[3]->up = peg[1];
			peg[5]->up = peg[3];
			break;
		case 2:
			peg[0]->right = peg[1];
			peg[2]->right = peg[3];
			peg[4]->right = peg[5];
			peg[1]->down = peg[3];
			peg[2]->down = peg[4];
			peg[1]->left = peg[0];
			peg[3]->left = peg[2];
			peg[5]->left = peg[4];
			peg[3]->up = peg[1];
			peg[4]->up = peg[2];
			break;
		case 3:
			peg[0]->right = peg[1];
			peg[2]->right = peg[3];
			peg[4]->right = peg[5];
			peg[1]->down = peg[3];
			peg[3]->down = peg[5];
			peg[1]->left = peg[0];
			peg[3]->left = peg[2];
			peg[5]->left = peg[4];
			peg[3]->up = peg[1];
			peg[5]->up = peg[3];
			break;
		case 4:
			peg[2]->right = peg[3];
			peg[0]->down = peg[2];
			peg[1]->down = peg[3];
			peg[3]->down = peg[5];
			peg[3]->left = peg[2];
			peg[2]->up = peg[0];
			peg[3]->up = peg[1];
			peg[5]->up = peg[3];
			break;
		case 5:
			peg[0]->right = peg[1];
			peg[2]->right = peg[3];
			peg[4]->right = peg[5];
			peg[0]->down = peg[2];
			peg[3]->down = peg[5];
			peg[1]->left = peg[0];
			peg[3]->left = peg[2];
			peg[5]->left = peg[4];
			peg[2]->up = peg[0];
			peg[5]->up = peg[3];
			break;
		case 6:
			peg[0]->right = peg[1];
			peg[2]->right = peg[3];
			peg[4]->right = peg[5];
			peg[0]->down = peg[2];
			peg[2]->down = peg[4];
			peg[3]->down = peg[5];
			peg[1]->left = peg[0];
			peg[3]->left = peg[2];
			peg[5]->left = peg[4];
			peg[2]->up = peg[0];
			peg[4]->up = peg[2];
			peg[5]->up = peg[3];
			break;
		case 7:
			peg[0]->right = peg[1];
			peg[1]->down = peg[3];
			peg[3]->down = peg[5];
			peg[1]->left = peg[0];
			peg[3]->up = peg[1];
			peg[5]->up = peg[3];
			break;
		case 8:
			peg[0]->right = peg[1];
			peg[2]->right = peg[3];
			peg[4]->right = peg[5];
			peg[0]->down = peg[2];
			peg[1]->down = peg[3];
			peg[2]->down = peg[4];
			peg[3]->down = peg[5];
			peg[1]->left = peg[0];
			peg[3]->left = peg[2];
			peg[5]->left = peg[4];
			peg[2]->up = peg[0];
			peg[3]->up = peg[1];
			peg[4]->up = peg[2];
			peg[5]->up = peg[3];
			break;
		case 9:
			peg[0]->right = peg[1];
			peg[2]->right = peg[3];
			peg[4]->right = peg[5];
			peg[0]->down = peg[2];
			peg[1]->down = peg[3];
			peg[3]->down = peg[5];
			peg[1]->left = peg[0];
			peg[3]->left = peg[2];
			peg[5]->left = peg[4];
			peg[2]->up = peg[0];
			peg[3]->up = peg[1];
			peg[5]->up = peg[3];
			break;
		default:
			break;
		}
	}
	~Digit()
	{
		delete[] peg;
		*peg = nullptr;
	}
};
class Clock
{
	friend class Digit;
	friend class Node;
	int minutes;
	int hours;
	int digit1;
	int digit2;
	int digit3;
	int digit4;
	Digit* digits[4];
	string time;
public:
	Clock(string t) :time(t), hours(0), minutes(0)
	{
		digit1 = 0;
		digit2 = 0;
		digit3 = 0;
		digit4 = 0;
		if (time.length() == 5 && time[2] == ':')
		{
			digit1 = time[0] - '0';
			digit2 = time[1] - '0';
			digit3 = time[3] - '0';
			digit4 = time[4] - '0';
			if (digit1 >= 0 && digit1 <= 2 && digit2 >= 0 && digit2 <= 9
				&&
				digit3 >= 0 && digit3 <= 5 && digit4 >= 0 && digit4 <= 9)
			{
				hours = digit1 * 10 + digit2;
				minutes = digit3 * 10 + digit3;
			}
			else
			{
				digit1 = 0;
				digit2 = 0;
				digit3 = 0;
				digit4 = 0;
			}
		}
		else
		{
			hours = 0;
			minutes = 0;
		}
	}
	void AddMinutes(int mins)
	{
		minutes += abs(mins);
		if (minutes >= 60)
		{
			int additionalHours = minutes / 60;
			minutes %= 60;
			AddHours(additionalHours);
		}
	}
	void SubtractMinutes(int mins)
	{
		mins = abs(mins);
		int excessHours = mins / 60;
		minutes -= mins % 60;
		if (minutes < 0)
		{
			minutes = 60 + minutes;
			SubtractHours(1);
		}
		SubtractHours(excessHours);
	}
	void AddHours(int hrs)
	{
		hrs = abs(hrs);
		hours += hrs % 24;
		if (hours >= 24)
		{
			hours %= 24;
		}
	}
	void SubtractHours(int hrs)
	{
		hrs = abs(hrs);
		hours -= hrs % 24;
		if (hours < 0)
		{
			hours += 24;
		}
	}
	void adjustDigits()
	{
		this->digit1 = hours / 10;
		this->digit2 = hours % 10;
		this->digit3 = minutes / 10;
		this->digit4 = minutes % 10;
	}
	void displayTime()
	{
		digits[0] = new Digit(digit1);
		digits[1] = new Digit(digit2);
		digits[2] = new Digit(digit3);
		digits[3] = new Digit(digit4);
		Digit* pad[4] =	{ digits[0], digits[1], digits[2], digits[3] };
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (digits[j]->peg[i * 2]->right != nullptr)
					cout << " ******\t";
				else
					cout << "\t";
				cout << "\t";
			}
			cout << endl;
			for (int j = 0; j < 4; j++)
			{
				if (digits[j]->peg[2 * i]->down != nullptr)
					cout << "|";
				cout << "\t";
				if (digits[j]->peg[(2 * i) + 1]->down != nullptr)
					cout << "|";
				cout << "\t";
			}
			cout << endl;
		}
	}
};
string getCurrentTime()
{
	time_t now = time(0);
	struct tm timeinfo;
	localtime_s(&timeinfo, &now);
	char timeStr[6];
	snprintf(timeStr, sizeof(timeStr), "%02d:%02d", timeinfo.tm_hour,timeinfo.tm_min);
	return string(timeStr);
}
void
run()
{
	string time;
	time = getCurrentTime();
	Clock clock(time);
	int choice;
	do
	{
		clock.adjustDigits();
		cout << "\n\n";
		clock.displayTime();
		cout << "\nMenu:\n";
		cout << "1. Add Minutes\n";
		cout << "2. Subtract Minutes\n";
		cout << "3. Add Hours\n";
		cout << "4. Subtract Hours\n";
		cout << "0. Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			int minutesToAdd;
			cout << "Enter minutes to add: ";
			cin >> minutesToAdd;			
			clock.AddMinutes(minutesToAdd);			
			break;
		case 2:
			int minutesToSubtract;
			cout << "Enter minutes to subtract: ";
			cin >> minutesToSubtract;
			clock.SubtractMinutes(minutesToSubtract);
			break;
		case 3:
			int hoursToAdd;
			cout << "Enter hours to add: ";
			cin >> hoursToAdd;
			clock.AddHours(hoursToAdd);
			break;
		case 4:
			int hoursToSubtract;
			cout << "Enter hours to subtract: ";
			cin >> hoursToSubtract;
			clock.SubtractHours(hoursToSubtract);
			break;
		case 0:
			cout << "Exiting the program. Goodbye!" << endl;
			Sleep(1500);
			break;
		default:
			cout << "Invalid choice. Please try again." << endl;
			Sleep(1500);
			break;
		}
		system("cls");
	} while (choice != 0);
	return;
}
int
main()
{
	run();
	return 0;
}
