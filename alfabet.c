/*
Mustata Alexandru-Ionut
Grupa 331CB
Tema 1 LFA
*/

#include "alfabet.h"
#include <stdio.h>
#include <stdlib.h>

/*Functia intoarce pointer catre o structura de alfabet initializata.*/
struct alfabet* alfabet_new(){
	struct alfabet* aux = (struct alfabet*)malloc(sizeof(struct alfabet));
	aux->nrElemente = 0;
	aux->sizeAlocat = 1;
	aux->vector = (unsigned char*)malloc(sizeof(unsigned char));
	return aux;
}

/*Functia aduaga intr-un alfabet un simbol transmis ca parametru.*/
void alfabet_add(struct alfabet* ab, unsigned char simbol){
	if(ab->nrElemente == ab->sizeAlocat){
		ab->sizeAlocat *= 2;
		ab->vector = (unsigned char*)realloc(ab->vector, ab->sizeAlocat * sizeof(unsigned char*));
	}
	ab->vector[ab->nrElemente] = simbol;
	ab->nrElemente++;
}

/*Functia verifica daca un simbol apartine alfabetului primit ca parametru.*/
int alfabet_contains(struct alfabet* ab, unsigned char simbol){
	int i = 0;
	for(i = 0; i < ab->nrElemente; i++){
		if(ab->vector[i] == simbol){
			return 1;
		}
	}
	return 0;
}

/*Functia verifica daca alfabetul este vid.*/
int alfabet_is_empty(struct alfabet* ab){
	if(ab->nrElemente != 0){
		return 1;
	}
	return 0;
}