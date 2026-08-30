#include <algorithm>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

int main() {
    std::ifstream fin("input.txt");
    if (!fin) {
        std::cerr << "Error opening file\n";
        return 1;
    }

    std::string line;
    std::vector<char> moves;
    while (std::getline(fin, line)) {
        for (char c : line) {
            moves.push_back(c);
        }
    }

    std::vector<std::pair<int, int>> visited;

    std::pair<int, int> santa {0, 0};
    std::pair<int, int> robo {0, 0};

    visited.push_back({0, 0}); // starting house

    for (size_t i = 0; i < moves.size(); i++) {
        std::pair<int, int>& curr = (i % 2 == 0) ? santa : robo;

        switch (moves[i]) {
            case '^':
                curr.first--;
                break;
            case 'v':
                curr.first++;
                break;
            case '>':
                curr.second++;
                break;
            case '<':
                curr.second--;
                break;
            default:
                std::cerr << "Invalid direction\n";
                return 1;
        }

        if (std::find(visited.begin(), visited.end(), curr) == visited.end()) {
            visited.push_back(curr);
        }
    }

    std::cout << visited.size() << "\n";
}

