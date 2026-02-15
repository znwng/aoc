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
    vector<string> p;
    string t;
    while (iss >> t) p.push_back(t);
    uint16_t r = 0;
    if (p.size() == 1)
        r = isNumber(p[0]) ? stoi(p[0]) : evaluate(p[0]);
    else if (p.size() == 2)
        r = ~evaluate(p[1]);
    else if (p.size() == 3) {
        uint16_t l = isNumber(p[0]) ? stoi(p[0]) : evaluate(p[0]);
        uint16_t rr = isNumber(p[2]) ? stoi(p[2]) : evaluate(p[2]);
        string op = p[1];
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
        size_t a = line.find("->");
        string instr = line.substr(0, a);
        if (!instr.empty() && instr.back() == ' ') instr.pop_back();
        string wire = line.substr(a + 2);
        if (!wire.empty() && wire.front() == ' ') wire = wire.substr(1);
        instructions[wire] = instr;
    }

    uint16_t a1 = evaluate("a");
    cache.clear();
    cache["b"] = a1;
    cout << evaluate("a") << endl;
}

