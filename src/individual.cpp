#include "individual.h"
#include <random>
#include <algorithm>

Individual::Individual(const vector<Point>& path) : path(path) {}

const vector<Point>& Individual::getPath() const { return path; }

double Individual::distance(const Point& a, const Point& b) const {
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

double Individual::getTotalDistance() const {
	double total = 0.0;
	for (size_t i = 0; i < path.size() - 1; ++i) {
		total += distance(path[i], path[i + 1]);
	}
	total += distance(path.back(), path.front()); // Return to start
	return total;
}

// Mutate this individual in-place
void Individual::mutate(double mutationRate) {
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0, 1);
	if (dis(gen) < mutationRate) {
		vector<Point> newPath = this->path;
		int n_cities = (int)newPath.size();
		int idx1 = uniform_int_distribution<>(0, n_cities - 1)(gen);
		int idx2 = uniform_int_distribution<>(0, n_cities - 1)(gen);
		swap(newPath[idx1], newPath[idx2]);
		this->path = move(newPath);
	}
}

// Static crossover: returns two offspring
pair<Individual, Individual> Individual::crossover(const Individual& parent1, const Individual& parent2) {
	random_device rd;
	mt19937 gen(rd());
	const vector<Point>& p1 = parent1.getPath();
	const vector<Point>& p2 = parent2.getPath();

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

	return { Individual(offspring1), Individual(offspring2) };
}