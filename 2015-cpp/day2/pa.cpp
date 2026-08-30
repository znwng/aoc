#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main() {
    std::ifstream fin("input.txt");
    if (!fin) {
        std::cerr << "Failed to open input.txt\n";
        return 1;
    }

    std::string line;
    int res = 0;

    while (std::getline(fin, line)) {
        int a, b, c;
        char x1, x2;

        std::stringstream ss(line);
        if (!(ss >> a >> x1 >> b >> x2 >> c)) {
            std::cerr << "Bad line: " << line << '\n';
            continue;
        }

        res += (2 * a * b) + (2 * b * c) + (2 * c * a) + std::min({a * b, b * c, c * a});
    }

    std::cout << res << '\n';
}

