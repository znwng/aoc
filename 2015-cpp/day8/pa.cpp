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
    long long code_count = 0;
    long long memory_count = 0;

    while (std::getline(fin, line)) {
        code_count += line.size();

        for (size_t i = 1; i < line.size() - 1;) {

            if (line[i] == '\\') {

                if (line[i + 1] == '\\' || line[i + 1] == '"') {
                    memory_count += 1;
                    i += 2;
                } else if (line[i + 1] == 'x') {
                    memory_count += 1;
                    i += 4;
                }
            } else {
                memory_count += 1;
                i += 1;
            }
        }
    }

    std::cout << code_count - memory_count << std::endl;
    return 0;
}

