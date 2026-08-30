#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

int main() {
    std::ifstream fin("input.txt");
    if (!fin) {
        std::cerr << "Couldn't open file" << std::endl;
        return 1;
    }

    std::string line;
    int tot = 0;

    while (getline(fin, line)) {
        int a, b, c;
        char x1, x2;

        std::stringstream ss(line);
        if (!(ss >> a >> x1 >> b >> x2 >> c)) {
            std::cerr << "Bad line: " << line << '\n';
            continue;
        }

        int l = 0, m = 0;
        int x = std::max(a, b);
        int y = std::min(a, b);

        l = std::max(x, c);
        m = std::max(y, std::min(x, c));

        tot += std::min({2 * (a + b), 2 * (b + c), 2 * (c + a)}) + (a*b*c);
    }

    std::cout << tot << std::endl;
}

