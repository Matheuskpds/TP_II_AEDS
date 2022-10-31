#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/* Tamanho máximo da string de entrada. */
#define MAX 250

int main() {
    
    FILE* file = NULL;
    char caractere;
    int cont=1;

    file = fopen("entrada_I.txt", "rt");
    if(file==NULL)
        printf("Arquivo nao encontrado\n");
    else
        printf("arquivo lido com sucesso!\n");

    for (char c = getc(file); c != EOF; c = getc(file)){
        if (c == '\n') // Increment count if this character is newline
            cont = cont + 1;
    }

    int matriz[cont][cont];
    for(int linha=0; linha<cont; linha++){
        for(int coluna=0; coluna<cont; coluna++){
            if(linha==coluna){
                matriz[linha][coluna] = -1;
            }
            else{
                matriz[linha][coluna] = 0;
            }
        }
    }
    //pegar o primeiro caracter o arquivo e associar ele à linha da matriz.
    //pega o outro caracter e asscia ele à coluna da matriz e tranforma o valor em 1.
    int contLido=1;
    char numero[50];
    int linha, coluna=0;
    file = fopen("arquivo.txt", "rt");
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
    for(int linha=0; linha<cont; linha++){
        for(int coluna=0; coluna<cont; coluna++){
            //printf("%d", matriz[linha][coluna]);
            if(coluna==cont-1){
                printf("%d \n", matriz[linha][coluna]);
            }
            else{
                printf("%d ", matriz[linha][coluna]);
            }
        }
    }
    
    //ALGORITMO DE CRIAÇÃO DOS VETORES!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    /* Nosso número na base n. Ele é um vetor
     * de n+1 posições representando um número
     * na base n.
     */
    int *num ;
    /* input é a string de entrada, e str
     * receberá cada permutação.
     */ 
    char input[MAX], str[MAX] ;
    int n, r, i, j, k ;

    printf("Entre com o conjunto inicial: ") ;
    scanf("%s", input) ;

    printf("Entre com o r: ") ;
    scanf("%d", &r) ;

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
        return -1;
    }

    /* Termina quando a última posição do vetor
     * for 1. */
    int cont2;
    while ( num[r] == 0 ) {
        cont2=0;
        for ( i = 0; i < n; i++ ) {
            /* processo de mapeamento. */
            for ( j = 0, k = r-1; j < r; j++ ) {
                str[k] = input[num[j]] ;
                k-- ;
            }
            /* Mostra o resultado. */
            str[r] = 0 ;
            //printf("%s\n", str)
            
            //VETOR DAS CORES GERADO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    if(str[i]==str[j] && matriz[i][j]==1){
                       return;
                    }
                }
            }
            printf("Combinação [%s] atende a matriz.");
            /*
            for(int i=0; i < strlen(str); i++){
                //str[i] == A ....apenas um exemplo em que o vetor começa com a cor A
                for(int j=i; j<linha; j++){
                    if(matriz[i][j]==1){ //a coluna que for adjacente
                        if(str[i]==str[j+1]){   //str[i]=A ==  str[j]
                            cont2++;
                        }
                    }
                }
            }
            */
            if(cont2==1){
                printf("%s\n", str);
            }

            /* incrementa o algarismo menos significativo. */
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
    //printf("Timestamp: %d\n",(int)time(NULL));

    return 0 ;
}   
