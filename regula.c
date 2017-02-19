/*
Mustata Alexandru-Ionut
Grupa 331CB
Tema 1 LFA
*/

#include "regula.h"
#include <stdio.h>
#include <stdlib.h>

/*Functia intoarce un pointer catre o structura initializata
ce poate memora o regula.*/
struct regula* regula_new(){
	struct regula* aux = (struct regula*)malloc(sizeof(struct regula));
	aux->nrElementeCorp = 0;
	aux->sizeAlocatCorp = 1;
	aux->corp = (unsigned char*)malloc(sizeof(unsigned char));
	return aux;
}

/*Functia adauga un simbol in corpul regulii primite ca parametru.*/
void regula_add_simbol(struct regula* r, unsigned char simbol){
	if(r->nrElementeCorp == r->sizeAlocatCorp){
		r->sizeAlocatCorp *= 2;
		r->corp = (unsigned char*)realloc(r->corp, r->sizeAlocatCorp * sizeof(unsigned char));		
	}
	r->corp[r->nrElementeCorp] = simbol;
	r->nrElementeCorp++;
}

/*Functia verifica daca corpul regulii contine un simbol primit
ca parametru.*/
int regula_contains_simbol(struct regula* r, unsigned char simbol){
	int i = 0;
	for(i = 0; i < r->nrElementeCorp; i++){
		if(r->corp[i] == simbol){
			return 1;
		}
	}
	return 0;
}

/*Functia verifica daca corpul regulii este vid.*/
int regula_is_empty(struct regula* r){
	if(r->nrElementeCorp != 0){
		return 1;
	}
	return 0;
}

/*Functia seteaza carui neterminal ii este asociata regula.*/
void regula_set_nonterminal(struct regula* r, unsigned char neterminal){
	r->neterminal = neterminal;
}