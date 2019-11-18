
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
    Pagina  *paginas;         //vetor de paginas
    unsigned   qtePaginas;       //tamanho do vetor
    unsigned    tamanhoDasPaginas;   //tamanho das paginas em kb
} TabelaPaginas;

typedef struct {
    unsigned memoriaTamanho;        //tamanho da memoria em kb
    unsigned qteFrames;			//numero de frames total da memoria
    unsigned qteFramesOcupados;    //quantidade de frames flagPreenchidos no momento
    unsigned paginasLidas;          //numero de paginas lidas
    unsigned paginasEscritas;       //numero de paginas que foram escritas
    unsigned paginasASerEscritas;   //paginas flagSujas que devem ser regravadas no disco
    unsigned clock;               //contador de acessos da memoria
    Frame *frames;				//frames da memoria
} Memoria;

void inicializa_tabela(TabelaPaginas *tabela, int paginaTamanho);

void inicializa_memoria(Memoria *memoria, int paginaTamanho, int memoriaTamanho);

void simulador(Memoria *memoria, TabelaPaginas *tabela, char *algoritmo, FILE *arq);

void carrega_pagina(Memoria *memoria, TabelaPaginas *tabela, unsigned pagina, unsigned frame);

unsigned segunda_chance(Memoria *memoria, TabelaPaginas *tabela);

unsigned retorna_frame_livre(Memoria *memoria);

unsigned fifo(Memoria *memoria, TabelaPaginas *tabela);

unsigned lru(Memoria *memoria, TabelaPaginas *tabela);

void libera_frame_flagPreenchido(Memoria *memoria, TabelaPaginas *tabela, unsigned frame);