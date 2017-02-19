/*
Mustata Alexandru-Ionut
Grupa 331CB
Tema 1 LFA
*/

#include "regula.h"
struct set_reguli{
	struct regula* reguli;
	int nrReguli;
	int sizeAlocat;
};

struct set_reguli* set_reguli_new();
void set_reguli_add(struct set_reguli*, struct regula*);