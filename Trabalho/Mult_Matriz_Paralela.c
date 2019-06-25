//         TRABALHO DE SISTEMAS OPERACIONAIS
// NOME : Alessandro Souza Silva  MATRICULA : 399941

// MÚLTIPLICAÇÃO DE MATRIZES - CÓDIGO PARALELO

#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h> //Biblioteca para descobrir o n° de núcleos de processamento
#include <pthread.h> //Biblioteca para utilização de threads

//Variáveis globais
int num_nucleos;

int ordem;

float *vetorA;
float *vetorB;
float *vetorC;

int a = 0;

pthread_mutex_t cadeado; //Criando um mutex

//Função que multiplica certo intervalo de linhas da matriz
void *Multiplica ( void *p){

	int linha_inicial;
	int linha_final;

	// threads[n] -> linha inicial : ( n * ordem ) / num_nucleos
	//				 linha final : ( n+1 * ordem ) / num_nucleos

	//Inicio da região crítica
	pthread_mutex_lock(&cadeado);

	linha_inicial = a;
	a++;

	pthread_mutex_unlock(&cadeado);
	//Final da região crítica

	linha_final = linha_inicial +1;
	linha_inicial = (linha_inicial * ordem)/num_nucleos;
	linha_final = (linha_final * ordem)/num_nucleos;

	int A,L,E;
	float aux;
	for( A = linha_inicial; A < linha_final; A++){

		for( L = 0; L < ordem ; L++){

            aux = 0;

			for ( E = 0; E < ordem; E++){

				aux += (vetorA[(A * ordem) + E]) * (vetorB[(L * ordem) + E]);

			}

            vetorC[(A * ordem) + L] = aux;

		}

	}

}


int main( int argc, char *argv[]){

	// Abrindo os arquivos
	FILE *file_A = fopen(argv[1],"r");
	FILE *file_B = fopen(argv[2],"r");
    FILE *file_C = fopen(argv[3],"w");

    //Descobrindo o número de núcleos de processamento
    num_nucleos = get_nprocs();

    //Lendo a ordem da matriz
    fscanf(file_A,"%d\n",&ordem);
    fscanf(file_B,"%d\n",&ordem);

    //Alocando vetores em vez de matrizes
    vetorA = malloc(sizeof(float)*ordem*ordem);
    vetorB = malloc(sizeof(float)*ordem*ordem);
    vetorC = malloc(sizeof(float)*ordem*ordem);

    // matriz[i][j] == vetor[ (i * ordem) + j]

    int i, j;

     //Lendo as matrizes
    for( i = 0; i < ordem; i++){
         for( j = 0; j < ordem; j++){

           fscanf(file_A,"%f:",&vetorA[(i*ordem) + j]);
           fscanf(file_B,"%f:",&vetorB[(j*ordem) + i]); //Lendo matriz transporte

        }
    }

    //Criando threads igual ao número de núcleos
    pthread_t threads[num_nucleos];


    //Fazendo cada thread executar a função de multiplicar
    for( i = 0; i < num_nucleos; i++){

    	pthread_create(&threads[i],NULL,Multiplica,NULL);

    }

    
    //Escrevendo a ordem no arquivo do resultado
    fprintf(file_C,"%d\n",ordem);


    //Verificando se as threads já encerraram
    for( i = 0; i < num_nucleos; i++){

		pthread_join(threads[i],NULL);
    }

    //Escrita do resultado da multiplicação no arquivo
    for( i = 0; i < ordem; i++){
         for( j = 0; j < ordem; j++){

           if( j < ordem-1 ) {
                 fprintf(file_C,"%0.1f:",vetorC[(i * ordem) + j]);
            }else{
                 fprintf(file_C,"%0.1f\n",vetorC[(i * ordem) + j]);
            }

        }
    }

    //Fechando os arquivos
    fclose(file_A);
    fclose(file_B);
    fclose(file_C);
    
    return 0;
}




