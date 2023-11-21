#include<iostream>
#include<string>
#include<queue>
#include<sstream>
#include<fstream>
#include<Windows.h>
using namespace std;
string FILENAME1 = "unsorted.txt";
string REFERENCES = "references.txt";
string RECORD = "record.txt";
int MIN_AGE = 5;
int MAX_AGE = 59;
char NORMAL = 'n';
char CRITICAL = 'c';
class Patient
{
	friend class PriorityQueue;
	string name;
	int age;
	char condition;
	int priority;
	void set_priority(int p)
	{
		priority = p;
	}
	int get_priority()
	{
		return this->priority;
	}
	bool is_urgent_patient(const string& name) const
	{
		ifstream referencesFile(REFERENCES);
		if (!referencesFile)
		{
			cerr << "Error opening references file." << endl;
			return false;
		}
		string line;
		while (getline(referencesFile, line))
		{
			if (line == name)
			{
				referencesFile.close();
				return true;
			}
		}
		referencesFile.close();
		return false;
	}
	int derive_priority()
	{
		bool is_urgent = is_urgent_patient(name);
		int priority = 0;
		if (age < MIN_AGE)
			priority =
			1 + (is_urgent ? 0 : 3) + (condition ==
				CRITICAL ? 6 : (condition ==
					NORMAL ? 12
					: 0));
		else if
			(age >= MIN_AGE && age <= MAX_AGE)
			priority =
			3 + (is_urgent ? 0 : 3) + (condition ==
				CRITICAL ? 6 : (condition ==
					NORMAL ? 12
					: 0));
		else if
			(age > MAX_AGE)
			priority =
			2 + (is_urgent ? 0 : 3) + (condition ==
				CRITICAL ? 6 : (condition ==
					NORMAL ? 12
					: 0));
		return priority;
	}
public:
	Patient(string n = "", int a = -1, char c = ' ')
	{
		name = n;
		age = a;
		condition = c;
		priority = derive_priority();
	}
	string get_name()
	{
		return name;
	}
	int get_age()
	{
		return age;
	}
	char get_condition()
	{
		return condition;
	}
	void set_age(int num)
	{
		age = num;
	}
	void set_condition(char c)
	{
		condition = c;
	}
	void set_name(string n)
	{
		name = n;
	}
	void show()
	{
		cout << "\t\tName: " << this->
			name << "\t\tAge: " << (this->
				age)
			<<
			"\t\t" << (condition =='c' ? "Serious": (condition=='i' ? "Critical": "Normal")) << endl;
	}
};
class PatientQueue
{
	friend class PriorityQueue;
	queue < Patient > patients;
	void write_file(const string& filename)
	{
		ofstream outputFile(filename);
		if (!outputFile)
		{
			cerr << "Error opening the file for writing." << endl;
			return;
		}
		while (!patients.empty())
		{
			Patient& patient = patients.front();
			outputFile << patient.get_name() << " " << patient.
				get_age() << " " << patient.get_condition() << endl;
			patients.pop();
		}
		outputFile.close();
	}
public:
	PatientQueue()
	{
	}
	void read_file(const string& filename)
	{
		ifstream inputFile(filename);
		if (!inputFile)
		{
			cerr << "Error opening the file for reading." << endl;
			return;
		}
		string line;
		while (getline(inputFile, line))
		{
			istringstream iss(line);
			string name;
			int age;
			char condition;
			if ((iss >> name >> age >> condition))
			{
				Patient p(name, age, condition);
				patients.push(p);
			}
		}
		inputFile.close();
		return;
	}
	void view()
	{
		queue < Patient > tempQueue;
		for (int i = 1; !patients.empty(); i++)
		{
			Patient p = patients.front();
			cout << "\t" << i << ".";
			p.show();
			patients.pop();
			tempQueue.push(p);
		}
		patients = tempQueue;
	}
	void update()
	{
		string name;
		int age;
		char condition;
		cout <<
			"\nEnter patient Data:\nName, Age and Condition (i)ntense, (c)critical or (n)ormal): ";
		while (true)
		{
			cin >> name >> age >> condition;			
			if (cin.fail() || age < 1 || age > 100 || (condition != 'i' && condition != 'c' && condition != 'n'))
			{
				cin.clear();
				cin.ignore(256, '\n');
				cout <<	"Invalid input. Please enter a valid name, age between 1 and 100, and condition (i/c/n): ";
			}
			else
			{
				break;
			}
		}
		bool found = false;
		queue < Patient > tempQueue;
		while (!patients.empty())
		{
			Patient patient = patients.front();
			patients.pop();
			if (patient.get_name() == name)
			{
				string newName;
				cout << "Enter New Name: " << endl;
				cin >> newName;				
				patient.set_name(newName);
				patient.set_age(age);
				patient.set_condition(condition);
				found = true;
			}
			tempQueue.push(patient);
		}
		if (!found)
		{
			Patient newPatient(name, age, condition);
			tempQueue.push(newPatient);
		}
		patients = tempQueue;
		write_file(FILENAME1);
		cout << "Patient data updated." << endl;
		patients = tempQueue;
	}
	queue < Patient > get_patients()
	{
		return patients;
	}
	void know(string name = " ")
	{
		bool found = false;
		queue < Patient > tempQueue;
		while (!patients.empty())
		{
			Patient patient = patients.front();
			patients.pop();
			if (patient.get_name() == name)
			{
				cout << "Patient Found:\n";
				patient.show();
				found = true;
			}
			tempQueue.push(patient);
		}
		patients = tempQueue;
		if (!found)
		{
			cout << "Patient with the name '" << name <<
				"' not found in the queue." << endl;
		}
	}
};
class PatientNode
{
	friend class PriorityQueue;
	Patient patient;
	PatientNode* next;
public:
	PatientNode()
	{
		next = nullptr;
		patient = Patient();
	}
	PatientNode(Patient p)
	{
		next = nullptr;
		patient = p;
	}
	Patient get_patient() {	return this->patient;}
	~PatientNode()
	{
	}
};
class PriorityQueue
{
	PatientNode* front;
	void enqueue(Patient p)
	{
		PatientNode* current = front;
		while (current != nullptr)
		{
			if (current->patient.get_name() == p.get_name()
				&&
				current->patient.get_age() == p.get_age()
				&&
				current->patient.get_condition() == p.get_condition())
			{
				return;
			}
			current = current->next;
		}
		PatientNode* n1 = new PatientNode(p);
		if (!front || p.get_priority() < front->patient.get_priority())
		{
			n1->next = front;
			front = n1;
		}
		else
		{
			current = front;
			while (current->next != nullptr
				&&
				p.get_priority() >=
				current->next->patient.get_priority())
			{
				current = current->next;
			}
			n1->next = current->next;
			current->next = n1;
			current = nullptr;
		}
		n1 = nullptr;
	}
public:
	PriorityQueue(PatientNode* front = nullptr)
	{
		this->front = front;
	}
	PriorityQueue(const PriorityQueue& other)
	{
		front = nullptr;
		PatientNode* current = other.front;
		while (current)
		{
			enqueue(current->patient);
			current = current->next;
		}
	}
	PriorityQueue& operator= (const PriorityQueue& other)
	{
		if (this != &other)
		{
			while (!empty())
			{
				pop();
			}
			PatientNode* current = other.front;
			while (current)
			{
				enqueue(current->patient);
				current = current->next;
			}
		}
		return *this;
	}
	void push(PatientQueue& q1)
	{
		queue < Patient > tempQueue;
		while (!q1.patients.empty())
		{
			Patient p = q1.patients.front();
			enqueue(p);
			q1.patients.pop();
			tempQueue.push(p);
		}
		q1.patients = tempQueue;
	}
	void push(PatientNode p)
	{
		Patient p1 = p.get_patient();
		enqueue(p1);
	}
	void pop()
	{
		front = front->next;
	}
	void store(const string& filename = RECORD)
	{
		PriorityQueue tempQueue;
		if (front)
		{
			ofstream outputFile(filename);
			if (!outputFile)
			{
				cerr << "Error opening the file for writing." << endl;
				return;
			}
			while (front)
			{
				Patient p = this->top();
				outputFile << p.get_name() <<
					" " << p.
					get_age() <<
					" " << p.get_condition() << endl;
				this->pop();
				tempQueue.push(p);
			}
			*this = tempQueue;
			outputFile.close();
		}
		else
			cout << "\nNo patients in the Priority Queue\n";
	}
	void view(string& filename = RECORD)
	{
		PriorityQueue tempQueue;
		if (front)
		{
			for (int i = 1; (front); i++)
			{
				Patient p = this->top();
				this->pop();
				tempQueue.push(p);
				cout << "\t" << i << ". ";
				p.show();
			}
			*this = tempQueue;
		}
		else
			cout << "\nNo patients in the Priority Queue\n";
	}
	PriorityQueue deal_elders()
	{
		PriorityQueue oldQueue;
		PriorityQueue tempQueue;
		Patient p1;
		int i = 0;
		while (!this->empty())
		{
			p1 = this->top();
			i++;
			if (!(p1.get_age() >= 60 && i > 4))
			{
				tempQueue.push(p1);
			}
			else
			{
				oldQueue.push(p1);
			}
			this->pop();
		}
		*this = tempQueue;
		return oldQueue;
	}
	Patient top()
	{
		return this->front->patient;
	}
	bool empty()
	{
		return front == nullptr;
	}
	~PriorityQueue()
	{
	}
};
void
serve_patients(PriorityQueue& general, PriorityQueue& elder)
{
	for (int i = 1; !general.empty(); i++)
	{
		Patient active = general.top();
		general.pop();

		cout << "\n\t\tNow Serving: " << i << endl;
		active.show();
		Sleep(1000);
		system("cls");
		if (i % 3 == 0 && !elder.empty())
		{

			active = elder.top();
			elder.pop();
			cout << "\n\t\tNow Serving: " << i + 1 << endl;
			active.show();
			i++;
			Sleep(1000);
			system("cls");
		}

	}
}
int
main()
{
	int choice;
	PatientQueue q1;
	PriorityQueue q2;
	PriorityQueue q3;
	q1.read_file(FILENAME1);
	do
	{
		cout << "\n\n\t\t\t\t\tWELCOME to the OPD QUEUE MANAGER\n\n";
		cout << "\t\t1. View Patients\n\n";
		cout << "\t\t2. Sort Patients by Priority\n\n";
		cout << "\t\t3. Prioritize elders\n\n";
		cout << "\t\t4. Serve Patients\n\n";
		cout << "\t\t5. Know a Patient\n\n";
		cout << "\t\t6. Update Patient Information\n\n";
		cout << "\t\t7. Exit\n\n";
		cout << "\t\tPlease enter your choice: \n\n\n";
		cin >> choice;
		system("cls");
		switch (choice)
		{
		case 1:
		{
			q1.view();
			break;
		}
		case 2:
		{
			q2.push(q1);
			q2.store();
			q2.view();
			break;

		}
		case 3:
		{
			string old_rec = "elder_queue.txt";
			q3 = q2.deal_elders();
			q3.store(old_rec);
			q3.view();
			break;
		}
		case 4:
		{
			serve_patients(q2, q3);
			break;
		}
		case 5:
		{
			string name;
			cout << "Enter the Patient's Name: ";
			cin >> (name);
			q1.know(name);
			break;
		}
		case 6:
		{
			q1.update();
			break;

		}
		case 7:
		{
			cout << "\n\n\t\tGoodbye! Exiting the OPD QUEUE MANAGER...\n";
		}
		default:
		{
			cout << "Invalid choice. Please enter a valid option." << endl;
		}
		}
	} while (choice != 7);
	return 0;
}
