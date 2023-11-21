#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

const string PEOPLE = "people.txt";
int rows, cols;

struct Person {
    char gender;
    char direction;

    Person(char gender = ' ', char direction = ' ') : gender(gender), direction(direction) {}
    bool operator==(const Person& other) const {
        return (gender == other.gender) && (direction == other.direction);
    }

    bool operator!=(const Person& other) const {
        return !(*this == other);
    }
};

auto read_file(const string& file) {
    ifstream infile(file);
    queue<Person> persons;
    if (infile.is_open()) {
        char character;
        while (infile.get(character)) {
            if (character == 'M' || character == 'F') {
                persons.push(Person(character, 'E')); // Set the initial direction to 'E'.
            }
        }
        infile.close();
    }
    else {
        cout << "File cannot be opened." << endl;
    }
    return persons;
}

void find_factors(int const size, int& rows, int& cols) {
    rows = 1;
    cols = size;

    for (int i = 2; i <= sqrt(size); i++) {
        if (size % i == 0) {
            rows = i;
            cols = size / i;
        }
    }
}

void print(vector<vector<Person>>& board, const int& rows, const int& cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << "|" << board[i][j].gender << " (" << board[i][j].direction << ") |\t";
        }
        cout << endl;
    }
}

bool isSafe(vector<vector<Person>>& board, const int& x, const int& y) {
    int n = rows * cols;

    if (n == 1) {
        return true;
    }

    if (n == 2) {
        return (board[x][y].direction != board[0][0].direction);
            
    }

    if (x == 0) {
        if (y == 0) {
            return (board[x][y] != board[x][y + 1]) && (board[x][y] != board[x + 1][y]);
        }
        else if (y == cols - 1) {
            return (board[x][y] != board[x][y - 1]) && (board[x][y] != board[x + 1][y]);
        }
        else {
            return (board[x][y] != board[x][y - 1]) && (board[x][y] != board[x][y + 1]) &&
                (board[x][y] != board[x + 1][y]);
        }
    }
    else if (x == rows - 1) {
        if (y == 0) {
            return (board[x][y] != board[x][y + 1]) && (board[x][y] != board[x - 1][y]);
        }
        else if (y == cols - 1) {

            return (board[x][y] != board[x][y - 1]) && (board[x][y] != board[x - 1][y]);
        }
        else {
            return (board[x][y] != board[x][y - 1]) && (board[x][y] != board[x][y + 1]) &&
                (board[x][y] != board[x - 1][y]);
        }
    }
    else if (y == 0) {
        return (board[x][y] != board[x][y + 1]) && (board[x][y] != board[x + 1][y]) &&
            (board[x][y] != board[x - 1][y]);
    }
    else if (y == cols - 1) {
        return (board[x][y] != board[x][y - 1]) && (board[x][y] != board[x + 1][y]) &&
            (board[x][y] != board[x - 1][y]);
    }
    else {
        return (board[x][y] != board[x][y - 1]) && (board[x][y] != board[x][y + 1]) &&
            (board[x][y] != board[x + 1][y]) && (board[x][y] != board[x - 1][y]);
    }
}


bool arrange(vector<vector<Person>>& board,  int x,  int y, queue<Person>& people) {
    if (y == cols) {
        y = 0;
        x++;
    }
    if (x == rows) {
        return true;  // All persons placed
    }

    Person front = people.front();
    people.pop();

    for (char dir : {'E', 'W', 'N', 'S'}) {
        front.direction = dir;
        board[x][y] = front;

        if (isSafe(board, x, y) && ( arrange(board, x, y + 1, people) || arrange(board, x + 1, y, people))) {
            return true;
        }
    }

    people.push(front);  // Backtrack
    return false;
}

int main() {
    cout << "\n\t\t E = East/Right\tW = West/Left\tN = North/Up\tS = South/Down\n\n";

    queue<Person> people;
    people = read_file(PEOPLE);

    find_factors(people.size(), rows, cols);
    cout << "\tTotal people = " << people.size() << endl;
    cout << "\tRows = " << rows << endl;
    cout << "\tColumns = " << cols << endl;
    vector<vector<Person>> board(rows, vector<Person>(cols));
    int zero = 0;
    if (arrange(board, zero, zero, people)) {
        print(board, rows, cols);
    }

    return 0;
}
