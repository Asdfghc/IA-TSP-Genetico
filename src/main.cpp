#include <cstdlib>
#include <iostream>
#include <vector>
#include "plot.h"
#include "individual.h"
#include "population.h"

using namespace std;

int main() {
    vector<Point> cities = { {1.5, 2.3, "A"}, {3.5, 13.1, "B"}, {13.3, 14.5, "C"}, {12.0, 2.2, "D"}, {7.5, 8.8, "E"},
                             {9.0, 1.5, "F"}, {6.4, 5.5, "G"} };
    int populationSize = 10;
    double crossoverRate = 0.7;
    double mutationRate = 0.1;
    int generations = 10;

    Population population(populationSize);
    population.initialize(cities);
    
    for (int i = 0; i < generations; i++) {
        cout << "Generation " << i + 1 << ":\n";

        vector<Individual> offspring;
        offspring.reserve((int)(populationSize * crossoverRate));
        for (int j = 0; j < populationSize * crossoverRate; j++) {
            population.evaluateFitness();
            Individual parent1 = roulette(population.getIndividuals(), population.fitnessValues);
            Individual parent2 = roulette(population.getIndividuals(), population.fitnessValues);
            for (Individual child : crossover(parent1, parent2)) {
                offspring.push_back(child);
            }
            //mutate(child, mutationRate);
        }
        population.insert(offspring);
        // print population before selection
        cout << "Population before selection:\n";
        for (Individual ind : population.getIndividuals()) {
            for (const auto& city : ind.getPath()) {
                printf("%s ", city.name.c_str());
            }
            printf(" | Distance: %.2f\n", ind.getTotalDistance());
        }
        population.select(populationSize);
        // print population after selection
        cout << "Population after selection:\n";
        for (Individual ind : population.getIndividuals()) {
            for (const auto& city : ind.getPath()) {
                printf("%s ", city.name.c_str());
            }
            printf(" | Distance: %.2f\n", ind.getTotalDistance());
        }

        signalsmith::plot::Plot2D plot;
        plot.x.linear(0, 17).majors(0).minors(17);
        plot.y.linear(0, 17).majors(0).minors(17);
        auto& line = plot.line();

        population.evaluateFitness();
        Individual bestIndividual = population.getBestIndividual();
        for (const auto& point : bestIndividual.getPath()) {
            line.add(point.x, point.y);
            line.marker(point.x, point.y);
            line.label(point.x - 1, point.y - 1, point.name);
        }
        line.add(bestIndividual.getPath().front().x, bestIndividual.getPath().front().y); // Fecha o ciclo
        //plot.toFrame(j * 0.5); // Adiciona um frame a cada 0.5 segundos

        plot.write("plots/individual_" + to_string(i) + ".svg"); // Gera arquivo SVG para cada indivíduo
        //cout << population.fitnessValues.at(i) << endl; // Imprime a aptidão do indivíduo
    }

    

    //plot.write("plots/evolution.svg"); // Gera arquivo SVG

    return 0;
}