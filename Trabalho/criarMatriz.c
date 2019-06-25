#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
   // Recuperar ordem da matriz.
   int ordem = atoi(argv[1]);

   // Recuperar nome do arquivo para salvar a matriz.
   char *nomeDoArquivo = argv[2];

   // Abrir arquivo para escrita.
   FILE *arquivo = fopen(nomeDoArquivo, "w+");

   // Escreve a ordem.
   fprintf(arquivo, "%d\n", ordem);
   for (int i = 0; i < ordem; i++) {
      for (int j = 0; j < ordem; j++) {
         if (j < ordem - 1)
            fprintf(arquivo, "%.2f:", 1.0);
	 else 
            fprintf(arquivo, "%.2f", 1.0);
      }
      fprintf(arquivo, "\n");
   }

   // Escreve os elementos.

   // Fecha arquivo.
   fclose(arquivo);

   return 0;
}
