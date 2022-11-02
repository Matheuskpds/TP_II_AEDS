#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/* Tamanho máximo da string de entrada. */
#define MAX 250

int conta_linhas(FILE* file){
    int cont=0;
    for (char c = getc(file); c != EOF; c = getc(file)){
        if (c == '\n')
            cont = cont + 1;
    }
    return cont;
}

void gera_matriz_zerada(int tamanho, int matriz[tamanho][tamanho]){
    for(int linha=0; linha<tamanho; linha++){
        for(int coluna=0; coluna<tamanho; coluna++){
            if(linha==coluna){
                matriz[linha][coluna] = -1;
            }
            else{
                matriz[linha][coluna] = 0;
            }
        }
    }
    printf("\nPrintando matriz zerada:\n");
    for(int linha=0; linha<tamanho; linha++){
        for(int coluna=0; coluna<tamanho; coluna++){
            if(coluna==tamanho-1){
                printf("%d \n", matriz[linha][coluna]);
            }
            else{
                printf("%d ", matriz[linha][coluna]);
            }
        }
    }
    printf("\n");
    
}



void preenche_matriz_com_arquivo(char* nomeArquivo, int tamanho, int matriz[tamanho][tamanho]){
    FILE* file;
    
    gera_matriz_zerada(tamanho, matriz);
    file = fopen(nomeArquivo, "rt");
    int contLido=1;
    char numero[50];
    int linha, coluna=0;
    char caractere;
    while (!feof(file)){
        fscanf(file,"%s%c", numero, &caractere);
        if(contLido == 1){
            linha = atoi(numero);
            contLido++;
        }
        else{
            coluna = atoi(numero);
            matriz[linha][coluna] = 1;
        }
        if(caractere=='\n'){
            contLido = 1;
        }
    }
    

}

void preenche_matriz_aleatoria(int tamanho, int matriz[tamanho][tamanho]){

    int i=0;//quantidade de 1's que serão colocados
    int linha=0;//linha em que os 1's serão colocados
    int coluna=0;
    gera_matriz_zerada(tamanho,matriz);//zera a matriz e preenche a diagonal principal com -1
    printf("Aguarde um estante! Estamos gerando a sua matriz...\n");
    while (linha<tamanho){//percorre as linhas da matriz
        srand((unsigned)time(NULL));
        i=rand()%5;//gera a quantidade de 1's no intervalo de 0 a 4, pois um número só pode ter 4 outros números adjacentes
        if(i>0){//se a quantidade gerada for maior que 0, preenche-se a matriz
            while(i>0){
                srand((unsigned)time(NULL));
                coluna=rand()%tamanho;//gera uma coluna aleatória para colocar o 1
                if(coluna != linha && matriz[linha][coluna]!=1){
                    //se não for da diagonal e se não existir 1 nela, 1 é inserido
                    matriz[linha][coluna]=1;
                    i--;
                }
            }
        }
        linha++;
    }
    
}
void print_matriz(int cont, int matriz[cont][cont]){
    for(int linha=0; linha<cont; linha++){
        for(int coluna=0; coluna<cont; coluna++){

            if(coluna==cont-1){
                printf("%d \n", matriz[linha][coluna]);
            }
            else{
                printf("%d ", matriz[linha][coluna]);
            }
        }
    }
}

int valida_arranjo(int cont, int matriz[cont][cont],char str[cont],int cont2){
    for(int i=0;i<cont;i++){
                for(int j=0;j<cont;j++){
                    if(matriz[i][j]==1){
                        if(str[i] == str[j]){
                            cont2++;
                            return cont2;
                        }
                    }
                }
            }
    return cont2;
}

void verifica_solucao(int cont, int matriz[cont][cont]){
    clock_t t; 
    int *num ;
    /* input é a string de entrada, e str
     * receberá cada permutação.
     */ 
    char input[3], str[cont] ;
    int n, r, i, j, k ;

    strcpy(input, "AV");

    /*printf("Entre com o r: ") ;
    scanf("%d", &r) ;*/
    r = cont;

    /* Aqui elimina-se caracteres repetidos na entrada.
     * Esse procedimento não faz parte do algoritmo, e
     * só é feito por questões práticas.
     */
    n = strlen(input) ;
    j = 0;
    str[0] = 0 ;
    for ( i = 0; i < n; i++ ) {
        if ( strchr(str, input[i]) == NULL ) {
            str[j] = input[i] ;
            j++ ;
            str[j] = 0 ;
        }
    }
    strcpy(input, str);
    n = strlen(input);

    /* Cria o nosso número. Ele é um vetor de
     * r+1 posições, sendo que a última é 
     * reservada para indicar quando todos os
     * números de tamanho r foram gerados. */
    num = (int *) calloc( (r+1), sizeof(int)) ;
    if ( num == NULL ) {
        perror("calloc") ;
        return;
    }

    /* Termina quando a última posição do vetor
     * for 1. */
    int cont2;
    int aux=0;
    t = clock(); //armazena tempo
    while ( num[r] == 0 ){
        for ( i = 0; i < n; i++ ) {
            cont2=0;
            /* processo de mapeamento. */
            for ( j = 0, k = r-1; j < r; j++ ) {
                str[k] = input[num[j]] ;
                k-- ;
            }
            /* Mostra o resultado. */
            str[r] = 0 ;
            
            //VETOR DAS CORES GERADO
            
            if(valida_arranjo(cont, matriz, str, cont2)==0){
                aux++;
                printf("Combinação [%s] atende a matriz.\n", str);
                num[r]=1;
                break;
            }
        
            num[0]++ ;
        }

        /* Muda de "casa" e lança os vai uns. */ 
        for ( i = 0; i < r; i++ ) {
            if ( num[i] == n ) {
                num[i] = 0 ;
                num[i+1]++ ;
            }
        }
    }
    if(aux==0){
        printf("------ Nenhuma solução encontrada ------\n");
    }
    t = clock()-t; //subtrai o tempo inicial do tempo final para gerar o tempo
    printf("--- Tempo de execucao: %lf ---\n", ((double)t)/((CLOCKS_PER_SEC/1000))); //conversão para double
}

int main() {
    
    FILE* file = NULL;
    int cont=1;
    char caractere;
    char nomeArquivo[50]={0};
    int primeiraVez=1; 
    
    printf("Digite o nome do arquivo desejado:\n");
    scanf("%[^\n]", nomeArquivo);

    file = fopen(nomeArquivo, "rt");
    if(file==NULL)
        printf("Arquivo nao encontrado\n");
    else
        printf("arquivo lido com sucesso!\n");
    cont+=conta_linhas(file);
    int matriz[cont][cont];
    fclose(file);  
    while (1){
        if(primeiraVez==5){
            break;
        }
        
        if(primeiraVez==1){
            printf("\n-=-=-=-=Printando matriz[%d][%d] gerada pelo ARQUIVO -=-=-=-=\n", cont, cont);
            preenche_matriz_com_arquivo(nomeArquivo, cont, matriz);
            print_matriz(cont, matriz);
            verifica_solucao(cont,matriz);
        }else{
            cont+=10;
            int matriz2[cont][cont];
            printf("\n-=-=-=-= Matriz Aleatória [%d][%d]-=-=-=-=\n", cont, cont);
            preenche_matriz_aleatoria(cont, matriz2);
            print_matriz(cont, matriz2);
            verifica_solucao(cont,matriz2);
        }
        primeiraVez++;
    }
    

    
    

    return 0 ;
} 
