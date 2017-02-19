/*
Mustata Alexandru-Ionut
Grupa 331CB
Tema 1 LFA
*/

#include <stdio.h>
#include <stdlib.h>
#include "set_reguli.h"

/*Functia intoarce un pointer catre o structura initializata ce
poate memora un set de reguli.*/
struct set_reguli* set_reguli_new(){
	struct set_reguli* aux = (struct set_reguli*)malloc(sizeof(struct set_reguli));
	aux->nrReguli = 0;
	aux->sizeAlocat = 1;
	aux->reguli = (struct regula*)malloc(sizeof(struct regula));
	return aux;
}

/*Functia adauga o noua regula in setul de reguli.*/
void set_reguli_add(struct set_reguli* set, struct regula* r){
	if(set->nrReguli == set->sizeAlocat){
		set->sizeAlocat *= 2;
		set->reguli = (struct regula*)realloc(set->reguli, set->sizeAlocat * sizeof(struct regula));
	}
	set->reguli[set->nrReguli] = *r;
	set->nrReguli++;
}