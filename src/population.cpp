#include "population.h"
#include <random>
#include <numeric>
#include <algorithm>

Population::Population(int size) : populationSize(size) { individuals.reserve(size); }

const vector<Individual>& Population::getIndividuals() const { return individuals; }

const vector<double>& Population::getFitnessValues() const { return fitnessValues; }

void Population::insertIndividuals(const pair<Individual, Individual>& individuals) {
	this->individuals.emplace_back(individuals.first);
	this->individuals.emplace_back(individuals.second);
}

void Population::initialize(const vector<Point>& cities) {
	individuals.clear();
	for (int i = 0; i < populationSize; i++) {
		random_device rd;
		mt19937 gen(rd());
		vector<Point> shuffledCities = cities;
		shuffle(shuffledCities.begin(), shuffledCities.end(), gen);
		Individual individual(shuffledCities);
		individuals.emplace_back(individual);
	}
}

void Population::evaluateFitness() {
	fitnessValues.clear();
	for (int i = 0; i < individuals.size(); i++)
		fitnessValues.emplace_back(individuals.at(i).getTotalDistance());
	double maxDistance = *max_element(fitnessValues.begin(), fitnessValues.end());
	for (int i = 0; i < individuals.size(); i++) {
		fitnessValues.at(i) = maxDistance - fitnessValues.at(i);
	}
	double fitnessSum = accumulate(fitnessValues.begin(), fitnessValues.end(), 0.0);
	if (fitnessSum == 0) fitnessSum = 1;
	for (int i = 0; i < individuals.size(); i++) {
		fitnessValues.at(i) /= fitnessSum;
	}
}

void Population::select(int populationSize) {
	sort(individuals.begin(), individuals.end(), [&](Individual a, Individual b) {
		return a.getTotalDistance() < b.getTotalDistance();
	});
	if (individuals.size() > populationSize)
		individuals.erase(individuals.begin() + populationSize, individuals.end());
}

Individual Population::getBestIndividual() {
	auto minIt = min_element(fitnessValues.begin(), fitnessValues.end());
	int index = distance(fitnessValues.begin(), minIt);
	return individuals.at(index);
}

Individual Population::roulette() {
	vector<double> fitnessCumsum;
	partial_sum(fitnessValues.begin(), fitnessValues.end(), back_inserter(fitnessCumsum));
	random_device rd;
	mt19937 gen(rd());
	double r = uniform_real_distribution<>(0, fitnessCumsum.back())(gen);
	auto it = lower_bound(fitnessCumsum.begin(), fitnessCumsum.end(), r);
	int idx = distance(fitnessCumsum.begin(), it);
	return individuals.at(idx);
}