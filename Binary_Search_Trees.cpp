#include <iostream>
#include <queue>
using namespace std;
struct Node
{
	int data;
	Node* left;
	Node* right;
};

class BST
{
	Node* root;

	Node* insert(Node* current, int value)
	{
		if (current == nullptr)
		{
			Node* newNode = new Node;
			newNode->data = value;
			newNode->left = newNode->right = nullptr;
			return newNode;
		}

		if (value < current->data)
			current->left = insert(current->left, value);
		else if (value > current->data)
			current->right = insert(current->right, value);

		return current;
	}
	Node* copyTree(Node* current) const
	{
		if (current == nullptr)
			return nullptr;

		Node* newNode = new Node;
		newNode->data = current->data;
		newNode->left = copyTree(current->left);
		newNode->right = copyTree(current->right);

		return newNode;
	}

	void inorderPrint(Node* current) const
	{
		if (current)
		{
			inorderPrint(current->left);
			cout << current->data << " ";
			inorderPrint(current->right);
		}
	}
	void preorderprint(Node* current) const
	{
		if (current)
		{
			cout << current->data << " ";
			preorderprint(current->left);
			preorderprint(current->right);
		}
	}

	void postorderprint(Node* current) const
	{
		if (current)
		{
			postorderprint(current->left);
			postorderprint(current->right);
			cout << current->data << " ";
		}
	}

	int height(Node* curr) const {
		if (!curr)
			return 0;
		return (max(height(curr->left), height(curr->right)) + 1);

	}
	int depth(Node* curr)const {
		if (!curr)
			return 0;
		int leftH = height(curr->left);
		int rightH = height(curr->right);
		return (max(leftH, rightH) + 1);

	}

	void singleLevelPrint(Node* curr, int level) const {
		if (!curr)
			return;
		if (level == 0) {

			cout << curr->data << " ";
		}
		else if (level > 0) {
			singleLevelPrint(curr->left, level - 1);
			singleLevelPrint(curr->right, level - 1);
		}
	}
	void HelperlevelorderPrint(Node* current) const
	{
		if (current == nullptr)
			return;

		queue<Node*> q;
		q.push(current);

		while (!q.empty())
		{
			Node* node = q.front();
			q.pop();
			cout << node->data << " ";

			if (node->left)
				q.push(node->left);
			if (node->right)
				q.push(node->right);
		}
	}

	Node* search(Node* current, int key) const
	{
		if (current == nullptr || current->data == key)
			return current;

		if (key < current->data)
			return search(current->left, key);

		return search(current->right, key);
	}

	int countNodes(Node* current) const
	{
		if (current == nullptr)
			return 0;

		return 1 + countNodes(current->left) + countNodes(current->right);
	}

	int leafCount(Node* current) const
	{
		if (current == nullptr)
			return 0;

		if (current->left == nullptr && current->right == nullptr)
			return 1;

		return leafCount(current->left) + leafCount(current->right);
	}

	bool isFullTree(const Node* root) const {
		if (root == nullptr)
			return true;

		if (root->left == nullptr && root->right == nullptr)
			return true;

		if (root->left && root->right)
			return isFullTree(root->left) && isFullTree(root->right);

		return false;
	}

	bool isCompleteTree(const Node* root) const {
		if (root == nullptr)
			return true;

		queue<const Node*> q;
		q.push(root);

		bool isFull = false;

		while (!q.empty()) {
			const Node* current = q.front();
			q.pop();

			if (current == nullptr) {
				isFull = true;
			}
			else {
				if (isFull)
					return false;

				q.push(current->left);
				q.push(current->right);
			}
		}

		return true;
	}

	bool isBalancedTree(const Node* root) const {
		if (root == nullptr)
			return true;

		int leftHeight = height(root->left);
		int rightHeight = height(root->right);

		return (abs(leftHeight - rightHeight) <= 1) && isBalancedTree(root->left) && isBalancedTree(root->right);
	}

	void destroyTree(Node* current)
	{
		if (current)
		{
			destroyTree(current->left);
			destroyTree(current->right);
			delete current;
		}
	}

	Node* findMin(Node* node)
	{
		while (node->left != nullptr)
			node = node->left;
		return node;
	}

	Node* remove(Node* current, int value)
	{
		if (current == nullptr)
			return current;

		if (value < current->data)
			current->left = remove(current->left, value);
		else if (value > current->data)
			current->right = remove(current->right, value);
		else
		{

			if (current->left == nullptr)
			{
				Node* temp = current->right;
				delete current;
				return temp;
			}
			else if (current->right == nullptr)
			{
				Node* temp = current->left;
				delete current;
				return temp;
			}

			Node* temp = findMin(current->right);

			current->data = temp->data;

			current->right = remove(current->right, temp->data);
		}
		return current;
	}

public:

