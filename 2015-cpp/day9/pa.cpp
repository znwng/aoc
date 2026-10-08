#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Route {
    // Stores information about a route between two cities.
    //
    // Input:
    // Faerun -> Norrath = 129
    //
    // Route:
    // {
    //     from = "Faerun",
    //     to = "Norrath",
    //     distance = 129
    // }

    std::string from;
    std::string to;
    int distance;
};

struct Route_distance {
    // Stores a complete route permutation and its total distance.
    //
    // Example:
    // Permutation: {Norrath, Straylight, Arbre, Faerun, AlphaCentauri, Snowdin, Tambi, Tristram}
    // Distance: 207

    std::vector<std::string> permutation;
    int distance = 0;
};

// Stores all routes read from the input file.
std::vector<Route> g_routes;

Route parseRoute(const std::string& line) {
    // Parses a line such as:
    // Faerun to Norrath = 129
    // and converts it into a Route object.

    std::istringstream iss(line);

    Route route;
    std::string word;

    iss >> route.from;      // Extract the source city.
    iss >> word;            // Extract and ignore the word "to".
    iss >> route.to;        // Extract the destination city.
    iss >> word;            // Extract and ignore the "=" symbol.
    iss >> route.distance;  // Extract the distance.

    g_routes.push_back(route);  // Store the route globally so it can be used later.

    return route;
}

std::vector<std::vector<std::string>> route_permutations(std::vector<std::string> routes) {
    // Generates every possible ordering of the given city names.

    std::vector<std::vector<std::string>> result;

    // Sort the cities first because next_permutation
    // expects the sequence to start in sorted order
    // to generate all permutations.
    std::sort(routes.begin(), routes.end());

    do {
        // Store the current permutation.
        result.push_back(routes);

        // Generate the next permutation.
    } while (std::next_permutation(routes.begin(), routes.end()));

    return result;
}

int get_distance(const std::string& from, const std::string& to) {
    // Finds the distance between two cities.

    for (const auto& route : g_routes) {
        // Check both directions because the route is undirected.
        if ((route.from == from && route.to == to) || (route.from == to && route.to == from)) {
            return route.distance;
        }
    }

    // Return -1 if no route exists.
    return -1;
}

int main() {
    std::ifstream fin("./input.txt");

    if (!fin) {
        std::cerr << "Error opening file\n";
        return 1;
    }

    std::string line;

    // Stores the unique city names found in the input.
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

    // Calculate the total distance of every permutation.
    for (const auto& permutation : permutations) {
        Route_distance route_distance;

        route_distance.permutation = permutation;

        for (size_t i = 0; i + 1 < permutation.size(); ++i) {
            // Find the distance between the current city
            // and the next city.
            int distance = get_distance(permutation[i], permutation[i + 1]);
            route_distance.distance += distance;
        }

        routes.push_back(route_distance);
    }

    // Find the route with the smallest total distance.
    auto shortest = std::min_element(
        routes.begin(), routes.end(),
        [](const Route_distance& a, const Route_distance& b) { return a.distance < b.distance; });

    std::cout << "Shortest route: ";

    for (const auto& city : shortest->permutation) {
        std::cout << city << ' ';
    }

    std::cout << "\nDistance: " << shortest->distance << '\n';
}
