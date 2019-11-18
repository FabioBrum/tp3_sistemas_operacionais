#include <stdio.h>
#include <stdlib.h>
#include "memoria.h"
#include "utils.h"

unsigned obter_pagina(unsigned addr, int s) {
	return (addr >> s);
}

void inicializa_tabela(TabelaPaginas *tabela, int paginaTamanho) {
    int i = 0;
    tabela->qtePaginas = (pow(2,32) / (paginaTamanho * pow(2, 10)));
    tabela->tamanhoDasPaginas = paginaTamanho;
    tabela->paginas = (Pagina *) malloc( tabela->qtePaginas * sizeof(Pagina) );

    for(i = 0; i < tabela->qtePaginas; i++) {
        tabela->paginas[i].frame = 0;
        tabela->paginas[i].flagLoaded = 0;
        tabela->paginas[i].flagDirty = 0;
        tabela->paginas[i].flagSegundaChance = 0;
        tabela->paginas[i].clockCarregado = 0;
        tabela->paginas[i].clockAcesso = -1;
    }
}

void inicializa_memoria(Memoria *memoria, int paginaTamanho, int memoriaTamanho) {
    int i = 0;

    memoria->memoriaTamanho = memoriaTamanho;
    memoria->qteFrames = memoriaTamanho / paginaTamanho;
    memoria->qteFramesOcupados = 0;
    memoria->paginasLidas = 0;
    memoria->paginasEscritas = 0;
    memoria->paginasASerEscritas = 0;
    memoria->clock = 0;
    memoria->frames = (Frame *) malloc(memoria->qteFrames * sizeof(Frame) );

    for(i = 0; i < memoria->qteFrames; i++) {
		memoria->frames[i].preenchido = 0;
	}
}

void carrega_pagina(Memoria *memoria, TabelaPaginas *tabela, unsigned pagina, unsigned frame) {
    tabela->paginas[pagina].frame = frame;
    tabela->paginas[pagina].flagDirty = 0;
    tabela->paginas[pagina].flagLoaded = 1;
    tabela->paginas[pagina].flagSegundaChance = 1;
	tabela->paginas[pagina].clockCarregado = memoria->clock;
    tabela->paginas[pagina].clockAcesso = memoria->clock;
    
	memoria->frames[frame].pagina = pagina;
	memoria->frames[frame].preenchido = 1;
	memoria->clock++;
	memoria->qteFramesOcupados++;
}

unsigned retorna_frame_livre(Memoria *memoria) {
    int i = 0;

    //se a memoria nao estiver cheia aloca o primeiro frame livre
    for(i = 0; i < memoria->qteFrames; i++) {
        if(memoria->frames[i].preenchido == 0)
            return i;
    }
}

void libera_frame_preenchido(Memoria *memoria, TabelaPaginas *tabela, unsigned frame) {
    unsigned pagina = memoria->frames[frame].pagina;

    if(tabela->paginas[pagina].flagDirty == 1) 
        memoria->paginasASerEscritas++;

    //atualizar informacoes da tabela
    tabela->paginas[pagina].flagLoaded = 0;
    tabela->paginas[pagina].flagDirty = 0;
    tabela->paginas[pagina].flagSegundaChance = 0;
    tabela->paginas[pagina].clockAcesso = 0;
    tabela->paginas[pagina].clockCarregado = -1;
    tabela->paginas[pagina].frame = 0;

    //atualizar informacoes da memoria
    memoria->frames[frame].preenchido = 0;
    memoria->frames[frame].pagina = 0;

    memoria->qteFramesOcupados--;
}