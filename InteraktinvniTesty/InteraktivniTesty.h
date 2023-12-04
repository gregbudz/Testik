#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 21

//prihlasenie funkce
int nacteni_uzivatelu(void);

int menu(void);
int prihlaseni(void);
int registrace(void);

//testy funkce
int nacteni_testu(void);

void menuUzi(int a);
void moje_hodnoceni(int a);
void zacit_novy_test(int a);
void pokracovat_v_nedokoncenom_teste(int a);
void hra_riskuj(int a);

void menuAdmin(void);
void vsechny_testy(void);
void vsechny_hodnoceni(void);
void vytvorit_novy_test(void);

//testy podfunkce
int prejst_otazku(int i, int j, int poradie, int* spravnespatne, int a, long zaciatok_c);

void vypisat();
void vypisat_pohl();
void vypisat_vek();
void vypisat_test();

struct h_testy
{
	int  uzivatel;
	char test[MAX_STR];
	double  cas;
	double   score;
	struct h_testy* dalsi;
};

void pridat(int uzivatel, char* test, double cas, double score, struct h_testy** uk_prvni)
{
	struct h_testy* novyTest;
	struct h_testy* aktTest;

	novyTest = (struct h_testy*)malloc(sizeof(struct h_testy));

	novyTest->uzivatel = uzivatel;
	strcpy_s(novyTest->test, MAX_STR, test);
	novyTest->cas = cas;
	novyTest->score = score;
	novyTest->dalsi = NULL;

	if (*uk_prvni == NULL)
	{
		*uk_prvni = novyTest;
		return;
	}
	else if (novyTest->uzivatel <= (*uk_prvni)->uzivatel)
	{
		novyTest->dalsi = *uk_prvni;
		*uk_prvni = novyTest;
		return;
	}

	aktTest = *uk_prvni;
	while (aktTest)
	{
		if (aktTest->dalsi == NULL)
		{
			aktTest->dalsi = novyTest;
			return;
		}
		else if (novyTest->uzivatel <= aktTest->dalsi->uzivatel)
		{
			novyTest->dalsi = aktTest->dalsi;
			aktTest->dalsi = novyTest;
			return;
		}
		aktTest = aktTest->dalsi;
	}
}
