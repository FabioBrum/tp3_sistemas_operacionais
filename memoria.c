#include <math.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include "memoria.h"
#include "utils.h"

void simulador(Memoria *memoria, TabelaPaginas *tabela, char *algoritmo, FILE *arq) {
    unsigned addr;
    char rw;
    unsigned s = 0, frame, index;

    // deslocando os bits
    unsigned tmp = tabela->tamanhoDasPaginas * 1024;
	while( tmp > 1 ) {
		tmp = tmp >> 1;
		s++;
	}

    while(!feof(arq)) {
        fscanf(arq, "%x %c", &addr, &rw);
        index = obter_pagina(addr, s);

        if(!feof(arq)) {
			if(tabela->paginas[index].flagCarregado == 1) { // caso a pagina ja esteja carregada, iremos acessar normalmente
                tabela->paginas[index].flagSegundaChance = 1;
				tabela->paginas[index].clockAcesso = memoria->clock;
			} else { // caso contrario, deveremos encontrar um quadro para ela
				memoria->paginasLidas++;

                // uma vez que a quantidade de letras do algoritmo é diferente, podemos
                // utilizar o tamanho da tecnica de reposição passada pra executar
                switch(strlen(algoritmo)) {
                    case 2: // CASO 1: 2A - SEGUNDA CHANCE - 
                        frame = segunda_chance(memoria, tabela);
                        break;
                    case 3: // CASO 2: LRU
                        frame = lru(memoria, tabela);
                        break;
                    case 4: // CASO 3: FIFO 
                        frame = fifo(memoria, tabela);
                        break;
                    case 6: // CASO 4: RANDOM
	                    frame = aleatorio(memoria);
                        break;
                    default:
                        printf("Tecnica de respoicao nao conhecida");
                }

                if(memoria->frames[frame].flagPreenchido)
				    libera_frame_flagPreenchido(memoria, tabela, frame);
        
				carrega_pagina(memoria, tabela, index, frame);
			}
            if(rw == 'W') 
                tabela->paginas[index].flagSuja = 1;
		}
    }
}

unsigned fifo(Memoria *memoria, TabelaPaginas *tabela) {
    unsigned menorTempo = UINT_MAX, frameVitima = 0, idx;
    int i = 0;
    
    // se a memoria nao estiver cheia, retornaremos o primeiro frame encontrado
    if(memoria->qteFramesOcupados < memoria->qteFrames)
        return retorna_frame_livre(memoria);

    for(i = 0; i < memoria->qteFrames; i++) {
        idx = memoria->frames[i].pagina;
        if(tabela->paginas[idx].clockCarregado < menorTempo) {
            frameVitima = i;
            menorTempo = tabela->paginas[idx].clockCarregado;
        }
    }
    
    return frameVitima;
}

unsigned segunda_chance(Memoria *memoria, TabelaPaginas *tabela) {
    unsigned menorTempo = UINT_MAX, frameVitima = 0, idx;
    int i = 0;
    
    // se a memoria nao estiver cheia, retornaremos o primeiro frame encontrado
    if(memoria->qteFramesOcupados < memoria->qteFrames)
        return retorna_frame_livre(memoria);

    for(i = 0; i < memoria->qteFrames; i++) {
        idx = memoria->frames[i].pagina;
        if(tabela->paginas[idx].clockCarregado < menorTempo) {
            if(tabela->paginas[idx].flagSegundaChance == 0) {
                frameVitima = i;
                menorTempo = tabela->paginas[idx].clockCarregado;
            } else {
                tabela->paginas[idx].flagSegundaChance = 0;
                tabela->paginas[idx].clockCarregado = memoria->clock; // faz parecer que a pagina foi recém carregada
                i = 0;
            }
        }
    }
    
    return frameVitima;
}

unsigned lru(Memoria *memoria, TabelaPaginas *tabela) {
    unsigned menorTempo = UINT_MAX, frameVitima = 0, idx;
	int i = 0;

    // se a memoria nao estiver cheia, retornaremos o primeiro frame encontrado
    if(memoria->qteFramesOcupados < memoria->qteFrames) 
        return retorna_frame_livre(memoria);

    for(i = 0; i < memoria->qteFrames; i++) {
        idx = memoria->frames[i].pagina;
        if(tabela->paginas[idx].clockAcesso < menorTempo) {
            frameVitima = i;
            menorTempo = tabela->paginas[idx].clockAcesso;
        }
    }
    
    return frameVitima;
}

unsigned aleatorio(Memoria *memoria) {
    srand(time(NULL));
	return (rand() % memoria->qteFrames);
}