/*
Mustata Alexandru-Ionut
Grupa 331CB
Tema 1 LFA
*/

#include <stdio.h>
#include <stdlib.h>
#include "gramatica.h"
#include <ctype.h>

/*Functia intoarce un pointer catre o structura ce poate memora
componentele unei gramatici independente de context.*/
struct gramatica* gramatica_new(){
	struct gramatica* aux = (struct gramatica*)malloc(sizeof(struct gramatica));
	aux->v = alfabet_new();
	aux->sigma = alfabet_new();
	aux->reguli = set_reguli_new();
	return aux;
}

/*Functia adauga un nou simbol in multimea de terminali a gramaticii.*/
void gramatica_add_simbol_sigma(struct gramatica* g, unsigned char simbol){
	alfabet_add(g->sigma, simbol);
}

/*Functia adauga un nou simbol in multimea de terminali si neterminali
a gramaticii.*/
void gramatica_add_simbol_v(struct gramatica* g, unsigned char simbol){
	alfabet_add(g->v, simbol);
}

/*Functia adauga o noua regula in gramatica.*/
void gramatica_add_regula(struct gramatica* g, struct regula* r){
	set_reguli_add(g->reguli, r);
}

/*Functia seteaza simbolul de start al gramaticii.*/
void gramatica_set_start(struct gramatica* g, unsigned char start){
	g->start = start;
}

/*Functia afiseaza la consola structura gramaticii primite
ca parametru.*/
void gramatica_print(struct gramatica* g){
	int i,j;
	printf("Start: %c\n", g->start);
	printf("V:\n");
	for(i = 0; i<g->v->nrElemente; i++){
		printf("%c ",g->v->vector[i]);
	}
	printf("\n");
	printf("Sigma:\n");
	for(i = 0; i<g->sigma->nrElemente; i++){
		printf("%c ",g->sigma->vector[i]);
	}
	printf("\n");
	printf("Reguli:\n");
	for(i = 0; i<g->reguli->nrReguli; i++){
		printf("%c -> ",g->reguli->reguli[i].neterminal);
		for(j = 0; j<g->reguli->reguli[i].nrElementeCorp; j++){
			printf("%c",g->reguli->reguli[i].corp[j]);
		}
		printf("\n");
	}
	printf("\n");
}

/*Functia verifica daca alfabetul este inclus in multimea de
terminali si neterminali pentru o gramatica primita ca parametru.*/
void sigma_inclus_in_v(struct gramatica* g){
	int i=0;
	for(i=0; i<g->sigma->nrElemente; i++){
		if(0 == alfabet_contains(g->v, g->sigma->vector[i])){
			fprintf(stderr, "Semantic error\n");
			exit(0);
		}
	}
}

/*Functia verifica daca terminalii din multimea de terminali si
neterminali sunt prezenti in alfabetul gramaticii.*/
void terminalii_din_v_sunt_in_sigma(struct gramatica* g){
	int i = 0;
	for(i=0; i<g->v->nrElemente; i++){
		if(isupper(g->v->vector[i])){
			continue;
		}
		if(0 == alfabet_contains(g->sigma, g->v->vector[i])){
			fprintf(stderr, "Semantic error\n");
			exit(0);
		}
	}
}

/*Functia verifica pentru o gramatica daca simbolul de start
se afla in multimea de terminali si neterminali.*/
void verificare_simbol_de_start(struct gramatica* g){
	if(0 == alfabet_contains(g->v, g->start)){
		fprintf(stderr, "Semantic error\n");
		exit(0);
	}
}

/*Functia verifica daca fiecare neterminal ce are asociat o
regula este prezent in multimea de terminali si neterminali.*/
void verificare_neterminali_reguli(struct gramatica* g){
	int i = 0;
	struct alfabet* neterminali = alfabet_new();
	for(i=0; i<g->v->nrElemente; i++){
		if(isupper(g->v->vector[i])){
			alfabet_add(neterminali, g->v->vector[i]);
		}
	}
	for(i=0; i<g->reguli->nrReguli; i++){
		if(0 == alfabet_contains(neterminali, g->reguli->reguli[i].neterminal)){
			fprintf(stderr, "Semantic error\n");
			exit(0);
		}
	}
}

/*Functia verifica daca fiecare simbol din corpul unei reguli
este prezent in multimea de terminali si neterminali.*/
void verificare_corp_reguli(struct gramatica* g){
	int i,j;
	for(i=0; i<g->reguli->nrReguli; i++){
		if(g->reguli->reguli[i].nrElementeCorp == 1 && 
			'e' == g->reguli->reguli[i].corp[0]){
			continue;
		}
		for(j=0; j<g->reguli->reguli[i].nrElementeCorp; j++){
			if(0 == alfabet_contains(g->v, g->reguli->reguli[i].corp[j])){
				fprintf(stderr, "Semantic error\n");
				exit(0);
			}
		}
	}
}

/*Functia verifica corectitudinea unei gramatici. Daca gramatica
nu este corect se afiseaza o eroare la stderr si se opreste executia
programului.*/
void gramatica_verifica_corectitudine(struct gramatica* g){
	sigma_inclus_in_v(g);
	terminalii_din_v_sunt_in_sigma(g);
	verificare_simbol_de_start(g);
	verificare_neterminali_reguli(g);
	verificare_corp_reguli(g);
}

