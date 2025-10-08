#pragma once

#include <vector>
#include <algorithm>
#include <random>
#include "individual.h"
#include "utils.h"

using namespace std;

class Population {
private:
    int populationSize;
    vector<Individual> individuals;
    
public:
    vector<double> fitnessValues;

    Population(int size) : populationSize(size) {
        individuals.reserve(size);
    }

    vector<Individual> getIndividuals() const { return individuals; }

    void insert(vector<Individual> individuals) {
        for (const auto& ind : individuals) {
            this->individuals.emplace_back(ind);
        }
    }

    void initialize(const vector<Point>& cities) {
        individuals.clear();
        for (int i = 0; i < populationSize; i++) {
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

    void evaluateFitness() {
        fitnessValues.clear();
        for (int i = 0; i < individuals.size(); i++)
            fitnessValues.emplace_back(individuals.at(i).getTotalDistance());
        double maxDistance = *max_element(fitnessValues.begin(), fitnessValues.end());
        for (int i = 0; i < individuals.size(); i++) {
            fitnessValues.at(i) = maxDistance - fitnessValues.at(i);
        }
        double fitnessSum = accumulate(fitnessValues.begin(), fitnessValues.end(), 0.0);
        if (fitnessSum == 0) fitnessSum = 1; // Evita divisão por zero
        for (int i = 0; i < individuals.size(); i++) {
            fitnessValues.at(i) /= fitnessSum;
        }
    }

    void select(int populationSize) {
        sort(individuals.begin(), individuals.end(), [&](Individual a, Individual b) {
            return a.getTotalDistance() < b.getTotalDistance();
        });
        if (individuals.size() > populationSize)
            individuals.erase(individuals.begin() + populationSize, individuals.end());
    }

    Individual getBestIndividual() {
        auto minIt = min_element(fitnessValues.begin(), fitnessValues.end());
        int index = distance(fitnessValues.begin(), minIt);
        return individuals.at(index);
    }
};