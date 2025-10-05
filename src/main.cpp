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

    

    plot.write("plots/gen_001.svg"); // Gera arquivo SVG
    plot.write("plots/gen_002.svg"); // Gera arquivo SVG
    plot.write("plots/gen_003.svg"); // Gera arquivo SVG


    // Usa PNG e nomes numerados (gen_000.png, gen_001.png, ...)

    std::string frames_folder = "plots";

    std::string cmd =
        "ffmpeg -y -framerate 2 -i \"" + frames_folder +
        "/gen_%03d.svg\" -vf \"scale=trunc(iw/2)*2:trunc(ih/2)*2\" "
        "-c:v libx264 -pix_fmt yuv420p " + frames_folder + "/evolution.mp4";

    std::cout << "Gerando vídeo com FFmpeg...\n";
    int result = std::system(cmd.c_str());
    if (result == 0)
        std::cout << "✅ Vídeo gerado com sucesso!\n";
    else
        std::cerr << "❌ Erro ao executar FFmpeg (código " << result << ")\n";

    return 0;
}