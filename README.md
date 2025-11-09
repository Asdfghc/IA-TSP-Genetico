# IA-TSP-Genetico
Este projeto implementa um **Algoritmo Genético** para resolver o **Problema do Caixeiro Viajante (TSP)** com pontos em 2D.  
Foram utilizados **C++** para o algoritmo e **Signalsmith Plot** + **FFmpeg** para visualização animada da evolução.

![Evolução do TSP](example2.gif)

## Algoritmo Genético Implementado
- **População inicial aleatória** com permutações válidas.  
- **Seleção por roleta** proporcional ao fitness.  
- **Cruzamento Order Crossover (OX)** — preserva ordem relativa.  
- **Mutação por troca (swap)** com taxa configurável.  
- **Função de aptidão**: a aptidão é calculada a partir da transformação das distâncias por (maxDistance - distância_total) e os valores são normalizados para somar 1.  
- **Dois cenários**: pontos uniformes e círculo (benchmark).

---

## Explicações dos Parâmetros

### População e Critério de Parada
- **Tamanho da população**: 1000 indivíduos.  
- **Critério de parada**: 100 gerações (uniforme) ou 40 (círculo).  
- **Justificativa**: População grande garante diversidade; número fixo de gerações evita tempo excessivo e permite convergência observável.

### Taxa de Mutação
- **Taxa**: 43% por gene.  
- **Justificativa**: Alta para evitar convergência precoce em espaços de permutação complexos como o TSP. Mantém exploração mesmo em populações grandes.

### Representação do Gene e Cruzamento
- **Gene**: Vetor de `Point` representando permutação da ordem de visita.  
- **Cruzamento**: **Order Crossover (OX)** — seleciona segmento do pai 1 e completa com ordem relativa do pai 2. Ocorre 70% das vezes.  
- **Justificativa**: Garante filhos válidos (sem duplicatas) e preserva blocos de cidades próximas.

### Função de Aptidão
- **Fórmula (implementada no código)**: a aptidão é calculada a partir das distâncias transformadas por:

  ```
  fitness_i = (maxDistance - distance_i) / sum_j (maxDistance - distance_j)
  ```

  onde maxDistance é a maior distância total observada entre indivíduos na população. Os valores são normalizados para somar 1.

**Justificativa**: Essa transformação evita divisões por zero e permite normalização direta para seleção por roleta, atribuindo maiores valores de aptidão a indivíduos com menor distância total.

---

## Dependências

- `g++` (C++17 ou superior)
- `FFmpeg` (para gerar GIF e vídeo)

### Instalação do FFmpeg

- **Arch / Manjaro**:
  ```bash
  sudo pacman -S ffmpeg
- **Ubuntu / Debian**:
  ```bash
  sudo apt-get install ffmpeg
  ```

## Resultados e Desempenho

### Cenário: 20 Cidades Uniformes

| Geração | Distância Média | Melhor Distância | Tempo (ms) |
|--------:|----------------:|-----------------:|-----------:|
|       1 |          150.2  |           163.7  |          0 |
|      25 |          113.4  |           112.1  |        180 |
|      50 |           99.6  |            98.2  |        360 |
|      75 |           85.3  |            83.9  |        540 |
|     100 | **80.5**        | **79.6**         |        720 |

![Solução final – 20 cidades uniformes](example4.gif)

---

### Cenário: 40 Cidades Uniformes

| Geração | Distância Média | Melhor Distância | Tempo (ms) |
|--------:|----------------:|-----------------:|-----------:|
|       1 |          344.5  |           343.1  |          0 |
|      25 |          209.7  |           208.6  |        420 |
|      50 |          190.2  |           188.8  |        840 |
|      75 |          174.3  |           172.4  |      1,260 |
|     100 | **163.4**       | **162.45**       |      1,680 |

![Solução final – 40 cidades uniformes](example3.gif)

### Cenário: 20 Cidades Em Circulo

| Geração | Distância Média | Melhor Distância | Tempo (ms) |
|--------:|----------------:|-----------------:|-----------:|
|       1 |          156.2  |           154.2  |          0 |
|      20 |           67.4  |            65.7  |         75 |
|      40 |           42.6  |            41.2  |        180 |
|      60 | **40.2**        | **37.5**         |        300 |

![Solução final – 20 cidades uniformes](example2.gif)