#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

enum class command_type { turn_on, turn_off, toggle };

struct command {
    command_type type;
    int x1, y1, x2, y2;
};

command parse_line(const std::string& line) {
    std::istringstream iss(line);
    std::string word;

    command cmd;

    iss >> word;

    if (word == "toggle") {
        cmd.type = command_type::toggle;
    } else if (word == "turn") {
        iss >> word;
        if (word == "on") {
            cmd.type = command_type::turn_on;
        } else {
            cmd.type = command_type::turn_off;
        }
    }

    char comma;
    std::string through;
    iss >> cmd.x1 >> comma >> cmd.y1;
    iss >> through;
    iss >> cmd.x2 >> comma >> cmd.y2;

    return cmd;
}

std::string to_string(command_type type) {
    switch (type) {
        case command_type::turn_on:
            return "turn_on";
        case command_type::turn_off:
            return "turn_off";
        case command_type::toggle:
            return "toggle";
    }
    return "unknown";
}

int main() {
    std::ifstream fin("input.txt");
    if (!fin) {
        std::cerr << "Error opening file";
        return 1;
    }

    std::vector<std::vector<int>> grid(1000, std::vector<int>(1000, 0));

    std::string line;
    while (getline(fin, line)) {
        std::cout << line << std::endl;
        command cmd = parse_line(line);

        // 0 -> turn on
        // 1 -> turn off
        // 2 -> toggle
        if (cmd.type == command_type::turn_on) {
            for (int i = cmd.x1; i <= cmd.x2; i++) {
                for (int j = cmd.y1; j <= cmd.y2; j++) {
                    grid[i][j] = 1;
                }
            }
        } else if (cmd.type == command_type::turn_off) {
            for (int i = cmd.x1; i <= cmd.x2; i++) {
                for (int j = cmd.y1; j <= cmd.y2; j++) {
                    grid[i][j] = 0;
                }
            }
        } else if (cmd.type == command_type::toggle) {
            for (int i = cmd.x1; i <= cmd.x2; i++) {
                for (int j = cmd.y1; j <= cmd.y2; j++) {
                    grid[i][j] = !grid[i][j];
                }
            }
        }
    }

    int count = 0;
    for (auto x : grid) {
        for (auto y : x) {
            if (y == 1) {
                count++;
            }
        }
    }

    std::cout << count << std::endl;
}

