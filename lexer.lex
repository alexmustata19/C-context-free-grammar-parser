%top{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gramatica.h"

#define lastchar yytext[yyleng - 1]

#define YY_BUF_SIZE 66000

struct gramatica* g;
struct regula* r;

}

%s CITIRE_N_TERMI CITIRE_N_TERM CITIRE_N_TERM_SEMN CITIRE_VIRGULA_1 CITIRE_ALFABET CITIRE_TERMINAL CITIRE_TERMINAL_SEMN CITIRE_VIRGULA_2 CITIRE_REGULI CITIRE_REGULA CITIRE_NETERMINAL_REGULA CITIRE_VIRGULA_DIN_REGULA CITIRE_CORP_REGULA CITIRE_PARANTEZA_INCHISA_REGULA CITIRE_CORP_REGULA_NEVID CITIRE_SEMN_REGULA CITIRE_VIRGULA_3 CITIRE_SIMBOL_START CITIRE_PARANTEZA_INCHISA CITIRE_SFARSIT CITIRE_REGULA_NEAPARAT CITIRE_TERMINAL_NEAPARAT

digit [0-9]
lower-case-letter [a-d]|[f-z]
other "'"|"-"|"="|"["|"]"|";"|"`"|"\\"|"."|"/"|"~"|"!"|"@"|"#"|"$"|"%"|"^"|"&"|"*"|"_"|"+"|":"|"\""|"\|"|"<"|">"|"?"
terminal {lower-case-letter}|{digit}|{other}
upper-case-letter [A-Z]
anything {digit}|{lower-case-letter}|"e"|{upper-case-letter}|{other}|"{"|"}"|"("|")"|","
nonterminal {upper-case-letter}

%option noinput
%option nounput
%option noyymore

%%

[ \t\r\n]

