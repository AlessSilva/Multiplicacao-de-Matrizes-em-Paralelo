#include <stdio.h>
#include <stdlib.h>

void lerMatriz(float **M, int ordem, FILE *arquivo){
	char a;
	for(int i=0; i<ordem; i++){
		M[i] = (float*) malloc(ordem * sizeof(float));
		for(int j=0; j<ordem; j++)
			fscanf(arquivo, "%f%c", &M[i][j], &a);
	}
}

void transposicao(float **M, int ordem){
	float **X = (float**)malloc (ordem * sizeof (float *));
	
	for(int i=0; i<ordem; i++){
		X[i] = (float*)malloc (ordem * sizeof (float *));
		for(int j=0; j<ordem; j++)
			X[i][j] = M[j][i];
	}
	for(int i=0; i<ordem; i++)
		for(int j=0; j<ordem; j++)
			M[i][j] = X[i][j];
		
}

void multiplicarMatriz(float **A, float **B, int ordem, FILE *arquivo){
	fprintf(arquivo, "%d\n", ordem);
	float acumula;
	
	for(int i=0; i<ordem; i++){
		for(int j=0; j<ordem; j++){
			acumula = 0;
			for(int k=0; k<ordem; k++){
				acumula += A[i][k]*B[j][k];
			}
			if (j<ordem-1)
				fprintf(arquivo, "%.2f:", acumula);
			else 
				fprintf(arquivo, "%.2f\n", acumula);
		}
	}
}

int main(int argc, char *argv[]){
	//Recebendo nome dos arquivos
	char *nomeArquivo1 = argv[1];
	char *nomeArquivo2 = argv[2];
	char *nomeArquivo3 = argv[3];
	
	//Abrindo arquivos para ler
	FILE *matriz1 = fopen(nomeArquivo1, "r");
	FILE *matriz2 = fopen(nomeArquivo2, "r");
	FILE *matriz3 = fopen(nomeArquivo3, "w+");
	
	//Lendo a ordem das matrízes e percorrendo a primeira linha dos dois arquivos
	char o[10];
	fscanf(matriz1, "%[^\n]", o);
	fscanf(matriz2, "%[^\n]", o);
	int ordem = atoi(o);

	float **A = (float**)malloc (ordem * sizeof (float *));
	float **B = (float**)malloc (ordem * sizeof (float *));	
	
	//Armazenando elementos do arquivo matriz1 e matriz2 em duas matrízes, A e B
	lerMatriz(A, ordem, matriz1);
	lerMatriz(B, ordem, matriz2);
	
	transposicao(B, ordem);
	
	//Multiplicação entre as matrízes A e B
	multiplicarMatriz(A, B, ordem, matriz3);
	
	//Fechando os arquivos
	fclose(matriz1);
	fclose(matriz2);
	fclose(matriz3);
	
	return 0;
}