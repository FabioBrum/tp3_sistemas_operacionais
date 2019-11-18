#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned obter_pagina(unsigned addr, int s);

void inicializa_tabela(TabelaPaginas *tabela, int paginaTamanho);

void inicializa_memoria(Memoria *memoria, int paginaTamanho, int memoriaTamanho);

void carrega_pagina(Memoria *memoria, TabelaPaginas *tabela, unsigned pagina, unsigned frame);

unsigned retorna_frame_livre(Memoria *memoria);

void libera_frame_preenchido(Memoria *memoria, TabelaPaginas *tabela, unsigned frame);