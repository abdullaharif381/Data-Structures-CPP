#include <iostream>

using namespace std;

template <class T>
class AVL;

template <class T>
class Node {
    friend class AVL<T>;

    T key; // Key to be stored in a node
    int height; // To store the height of each node
    Node* left;
    Node* right;

    Node(T key) : key(key), height(1), left(nullptr), right(nullptr) {}
};

template <class T>
class AVL {
public:
    AVL() : root(nullptr) {} // Driver functions for insert, delete, display
    void insert(T val);
    void remove(T val);
    bool search(T val);
    bool isAVL();
    T findmin();
    void print();
    void printAllPaths();

private:
    Node<T>* root;
    int avlHeight(Node<T>*);
    int max(int, int);
    int getBalance(Node<T>*);
    Node<T>* find_min(Node<T>*);
    Node<T>* SingleRightRotation(Node<T>*);
    Node<T>* SingleLeftRotation(Node<T>*);
    Node<T>* LeftRightRotation(Node<T>*);
    Node<T>* RightLeftRotation(Node<T>*);
    Node<T>* insert(T key, Node<T>* n1);
    Node<T>* remove(T key, Node<T>* n1);
    bool search(T key, Node<T>* n1);
    void display_inorder(Node<T>* n1);
    bool is_AVL(Node<T>* n1);
    void inorderPrint(Node<T>* current);
    void postorderPrint(Node<T>* current);
    void preorderPrint(Node<T>* current);
    void helpAllPaths(Node<T>* curr, int path[], int pathLength);
};

template <class T>
void AVL<T>::insert(T val) {
   this->root = insert(val, root);
}

template <class T>
void AVL<T>::remove(T val) {
    root = remove(val, root);
}

template <class T>
bool AVL<T>::search(T val) {
    return search(val, root);
}

template <class T>
bool AVL<T>::isAVL() {
    return is_AVL(root);
}

template <class T>
T AVL<T>::findmin() {
    Node<T>* minNode = find_min(root);
    if (minNode)
        return minNode->key;
    return T(); // Return a default value if the tree is empty.
}

template <class T>
void AVL<T>::print() {
    cout << "Inorder print: ";
    inorderPrint(root);
    cout << endl;
    cout << "Preorder print: ";
    preorderPrint(root);
    cout << endl;
    cout << "Postorder print: ";
    postorderPrint(root);
    cout << endl;
}

template <class T>
void AVL<T>::printAllPaths() {
    int path[100];
    helpAllPaths(root, path, 0);
}

template <class T>
int AVL<T>::avlHeight(Node<T>* n1) {
    return !n1 ? 0 : n1->height;
}

template <class T>
int AVL<T>::max(int a, int b) {
    return a > b ? a : b;
}

template <class T>
int AVL<T>::getBalance(Node<T>* n1) {
    return avlHeight(n1->left) - avlHeight(n1->right);
}

template <class T>
Node<T>* AVL<T>::find_min(Node<T>* n1) {
    if (!n1) {
        return n1;
    }
    while (n1->left) {
        n1 = n1->left;
    }
    return n1;
}

template <class T>
Node<T>* AVL<T>::SingleRightRotation(Node<T>* n1) {
    Node<T>* n2 = n1->left;
    Node<T>* save = n2->right;
    n2->right = n1;
    n1->left = save;
    n1->height = max(avlHeight(n1->left), avlHeight(n1->right)) + 1;
    n2->height = max(avlHeight(n2->left), avlHeight(n2->right)) + 1;
    return n2;
}

template <class T>
Node<T>* AVL<T>::SingleLeftRotation(Node<T>* n1) {
    Node<T>* n2 = n1->right;
    Node<T>* save = n2->left;
    n2->left = n1;
    n1->right = save;
    n1->height = max(avlHeight(n1->left), avlHeight(n1->right)) + 1;
    n2->height = max(avlHeight(n2->left), avlHeight(n2->right)) + 1;
    return n2;
}

template <class T>
Node<T>* AVL<T>::LeftRightRotation(Node<T>* n1) {
    n1->left = SingleLeftRotation(n1->left);
    return SingleRightRotation(n1);
}

template <class T>
Node<T>* AVL<T>::RightLeftRotation(Node<T>* n1) {
    n1->right = SingleRightRotation(n1->right);
    return SingleLeftRotation(n1);
}

template <class T>
Node<T>* AVL<T>::insert(T key, Node<T>* n1) {
    if (!n1) {
        Node<T>* newNode = new Node<T>(key);
        return newNode;
    }
    if (key < n1->key) {
        n1->left = insert(key, n1->left);
    }
    else if (key > n1->key) {
        n1->right = insert(key, n1->right);
    }

    n1->height = max(avlHeight(n1->left), avlHeight(n1->right)) + 1;
    int balance = getBalance(n1);
    // LL case
    if (balance > 1 && key < n1->left->key) {
        return SingleRightRotation(n1);
    }
    // RR case
    if (balance < -1 && key > n1->right->key) {
        return SingleLeftRotation(n1);
    }
    // LR case
    if (balance > 1 && key > n1->left->key) {
        n1->left = SingleLeftRotation(n1->left);
        return SingleRightRotation(n1);
    }
    // RL case
    if (balance < -1 && key < n1->right->key) {
        n1->right = SingleRightRotation(n1->right);
        return SingleLeftRotation(n1);
    }
    return n1;
}