/*Functia verifica daca limbajul genereat de gramatica primita ca
parametru contine sirul vid.*/
int gramatica_contine_sirul_vid(struct gramatica* g){
	/*Se extrag regulile care genereaza sirul vid si regulile
	care inlocuiesc un neterminal cu unul sau mai multi neterminali.*/
	struct set_reguli* reguliReduse = set_reguli_new();
	int i, j, ok;
	for(i = 0; i < g->reguli->nrReguli; i++){
		ok = 1;
		for(j = 0; j < g->reguli->reguli[i].nrElementeCorp; j++){
			if(!isupper(g->reguli->reguli[i].corp[j])
				&& 'e' != g->reguli->reguli[i].corp[j]){
				ok = 0;
				break;
			}
		}
		if(ok == 1){
			set_reguli_add(reguliReduse, &(g->reguli->reguli[i]) );
		}
	}

	/*Daca nu exista astfel de reguli gramatica nu genereaza sirul vid.*/
	if(reguliReduse->nrReguli == 0){
		return 0;
	}

	/*Se alcatuieste multimea formata din neterminali.*/
	struct alfabet* neterminali = alfabet_new();
	for(i = 0; i < g->v->nrElemente; i++){
		if(isupper(g->v->vector[i])){
			alfabet_add(neterminali, g->v->vector[i]);
		}
	}

	/*Se initializeaza un vector care va memora ce neterminali
	pot genera sirul vid.*/
	int contineE[26];
	for(i = 0; i < 26; i++){
		contineE[i] = 0;
	}

	int marcat = 1;
	while(marcat == 1){
		marcat = 0;
		/*Neterminalii ce au asociate reguli ce genereaza sirul vid
		sau contin numai terminali ce genereaza sirul vid vor genera
		si ei sirul vid.*/
		for(i = 0; i < reguliReduse->nrReguli; i++){
			unsigned char neterm = reguliReduse->reguli[i].neterminal;
			int index = neterm-65;
			if(contineE[index] == 1){
				continue;
			}
			if(reguliReduse->reguli[i].nrElementeCorp == 1 && 
				reguliReduse->reguli[i].corp[0] == 'e'){
				marcat = 1;
				contineE[index] = 1;
			}else{
				int suma = 0;
				for(j = 0; j < reguliReduse->reguli[i].nrElementeCorp; j++){
					unsigned char aux1 = reguliReduse->reguli[i].corp[j];
					int aux2 = aux1-65;
					suma += contineE[aux2];
				}
				if(suma == reguliReduse->reguli[i].nrElementeCorp){
					marcat = 1;
					contineE[index] = 1;
				}
			}
		}
	}

	/*Se intoarce faptul daca sirul vid poate fi generat
	pornind din simbolul de start al gramaticii.*/
	i = g->start - 65;
	return contineE[i];
}

/*Functia verifica daca limbajul generat de gramatica este vid in cazul in 
care verificareVida != 0, altfel afiseaza terminalii inutili din gramatica.
Functia rezolva aceste doua probleme, deoarece algoritmul de rezolvare este 
acelasi.*/
void gramatica_terminali_nefolositori(struct gramatica* g, int verificareVida){
	/*Se alcatuieste multimea de neterminali.*/
	int i, j;
	struct alfabet* neterminali = alfabet_new();
	for(i = 0; i < g->v->nrElemente; i++){
		if(isupper(g->v->vector[i])){
			alfabet_add(neterminali, g->v->vector[i]);
		}
	}

	/*Pentru fiecare neterminal se memoreaza daca acesta
	poate sau nu sa genereze cuvinte.*/
	int genereazaCuvant[26];
	for(i = 0; i < 26; i++){
		genereazaCuvant[i] = 0;
	}

	/*Pentru fiecare regula se memoreaza numarul de neterminali 
	din corpul acesteia.*/
	int* numarNeterminaliDinRegula = (int*)malloc(g->reguli->nrReguli * sizeof(int));
	for(i = 0; i < g->reguli->nrReguli; i++){
		numarNeterminaliDinRegula[i] = 0;
	}

	/*Neterminalii ce au asociate reguli ce nu contin neterminali
	pot genera direct cuvinte.*/
	for(i = 0; i < g->reguli->nrReguli; i++){
		for(j = 0; j < g->reguli->reguli[i].nrElementeCorp; j++){
			if(isupper(g->reguli->reguli[i].corp[j])){
				numarNeterminaliDinRegula[i]++;
			}
		}
		unsigned char neterm = g->reguli->reguli[i].neterminal;
		int index = neterm-65;
		if(numarNeterminaliDinRegula[i] == 0){
			genereazaCuvant[index] = 1;
		}
	}

	int marcat = 1;
	while(marcat == 1){
		marcat = 0;
		/*Fiecare neterminal ce are asociata o regula cu neterminali
		care genereaza toti cuvinte va generea la randul sau cuvinte.*/
		for(i = 0; i < g->reguli->nrReguli; i++){
			int suma = 0;
			unsigned char aux1 = g->reguli->reguli[i].neterminal;
			int aux2 = aux1 - 65;
			if(genereazaCuvant[aux2] == 1){
				continue;
			}
			for(j = 0; j < g->reguli->reguli[i].nrElementeCorp; j++){
				unsigned char simbol = g->reguli->reguli[i].corp[j];
				if(isupper(simbol)){
					suma += genereazaCuvant[(int)(simbol-65)];
				}
			}
			if(suma == numarNeterminaliDinRegula[i]){
				marcat = 1;
				genereazaCuvant[aux2] = 1;
			}
		}
	}

	if(verificareVida == 0){
		/*Afisarea tuturor neterminalilor inutili.*/
		for(i = 0; i < neterminali->nrElemente; i++){
			int index = neterminali->vector[i] - 65;
			if(genereazaCuvant[index] == 0){
				printf("%c\n", neterminali->vector[i]);
			}
		}
	}else{
		/*Raspunderea la intrebarea daca limbajul
		generat de gramatica este vid.*/
		i = g->start - 65;
		if(genereazaCuvant[i] == 1){
			printf("No\n");
		}else{
			printf("Yes\n");
		}
	}
	return;
}