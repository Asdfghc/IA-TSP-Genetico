#include <cstdlib>
#include <iostream>
#include <vector>
#include <filesystem>
#include "plot.h"
#include "individual.h"
#include "population.h"
#include "utils.h"

using namespace std;

int main() {
    clearPlots();

    vector<Point> cities = { {1.5, 2.3, "A"}, {3.5, 13.1, "B"}, {13.3, 14.5, "C"}, {12.0, 2.2, "D"}, {7.5, 8.8, "E"},
                             {9.0, 1.5, "F"}, {6.4, 5.5, "G"} };
    
    int populationSize = 100;
    double crossoverRate = 0.7;
    double mutationRate = 0.3;
    int generations = 15;

    Population population(populationSize);
    population.initialize(cities);
    
    for (int i = 0; i < generations; i++) {

        for (int j = 0; j < populationSize * crossoverRate; j++) {
            population.evaluateFitness();
            Individual parent1 = population.roulette();
            Individual parent2 = population.roulette();
            auto children = Individual::crossover(parent1, parent2);
            population.insertIndividuals(children);
        }
        population.select(populationSize);

        // --- Gráficos ---

        signalsmith::plot::Plot2D plot(500, 400);
        plot.x.linear(0, 17).majors(0).minors(17);
        plot.y.linear(0, 17).majors(0).minors(17);
        auto& line = plot.line();

        population.evaluateFitness();
        Individual bestIndividual = population.getBestIndividual();
        for (const auto& point : bestIndividual.getPath()) {
            line.add(point.x, point.y);
            line.marker(point.x, point.y);
            line.label(point.x - 0.5, point.y - 0.7, point.name);
        }
        line.add(bestIndividual.getPath().front().x, bestIndividual.getPath().front().y); // Fecha o ciclo
        //plot.toFrame(j * 0.5); // Adiciona um frame a cada 0.5 segundos

        char filename[64];
        snprintf(filename, sizeof(filename), "plots/individual/gen_%03d.svg", i);
        plot.title("Generation " + to_string(i + 1) + " - Distance: " + to_string(bestIndividual.getTotalDistance()));
        plot.write(filename); // Gera arquivo SVG para cada indivíduo
    }
    //plot.write("plots/evolution.svg"); // Gera arquivo SVG

    createGif();
    createVideo();

    return 0;
}