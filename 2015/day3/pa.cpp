#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

int main() {
    std::ifstream fin("input.txt");
    if (!fin) {
        std::cerr << "Error opening file";
        return 1;
    }

    std::string line;
    std::vector<char> vec;
    while (std::getline(fin, line)) {
        for (char dir : line) {
            vec.push_back(dir);
        }
    }

    std::vector<std::pair<int, int>> visited;
    std::pair<int, int> curr = {0, 0};
    int revisited = 0;

    visited.push_back(curr);

    for (char direction : vec) {
        switch (direction) {
            case '^':
                curr.first--;
                break;
            case '>':
                curr.second++;
                break;
            case '<':
                curr.second--;
                break;
            case 'v':
                curr.first++;
                break;
            default:
                std::cerr << "Invalid direction";
                return 1;
        }

        if (std::find(visited.begin(), visited.end(), curr) == visited.end()) {
            visited.push_back(curr);
        }
    }

    std::cout << visited.size() << "\n";
}

