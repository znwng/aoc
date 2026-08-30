#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <pthread.h>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct route {
    string source;
    string destination;
    int distance;

    route(string source, string destination, int distance) {
        this->source = source;
        this->destination = destination;
        this->distance = distance;
    }

    void print_info() {
        cout << "Source: " << this->source << '\n';
        cout << "Destination: " << this->destination << '\n';
        cout << "Distance: " << this->distance << '\n';

        cout << endl;
    }
};

int main() {
    ifstream file("input.txt");
    string line;

    vector<route> routes;
    vector<string> city_names;

    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> words;
        string word;

        while (ss >> word) {
            words.push_back(word);
        }

        routes.push_back(route(words[0], words[2], stoi(words[4])));
    }

    for (auto& r : routes) {
        string source = r.source;

        if (find(city_names.begin(), city_names.end(), source) != city_names.end()) {
            continue;
        } else {
            city_names.push_back(source);
        }
    }

    vector<vector<string>> permutations_of_available_cities;
    sort(city_names.begin(), city_names.end());
    do {
        permutations_of_available_cities.push_back(city_names);
    } while (next_permutation(city_names.begin(), city_names.end()));

    return 0;
}

