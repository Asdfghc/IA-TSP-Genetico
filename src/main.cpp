#include <cstdlib>
#include <iostream>
#include <filesystem>
#include "plot.h"

int main() {
    signalsmith::plot::Plot2D plot;
    plot.title("Função Seno");
    plot.x.label("x");
    plot.y.label("sin(x)");

    auto &line = plot.line();
    for (double x = 0; x < 6.28; x += 0.01) {
        line.add(x, std::sin(x));
    }

    plot.write("plots/generation_001.svg"); // Gera arquivo SVG
    plot.write("plots/generation_002.svg"); // Gera arquivo SVG
    plot.write("plots/generation_003.svg"); // Gera arquivo SVG


    std::string cmd = 
        "ffmpeg -y -framerate 10 -pattern_type glob -i plots/gen_*.svg\" "
        "-pix_fmt yuv420p plots/evolution.mp4";

    std::cout << "Gerando vídeo com FFmpeg...\n";
    int result = std::system(cmd.c_str());
    if (result == 0)
        std::cout << "✅ Vídeo gerado com sucesso!\n";
    else
        std::cerr << "❌ Erro ao executar FFmpeg (código " << result << ")\n";

    return 0;
}