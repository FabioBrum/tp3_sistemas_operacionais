
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned frame;
    int flagCarregado;
    int flagSuja;
    int flagSegundaChance;
    unsigned clockCarregado;
    long int clockAcesso;
} Pagina;

typedef struct {
	int flagPreenchido;
	unsigned	pagina;
} Frame;

typedef struct {
    Pagina  *paginas;
    unsigned   qtePaginas;
    unsigned    tamanhoDasPaginas;
} TabelaPaginas;

typedef struct {
    unsigned memoriaTamanho;
    unsigned qteFrames;
    unsigned qteFramesOcupados;
    unsigned paginasLidas;
    unsigned paginasASerEscritas;
    unsigned clock;
    Frame *frames;
} Memoria;

void simulador(Memoria *memoria, TabelaPaginas *tabela, char *algoritmo, FILE *arq);

unsigned segunda_chance(Memoria *memoria, TabelaPaginas *tabela);

unsigned fifo(Memoria *memoria, TabelaPaginas *tabela);

unsigned lru(Memoria *memoria, TabelaPaginas *tabela);

unsigned aleatorio(Memoria *memoria);