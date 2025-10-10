#pragma once

#include <vector>
#include <algorithm>
#include <random>
#include "individual.h"
#include "point.h"

using namespace std;

class Population {
private:
    int populationSize;
    vector<Individual> individuals;
    vector<double> fitnessValues;
    
public:
    Population(int size);

    const vector<Individual>& getIndividuals() const;

    const vector<double>& getFitnessValues() const;

    void insertIndividuals(const pair<Individual, Individual>& individuals);

    void initialize(const vector<Point>& cities);

    void evaluateFitness();

    void select(int populationSize);

    Individual getBestIndividual();
    
    Individual roulette();
};