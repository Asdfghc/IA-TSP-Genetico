#include <cstdlib>
#include <iostream>
#include <vector>
#include "plot.h"
#include "individual.h"
#include "population.h"

using namespace std;

int main() {
    vector<Point> cities = { {1.5, 2.3, "A"}, {3.5, 13.1, "B"}, {13.3, 14.5, "C"}, {12.0, 2.2, "D"} };

    Population population(10);
    population.initialize(cities);

    //Individual individual = population.getIndividuals().front();

    signalsmith::plot::Plot2D plot;
    plot.x.linear(0, 17).majors(0).minors(17);
    plot.y.linear(0, 15).majors(0).minors(15);
    auto& line = plot.line();

    for (int i = 0; i < 10; i++) {
        Individual individual = population.getIndividuals().at(i);
        for (const auto& point : individual.getPath()) {
            line.add(point.x, point.y);
            line.marker(point.x, point.y);
            line.label(point.x - 1, point.y - 1, point.name);
        }
        line.add(individual.getPath().front().x, individual.getPath().front().y); // Fecha o ciclo
        plot.toFrame(i * 0.5); // Adiciona um frame a cada 0.5 segundos
    }

    plot.write("plots/evolution.svg"); // Gera arquivo SVG

    return 0;
}