#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define maxpal 100
#define tam 25

FILE *arqpal;
int qpal=0, posicao;
char palavras[maxpal][20];
char palavrasorteada[20];
char pal[tam][tam];

bool abreArquivo();
void leArquivo();
void mostraPalavras();
void sorteia();
void mostra();
void inserepalavra();
int buscapalavra();
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//---------------------------------------------
int main () {
  srand(time(NULL));
  if (abreArquivo()==0)
     return 0;
  leArquivo();
  //mostraPalavras();
  strcpy(palavrasorteada,palavras[rand()%maxpal]);
  sorteia();
  printf("Palavra sorteada: %s \n\n",palavrasorteada);
  inserepalavra();
  mostra();
  buscapalavra();
  printf("\n");
  system("pause");
  return 0;
}
//---------------------------------------------
bool abreArquivo(){
  arqpal = fopen("palavras.txt", "r"); //leitura
  if (arqpal == NULL)
  {  // Se houve erro na leitura do arquivo
     printf("Problemas na leitura do arquivo\n");
     system("pause");
     return 0; //n?o conseguiu abrir o arquivo
  }   
  else
  {
     fclose(arqpal);
     return 1; //conseguiu abrir o arquivo
  }   
}
//---------------------------------------------
void leArquivo(){
   arqpal = fopen("palavras.txt", "r"); //leitura
   qpal=0;
   while (!feof(arqpal))
   {
      //fgets(string,tamanho,arquivo)
      fgets(palavras[qpal],20,arqpal);
      palavras[qpal][strlen(palavras[qpal])-1]='\0';
      qpal++;
   }
   fclose(arqpal);
}
//---------------------------------------------
void sorteia(){
  char vog[6]="AEIOU";
  char con[22]="BCDFGHJKLMNPQRSTVXWYZ";
  int cont=1;
  //A=65   Z=90
  
  for (int x=0; x<tam; x++)
    for (int y=0; y<tam; y++){
      if (cont==1 || cont==3)
      { 
         pal[x][y]=vog[rand()%5];
      }   
      else
      {
         pal[x][y]=con[rand()%21];
      }   
      cont++;
      if (cont>3)
      {
        cont=1;
      }  
    }      
}
//---------------------------------------------
void mostra(){
    SetConsoleTextAttribute(hConsole, BACKGROUND_RED);
    for (int x=0; x<tam; x++){
        for (int y=0; y<tam; y++){
            printf("%c ",pal[x][y]);
        }
        printf("\n");   
    }   
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
//---------------------------------------------
void inserepalavra(){
    int valid=1, l=0, y, linha=rand()%25, coluna=rand()%25;
    //1=Cima para baixo
    //2=Esquerda para a direita
    //3=Direita para a esquerda
    //4=Baixo para cima
    printf("Coordenadas:linha(%d), coluna(%d).\n", linha+1, coluna+1);

    while (valid==1)//Essa laço de repetiç?o garante que a palavra sorteada tenha o espaço adequado para inserç?o, e insere a palavra na matriz.
    {posicao=rand()%4+1;
        switch (posicao)
        {
        case 1:
            if((tam-linha-1)<strlen(palavrasorteada)){
                valid=1;
            }else{
                y=linha+strlen(palavrasorteada);
                printf("\nPosicao 1:Cima para baixo\n\n");
                for(int x=linha; x<y; x++){
                    pal[x][coluna]=palavrasorteada[l];
                    l++;
                }
                valid=0;
            }
            break;
        
        case 2:
            if((tam-coluna-1)<strlen(palavrasorteada)){
                valid=1;
            }else{
                y=coluna+strlen(palavrasorteada);
                printf("\nPosicao 2:Esquerda para a direita\n\n");
                for(int x=coluna; x<y; x++){
                    pal[linha][x]=palavrasorteada[l];
                    l++;
                }
                valid=0;
            }
            break;
        
        case 3:
            if(coluna+1<strlen(palavrasorteada)){
                valid=1;
            }else{
                y=coluna-strlen(palavrasorteada);
                printf("\nPosicao 3:Direita para a esquerda\n\n");
                for(int x=coluna; x>y; x--){
                    pal[linha][x]=palavrasorteada[l];
                    l++;
                }
                valid=0;
            }
            break;

        case 4:
            if(linha<strlen(palavrasorteada)){
                valid=1;
            }else{
                y=linha-strlen(palavrasorteada);
                printf("\nPosicao 4:Baixo para cima\n\n");
                for(int x=linha; x>y; x--){
                    pal[x][coluna]=palavrasorteada[l];
                    l++;
                }
                valid=0;
            }
            break;
        }
    };
}
//---------------------------------------------
int buscapalavra() {
    int a, b;
    char palavrasol[20];
    printf("\nDigite uma palavra(LETRAS MAIÚSCULAS):\n");
    char buffer[1024];
    if (setvbuf(arqpal, buffer, _IOFBF, 1024) != 0) {
        printf("Erro ao configurar o buffering de saida.");
        return 1;
    }
    fgets(palavrasol, 20, stdin);
    for (int x = 0; x < tam; x++) {
        for (int y = 0; y < tam; y++) {
            if (pal[x][y] == palavrasol[0]) {

                for (a = 1; a < strlen(palavrasol)-1; a++) {
                    if (pal[x + a][y] != palavrasol[a]) {
                        break;
                    }
                }
                if (a == strlen(palavrasol)-1){
                    printf("\nPalavra encontrada:Posiç?o: linha(%d), coluna(%d)\nDiraç?o:Cima para baixo.\n", x + 1, y + 1);
                    return -1;
                }
                for (a = 1; a<strlen(palavrasol) - 1; a++) {
                    if (pal[x][y+a]!= palavrasol[a]) {
                        break;
                    }
                }
                if (a == strlen(palavrasol) - 1) {
                    printf("\nPalavra encontrada:Posiç?o: linha(%d), coluna(%d)\nDiraç?o:Esquerda para a direita.\n", x + 1, y + 1);
                    return -1;
                }
                for (a = 1; a < strlen(palavrasol) - 1; a++) {
                    if (pal[x][y - a] != palavrasol[a]) {
                        break;
                    }
                }
                if (a == strlen(palavrasol) - 1) {
                    printf("\nPalavra encontrada:Posiç?o: linha(%d), coluna(%d)\nDiraç?o:Direita para a esquerda.\n", x + 1, y + 1);
                    return -1;
                }
                for (a = 1; a < strlen(palavrasol) - 1; a++) {
                    if (pal[x-a][y] != palavrasol[a]) {
                        break;
                    }
                }
                if (a == strlen(palavrasol) - 1) {
                    printf("\nPalavra encontrada:Posiç?o: linha(%d), coluna(%d)\nDiraç?o:Baixo para cima.\n", x + 1, y + 1);
                    return -1;
                }

            }
        }
    }
    printf("\nPalavra n?o encontrada\n");
}
//---------------------------------------------
