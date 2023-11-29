#include "InteraktivniTesty.h"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <time.h>

/*
Treba:
opravit moje_hodnoceni (+dat tam strukturu h_testy) a vsechny_hodnoceni
hra riskuj
*/

using namespace std;

#define MAX_UZI 30
#define MAX_TEST 10
#define MAX_STR_P 21
#define MAX_STR_T 40

//prihlasenie pole
char jmena[MAX_UZI][MAX_STR_P];
char hesla[MAX_UZI][MAX_STR_P];
char pohlavia[MAX_UZI][MAX_STR_P];
int veky[MAX_UZI];
int loc1 = 0;

//testy pole
char testy[MAX_TEST][MAX_STR_T];
char otazky[MAX_TEST][10][MAX_STR_T];
char odpovedi[MAX_TEST][10][10][MAX_STR_T];
int loc2 = 0;

//individualne testy pole
char moje_testy[MAX_UZI][MAX_TEST][MAX_STR_T];
char moje_n_testy[MAX_UZI][MAX_TEST][MAX_STR_T];
double moje_score[MAX_UZI][MAX_TEST];

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
void vratit_sa_k_otazke(int a, int* spravnespatne);

void vypisat();
void vypisat_pohl();
void vypisat_vek();
void vypisat_test();


int main() 
{
	nacteni_uzivatelu();
	nacteni_testu();

	int uzivatel = menu();

	if (uzivatel == 100) menuAdmin();
	else if (0 <= uzivatel && uzivatel < 100) menuUzi(uzivatel);

	return 0;
}

// <- otestovane dokoncene
//? <- neotestovane (ne?)dokoncene

int nacteni_uzivatelu(void)
{
	FILE* fp;

	if ((fp = fopen("..\\..\\..\\uzivatele.txt", "r")) == NULL)
	{
		printf("Soubor uzivatele.txt nelze otevrit.\n");
		exit(1);
	}

	while (!feof(fp)) 
	{
		fscanf(fp, "%s %s %s %d", jmena[loc1], hesla[loc1], pohlavia[loc1], &veky[loc1]); 
		loc1++;
	}

	fclose(fp);
	return loc1;
}
//
int menu(void) 
{
	char i;

	do 
	{
		system("cls");
		printf(
			" P Prihlaseni\n"
			" R Registrace\n"
			" Q Ukoncit program\n"
			"\n");
		printf("Zadejte volbu: ");
		i = tolower(getchar());

	} while (i != 'p' && i != 'r' && i != 'q');

	printf("\n");

	int j;

	switch (i)
	{
	case 'p': j = prihlaseni();
		break;
	case 'r': j = registrace();
		break;
	case 'q': j = 101;
	}
	return j;
} 
//
int prihlaseni(void)
{
	char jmeno[100];
	char heslo[100];
	int j = 0;

	
	getchar();
	system("cls");
	printf_s("Zadejte uzivatelske jmeno: ");
	gets_s(jmeno);
	printf_s("Zadejte uzivatelske heslo: ");
	gets_s(heslo);
	printf("\n");

	if (!strcmp(jmeno, "admin") && !strcmp(heslo, "admin"))
	{
		printf("Prihlaseni admina probehlo uspesne.\n\n");
		j = 100;
		return j;
	}

	for (; j < 100; j++) 
	{
		if (!strcmp(jmeno, jmena[j]) && !strcmp(heslo, hesla[j]))
		{
			printf("Prihlaseni probehlo uspesne.\n\n");
			return j;
		}
	}

	printf("Neexistuje takyto pouzivatel, skuste znovu.\n");
	prihlaseni();
	if (j < 100) return j;
}
//
int registrace(void)
{
	char jmeno[100];
	char heslo[100], heslo1[100];
	char pohlavie[100];
	int vek = 0;
	int j = 0;

	system("cls");
	getchar();
	printf_s("Zadejte jmeno: ");
	gets_s(jmeno);
	printf_s("Zadejte heslo: ");
	gets_s(heslo);
	printf_s("Znova zadejte heslo: ");
	gets_s(heslo1);
	printf("\n");

	if (strcmp(heslo, heslo1))
	{
		printf("Hesla se nezhoduji, skuste znovu.\n");
		registrace();
		return j;
	}

	if (!strcmp(jmeno, "admin") && !strcmp(heslo, "admin"))
	{
		printf("Prihlaseni admina probehlo uspesne.\n\n");
		j = 100;
		return j;
	}

	for (j = 0; j < (sizeof(jmena) / sizeof(jmena[0])); j++)
	{
		if (!strcmp(jmeno, jmena[j]) && !strcmp(heslo, hesla[j]))
		{
			printf("Takyto uzivatel uz existuje, skuste znovu.\n");
			registrace();
			return j;
		}
	}

	do
	{
		printf("Zadajte svoje pohlavie (muz/zena): ");
		gets_s(pohlavie);
	} while (strcmp(pohlavie, "muz") && strcmp(pohlavie, "zena"));

	printf("Zadajte svoj vek: ");
	scanf_s("%d", &vek);
	printf("\n");
	printf("Registrace probehla uspesne.\n\n");

	strcpy_s(jmena[loc1], jmeno);
	strcpy_s(hesla[loc1], heslo);
	strcpy_s(pohlavia[loc1], pohlavie);
	veky[loc1] = vek;

	FILE* fp;

	fp = fopen("..\\..\\..\\uzivatele.txt", "a");
	fprintf(fp, "%s %s %s %d \n", jmena[loc1], hesla[loc1], pohlavia[loc1], veky[loc1]);

	fclose(fp);

	j = loc1;
	loc1++;
	return j;
}
//

