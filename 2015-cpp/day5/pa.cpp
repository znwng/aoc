#include <fstream>
#include <iostream>
#include <string>

bool is_vowel(char c) {
    c = std::tolower(static_cast<char>(c));
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

bool is_good(std::string str) {
    int vowels = 0;
    for (char x : str) {
        if (is_vowel(x)) vowels++;
    }

    if (vowels < 3) {
        return false;
    }

    bool has_repeating = false;
    for (int i = 1; i < str.length(); i++) {
        if (str[i] == str[i - 1]) {
            has_repeating = true;
            break;
        }
    }

    if (!has_repeating) {
        return false;
    }

    if (str.find("ab") != std::string::npos || str.find("cd") != std::string::npos ||
        str.find("pq") != std::string::npos || str.find("xy") != std::string::npos) {
        return false;
    }

    return true;
}

int main() {
    std::ifstream fin("input.txt");
    if (!fin) {
        std::cerr << "Error opening file";
        return 1;
    }

    std::string line;
    int good_lines;
    while (getline(fin, line)) {
        if (is_good(line)) {
            good_lines++;
        }
    }

    std::cout << good_lines << std::endl;

    return 0;
}

