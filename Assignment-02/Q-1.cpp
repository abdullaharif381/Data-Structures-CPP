#include <iostream>
using namespace std;
template <typename T>
class LinkedList {
public:
	class Node {
	public:
		T data;
		Node* next;
		Node(T val) : data(val), next(nullptr) {}
	};
	Node* head;
	LinkedList() : head(nullptr) {}
	void addNode(T val) {
		Node* newNode = new Node(val);
		if (!head) {
			head = newNode;
		}
		else {
			Node* current = head;
			while (current->next) {
				current = current->next;
			}
			current->next = newNode;
		}
	}
	friend ostream& operator<<(ostream& os, const LinkedList<T>& list) {
		Node* current = list.head;
		while (current) {
			os << current->data;
			current = current->next;
			if (current) {
				os << " -> ";
			}
		}
		return os;
	}
};
template <typename T>
LinkedList<LinkedList<T>> BreakDown(LinkedList<T>& inputList, int k) {
	LinkedList<LinkedList<T>> result;
	typename LinkedList<T>::Node* current = inputList.head;
	LinkedList<T> subList;
	while (current) {
		int count = 0;
		while (current && count < k) {
			subList.addNode(current->data);
			current = current->next;
			count++;
		}
		result.addNode(subList);
		subList.head = nullptr;
	}
	return result;
}
template <typename T>
void print(const LinkedList<LinkedList<T>>& nestedList) {
	class LinkedList<LinkedList<T>>::Node* current = nestedList.head;
	while (current) {
		cout << "\t[";
		cout << current->data;
		cout << "]\t";
		current = current->next;
		if (current) {
			cout << " -> ";
		}
	}
}
void run() {
	cout << "\n\t+=====+=====+=====+=====+====+\n\t Breakdown a Linked List \n\t+=====+=====+=====+=====+====+\n";
	LinkedList<int> inputList;
	int k;
	int size = 0;
	
	cout << "\tEnter size of Linked List: ";
	cin >> size;
	for (int i = 1; i <= size; i++) {
				
		inputList.addNode(i);
	}
	cout << "\n\tEnter value of k (size of sub-lists): ";
	cin >> k;
	cout << "\n\n\tOriginal Linked List: " << inputList;
	cout << "\n\n\tk = " << k<<"\n\tsize = "<<size;
	LinkedList<LinkedList<int>> groupedLists = BreakDown(inputList, k);
	cout << "\n\n\tLinked List of linked lists: ";
	print(groupedLists);
	cout << endl;
}
int main() {
	run();
	return 0;
}