template <class T>
Node<T>* AVL<T>::remove(T key, Node<T>* n1) {
    if (!n1) {
        return n1;
    }
    if (key < n1->key) {
        n1->left = remove(key, n1->left);
    }
    else if (key > n1->key) {
        n1->right = remove(key, n1->right);
    }
    else {
        if (!n1->left && n1->right) {
            Node<T>* temp = n1;
            n1 = n1->right;
            delete temp;
        }
        else if (n1->left && !n1->right) {
            Node<T>* temp = n1;
            n1 = n1->left;
            delete temp;
        }
        else if (n1->right && n1->left) {
            Node<T>* temp = find_min(n1->right);
            swap(temp->key, n1->key);
            n1->right = remove(temp->key, n1->right);
        }
        else {
            delete n1;
            n1 = nullptr;
        }
    }

    if (!n1) {
        return nullptr;
    }
    n1->height = max(avlHeight(n1->left), avlHeight(n1->right)) + 1;
    int balance = getBalance(n1);
    // LL
    if (balance > 1 && getBalance(n1->left) >= 0) {
        return SingleRightRotation(n1);
    }
    // LR
    if (balance > 1 && getBalance(n1->left) < 0) {
        n1->left = SingleLeftRotation(n1->left);
        return SingleRightRotation(n1);
    }
    // RR
    if (balance < -1 && getBalance(n1->right) <= 0) {
        return SingleLeftRotation(n1);
    }
    // RL
    if (balance < -1 && getBalance(n1->right) > 0) {
        n1->right = SingleRightRotation(n1->right);
        return SingleLeftRotation(n1);
    }
    return n1;
}

template <class T>
bool AVL<T>::search(T key, Node<T>* n1) {
    if (!n1) {
        return false;
    }
    if (key == n1->key) {
        return true;
    }
    else if (key < n1->key) {
        return search(key, n1->left);
    }
    else {
        return search(key, n1->right);
    }
}

template <class T>
void AVL<T>::display_inorder(Node<T>* n1) {
    if (n1) {
        display_inorder(n1->left);
        cout << n1->key << " ";
        display_inorder(n1->right);
    }
}

template <class T>
bool AVL<T>::is_AVL(Node<T>* n1) {
    if (!n1) {
        return true;
    }

    int leftHeight = avlHeight(n1->left);
    int rightHeight = avlHeight(n1->right);

    return (abs(leftHeight - rightHeight) <= 1) && is_AVL(n1->left) && is_AVL(n1->right);
}

template <class T>
void AVL<T>::inorderPrint(Node<T>* current) {
    if (current) {
        inorderPrint(current->left);
        cout << current->key << " ";
        inorderPrint(current->right);
    }
}

template <class T>
void AVL<T>::preorderPrint(Node<T>* current) {
    if (current) {
        cout << current->key << " ";
        preorderPrint(current->left);
        preorderPrint(current->right);
    }
}

template <class T>
void AVL<T>::postorderPrint(Node<T>* current) {
    if (current) {
        postorderPrint(current->left);
        postorderPrint(current->right);
        cout << current->key << " ";
    }
}

template <typename T>
void AVL<T>::helpAllPaths(Node<T>* curr, int path[], int pathLength) {
    if (curr == nullptr) {
        return;
    }

    // Add the current node's key to the path
    path[pathLength] = curr->key;
    pathLength++;

    // If it's a leaf node, print the path
    if (!curr->left && !curr->right) {
        cout << "Path: ";
        for (int i = 0; i < pathLength; i++) {
            cout << path[i];
            if (i < pathLength - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
    }
    else {
        // If not a leaf node, continue the traversal
        helpAllPaths(curr->left, path, pathLength);
        helpAllPaths(curr->right, path, pathLength);
    }
}

int main() {
    AVL<int> myTree;

    int choice;

    myTree.insert(50);
    myTree.insert(30);
    myTree.insert(70);
    myTree.insert(20);
    myTree.insert(10);

    while (true) {
        cout << "\n\t\t\tBALANCED BINARY SEARCH TREE\n\n\tEnter your choice: \n\t1) Insert Value\n\t2) Search Value\n\t3) Remove Value\n\t4) See details \n\t";
        cin >> choice;
        system("cls");
        int v;
        if (choice == 1) {
            cout << "\n\tValue to insert: ";
            cin >> v;
            myTree.insert(v);
        }
        else if (choice == 2) {
            cout << "Enter a value to search: ";
            auto a = 0;
            cin >> a;
            if (myTree.search(a))
                cout << "Value is present\n";
            else "Value not present\n";
            
        }
        else if (choice == 3) {
            cout << "Enter a value to remove: ";
            auto a = 0;
            cin >> a;
            myTree.remove(a);
        }
        else if (choice == 4) {
            cout << "\n\n\t\t-+-+-+-+-+-+- DETAILS OF AVL -+-+-+-+-+-+-\n\n";
            myTree.print();
            myTree.printAllPaths();
            cout << "Minimum: " << myTree.findmin() << endl;
            cout << (myTree.isAVL() ? "It is AVL Tree\n" : "It is Not AVL Tree\n");
        }
        else break;
    }
    return 0;
}
