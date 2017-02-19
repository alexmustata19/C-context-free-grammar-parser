/*
Mustata Alexandru-Ionut
Grupa 331CB
Tema 1 LFA
*/

struct regula{
	unsigned char neterminal;
	unsigned char* corp;
	int nrElementeCorp;
	int sizeAlocatCorp;
};

struct regula* regula_new();
void regula_add_simbol(struct regula*, unsigned char);
int regula_contains_simbol(struct regula*, unsigned char);
int regula_is_empty(struct regula*);
void regula_set_nonterminal(struct regula* , unsigned char);