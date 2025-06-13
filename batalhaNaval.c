#include <stdio.h>

    // Constantes para tabuleiro e navios

    #define TAB_SIZE 10
    #define NAVIO_TAM 3

    // Valores no tabuleiro

    #define AGUA 0
    #define NAVIO 3
    #define HABILIDADE 5

    // Prototipos

    void inicializarTabuleiro(int tab[TAB_SIZE][TAB_SIZE]);
    int posicionarNavioReto(int tab[TAB_SIZE][TAB_SIZE], int linha, int coluna, int tamanho, char orientacao);
    int posicionarNavioDiagonal(int tab[TAB_SIZE][TAB_SIZE], int linha, int coluna, int tamanho, char diagonal);
    void construirHabilidadeCone(int area[5][5]);
    void construirHabilidadeCruz(int area[5][5]);
    void construirHabilidadeOctaedro(int area[5][5]);
    void aplicarHabilidade(int tab[TAB_SIZE][TAB_SIZE], int area[5][5], int origemLinha, int origemColuna);
    void exibirTabuleiro(int tab [TAB_SIZE][TAB_SIZE]);


    int main() {
        int tabuleiro[TAB_SIZE][TAB_SIZE];

        // Nivel novato:

        inicializarTabuleiro(tabuleiro);
        posicionarNavioReto(tabuleiro, 1, 1, NAVIO_TAM, 'H'); // Horizontal no ponto (1,1)
        posicionarNavioReto(tabuleiro, 3, 5, NAVIO_TAM, 'V'); // Vertical no ponto (3,5)

        // Nivel Aventureiro:

        posicionarNavioDiagonal(tabuleiro, 6, 0, NAVIO_TAM, 'P'); // Diagonal principal (para baixo e direita)
        posicionarNavioDiagonal(tabuleiro, 6, 9, NAVIO_TAM, 'S'); // Diagonal secundária (pra baixo e esquerda)

        // Nivel Mestre:

        int cone[5][5], cruz[5][5], octaedro[5][5];

        construirHabilidadeCone(cone);
        construirHabilidadeCruz(cruz);
        construirHabilidadeOctaedro(octaedro);

        // Aplicando as habilidades nas origens

        aplicarHabilidade(tabuleiro, cone, 0, 4);  // Cone no topo, na coluna 4
        aplicarHabilidade(tabuleiro, cruz, 5, 5); // Cruz no centro aproximado
        aplicarHabilidade(tabuleiro, octaedro, 9, 4); // Octaedro na base

        // Exibindo tabuleiro final
        exibirTabuleiro(tabuleiro);

        return 0;

    }

    // Iniciando tabuleiro com agua (0)

    void inicializarTabuleiro(int tab[TAB_SIZE][TAB_SIZE]) {
        for (int i = 0; i < TAB_SIZE; i++) {
          for (int j = 0; j < TAB_SIZE; j++) {
            tab[i][j] = AGUA;
          }  
        }
    }

    // Posiciona navio reto horizontal ou vertical; retorna 1 se sucesso, 0 se falhar

    int posicionarNavioReto(int tab[TAB_SIZE][TAB_SIZE], int linha, int coluna, int tamanho, char orientacao) {
        //Verificando limites
        if (orientacao == 'H') {
            if (coluna + tamanho > TAB_SIZE) return 0;
            for (int i = 0; i < tamanho; i++) {
                if (tab[linha][coluna + i] == NAVIO) return 0; // Sobreposição
            }
            for (int i = 0; i < tamanho; i++) {
                tab[linha][coluna + i] = NAVIO;
            }
        } else if (orientacao == 'V') {
            int (linha + tamanho > TAB_SIZE) return 0;
            for (int i = 0; i < tamanho; i++) {
                if (tab[linha + i][coluna] == NAVIO) return 0; // Sobreposição
            }
            for (int i = 0; i < tamanho; i++) {
                tab[linha + i] [coluna] = NAVIO;
            }
        } else {
            return 0; // Orientação inválida
    }
    return 1;
}

// Posiciona navio diagonal principal (P) ou secundaria (S); retorna 1 se sucesso, 0 se falha

int posicionarNavioDiagonal(int tab[TAB_SIZE][TAB_SIZE], int linha, int coluna, int tamanho, char diagonal) {
  
    //Verificando limites e sobreposição
    for (int i = 0; i < tamanho; i++) {
        int l = linha + i;
        int c = (diagonal == 'P') ? coluna + i : coluna - i;

        if (l < 0 || l >= TAB_SIZE || c < 0 || c >= TAB_SIZE) return 0;
        if (tab[l][c] == NAVIO) return  0;
    }

    // Posicionando navio

    for (int i = 0; i < tamanho; i++) {
        int l = linha + i;
        int c = (diagonal == 'P') ? coluna + i : coluna - i;
        tab[l][c] = NAVIO;
    }
    return 1;

    // Constroi matriz de habilidade Cone 5x5 com a ponta no topo
    
    void construirHabilidadeCone(int area[5][5]) {
        for (int i = 0; i < 5; i++) { // linhas
            for (int j = 0; j < 5; j++) { // colunas
                if (j >= 2 - i && j <= 2 + i) // faixa em formato de cone 
                   area[i][j] = 1;
              else
                   area[i][j] = 0;

        }
    }
}

// Construindo matriz de habilidade Cruz 5x5 (ponto central)

void construirHabilidadeCruz(int area[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i == 2 || j == 2) // linha e coluna central
            area[i][j] = 1;
            
            else

            area[i][j] = 0;

        }
    }
}

// Aplicando a habilidade no tabuleiro centrando na origem (linha, coluna)
void aplicarHabilidade(int tab[TAB_SIZE][TAB_SIZE], int area[5][5], int origemLinha, int origemColuna) {
    int offset = 2; // Centro da matrix 5x5

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (area[i][j] == 1) {
               int lin = origemLinha - offset + i;
               int col = origemColuna - offset + j;

               if (lin >= 0 && lin < TAB_SIZE && col >= 0 && col < TAB_SIZE {
                if (tab[lin][col] == AGUA { // Só marco agua para nao sobrescrever navios
                    tab[lin][col] = HABILIDADE;
                }
               }
            }
        }
    }
}

//Exibindo tabuleiro no console 
void exibirTabuleiro(int tab[TAB_SIZE][TAB_SIZE]) {
    printf("Tabuleiro:\n");
    for (int i = 0; i < TAB_SIZE; i++) {
        for (int j = 0; j < TAB_SIZE; j++) {
            if (tab[i][j] == AGUA) {
                printf("0 ");
            } else if (tab[i][j] == NAVIO) {
                printf("3 ");
            } else if (tab[i][j] == HABILIDADE) {
                printf("5 ");
            } else {
                printf("? "); // Caso inesperado
        }
    }
    printf("\n");

}

}




