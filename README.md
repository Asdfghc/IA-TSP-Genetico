# Algoritmo Genético para o Problema do Caixeiro Viajante (TSP)

## Dependências

- `g++`
- `FFmpeg`

Para instalar o FFmpeg:

- Arch / Manjaro:
`sudo pacman -S ffmpeg`  
- Ubuntu / Debian:
`sudo apt install ffmpeg`  
- Windows:
`n sei, acho q tem q baixar do site do ffmpeg.org e extrair e colocar o bin no path`

## Como usar

- Criar pasta `build`

- **Compilar:** `g++ src/*.cpp -Iinclude -o build/main`

- **Rodar:** `./build/main`

Ele irá gerar o gif e o vídeo na pasta `plots`.
