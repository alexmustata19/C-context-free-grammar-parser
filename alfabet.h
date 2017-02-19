/*
Mustata Alexandru-Ionut
Grupa 331CB
Tema 1 LFA
*/

struct alfabet{
	unsigned char* vector;
	int nrElemente;
	int sizeAlocat;
};

struct alfabet* alfabet_new();
void alfabet_add(struct alfabet*, unsigned char);
int alfabet_contains(struct alfabet*, unsigned char);
int alfabet_is_empty(struct alfabet*);