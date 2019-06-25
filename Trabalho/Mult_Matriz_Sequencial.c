//         TRABALHO DE SISTEMAS OPERACIONAIS
// NOME : Alessandro Souza Silva  MATRICULA : 399941

// MÚLTIPLICAÇÃO DE MATRIZES - CÓDIGO SEQUENCIAL

#include <stdio.h>
#include <stdlib.h>

 // Função main -> Entrada : nome do arquivo com a primeira matriz,
 //                          nome do arquivo com a segunda matriz,
 //                          nome do arquivo com o resultado da multiplicação entre matrizes

int main( int argc, char *argv[]){

    // Abrindo os arquivos
    FILE *file_A = fopen(argv[1],"r");
    FILE *file_B = fopen(argv[2],"r");
    FILE *file_C = fopen(argv[3],"w");

    int ordem;

    //Lendo a ordem da matriz
    fscanf(file_A,"%d\n",&ordem);
    fscanf(file_B,"%d\n",&ordem);

    //Alocando vetores em vez de matrizes
    float *vetorA = malloc(sizeof(float)*ordem*ordem);
    float *vetorB = malloc(sizeof(float)*ordem*ordem);

    // matriz[i][j] == vetor[ (i * ordem) + j]

    int i, j, k;

    //Lendo as matrizes
    for( i = 0; i < ordem; i++){
         for( j = 0; j < ordem; j++){

           fscanf(file_A,"%f:",&vetorA[(i*ordem) + j]);
           fscanf(file_B,"%f:",&vetorB[(j*ordem) + i]); //Lendo matriz transporte

        }
    }

    //Escrevendo a ordem no arquivo do resultado
    fprintf(file_C,"%d\n",ordem);

    float aux;

    //Multiplicação e escrita no arquivo resultado
    for(i = 0; i < ordem; i++){

         for( j = 0; j < ordem; j++){

            aux =  0;

            for ( k = 0; k < ordem ; k++ ){

                    aux += (vetorA[(i * ordem) + k]) * (vetorB[(j * ordem) + k]);

            }

            if( j < ordem-1 ) {
                 fprintf(file_C,"%0.1f:",aux);
            }else{
                 fprintf(file_C,"%0.1f\n",aux);
            }

        } 

    }

    //Fechando os arquivos
    fclose(file_A);
    fclose(file_B);
    fclose(file_C);

    return 0;
}