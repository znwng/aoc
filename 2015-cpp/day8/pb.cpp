#include <fstream>
#include <iostream>
#include <string>

int main() {
    std::ifstream fin("input.txt");
    if (!fin) {
        std::cerr << "Error opening file\n";
        return 1;
    }

    std::string line;
    long long original_count = 0;
    long long encoded_count = 0;

    while (std::getline(fin, line)) {

        original_count += line.size();

        encoded_count += 2;

        for (char c : line) {
            if (c == '"' || c == '\\') {
                encoded_count += 2;
            } else {
                encoded_count += 1;
            }
        }
    }

    std::cout << encoded_count - original_count << std::endl;
    return 0;
}

