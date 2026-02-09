#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ifstream fin("input.txt");
    string line;
    getline(fin, line);
    vector<char> dir(line.begin(), line.end());

    // dir = {'(', ')', ')', '(', ')', ')', '(', ')', ')'};

    int count = 0;
    for (int i = 0; i < dir.size(); i++) {
        if (dir[i] == '(') count++;
        if (dir[i] == ')') count--;

        if (count == -1) {
            cout << i + 1 << endl;
            cout << "Count: " << count << endl;
        }
    }

    cout << count << endl;

    return 0;
}

