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

    int populationSize = 100;
    double crossoverRate = 0.7;
    double mutationRate = 0.43;
    int generations = 100;

    vector<Point> cities;

    // Switch de circle para pontos uniformes
    bool circle = false;

    if (circle) {
        cities = generateCirclePoints(20, 8.0, 8.0, 6.0);
    } else {
        cities = generateUniformPoints(20);
    }

    Population population(populationSize);
    population.initialize(cities);
    
    for (int i = 0; i < generations; i++) {

        for (int j = 0; j < populationSize * crossoverRate; j++) {
            population.evaluateFitness();
            Individual parent1 = population.roulette();
            Individual parent2 = population.roulette();
            auto children = Individual::crossover(parent1, parent2);
            children.first.mutate(mutationRate);
            children.second.mutate(mutationRate);
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