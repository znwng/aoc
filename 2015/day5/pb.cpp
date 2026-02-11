#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

bool is_nice(const std::string& s) {
    if (s.length() < 3) return false;

    bool has_pair = false;
    bool has_repeat_with_gap = false;

    std::unordered_map<std::string, int> pair_index;

    for (int i = 0; i < s.length(); i++) {

        if (i + 1 < s.length()) {
            std::string pair = s.substr(i, 2);

            if (pair_index.count(pair)) {
                if (i - pair_index[pair] > 1) {
                    has_pair = true;
                }
            } else {
                pair_index[pair] = i;
            }
        }

        if (i + 2 < s.length()) {
            if (s[i] == s[i + 2]) {
                has_repeat_with_gap = true;
            }
        }

        if (has_pair && has_repeat_with_gap) return true;
    }

    return false;
}

int main() {
    std::fstream fin("input.txt");
    if (!fin) {
        std::cerr << "Error opening file";
        return 1;
    }

    std::string line;
    int count = 0;
    while (getline(fin, line)) {
        if (is_nice(line)) count++;
    }

    std::cout << count << std::endl;

    return 0;
}

