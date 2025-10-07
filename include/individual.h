#pragma once

#include <vector>
#include <string>
#include <cmath>

using namespace std;

struct Point {
    double x, y;
    string name;
};

class Individual {
private:
    vector<Point> path;

    double distance(const Point& a, const Point& b) {
        return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
    }

public:
    Individual(const vector<Point>& path) : path(path) {}

    vector<Point> getPath() const { return path; }

    double getTotalDistance() {
        double total = 0.0;
        for (size_t i = 0; i < path.size() - 1; ++i) {
            total += distance(path[i], path[i + 1]);
        }
        total += distance(path.back(), path.front()); // Return to start
        return total;
    }

};