void menuUzi(int a)
{
	int x;

	do 
	{
		system("cls");
		printf("Menu uzivatele: %s\n", jmena[a]);
		printf(
			" H Moje hodnoceni\n"
			" N Zacit novy test\n"
			" P Pokracovat v nedokoncenom teste\n"
			" R Hra riskuj\n"
			" Q Ukoncit program\n"
			"\n"
			"Zadejte volbu: ");
		x = tolower(getchar());
		while (getchar() != '\n');

		printf("\n");

		switch (x)
		{
		case 'h': moje_hodnoceni(a);
			break;
		case 'n': zacit_novy_test(a);
			break;
		case 'p': pokracovat_v_nedokoncenom_teste(a);
			break;
		case 'r': hra_riskuj(a);
			break;
		}

	} while (x != 'q');
}
//
void moje_hodnoceni(int a) 
{
	//TREBA DAT STRUKTURU h_testy ALE VYPISAT IBA PRE UZIVATELA
	FILE* fp;

	if ((fp = fopen("..\\..\\..\\d_testy.txt", "r")) == NULL)
	{
		printf("Soubor d_testy.txt nelze otevrit.\n");
		exit(1);
	}

	int x = 0, i = 0;
	double cas = 0;

	while (!feof(fp))
	{
		fscanf(fp, "%d %s %.2lf %.0lf", &x, moje_n_testy[a][i], moje_score[a][i], &cas);
		if (a == x) i++;
		else moje_n_testy[a][i][80] = {};
	}

	fclose(fp);

	double score = 0;
	int velkost = sizeof(moje_testy[a]) / sizeof(moje_testy[a][0]);

	for (int j = 0; j < velkost; j++)
	{
		printf("%s: %.2lf\n", moje_testy[a][j], moje_score[a][j]);
		score += moje_score[a][j];
	}

	score /= velkost;
	printf("Celkove hodnotenie: %.2lf\n", score);
	getchar();
}
//? NEFUNGUJE
void zacit_novy_test(int a)
{
	int poradi = 1, poradie = 1;
	int i = 0;
	int spravnespatne[MAX_UZI] = { 0 };
	double velkost = 0;

	printf("Testy na vyber:\n");

	for (int x = 1; x < loc2; x++) printf("%d. %s \n", x, testy[x - 1]);

	printf("Zadaj cislo testu: ");
	scanf_s("%d", &i);
	getchar();
	i -= 1;

	printf("\n* = Chci se vratit k jine otazce.\n");
	printf("/ = Chci si ulozit test.\n\n");

	time_t zaciatok_c, koniec_c;
	time(&zaciatok_c);

	int j = 0;
	while(otazky[i][j][0] != '\0')
	{
		int t = 0;
		char spravna_odpoved = 0, typ = 0;
		char spravna_text_odpoved[MAX_STR_T] = {}, text_typ[MAX_STR_T] = {};

		int c = 0;
		while (otazky[i][j][c] != '\0')
		{
			if (otazky[i][j][c] == '_') otazky[i][j][c] = ' ';
			c++;
		}

		if (otazky[i][j][strlen(otazky[i][j]) - 1] == '*')
		{
			otazky[i][j][strlen(otazky[i][j]) - 1] = ' ';
			t = 1;
		}

		printf("%d. Otazka: %s\n", poradie, otazky[i][j]);

		c = 0;
		while (otazky[i][j][c] != '\0')
		{
			if (otazky[i][j][c] == ' ') otazky[i][j][c] = '_';
			c++;
		}

		if (t == 1)
		{
			strcpy(spravna_text_odpoved, odpovedi[i][j][0]);
			strcat(otazky[i][j], "*");

			printf("Zadej svoji odpoved: ");
			scanf("%79s", text_typ);
			while (getchar() != '\n');
			if (strcmp(spravna_text_odpoved, text_typ) == 0)
			{
				printf("Odpovedel si spravne\n");
				spravnespatne[j] = 1;
			}

			else if (strcmp("*", text_typ) == 0)
			{
				vratit_sa_k_otazke(i, spravnespatne);
				j--;
			}

			else if (strcmp("/", text_typ) == 0)
			{
				time(&koniec_c);
				double cas = difftime(koniec_c, zaciatok_c);

				FILE* fp;

				fp = fopen("..\\..\\..\\n_testy.txt", "a");

				fprintf(fp, "%d %s %d %.0lf ", a, testy[i], poradie, cas);
				int x = 0;
				while (spravnespatne[x])
				{
					fprintf(fp, "%d ", spravnespatne[x]);
					x++;
				}
				fprintf(fp, "\n");

				fclose(fp);
				return;
			}

			else
			{
				printf("Spatna odpoved\n");
				spravnespatne[j] = 0;
			}
		}

		else if (t == 0)
		{
			int k = 0;
			while (odpovedi[i][j][k][0] != '\0')
			{
				if (odpovedi[i][j][k][strlen(odpovedi[i][j][k]) - 1] == '*')
				{
					odpovedi[i][j][k][strlen(odpovedi[i][j][k]) - 1] = ' ';
					spravna_odpoved = (char)(poradi + '0');

					int c = 0;
					while (odpovedi[i][j][k][c] != '\0')
					{
						if (odpovedi[i][j][k][c] == '_') odpovedi[i][j][k][c] = ' ';
						c++;
					}
					printf("%d. Odpoved: %s\n", poradi, odpovedi[i][j][k]);

					strcat(odpovedi[i][j][k], "*");

					c = 0;
					while (odpovedi[i][j][k][c] != '\0')
					{
						if (odpovedi[i][j][k][c] == ' ') odpovedi[i][j][k][c] = '_';
						c++;
					}
				}

				else
				{
					int c = 0;
					while (odpovedi[i][j][k][c] != '\0')
					{
						if (odpovedi[i][j][k][c] == '_') odpovedi[i][j][k][c] = ' ';
						c++;
					}
					printf("%d. Odpoved: %s\n", poradi, odpovedi[i][j][k]);

					c = 0;
					while (odpovedi[i][j][k][c] != '\0')
					{
						if (odpovedi[i][j][k][c] == ' ') odpovedi[i][j][k][c] = '_';
						c++;
					}
				}
				k++;
				poradi++;
			}

			printf("Zadej svoji odpoved: ");
			scanf_s("%c", &typ);
			getchar();
			printf("Spravna odpoved bola: %c\n", spravna_odpoved);

			if (typ == spravna_odpoved)
			{
				printf("Odpovedel si spravne\n");
				spravnespatne[j] = 1;
			}

			else if (typ == '*')
			{
				vratit_sa_k_otazke(i, spravnespatne);
				j--;
			}

			else if (typ == '/')
			{
				time(&koniec_c);
				double cas = difftime(koniec_c, zaciatok_c);

				FILE* fp;

				fp = fopen("..\\..\\..\\n_testy.txt", "a");

				fprintf(fp, "%d %s %d %.0lf ", a, testy[i], poradie, cas);

				int x = 0;
				while (spravnespatne[x])
				{
					fprintf(fp, "%d ", spravnespatne[x]);
					x++;
				}
				fprintf(fp, "\n");

				fclose(fp);
				return;
			}

			else
			{
				printf("Spatna odpoved\n");
				spravnespatne[j] = 0;
			}
			printf("\n");
		}

		j++;
		poradi = 1;
		poradie++;
		velkost++;
	}

	time(&koniec_c);
	double cas = difftime(koniec_c, zaciatok_c);
	printf("Trvalo to: %.0lf s\n", cas);
	printf("\n");

	int x = sizeof(moje_testy[a]) / sizeof(moje_testy[a][0]) + 1;
	strcpy_s(moje_testy[a][x], testy[i]);

	double spravne_odpovede = 0;
	for (int z = 0; z <= velkost; z++) if (spravnespatne[z] == 1) spravne_odpovede++;

	if (spravne_odpovede == 0) moje_score[a][x] = 0;
	else moje_score[a][x] = spravne_odpovede / velkost * 100;

	printf("Tvoje hodnotenie: %.2lf percent", moje_score[a][x]);
	printf("\n");

	FILE* fp;
	fp = fopen("..\\..\\..\\d_testy.txt", "a");

	fprintf(fp, "%d %s %.2lf %.0lf\n", a, moje_testy[a][x], moje_score[a][x], cas);
	fclose(fp);
	while (getchar() != '\n');
}
//
void vratit_sa_k_otazke(int i, int* spravnespatne)
{
	int poradi = 1, poradie = 1;

	printf("Zadej cislo otazky: ");
	scanf("%d", &poradie);
	int j = poradie - 1;

	int t = 0;
	char spravna_odpoved = 0, typ = 0;
	char spravna_text_odpoved[MAX_STR_T] = {}, text_typ[MAX_STR_T] = {};

	for (int x = 0; x < 100 && otazky[i][j][0] != '\0'; x++) if (otazky[i][j][x] == '_') otazky[i][j][x] = ' ';

	if (otazky[i][j][strlen(otazky[i][j]) - 1] == '*')
	{
		otazky[i][j][strlen(otazky[i][j]) - 1] = ' ';
		t = 1;
	}
	printf("%d. Otazka: %s\n", poradie, otazky[i][j]);

	if (t == 1)
	{
		strcpy(spravna_text_odpoved, odpovedi[i][j][0]);
		strcat(otazky[i][j], "*");

		printf("Zadej svoji odpoved: ");
		scanf("%79s", text_typ);
		while (getchar() != '\n');
		if (strcmp(spravna_text_odpoved, text_typ) == 0)
		{
			printf("Odpovedel si spravne\n");
			spravnespatne[j] = 1;
		}

		else if (strcmp("*", text_typ) == 0)
		{
			vratit_sa_k_otazke(i, spravnespatne);
			j--;
		}

		else
		{
			printf("Spatna odpoved\n");
			spravnespatne[j] = 0;
		}
	}

	else if (t == 0)
	{
		int k = 0;
		while(odpovedi[i][j][k][0] != '\0')
		{
			if (odpovedi[i][j][k][strlen(odpovedi[i][j][k]) - 1] == '*')
			{
				odpovedi[i][j][k][strlen(odpovedi[i][j][k]) - 1] = ' ';
				spravna_odpoved = (char)(poradi + '0');

				int c = 0;
				while (odpovedi[i][j][k][c] != '\0')
				{
					if (odpovedi[i][j][k][c] == '_') odpovedi[i][j][k][c] = ' ';
					c++;
				}
				printf("%d. Odpoved: %s\n", poradi, odpovedi[i][j][k]);

				strcat(odpovedi[i][j][k],"*");

				c = 0;
				while (odpovedi[i][j][k][c] != '\0')
				{
					if (odpovedi[i][j][k][c] == ' ') odpovedi[i][j][k][c] = '_';
					c++;
				}
			}

			else
			{
				int c = 0;
				while (odpovedi[i][j][k][c] != '\0')
				{
					if (odpovedi[i][j][k][c] == '_') odpovedi[i][j][k][c] = ' ';
					c++;
				}
				printf("%d. Odpoved: %s\n", poradi, odpovedi[i][j][k]);

				c = 0;
				while (odpovedi[i][j][k][c] != '\0')
				{
					if (odpovedi[i][j][k][c] == ' ') odpovedi[i][j][k][c] = '_';
					c++;
				}
			}
			k++;
			poradi++;
		}

		printf("Zadej svoji odpoved: ");
		scanf_s("%c", &typ);
		getchar();
		printf("Spravna odpoved bola: %c\n", spravna_odpoved);

		if (typ == spravna_odpoved)
		{
			printf("Odpovedel si spravne\n");
			spravnespatne[j] = 1;
		}

		else if (typ == '*')
		{
			vratit_sa_k_otazke(i, spravnespatne);
		}

		else
		{
			printf("Spatna odpoved\n");
			spravnespatne[j] = 0;
		}
		printf("\n");
	}
}
//
void pokracovat_v_nedokoncenom_teste(int a)
{
	// TU SA DA ASI SPRAVIT CONSTR AKO V CELKOVOM HODNOTENI

	FILE* fp, *tfp;

	if ((fp = fopen("..\\..\\..\\n_testy.txt", "r")) == NULL)
	{
		printf("Soubor n_testy.txt nelze otevrit.\n");
		exit(1);
	}

	int x = 0, index = 0;
	int pocet_odp_otazok[10] = { 0 };
	int sprspa[10][10] = { 0 };
	double cas[10] = { 0 };

	while (!feof(fp))
	{
		fscanf(fp, "%d %s %d %.0lf", &x, moje_n_testy[a][index], &pocet_odp_otazok[index], &cas[index]);
		for (int y = 0; y < pocet_odp_otazok[index]; y++) fscanf(fp, "%d ", &sprspa[index][y]);
		if (a == x) index++;
		else moje_n_testy[a][index][80] = {};
	}

	fclose(fp);

	if (index == 0)
	{
		printf("Nemate ziadne nedokoncene testy.\n");
		getchar();
		return;
	}

	printf("Vase nedokoncene testy na vyber:\n");
	for (int x = 1; x <= index; x++) printf("%d. %s\n", x, moje_n_testy[a][x - 1]);

	printf("Zadaj cislo testu: ");
	scanf_s("%d", &index);
	getchar();
	index -= 1;

	int i = 0;
	while (testy[i][0] != '\0')
	{
		if (strcmp(moje_n_testy[a][index], testy[i]) == 0) break;
		i++;
	}

	fp = fopen("..\\..\\..\\n_testy.txt", "r");
	tfp = fopen("temp.txt", "w");

	while (!feof(fp))
	{
		char temp[80] = {};
		int tem = 0, te[10] = { 0 }, t = 0;
		fscanf(fp, "%d %s %d ", &t, temp, &tem);
		for (int y = 0; y < tem; y++) fscanf(fp, "%d ", &te[y]);
		if (a != t && strcmp(temp, testy[i]) != 0)
		{
			fprintf(tfp, "%d %s %d ", t, temp, tem);
			for (int y = 0; y < tem; y++) fprintf(tfp, "%d ", te[y]);
			fprintf(tfp, "\n");
		}
	}
	fclose(fp);
	fclose(tfp);
	remove("..\\..\\..\\n_testy.txt");
	rename("temp.txt", "..\\..\\..\\n_testy.txt");

	int poradie = pocet_odp_otazok[index];
	int poradi = 1;
	int spravnespatne[10] = { 0 };
	for (int y = 0; y < poradie; ++y) spravnespatne[y] = sprspa[index][y];
	double velkost = 0;

	printf("* = Chci se vratit k jine otazce.\n");
	printf("/ = Chci si ulozit test.\n\n");

	time_t zaciatok_c, koniec_c;
	time(&zaciatok_c);

	int j = poradie - 1;
	while(otazky[i][j][0] != '\0')
	{
		int t = 0;
		char spravna_odpoved = 0, typ = 0;
		char spravna_text_odpoved[MAX_STR_T] = {}, text_typ[MAX_STR_T] = {};

		int c = 0;
		while (otazky[i][j][c] != '\0')
		{
			if (otazky[i][j][c] == '_') otazky[i][j][c] = ' ';
			c++;
		}

		if (otazky[i][j][strlen(otazky[i][j]) - 1] == '*')
		{
			otazky[i][j][strlen(otazky[i][j]) - 1] = ' ';
			t = 1;
		}

		printf("%d. Otazka: %s\n", poradie, otazky[i][j]);

		c = 0;
		while (otazky[i][j][c] != '\0')
		{
			if (otazky[i][j][c] == ' ') otazky[i][j][c] = '_';
			c++;
		}

		if (t == 1)
		{
			strcpy(spravna_text_odpoved, odpovedi[i][j][0]);
			strcat(otazky[i][j], "*");

			printf("Zadej svoji odpoved: ");
			scanf("%79s", text_typ);
			while (getchar() != '\n');
			if (strcmp(spravna_text_odpoved, text_typ) == 0)
			{
				printf("Odpovedel si spravne\n");
				spravnespatne[j] = 1;
			}

			else if (strcmp("*", text_typ) == 0)
			{
				vratit_sa_k_otazke(i, spravnespatne);
				j--;
			}

			else if (strcmp("/", text_typ) == 0)
			{
				time(&koniec_c);
				cas[index] += difftime(koniec_c, zaciatok_c);

				FILE* fp;

				fp = fopen("..\\..\\..\\n_testy.txt", "a");

				fprintf(fp, "%d %s %d %.0lf ", a, testy[i], poradie, cas[index]);
				int x = 0;
				while (spravnespatne[x])
				{
					fprintf(fp, "%d ", spravnespatne[x]);
					x++;
				}
				fprintf(fp, "\n");

				fclose(fp);
				return;
			}

			else
			{
				printf("Spatna odpoved\n");
				spravnespatne[j] = 0;
			}
		}

		else if (t == 0)
		{
			int k = 0;
			while(odpovedi[i][j][k][0] != '\0')
			{
				if (odpovedi[i][j][k][strlen(odpovedi[i][j][k]) - 1] == '*')
				{
					odpovedi[i][j][k][strlen(odpovedi[i][j][k]) - 1] = ' ';
					spravna_odpoved = (char)(poradi + '0');

					int c = 0;
					while (odpovedi[i][j][k][c] != '\0')
					{
						if (odpovedi[i][j][k][c] == '_') odpovedi[i][j][k][c] = ' ';
						c++;
					}
					printf("%d. Odpoved: %s\n", poradi, odpovedi[i][j][k]);

					strcat(odpovedi[i][j][k], "*");

					c = 0;
					while (odpovedi[i][j][k][c] != '\0')
					{
						if (odpovedi[i][j][k][c] == ' ') odpovedi[i][j][k][c] = '_';
						c++;
					}
				}

				else
				{
					int c = 0;
					while (odpovedi[i][j][k][c] != '\0')
					{
						if (odpovedi[i][j][k][c] == '_') odpovedi[i][j][k][c] = ' ';
						c++;
					}
					printf("%d. Odpoved: %s\n", poradi, odpovedi[i][j][k]);

					c = 0;
					while (odpovedi[i][j][k][c] != '\0')
					{
						if (odpovedi[i][j][k][c] == ' ') odpovedi[i][j][k][c] = '_';
						c++;
					}
				}
				k++;
				poradi++;
			}

			printf("Zadej svoji odpoved: ");
			scanf_s("%c", &typ);
			getchar();
			printf("Spravna odpoved bola: %c\n", spravna_odpoved);

			if (typ == spravna_odpoved)
			{
				printf("Odpovedel si spravne\n");
				spravnespatne[j] = 1;
			}

			else if (typ == '*')
			{
				vratit_sa_k_otazke(i, spravnespatne);
				j--;
			}

			else if (typ == '/')
			{
				time(&koniec_c);
				double cas = difftime(koniec_c, zaciatok_c);

				FILE* fp;

				fp = fopen("..\\..\\..\\n_testy.txt", "a");

				fprintf(fp, "%d %s %d %.0lf ", a, testy[i], poradie, cas);

				int x = 0;
				while (spravnespatne[x])
				{
					fprintf(fp, "%d ", spravnespatne[x]);
					x++;
				}
				fprintf(fp, "\n");

				fclose(fp);
				return;
			}

			else
			{
				printf("Spatna odpoved\n");
				spravnespatne[j] = 0;
			}
		}

		printf("\n");
		j++;
		poradi = 1;
		poradie++;
		velkost++;
	}

	while (getchar() != '\n');

	time(&koniec_c);
	cas[index] += difftime(koniec_c, zaciatok_c);
	printf("Trvalo to: %.0f\n", cas[index]);
	printf("\n");

	double spravne_odpovede = 0;
	for (int x = 0; x <= velkost; x++) if (spravnespatne[x] == 1) spravne_odpovede++;
	moje_score[a][i] = spravne_odpovede / velkost * 100;

	printf("Tvoje hodnotenie: %.2lf percent", moje_score[a][i]);
	printf("\n");

	int miesto = sizeof(moje_testy[a]) / sizeof(moje_testy[a][0]) + 1;
	strcpy_s(moje_testy[a][miesto], testy[i]);

	fp = fopen("..\\..\\..\\d_testy.txt", "a");

	fprintf(fp, "%d %s %d %.0lf", a, moje_testy[a][miesto], moje_score[a][miesto], cas[index]);

	fclose(fp);
}
//
void hra_riskuj(int a)
{
	while (getchar() != '\n');
}


