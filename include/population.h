#pragma once

#include <vector>
#include <algorithm>
#include <random>
#include "individual.h"

using namespace std;

class Population {
private:
    int populationSize;
    vector<Individual> individuals;

public:
    Population(int size) : populationSize(size) {
        individuals.reserve(size);
    }

    vector<Individual> getIndividuals() const { return individuals; }

    void initialize(const vector<Point>& cities) {
        individuals.clear();
        for (int i = 0; i < populationSize; ++i) {
            // cria um gerador aleatório baseado em hardware (seed)
            random_device rd;
            mt19937 gen(rd());

            // embaralha o vetor
            vector<Point> shuffledCities = cities;
            shuffle(shuffledCities.begin(), shuffledCities.end(), gen);

            Individual individual(shuffledCities);
            individuals.emplace_back(individual);
        }
    }
};