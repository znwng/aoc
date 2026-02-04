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

    int count = 0;
    for (auto x : dir) {
        if (x == '(') count++;
        if (x == ')') count--;
    }

    cout << count << endl;

    return 0;
}

