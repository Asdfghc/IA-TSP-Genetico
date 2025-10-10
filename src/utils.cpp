#include <iostream>
#include <filesystem>
#include <random>
#include <algorithm>
#include <numeric>
#include <string>
#include <cstdlib>
#include "utils.h"
#include "individual.h"
#include "point.h"

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