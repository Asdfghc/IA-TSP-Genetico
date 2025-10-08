#pragma once

#include <vector>
#include <algorithm>
#include <random>
#include <numeric>
#include "individual.h"
#include <iostream>

using namespace std;

Individual roulette(const vector<Individual>& individuals, const vector<double>& fitnessValues) {
    vector<double> fitnessCumsum;
    partial_sum(fitnessValues.begin(), fitnessValues.end(), back_inserter(fitnessCumsum));
    random_device rd;
    mt19937 gen(rd());
    double r = uniform_real_distribution<>(0, fitnessCumsum.back())(gen);
    auto it = lower_bound(fitnessCumsum.begin(), fitnessCumsum.end(), r);
    return individuals.at(distance(fitnessCumsum.begin(), it));
}

vector<Individual> crossover(Individual parent1, Individual parent2) {
    vector<Individual> offspring;
    random_device rd;
    mt19937 gen(rd());
    const vector<Point>& p1 = parent1.getPath();
    const vector<Point>& p2 = parent2.getPath();

    /*
    cout << "Parent 1: ";
    for (const auto& city : p1) {
        printf("%s ", city.name.c_str());
    }
    printf("\n");
    
    cout << "Parent 2: ";
    for (const auto& city : p2) {
        printf("%s ", city.name.c_str());
    }
    printf("\n");
    */

    int n_cities_cut = (int)p1.size() - 1;
    int cut = round(uniform_real_distribution<>(1, n_cities_cut)(gen));

    vector<Point> offspring1, offspring2;
    offspring1.insert(offspring1.end(), p1.begin(), p1.begin() + cut);
    for (const auto& city : p2) {
        auto it = find_if(offspring1.begin(), offspring1.end(), [&](const Point& pt) { return pt.name == city.name; });
        if (it == offspring1.end()) {
            offspring1.push_back(city);
        }
    }

    offspring2.insert(offspring2.end(), p2.begin(), p2.begin() + cut);
    for (const auto& city : p1) {
        auto it = find_if(offspring2.begin(), offspring2.end(), [&](const Point& pt) { return pt.name == city.name; });
        if (it == offspring2.end()) {
            offspring2.push_back(city);
        }
    }

    offspring.push_back(Individual(offspring1));
    offspring.push_back(Individual(offspring2));
    
    return offspring;
}

void mutate(Individual& individual, double mutationRate) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0, 1);
    if (dis(gen) < mutationRate) {
        vector<Point> path = individual.getPath();
        int n_cities = (int)path.size();
        int idx1 = uniform_int_distribution<>(0, n_cities - 1)(gen);
        int idx2 = uniform_int_distribution<>(0, n_cities - 1)(gen);
        swap(path[idx1], path[idx2]);
        individual = Individual(path);
    }
}