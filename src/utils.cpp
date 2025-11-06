#include <iostream>
#include <filesystem>
#include <random>
#include <algorithm>
#include <numeric>
#include <string>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <iomanip>
#include "utils.h"
#include "individual.h"
#include "point.h"

vector<Point> generateUniformPoints(int n, double xmin, double xmax, double ymin, double ymax) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution <> dx(xmin, xmax);
    uniform_real_distribution <> dy(ymin, ymax);

    vector<Point> points;

    for (int i = 0; i < n; i++) {
        ostringstream name;
        name << "P" << i;
        points.push_back({dx(gen),dy(gen),name.str()});
    }

    return points;
}

vector<Point> generateCirclePoints(int n, double cx, double cy, double radius) {
    vector<Point> points;
    for (int i = 0; i < n; i++) {
        double theta = 2 * M_PI * i / n;
        double x = cx + radius * cos(theta);
        double y = cy + radius * sin(theta);
        ostringstream name;
        name << "C" << i;
        points.push_back({x, y, name.str()});
    }
    return points;
}

void clearPlots() {
    string plots_folder = "plots";
    if (!filesystem::exists(plots_folder)) {
        filesystem::create_directory(plots_folder);
    } else {
        for (const auto& entry : filesystem::directory_iterator(plots_folder)) {
            filesystem::remove_all(entry.path());
        }
    }
    plots_folder = "plots/individual";
    if (!filesystem::exists(plots_folder)) {
        filesystem::create_directory(plots_folder);
    } else {
        for (const auto& entry : filesystem::directory_iterator(plots_folder)) {
            filesystem::remove_all(entry.path());
        }
    }
}

void createGif() {
    string frames_folder = "plots";

    string cmd =
        "ffmpeg -y -i plots/individual/gen_%03d.svg -vf palettegen plots/palette.png -nostats -loglevel 0 && "
        "ffmpeg -y -framerate 2 -i plots/individual/gen_%03d.svg -i plots/palette.png -lavfi paletteuse plots/evolution.gif -nostats -loglevel 0";

    cout << "Gerando gif com FFmpeg...\n";
    int result = system(cmd.c_str());
    if (result == 0)
        cout << "Gif gerado com sucesso!\n";
    else
        cerr << "Erro ao executar FFmpeg (código " << result << ")\n";
}

void createVideo() {
    string frames_folder = "plots";

    string cmd =
        "ffmpeg -y -framerate 2 -i plots/individual/gen_%03d.svg -c:v libx264 -pix_fmt yuv420p plots/evolution.mp4 -nostats -loglevel 0";

    cout << "Gerando vídeo com FFmpeg...\n";
    int result = system(cmd.c_str());
    if (result == 0)
        cout << "Vídeo gerado com sucesso!\n";
    else
        cerr << "Erro ao executar FFmpeg (código " << result << ")\n";
}