void menuAdmin(void)
{
	int x;

	do
	{
		system("cls");
		printf(
			"Menu admina\n"
			" T Vsetky testy\n"
			" H Vsetky hodnoceni\n"
			" N Vytvorit novy test\n"
			" Q Ukoncit program\n"
			"\n"
			"Zadejte volbu: ");
		x = tolower(getchar());
		while (getchar() != '\n');

		printf("\n");

		switch (x)
		{
		case 't': vsechny_testy();
			break;
		case 'h': vsechny_hodnoceni();
			break;
		case 'n': vytvorit_novy_test();
			break;
		}

	} while (x != 'q');
}
//
void vsechny_testy(void) 
{
	int i = 0;
	while (testy[i][0] != '\0')
	{
		printf("%d. %s\n", i + 1, testy[i]);
		i++;
	}
	while (getchar() != '\n');
}
//
void vsechny_hodnoceni(void)
{
	FILE* fp;

	if ((fp = fopen("..\\..\\..\\d_testy.txt", "r")) == NULL)
	{
		printf("Soubor d_testy.txt nelze otevrit.\n");
		exit(1);
	}

	//POZOR POZOR, STRUKTURA JE V IntTesty.h POTOM PREPIS PODLA POTREBY
	 
	struct h_testy* prvni = NULL;

	while (!feof(fp))
	{
		int my_uzivatel = 0;
		char my_test[MAX_STR_T] = {};
		double  my_cas = 0;
		int my_score = 0;

		fscanf(fp, "%d %s %d %.0lf", &my_uzivatel, my_test, &my_score, &my_cas);

		pridat(my_uzivatel, my_test, my_cas, my_score, &prvni);
	}

	fclose(fp);

	int x;
	do 
	{
		system("cls");
		printf(
			"Moznosti\n"
			" H Vsetky hodnoceni\n"
			" P Hodnoceni podle pohlavi\n"
			" V Hodnoceni podle veku\n"
			" T Hodnoceni podle testu\n"
			" Q Vratit se do menu\n"
			"\n"
			"Zadejte volbu: ");
		x = tolower(getchar());
		while (getchar() != '\n');

		printf("\n");

		switch (x)
		{
		case 'h': vypisat();
			break;

		case 'p': vypisat_pohl();
			break;

		case 'v': vypisat_vek();
			break;

		case 't': vypisat_test();
			break;
		}
	} while (x != 'q');
}
//?
void vytvorit_novy_test(void)
{
	FILE* fp;

	fp = fopen("..\\..\\..\\testy.txt", "a");

	int MAX_OT = 0, MAX_OD = 0;
	int typ;
	int w;

	printf("Namiesto medzier davajte '_'.\n");

	do 
	{
		printf("Zadajte nazov testu: ");
		scanf("%79s", testy[loc2]);
		for (int x = 0; x < 100 && testy[loc2][0] != '\0'; x++) if (testy[loc2][x] == ' ') testy[loc2][x] = '_';
		for (int x = 0; x < loc2; x++)
		{
			if (!strcmp(testy[loc2], testy[x]))
			{
				printf("Test so zadanym menom uz existuje, skuste znova.\n");
				w = 1;
				break;
			}
			else w = 0;
		}
	} while (w);

	fprintf(fp, "%s ", testy[loc2]);

	printf("Zadajte pocet otazok: ");
	scanf("%d", &MAX_OT);;
	fprintf(fp, "%d ", MAX_OT);

	for (int j = 0; j < MAX_OT; j++)
	{
		printf("Zadejte otazku: ");
		scanf("%79s", otazky[loc2][j]);
		while (getchar() != '\n');

		for (int x = 0; x < 100 && otazky[loc2][j][0] != '\0'; x++) if (otazky[loc2][j][x] == ' ') otazky[loc2][j][x] = '_';

		printf("Zadajte typ otazky (1 = dane otazky, 2 = uzivatel musi zadat): ");
		scanf("%d", &typ);

		if (typ == 1)
		{
			fprintf(fp, "%s ", otazky[loc2][j]);
			fprintf(fp, "%d ", typ);
			printf("Zadajte pocet odpovedi: ");
			scanf("%d", &MAX_OD);
			fprintf(fp, "%d ", MAX_OD);

			for (int k = 0; k < MAX_OD; k++)
			{
				printf("Zadejte odpoved (pri spravnej zadajte *): ");
				scanf("%79s", odpovedi[loc2][j][k]);
				while (getchar() != '\n');
				fprintf(fp, "%s ", odpovedi[loc2][j][k]);

			}
		}
		else if (typ == 2)
		{
			strcat(otazky[loc2][j],"*");
			fprintf(fp, "%s ", otazky[loc2][j]);
			fprintf(fp, "%d ", typ);
			printf("Zadejte spravnu odpoved: ");
			scanf("%79s", odpovedi[loc2][j][0]);
			fprintf(fp, "%s ", odpovedi[loc2][j][0]);
		}
	}
	loc2++;

	printf("\n");
	fprintf(fp, "\n");
	fclose(fp);
}
//
int nacteni_testu(void)
{
	FILE* fp;

	if ((fp = fopen("..\\..\\..\\testy.txt", "r")) == NULL)
	{
		printf("Soubor testy.txt nelze otevrit.\n");
		exit(1);
	}

	while (!feof(fp))
	{
		int pocet_otazok = 0;
		fscanf(fp, "%s %d", testy[loc2], &pocet_otazok);

		for (int j = 0; j < pocet_otazok; j++)
		{
			int typ = 0;
			fscanf(fp, "%s %d", otazky[loc2][j], &typ);
			if (typ == 1)
			{
				int pocet_odpovedi = 0;
				fscanf(fp, "%d", &pocet_odpovedi);
				for (int k = 0; k < pocet_odpovedi; k++)
				{
					fscanf(fp, "%s", odpovedi[loc2][j][k]);
				}
			}
			else if (typ == 2)
			{
				fscanf(fp, "%s", &odpovedi[loc2][j][0]);
			}
		}
		loc2++;
	}

	fclose(fp);
	return loc2;
}
//

