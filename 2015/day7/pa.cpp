#include <cctype>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

unordered_map<string, string> instructions;
unordered_map<string, uint16_t> cache;

bool isNumber(const string& s) {
    return !s.empty() && isdigit(s[0]);
}

uint16_t evaluate(const string& w) {
    if (cache.count(w)) return cache[w];
    string instr = instructions[w];
    istringstream iss(instr);
    vector<string> parts;
    string t;
    while (iss >> t) parts.push_back(t);
    uint16_t r = 0;
    if (parts.size() == 1)
        r = isNumber(parts[0]) ? stoi(parts[0]) : evaluate(parts[0]);
    else if (parts.size() == 2)
        r = ~evaluate(parts[1]);
    else if (parts.size() == 3) {
        uint16_t l = isNumber(parts[0]) ? stoi(parts[0]) : evaluate(parts[0]);
        uint16_t rr = isNumber(parts[2]) ? stoi(parts[2]) : evaluate(parts[2]);
        string op = parts[1];
        if (op == "AND")
            r = l & rr;
        else if (op == "OR")
            r = l | rr;
        else if (op == "LSHIFT")
            r = l << rr;
        else if (op == "RSHIFT")
            r = l >> rr;
    }
    cache[w] = r;
    return r;
}

int main() {
    ifstream fin("input.txt");
    string line;
    while (getline(fin, line)) {
        size_t arrow = line.find("->");
        string instr = line.substr(0, arrow);
        if (!instr.empty() && instr.back() == ' ') instr.pop_back();
        string wire = line.substr(arrow + 2);
        if (!wire.empty() && wire.front() == ' ') wire = wire.substr(1);
        instructions[wire] = instr;
    }
    cout << evaluate("a") << endl;
}

