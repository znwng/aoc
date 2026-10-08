#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Route {
    std::string from;
    std::string to;
    int distance;
};

struct Route_distance {
    std::vector<std::string> permutation;
    int distance = 0;
};

std::vector<Route> g_routes;

Route parseRoute(const std::string& line) {
    std::istringstream iss(line);

    Route route;
    std::string word;

    iss >> route.from;      // Faerun
    iss >> word;            // to
    iss >> route.to;        // Norrath
    iss >> word;            // =
    iss >> route.distance;  // 129

    g_routes.push_back(route);

    return route;
}

std::vector<std::vector<std::string>> route_permutations(std::vector<std::string> routes) {
    std::vector<std::vector<std::string>> result;

    std::sort(routes.begin(), routes.end());

    do {
        result.push_back(routes);
    } while (std::next_permutation(routes.begin(), routes.end()));

    return result;
}

int get_distance(const std::string& from, const std::string& to) {
    for (const auto& route : g_routes) {
        if ((route.from == from && route.to == to) || (route.from == to && route.to == from)) {
            return route.distance;
        }
    }

    return -1;
}

int main() {
    std::ifstream fin("./input.txt");
    if (!fin) {
        std::cerr << "Error opening file\n";
        return 1;
    }

    std::string line;
    std::vector<std::string> city_names;

    while (std::getline(fin, line)) {
        Route route = parseRoute(line);

        if (std::find(city_names.begin(), city_names.end(), route.from) == city_names.end()) {
            city_names.push_back(route.from);
        }

        if (std::find(city_names.begin(), city_names.end(), route.to) == city_names.end()) {
            city_names.push_back(route.to);
        }
    }

    auto permutations = route_permutations(city_names);

    std::vector<Route_distance> routes;

    for (const auto& permutation : permutations) {
        Route_distance route_distance;
        route_distance.permutation = permutation;

        for (size_t i = 0; i + 1 < permutation.size(); ++i) {
            int distance = get_distance(permutation[i], permutation[i + 1]);

            route_distance.distance += distance;
        }

        routes.push_back(route_distance);
    }

    auto longest = std::max_element(
        routes.begin(), routes.end(),
        [](const Route_distance& a, const Route_distance& b) { return a.distance < b.distance; });

    std::cout << "Longest route: ";

    for (const auto& city : longest->permutation) {
        std::cout << city << ' ';
    }

    std::cout << "\nDistance: " << longest->distance << '\n';
}
