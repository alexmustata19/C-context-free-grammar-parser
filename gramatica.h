/*
Mustata Alexandru-Ionut
Grupa 331CB
Tema 1 LFA
*/

#include "set_reguli.h"
#include "alfabet.h"

struct gramatica{
	struct alfabet* v;
	struct alfabet* sigma;
	struct set_reguli* reguli;
	unsigned char start;
};

struct gramatica* gramatica_new();
void gramatica_add_simbol_sigma(struct gramatica*, unsigned char);
void gramatica_add_simbol_v(struct gramatica*, unsigned char);
void gramatica_add_regula(struct gramatica*, struct regula*);
void gramatica_set_start(struct gramatica*, unsigned char);
void gramatica_print(struct gramatica*);
void sigma_inclus_in_v(struct gramatica*);
void terminalii_din_v_sunt_in_sigma(struct gramatica* g);
void verificare_simbol_de_start(struct gramatica* g);
void verificare_neterminali_reguli(struct gramatica* g);
void verificare_corp_reguli(struct gramatica* g);
void gramatica_verifica_corectitudine(struct gramatica*);
int gramatica_contine_sirul_vid(struct gramatica*);
void gramatica_terminali_nefolositori(struct gramatica*, int);