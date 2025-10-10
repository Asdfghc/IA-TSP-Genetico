#pragma once

#include <vector>
#include <string>
#include <cmath>
#include "point.h"

using namespace std;

class Individual {
private:
    vector<Point> path;

    double distance(const Point& a, const Point& b) const;

public:
    Individual(const vector<Point>& path);
    const vector<Point>& getPath() const;
    double getTotalDistance() const;
    
    void mutate(double mutationRate);

    static pair<Individual, Individual> crossover(const Individual& parent1, const Individual& parent2);

};