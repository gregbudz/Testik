#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 21

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