<INITIAL>{
	"(" {
		g = gramatica_new();
		BEGIN(CITIRE_N_TERMI);
	}
	{anything} {
		fprintf(stderr, "Syntax error\n");
		exit(0);
	}
}
<CITIRE_N_TERMI>{
	"{" {
		BEGIN(CITIRE_N_TERM);
	}
	{anything} {
		fprintf(stderr, "Syntax error\n");
		exit(0);
	}
}
<CITIRE_N_TERM>{
	{nonterminal} {
		gramatica_add_simbol_v(g, lastchar);
		BEGIN(CITIRE_N_TERM_SEMN);
	}
	{terminal} {
		gramatica_add_simbol_v(g, lastchar);
		BEGIN(CITIRE_N_TERM_SEMN);
	}
	{anything} {
		fprintf(stderr, "Syntax error\n");
		exit(0);
	}
}
<CITIRE_N_TERM_SEMN>{
	"," {
		BEGIN(CITIRE_N_TERM);
	}
	"}" {
		BEGIN(CITIRE_VIRGULA_1);
	}
	{anything} {
		fprintf(stderr, "Syntax error\n");
		exit(0);
	}
}
<CITIRE_VIRGULA_1>{
	"," {
		BEGIN(CITIRE_ALFABET);
	}
	{anything} {
		fprintf(stderr, "Syntax error\n");
		exit(0);
	}
}
<CITIRE_ALFABET>{
	"{" {
		BEGIN(CITIRE_TERMINAL);
	}
	{anything} {
		fprintf(stderr, "Syntax error\n");
		exit(0);
	}
}
<CITIRE_TERMINAL>{
	{terminal} {
		gramatica_add_simbol_sigma(g, lastchar);
		BEGIN(CITIRE_TERMINAL_SEMN);
	}
	"}" {
		BEGIN(CITIRE_VIRGULA_2);
	}
	{anything} {
		fprintf(stderr, "Syntax error\n");
		exit(0);
	}
}
<CITIRE_TERMINAL_NEAPARAT>{
	{terminal} {
		gramatica_add_simbol_sigma(g, lastchar);
		BEGIN(CITIRE_TERMINAL_SEMN);
	}
	{anything} {
		fprintf(stderr, "Syntax error\n");
		exit(0);
	}
}
<CITIRE_TERMINAL_SEMN>{
	"," {
		BEGIN(CITIRE_TERMINAL_NEAPARAT);
	}
	"}" {
		BEGIN(CITIRE_VIRGULA_2);
	}
	{anything} {
		fprintf(stderr, "Syntax error\n");
		exit(0);
	}
}
<CITIRE_VIRGULA_2>{
	"," {
		BEGIN(CITIRE_REGULI);
	}
	{anything} {
		fprintf(stderr, "Syntax error\n");
		exit(0);
	}
}
<CITIRE_REGULI>{
	"{" {
		BEGIN(CITIRE_REGULA);
	}
	{anything} {
		fprintf(stderr, "Syntax error\n");
		exit(0);
	}
}
<CITIRE_REGULA>{
	"(" {
		r = regula_new();
		BEGIN(CITIRE_NETERMINAL_REGULA);
	}
	"}" {
		BEGIN(CITIRE_VIRGULA_3);
	}
	{anything} {
		fprintf(stderr, "Syntax error\n");
		exit(0);
	}
}
<CITIRE_NETERMINAL_REGULA>{
	{nonterminal} {
		regula_set_nonterminal(r, lastchar);
		BEGIN(CITIRE_VIRGULA_DIN_REGULA);
	}
	{anything} {
		fprintf(stderr, "Syntax error\n");
		exit(0);
	}
}
<CITIRE_VIRGULA_DIN_REGULA>{
	"," {
		BEGIN(CITIRE_CORP_REGULA);
	}
	{anything} {
		fprintf(stderr, "Syntax error\n");
		exit(0);
	}
}
<CITIRE_CORP_REGULA>{
	"e" {
		regula_add_simbol(r, 'e');
		BEGIN(CITIRE_PARANTEZA_INCHISA_REGULA);
	}
	{nonterminal} {
		regula_add_simbol(r, lastchar);
		BEGIN(CITIRE_CORP_REGULA_NEVID);
	}
	{terminal} {
		regula_add_simbol(r, lastchar);
		BEGIN(CITIRE_CORP_REGULA_NEVID);
	}
	{anything} {
		fprintf(stderr, "Syntax error\n");
		exit(0);
	}
}
<CITIRE_PARANTEZA_INCHISA_REGULA>{
	")" {
		gramatica_add_regula(g, r);
		BEGIN(CITIRE_SEMN_REGULA);
	}
	{anything} {
		fprintf(stderr, "Syntax error\n");
		exit(0);
	}
}
<CITIRE_CORP_REGULA_NEVID>{
	{nonterminal} {
		regula_add_simbol(r, lastchar);
		BEGIN(CITIRE_CORP_REGULA_NEVID);
	}
	{terminal} {
		regula_add_simbol(r, lastchar);
		BEGIN(CITIRE_CORP_REGULA_NEVID);
	}
	")" {
		gramatica_add_regula(g, r);
		BEGIN(CITIRE_SEMN_REGULA);
	}
	{anything} {
		fprintf(stderr, "Syntax error\n");
		exit(0);
	}
}
<CITIRE_REGULA_NEAPARAT>{
	"(" {
		r = regula_new();
		BEGIN(CITIRE_NETERMINAL_REGULA);
	}
	{anything} {
		fprintf(stderr, "Syntax error\n");
		exit(0);
	}
}
<CITIRE_SEMN_REGULA>{
	"," {
		BEGIN(CITIRE_REGULA_NEAPARAT);
	}
	"}" {
		BEGIN(CITIRE_VIRGULA_3);
	}
	{anything} {
		fprintf(stderr, "Syntax error\n");
		exit(0);
	}
}
<CITIRE_VIRGULA_3>{
	"," {
		BEGIN(CITIRE_SIMBOL_START);
	}
	{anything} {
		fprintf(stderr, "Syntax error\n");
		exit(0);
	}
}
<CITIRE_SIMBOL_START>{
	{upper-case-letter} {
		gramatica_set_start(g, lastchar);
		BEGIN(CITIRE_PARANTEZA_INCHISA);
	}
	{anything} {
		fprintf(stderr, "Syntax error\n");
		exit(0);
	}
}
<CITIRE_PARANTEZA_INCHISA>{
	")" {
		BEGIN(CITIRE_SFARSIT);
	}
	{anything} {
		fprintf(stderr, "Syntax error\n");
		exit(0);
	}
}
<CITIRE_SFARSIT>{
	{anything} {
		fprintf(stderr, "Syntax error\n");
		exit(0);
	}
}
%%

/*
Mustata Alexandru-Ionut
Grupa 331CB
Tema 1 LFA
*/

int main(int argc, char** argv){
	/*Verificarea posibilelor erori de argument.*/
	if(argc != 2 || 
		(strcmp("--is-void", argv[1]) != 0 &&
		strcmp("--has-e", argv[1]) != 0 &&
		strcmp("--useless-nonterminals", argv[1]) != 0) ){
		fprintf(stderr, "Argument error\n");
		return 0;
	}
	
	/*Deschiderea si parsarea fisierului ce contine gramatica.*/
	FILE* f = fopen("grammar", "rt");
	yyrestart(f);
    yylex();
    fclose(f);
	
	/*Verificare corectitudinii semantice a gramaticii.*/ 
    gramatica_verifica_corectitudine(g);

    /*Verificare daca limbajul generat de gramatica contine sirul vid.*/
    if(strcmp("--has-e", argv[1]) == 0){
    	int ok = gramatica_contine_sirul_vid(g);
    	if(ok==1){
    		printf("Yes\n");
    	}else{
    		printf("No\n");
    	}
    }

    /*Afisarea neterminalilor inutili din gramatica.*/
    if(strcmp("--useless-nonterminals", argv[1]) == 0){
    	gramatica_terminali_nefolositori(g, 0);
    }

    /*Verificarea daca limbajul generat de gramatica este vid.*/
    if(strcmp("--is-void", argv[1]) == 0){
    	gramatica_terminali_nefolositori(g, 1);
    }

	return 0;
}