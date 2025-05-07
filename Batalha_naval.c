#include <stdio.h>

#define SIZE 10
#define HSIZE 5  // tamanho das matrizes de habilidade (5x5)

// Função para inicializar o tabuleiro com água (0) e alguns navios (3)
void inicializarTabuleiro(int tabuleiro[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            tabuleiro[i][j] = 0;

    // Adicionando alguns navios como exemplo
    tabuleiro[2][3] = 3;
    tabuleiro[5][5] = 3;
    tabuleiro[7][8] = 3;
}

// Função para imprimir o tabuleiro
void imprimirTabuleiro(int tabuleiro[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Função para gerar matriz cone (em forma de triângulo apontando para baixo)
void gerarCone(int cone[HSIZE][HSIZE]) {
    for (int i = 0; i < HSIZE; i++) {
        for (int j = 0; j < HSIZE; j++) {
            if (j >= HSIZE/2 - i && j <= HSIZE/2 + i)
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }
}

// Função para gerar matriz cruz
void gerarCruz(int cruz[HSIZE][HSIZE]) {
    for (int i = 0; i < HSIZE; i++) {
        for (int j = 0; j < HSIZE; j++) {
            if (i == HSIZE / 2 || j == HSIZE / 2)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }
}

// Função para gerar matriz octaedro (losango)
void gerarOctaedro(int octaedro[HSIZE][HSIZE]) {
    for (int i = 0; i < HSIZE; i++) {
        for (int j = 0; j < HSIZE; j++) {
            if (abs(i - HSIZE/2) + abs(j - HSIZE/2) <= HSIZE/2)
                octaedro[i][j] = 1;
            else
                octaedro[i][j] = 0;
        }
    }
}

// Função para aplicar habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[SIZE][SIZE], int habilidade[HSIZE][HSIZE], int origemX, int origemY) {
    int offset = HSIZE / 2;

    for (int i = 0; i < HSIZE; i++) {
        for (int j = 0; j < HSIZE; j++) {
            int tabX = origemX - offset + i;
            int tabY = origemY - offset + j;

            // Verificar se está dentro do tabuleiro
            if (tabX >= 0 && tabX < SIZE && tabY >= 0 && tabY < SIZE) {
                if (habilidade[i][j] == 1 && tabuleiro[tabX][tabY] != 3) {
                    tabuleiro[tabX][tabY] = 5; // Marca área de efeito, sem sobrescrever navio (3)
                }
            }
        }
    }
}

int main() {
    int tabuleiro[SIZE][SIZE];
    int cone[HSIZE][HSIZE];
    int cruz[HSIZE][HSIZE];
    int octaedro[HSIZE][HSIZE];

    inicializarTabuleiro(tabuleiro);
    gerarCone(cone);
    gerarCruz(cruz);
    gerarOctaedro(octaedro);

    printf("Tabuleiro inicial:\n");
    imprimirTabuleiro(tabuleiro);

    // Aplicar cone no centro superior
    aplicarHabilidade(tabuleiro, cone, 2, 2);
    printf("Tabuleiro após aplicar Cone em (2,2):\n");
    imprimirTabuleiro(tabuleiro);

    // Aplicar cruz no centro do tabuleiro
    aplicarHabilidade(tabuleiro, cruz, 5, 5);
    printf("Tabuleiro após aplicar Cruz em (5,5):\n");
    imprimirTabuleiro(tabuleiro);

    // Aplicar octaedro no canto inferior direito
    aplicarHabilidade(tabuleiro, octaedro, 7, 8);
    printf("Tabuleiro após aplicar Octaedro em (7,8):\n");
    imprimirTabuleiro(tabuleiro);

    return 0;
}
