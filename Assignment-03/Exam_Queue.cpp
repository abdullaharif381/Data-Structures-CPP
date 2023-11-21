#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
double ALREADY_SUBMITTED = 0.72;
double STUDENTS_INFRONT = 0.03;
double RECIEVED_AFTER = 0.37;
int JOHN_ROLL = 420;
int TOTAL = 155;
struct Paper {
	int number;
	Paper() :number(0){}
};
struct Student {
	int rollNumber;
	string name;
	Paper paper;
	Student() :name(" "), rollNumber(0), paper(Paper()) {}
};
vector < Student > read_txt(string people) {
	ifstream read_file(people);
	if (!read_file)	{
		cerr << "Error opening data file." << endl;
		exit(1);
	}
	vector < Student > seated_students;
	Student student;
	char comma;
	while (read_file >> student.rollNumber >> comma >> student.name) {
		student.paper.number = student.rollNumber;
		seated_students.push_back(student);
	}
	return seated_students;
}
void print(const vector < Student > students) {
	cout << "Roll Number\tName" << endl;
	for (const Student& student : students)
	{
		cout << student.rollNumber << "\t\t" << student.name << endl;
	}
}
void received(vector < Student >& s) {
	int i = 0;
	for (const Student& student : s)
	{
		if (student.paper.number == JOHN_ROLL)
		{
			cout << "\n\t\t\t1) John received his paper after " << i <<
				" students\n\n"
				<< endl;
		}
		i++;
	}
}
void submit_paper(stack < Paper >& submission_stack, queue < Student >& desk_queue) {
	while (!desk_queue.empty())
	{
		Student student = desk_queue.front();
		desk_queue.pop();
		submission_stack.push(student.paper);
		if (student.paper.number == JOHN_ROLL)
		{
			cout << "\n\t\t\t3) John's paper is at " 
				<< TOTAL -	submission_stack.size() 
				<<" position in submission stack (from top).\n\n"
				<< "\n\t\t\t3) John's paper is at "
				<< submission_stack.size()
				<< " position in submission stack (from bottom).\n\n" <<endl;
		}
		cout << submission_stack.size() << " : " << student.
			name << "\t\t (" << student.rollNumber << ")" << endl;
	}
}
void enqueue(int roll, const vector < Student >& seated_students,
	queue < Student >& desk_queue)
{
	for (const Student& student : seated_students)
	{
		if (student.rollNumber == roll)
		{
			desk_queue.push(student);
		}
	}
}
void submission(const vector < Student >& seated_students, stack < Paper >& submission_pile, queue < Student >& desk_queue)
{
	cout << "\n\tQUEUE AFTER EXAM: \n" << endl;
	int students_before_john = (TOTAL * ALREADY_SUBMITTED);
	int students_after_john = (TOTAL - students_before_john - 1);
	int out_before_john = (TOTAL * (ALREADY_SUBMITTED - STUDENTS_INFRONT));
	int in_before_john = (TOTAL * STUDENTS_INFRONT);
	int position_of_john = students_before_john + 1;
	int second_queue_size = TOTAL - out_before_john;
	vector < int >unique_indices;
	for (int i = 0; i < TOTAL; i++)
	{
		unique_indices.push_back(i);
	}
	random_shuffle(unique_indices.begin(), unique_indices.end());
	for (int i = 0; i < TOTAL; i++)
	{
		int index = unique_indices[i];
		Student student = seated_students[index];
		if (submission_pile.size() < out_before_john
			&& desk_queue.size() < out_before_john
			&& student.rollNumber != JOHN_ROLL)
		{
			desk_queue.push(student);
			if (desk_queue.size() == out_before_john)
			{
				submit_paper(submission_pile, desk_queue);
				continue;
			}
		}
		if (submission_pile.size() >= out_before_john)
		{
			if (desk_queue.size() < in_before_john
				&& student.rollNumber != JOHN_ROLL)
			{
				desk_queue.push(student);
			}
			else if (desk_queue.size() == in_before_john)
			{
				enqueue(JOHN_ROLL, seated_students, desk_queue);
				cout << "\n\t\t\t2) John had to wait for " << in_before_john <<
					" students before submitting the paper.\n\n" << endl;
			}
			else if (desk_queue.size() > in_before_john
				&& student.rollNumber != JOHN_ROLL)
			{
				desk_queue.push(student);
			}
		}
	}
	submit_paper(submission_pile, desk_queue);
}
void
checking(vector < Student > student, stack < Paper >& submission_pile,
	stack < Paper >& resultant_pile)
{
	cout << "\n\tCHECKING DAY: \n\n" << endl;
	int i = 0;
	while (!submission_pile.empty())
	{
		Paper paper = submission_pile.top();
		submission_pile.pop();
		resultant_pile.push(paper);
		cout << resultant_pile.size() << " : " << "\t\t (" << paper.
			number << ")" << endl;
		if (paper.number == JOHN_ROLL)
		{
			cout << "\n\t\t\t4) John's paper was marked at " << resultant_pile.
				size() << " position.\n";
			cout << "\n\t\t\t5) John's paper is at " << TOTAL -
				resultant_pile.
				size() <<
				" position in resultant stack (from top).\n\n";
			cout << "\n\t\t\t5) John's paper is at " << resultant_pile.
				size() << " position in resultant stack (from bottom).\n\n" <<
				endl;
		}
		i++;
	}
}
void
return_paper(stack < Paper >& resultant_pile,
	queue < Student >& result_day_queue)
{
	cout << "\n\tRESULT DAY QUEUE: " << endl;
	vector < Paper > p;
	while (!resultant_pile.empty())
	{
		p.push_back(resultant_pile.top());
		resultant_pile.pop();
	}
	reverse(p.begin(), p.end());
	while (!result_day_queue.empty())
	{
		int queueFront = result_day_queue.front().rollNumber;
		bool found = false;
		int i = 0;
		for (auto it = p.begin(); it != p.end(); ++it)
		{
			if (queueFront == it->number)
			{
				found = true;
				cout << result_day_queue.size() << " : " << result_day_queue.
					front().name << " (" << it->number << ")" << endl;
				if (it->number == JOHN_ROLL)
				{
					if (i >= TOTAL - i)
					{
						cout << "\n\t\t\t7) John has to go through " << i <<" papers at maximum on result day.\n\n"<< "\n\t\t\t8) John has to go through " << TOTAL -	i << " papers at minimum  on result day.\n\n" << endl;
					}
					if ((i <= TOTAL - i))
					{
						cout << "\n\t\t\t7) John has to go through " << i <<" papers at minimum  on result day.\n\n";
						cout << "\n\t\t\t8) John has to go through " << TOTAL-i << " papers at maximum  on result day.\n\n" << endl;
					}
				}
				result_day_queue.pop();
				it = p.erase(it);
				break;
			}
			else
				i++;		
		}
		if (!found)
		{
			result_day_queue.pop();
		}
	}
}
void
rechecking(const vector < Student > seated_students,
	stack < Paper >& resultant_pile,
	queue < Student >& result_day_queue)
{
	cout << "\n\tRESULT DAY QUEUE: " << endl;
	int students_before_john = round(TOTAL * RECIEVED_AFTER);
	int students_after_john = round(TOTAL - students_before_john - 1);
	int position_of_john = students_before_john + 1;
	vector < int >unique_indices;
	cout << "\n\t\t6) John received his paper back after " <<
		students_before_john
		<< " students.\n\n" << endl;
	for (int i = TOTAL - 1; i >= 0; i--)
	{
		unique_indices.push_back(i);
	}
	random_shuffle(unique_indices.begin(), unique_indices.end());
	for (int i = 0; i < TOTAL; i++)
	{
		int index = unique_indices[i];
		Student student = seated_students[index];
		if (student.rollNumber != JOHN_ROLL
			&& result_day_queue.size() < students_before_john)
		{
			result_day_queue.push(student);
		}
		else if (result_day_queue.size() == students_before_john)
		{
			enqueue(JOHN_ROLL, seated_students, result_day_queue);
		}
		else if (student.rollNumber != JOHN_ROLL&& result_day_queue.size() > students_before_john)
		{
			result_day_queue.push(student);
		}
	}
	return_paper(resultant_pile, result_day_queue);
}
int
main()
{
	vector < Student > seated_students = read_txt("data.txt");
	stack < Paper > submission_pile;
	queue < Student > desk_queue;
	stack < Paper > resultant_pile;
	queue < Student > result_day_queue;
	stack < Paper > result_pile;
	print(seated_students);
	received(seated_students);
	submission(seated_students, submission_pile, desk_queue);
	checking(seated_students, submission_pile, resultant_pile);
	rechecking(seated_students, resultant_pile, result_day_queue);
	return 0;
}
