#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define tam 26
#define maxpal 100

FILE* arquivo;

int qpal = 0;

char palavras[maxpal][26];
char palavrasorteada[26];
char pal[tam][tam];

bool abreArquivo();
void leArquivo();
void sorteia();
void inserePalavra(char* palavrasorteada);
void mostra();
bool buscaPalavra();
//---------------------------------------------
int main() {
    srand(time(NULL));
    if (!abreArquivo())
        return 0;
    leArquivo();
    do {
        strcpy(palavrasorteada, sizeof(palavrasorteada), palavras[rand() % maxpal]);
    } while (strlen(palavrasorteada) == 0);
    printf("%s \n", palavrasorteada);
    sorteia();
    inserePalavra(palavrasorteada);
    mostra();
    buscaPalavra("PALAVRA");
    printf("\n");
    system("pause");
    return 0;
}
//---------------------------------------------
bool abreArquivo() { //Essa função abre o arquivo .txt;
    if (fopen(&arquivo, "palavras.txt", "r") != 0) //leitura
    {  // Se houve erro na leitura do arquivo
        printf("Problemas na leitura do arquivo\n");
        return false; //não conseguiu abrir o arquivo
    }
    return true; //conseguiu abrir o arquivo
}
/*abreArquivo(): abre o arquivo de palavras e retorna true se o arquivo foi aberto com sucesso e false caso contrário.*/
//---------------------------------------------
void leArquivo() { //Esse procedimento lê os arquivos que estão na .txt
    qpal = 0;
    while (fgets(palavras[qpal], 26, arquivo) != NULL)
    {
        palavras[qpal][strlen(palavras[qpal]) - 1] = '\0';
        qpal++;
    }
    fclose(arquivo); //Fecha o arquivo .txt
}
/*leArquivo(): lê o arquivo de palavras e armazena as palavras em um array palavras, que é uma variável global.*/
//---------------------------------------------
void sorteia() { //Esse procedimento sorteia as palavras para serem apresentadas na matriz
    char vog[6] = "AEIOU";
    char con[22] = "BCDFGHJKLMNPQRSTVXWYZ";
    int cont = 1;
    //A=65   Z=90
    for (int x = 0; x < tam; x++)
        for (int y = 0; y < tam; y++) {
            if (cont == 1 || cont == 3)
            {
                pal[x][y] = vog[rand() % 5];
            }
            else
            {
                pal[x][y] = con[rand() % 21];
            }
            cont++;
            if (cont > 3)
            {
                cont = 1;
            }
        }
}
/*sorteia(): preenche a matriz pal com letras geradas aleatoriamente. A cada três posições na matriz, são inseridas vogais, e nas outras posições, consoantes.*/
//---------------------------------------------
void mostra() {
    printf("");
    for (int lin = 1; lin <= tam; lin++) {
        for (int col = 1; col <= tam; col++) {
            printf("%2c ", pal[lin][col]);
        }
        printf("\n");
    }
}
/*mostra(): imprime a matriz pal na tela.*/
//---------------------------------------------
void inserePalavra(char* palavrasorteada) {
    int x, y, x0, y0, dx, dy;
    bool horizontal = rand() % 2 == 0;
    bool diagonal = rand() % 2 == 0; // adicionado

    do {
        x0 = rand() % tam;
        y0 = rand() % tam;

        if (horizontal) {
            if (y0 + strlen(palavrasorteada) > tam) {
                continue;
            }
            dx = 0;
            dy = 1;
        }
        else if (diagonal && y0 + strlen(palavrasorteada) <= tam && x0 - strlen(palavrasorteada) >= -1) { // adicionado
            dx = -1;
            dy = 1;
        }
        else if (diagonal && y0 - strlen(palavrasorteada) >= -1 && x0 + strlen(palavrasorteada) <= tam) { // adicionado
            dx = 1;
            dy = -1;
        }
        else {
            if (x0 + strlen(palavrasorteada) > tam) {
                continue;
            }
            dx = 1;
            dy = 0;
        }

        x = x0;
        y = y0;

        for (int i = 0; i < strlen(palavrasorteada); i++) {
            pal[x][y] = palavrasorteada[i];
            x += dx;
            y += dy;
        }

        int x1 = x0;
        int y1 = y0;
        for (int i = 0; i < strlen(palavrasorteada); i++) {
            x1 += dx;
            y1 += dy;
        }
    } while ((x < 0 || x >= tam || y < 0 || y >= tam));

    printf("Palavra '%s' inserida na matriz na posicao(linha: % d, coluna : % d) e vai ", palavrasorteada, x0, y0);
    if (horizontal) {
        if (dy == 1) {
            printf("da esquerda para direita\n");
        }
        else if (dy == 0) {
            printf("da direita para esquerda\n");
        }
    }
    else if (diagonal && dx == -1 && dy == 1) { // adicionado
        printf("da direita inferior para esquerda superior\n");
    }
    else if (diagonal && dx == 1 && dy == -1) { // adicionado
        printf("da esquerda superior para direita inferior\n");
    }
    else {
        if (dx == 1) {
            printf("de cima para baixo\n");
        }
        else if (dx == 0) {
            printf("de baixo para cima\n");
        }
    }
}
//---------------------------------------------
bool buscaPalavra(char* palavra) {
    for (int lin = 0; lin < tam; lin++) {
        for (int col = 0; col < tam; col++) {
            // procura na horizontal
            if (col + strlen(palavra) <= tam) {
                int i;
                for (i = 0; i < strlen(palavra); i++) {
                    if (pal[lin][col + i] != palavra[i]) {
                        break;
                    }
                }
                if (i == strlen(palavra)) {
                    printf("Palavra encontrada na horizontal, linha %d, coluna %d.\n", lin, col);
                    return true;
                }
            }
            // procura na vertical
            if (lin + strlen(palavra) <= tam) {
                int i;
                for (i = 0; i < strlen(palavra); i++) {
                    if (pal[lin + i][col] != palavra[i]) {
                        break;
                    }
                }
                if (i == strlen(palavra)) {
                    printf("Palavra encontrada na vertical, linha %d, coluna %d.\n", lin, col);
                    return true;
                }
            }
        }
    }
    printf("Palavra nao encontrada.\n");
    return false;
}
