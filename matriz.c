#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE* file = NULL;
    FILE* file2 = NULL;
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
    fclose(file);

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
    int linha, coluna=0;

    file2 = fopen("entrada_I.txt", "rt");
    while(!feof(file2)){
        caractere = getc(file2);//pega o caracter do arquivo
        if(contLido==1 && caractere!='\n' && caractere!='\0'){
            linha=(int)caractere;
            contLido++;
        }else{
            if(caractere!='\n' && caractere!='\0')
                coluna=(int)caractere;
            matriz[linha][coluna]=1;
            if(caractere=='\n'){
                contLido=1;
            }
        }
    }
    fclose(file2);

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

    return 0;
}