	BST() : root(nullptr) {}

	BST(const BST& other)
	{
		this->root = copyTree(other.root);

	}

	bool insert(int value)
	{
		if (search(root, value) != nullptr)
			return false;

		root = insert(root, value);
		return true;
	}

	void inorderPrint() const
	{
		inorderPrint(root);
		cout << endl;
	}
	void preorderPrint() const
	{
		preorderprint(root);
		cout << endl;
	}
	void postorderPrint() const
	{
		postorderprint(root);
		cout << endl;
	}

	void printLevels() const {
		int h = this->height();
		for (int i = 0; i < h; i++) {
			singleLevelPrint(this->root, i);
		}

	}
	void levelorderPrint() const
	{
		HelperlevelorderPrint(root);
		cout << endl;
	}

	bool remove(int value)
	{
		if (search(root, value) == nullptr)
			return false;

		root = remove(root, value);
		return true;
	}

	Node* search(int key) const
	{
		return search(root, key);
	}

	int countNodes() const
	{
		return countNodes(root);
	}

	int leafCount() const
	{
		return leafCount(root);
	}

	int height() const {

		return height(root);
	}

	int depth()const {
		return depth(root);
	}

	int Type()const {
		return isFullTree(root) ? 1 : isCompleteTree(root) ? 2 : 3;
	}

	~BST()
	{
		destroyTree(root);
	}
};

void searchValue(const BST& tree) {
	cout << "\nEnter a number to search for: ";
	int searchKey;
	cin >> searchKey;
	Node* searchResult = tree.search(searchKey);
	if (searchResult)
		cout << "Node with value " << searchKey << " found!" << endl;
	else
		cout << "Node with value " << searchKey << " not found." << endl;
}

void printInOrder(const BST& tree) {
	cout << "In-Order Traversal: \t";
	tree.inorderPrint();
	
}
void printPreOrder(const BST& tree) {
	cout << "Pre-Order Traversal: \t";
	tree.preorderPrint();

}
void printPostOrder(const BST& tree) {
	cout << "Post-Order Traversal: \t";
	tree.postorderPrint();

}

void printLevelorder(const BST& tree) {
	cout << "Level-Order Traversal: \t";
	tree.levelorderPrint();

}

void NoQueueLevelPrint(const BST& tree) {
	cout << "Level-Order traversal:\t";
	tree.printLevels();
	cout << "\t (without queues)";

}
void printHeight(const BST& tree) {
	cout << "Total Height of the tree: " << tree.height();
	cout << endl;
}
void printDepth(const BST& tree) {
	cout << "Total Depth of the tree: " << tree.depth()<<endl;
}

void countNodes(const BST& tree) {
	int nodeCount = tree.countNodes();
	cout << "\nTotal Nodes in BST: " << nodeCount << endl;
}

void countLeafNodes(const BST& tree) {
	int leafCount = tree.leafCount();
	cout << "Leaf Nodes in BST: " << leafCount << endl;
}

void printType(const BST& tree) {
	int type = tree.Type();
	cout << "This is a ";
	cout << (type == 1 ? "Full BST\n" : type == 2 ? "Complete BST\n" : "Balanced BST\n");
}

void removeValue(BST& tree) {
	cout << "Enter a number to remove: ";
	int removeNum;
	cin >> removeNum;
	if (tree.remove(removeNum))
		cout << "Node with value " << removeNum << " removed." << endl;
	else
		cout << "Node with value " << removeNum << " not found and couldn't be removed." << endl;
}

int main() {
	BST myTree;

	int choice;
	
	myTree.insert(50);
	myTree.insert(30);
	myTree.insert(70);
	myTree.insert(20);


	while (true) {		
		cout << "\n\t\t\tBINARY SEARCH TREE\n\n\tEnter your choice: \n\t1) Insert Value\n\t2) Search Value\n\t3) Remove Value\n\t4) See details \n\t";
		cin >> choice;
		system("cls");
		int v;
		if (choice == 1) {
			
			cout << "\n\tValue to insert: ";
			cin >> v;
			myTree.insert(v);


		}
		else if (choice == 2) {
			
		
			searchValue(myTree);
		}
		else if(choice == 3) {
			
			removeValue(myTree);
		}
		else if (choice == 4) {
			cout << "\n\n\t\t-+-+-+-+-+-+- DETAILS OF BST -+-+-+-+-+-+-\n\n";
			printInOrder(myTree);
			printPreOrder(myTree);
			printPostOrder(myTree);
			printLevelorder(myTree);
			NoQueueLevelPrint(myTree);

			countNodes(myTree);
			countLeafNodes(myTree);
			printHeight(myTree);
			printDepth(myTree);
			printType(myTree);
		}
		else break;
		
		
	}
	



	

	

	return 0;
}
