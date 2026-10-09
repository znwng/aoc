#include <fstream>
#include <iostream>
#include <string>

std::string apply(const std::string& number) {
    std::string result;

    for (std::size_t i = 0; i < number.size();) {
        std::size_t j = i;

        while (j < number.size() && number[j] == number[i]) {
            ++j;
        }

        result += std::to_string(j - i);
        result += number[i];

        i = j;
    }

    return result;
}

int main() {
    std::ifstream fin("./input.txt");

    std::string number;
    std::getline(fin, number);

    for (int i = 0; i < 40; ++i) {
        number = apply(number);
    }

    std::cout << number.size() << '\n';
}