struct h_testy* prvni = NULL;
void vypisat()
{
	struct h_testy* aktTest = prvni;
	printf("\n\n");
	while (aktTest)
	{
		printf("%s: %s %d % %.0l\n", jmena[aktTest->uzivatel], aktTest->test, aktTest->score, aktTest->cas);
		aktTest = aktTest->dalsi;
	}
	getchar();
}
//?
void vypisat_pohl()
{
	struct h_testy* aktTest = prvni;
	char pohlavi[MAX_STR];
	int i = 0;
	int score = 0;
	do
	{
		printf("Zadejte pohlavi (muz/zena): ");
		scanf_s("%s", pohlavi);
		while (getchar() != '\n');
	} while (strcmp(pohlavi, "muz") && strcmp(pohlavi, "zena"));

	while (aktTest)
	{
		if (strcmp(pohlavi, pohlavia[aktTest->uzivatel]) == 0)
		{
			printf("%s: %s %d % %.0l\n", jmena[aktTest->uzivatel], aktTest->test, aktTest->score, aktTest->cas);
			i++;
			score += aktTest->score;
		}
		aktTest = aktTest->dalsi;
	}
	if (i == 0) printf("Dane pohlavie nedokoncilo ani 1 test.\n");
	else
	{
		score /= i;
		printf("Priemerne skore pohlavia %s: %d %", pohlavi, score);
	}
	getchar();
}
//?
void vypisat_vek()
{
	struct h_testy* aktTest = prvni;
	int z_vek, k_vek;
	int i = 0;
	int score = 0;

	printf("Zadejte vek od, do: ");
	scanf_s("%d, %d", &z_vek, &k_vek);
	while (getchar() != '\n');
	while (aktTest)
	{
		if (z_vek <= veky[aktTest->uzivatel] && veky[aktTest->uzivatel] <= k_vek)
		{
			printf("%s: %s %d % %.0l\n", jmena[aktTest->uzivatel], aktTest->test, aktTest->score, aktTest->cas);
			i++;
			score += aktTest->score;
		}
		aktTest = aktTest->dalsi;
	}
	if (i == 0) printf("Dane rocniky nedokoncily ani 1 test.\n");
	else
	{
		score /= i;
		printf("Priemerne skore rocnikov od %d do %d: %d", z_vek, k_vek, score);
	}
	getchar();
}
//?
void vypisat_test()
{
	struct h_testy* aktTest = prvni;
	char test[MAX_STR_P];
	int i = 0;
	int score = 0;

	printf("Zadejte nazev testu: ");
	scanf_s("%s", test);
	while (getchar() != '\n');
	while (aktTest)
	{
		if (strcmp(test, aktTest->test) == 0)
		{
			printf("%s: %s %d % %.0l\n", jmena[aktTest->uzivatel], aktTest->test, aktTest->score, aktTest->cas);
			i++;
			score += aktTest->score;
		}
		aktTest = aktTest->dalsi;
	}
	if (i == 0) printf("Dany test nedokoncil ani 1 uzivatel.\n");
	else
	{
		score /= i;
		printf("Priemerne skore v teste %s: %d", test, score);
	}
	getchar();
}
//?