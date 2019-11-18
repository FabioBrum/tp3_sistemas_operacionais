#include <string.h>
#include "memoria.h"
#include "utils.h"

int main(int argc, char **argv) {
	FILE* arq = fopen(argv[2], "r");
	if(arq == NULL) {
		printf("ERRO: Arquivo nao encontrado %s\n", argv[2]);
		return 1;
	}

    char tecnica[7];
    strcpy(tecnica, argv[1]);
	int paginaTamanho = atoi(argv[3]);
	int memoriaTamanho = atoi(argv[4]);

	Memoria memoria;
	TabelaPaginas tabela;

    inicializa_memoria(&memoria, paginaTamanho, memoriaTamanho);
	inicializa_tabela(&tabela, paginaTamanho);

	printf("prompt> tp3virtual %s %s %s %s\n", argv[1], argv[2], argv[3], argv[4]);
	printf("Executando o simulador...\n");
    
    simulador(&memoria, &tabela, tecnica, arq);

	printf("Arquivo de entrada: %s\n", argv[2]);
	printf("Tamanho da memoria: %s KB\n", argv[4]);
	printf("Tamanho das paginas: %s KB\n", argv[3]);
	printf("Tecnica de reposicao: %s\n", argv[1]);
	printf("Paginas lidas: %d\n", memoria.paginasLidas);
	printf("Paginas escritas: %d\n", memoria.paginasASerEscritas);
	
    free(memoria.frames);
    free(tabela.paginas);

	fclose(arq);
    
	return 0;
}