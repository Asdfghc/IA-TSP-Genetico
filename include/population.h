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
    vector<double> fitnessValues;

    Population(int size) : populationSize(size) {
        individuals.reserve(size);
    }

    vector<Individual> getIndividuals() const { return individuals; }

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
        for (int i = 0; i < populationSize; i++) 
            fitnessValues.emplace_back(individuals.at(i).getTotalDistance());
        double maxDistance = *max_element(fitnessValues.begin(), fitnessValues.end());
        for (int i = 0; i < populationSize; i++) {
            fitnessValues.at(i) = maxDistance - fitnessValues.at(i);
        }
        double fitnessSum = accumulate(fitnessValues.begin(), fitnessValues.end(), 0.0);
        for (int i = 0; i < populationSize; i++) {
            double normalizedFitness = fitnessValues.at(i) / fitnessSum;
            fitnessValues.emplace_back(normalizedFitness);
        }
    }

    Individual roulette() {
        vector<double> fitnessCumsum;
        partial_sum(fitnessValues.begin(), fitnessValues.end(), back_inserter(fitnessCumsum));
        random_device rd;
        mt19937 gen(rd());
        double r = uniform_real_distribution<>(0, fitnessCumsum.back())(gen);
        auto it = lower_bound(fitnessCumsum.begin(), fitnessCumsum.end(), r);
        return individuals.at(distance(fitnessCumsum.begin(), it));
    }
};