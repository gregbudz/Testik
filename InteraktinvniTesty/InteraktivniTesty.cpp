#include "InteraktivniTesty.h"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <time.h>

/*
Treba:
hra riskuj
*/

#define MaX_UZI 30
#define MaX_TEST 10
#define MaX_STR_P 21
#define MaX_STR_T 40

struct {
	char jmena[MaX_UZI][MaX_STR_P];
	char hesla[MaX_UZI][MaX_STR_P];
	char pohlavia[MaX_UZI][MaX_STR_P];
	int veky[MaX_UZI];
	int loc1 = 0;
}uzi;


//testy pole
struct {
	char testy[MaX_TEST][MaX_STR_T];
	char otazky[MaX_TEST][10][MaX_STR_T];
	char odpovedi[MaX_TEST][10][10][MaX_STR_T];
	int loc2 = 0;
}of;


//individualne testy pole
struct {
	char testy[MaX_UZI][MaX_TEST][MaX_STR_T];
	char n_testy[MaX_UZI][MaX_TEST][MaX_STR_T];
	double score[MaX_UZI][MaX_TEST];
	double casy[MaX_UZI][MaX_TEST];
}moje;

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

	while (fscanf(fp, "%s %s %s %d", uzi.jmena[uzi.loc1], uzi.hesla[uzi.loc1], uzi.pohlavia[uzi.loc1], &uzi.veky[uzi.loc1]) == 4) uzi.loc1++;

	fclose(fp);
	return uzi.loc1;
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
		if (!strcmp(jmeno, uzi.jmena[j]) && !strcmp(heslo, uzi.hesla[j]))
		{
			printf("Prihlaseni probehlo uspesne.\n\n");
			return j;
		}
	}

	printf("Neexistuje takyto pouzivatel, skuste znovu.\n");
	j = prihlaseni();
	return j;
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

	int x = 0;
	while (uzi.jmena[x][0] != '\0')
	{
		if (!strcmp(jmeno, uzi.jmena[x]))
		{
			printf("Takyto uzivatel uz existuje, skuste znovu.\n");
			getchar();
			j = registrace();
			return j;
		}
		x++;
	}

	printf_s("Zadejte heslo: ");
	gets_s(heslo);
	printf_s("Znova zadejte heslo: ");
	gets_s(heslo1);
	printf("\n");

	if (strcmp(heslo, heslo1))
	{
		printf("Hesla se nezhoduji, skuste znovu.\n");
		getchar();
		j = registrace();
		return j;
	}

	if (!strcmp(jmeno, "admin") && !strcmp(heslo, "admin"))
	{
		printf("Prihlaseni admina probehlo uspesne.\n\n");
		getchar();
		j = 100;
		return j;
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

	getchar();

	strcpy_s(uzi.jmena[uzi.loc1], jmeno);
	strcpy_s(uzi.hesla[uzi.loc1], heslo);
	strcpy_s(uzi.pohlavia[uzi.loc1], pohlavie);
	uzi.veky[uzi.loc1] = vek;

	FILE* fp;

	fp = fopen("..\\..\\..\\uzivatele.txt", "a");
	fprintf(fp, "%s %s %s %d \n", uzi.jmena[uzi.loc1], uzi.hesla[uzi.loc1], uzi.pohlavia[uzi.loc1], uzi.veky[uzi.loc1]);

	fclose(fp);

	j = uzi.loc1;
	uzi.loc1++;
	return j;
}
//

void menuUzi(int a)
{
	int x;

	do 
	{
		system("cls");
		printf("Menu uzivatele: %s\n", uzi.jmena[a]);
		printf(
			" H Moje hodnoceni\n"
			" N Zacit novy test\n"
			" P Pokracovat v nedokoncenom teste\n"
			" R Hra riskuj\n"
			" Q Ukoncit program\n"
			"\n"
			"Zadejte volbu: ");
		int y = 0;

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
	FILE* fp;

	if ((fp = fopen("..\\..\\..\\d_testy.txt", "r")) == NULL)
	{
		printf("Soubor d_testy.txt nelze otevrit.\n");
		exit(1);
	}

	int x = 0, i = 0;
	char test[MaX_STR_T] = { 0 };
	double cas = 0;
	double score = 0;

	while (fscanf(fp, "%d %s %lf %lf", &x, test, &moje.score[a][i], &moje.casy[a][i]) == 4)
	{
		if (x == a)
		{
			printf("%s: %.2lf P %.2lf s\n", test, moje.score[a][i], moje.casy[a][i]);
			strcpy(moje.testy[a][i], test);
			score += moje.score[a][i];
			cas += moje.casy[a][i];
			i++;
		}
	}

	fclose(fp);

	if (i != 0) 
	{
		score /= i;
		cas /= i;
		printf("\nPriemerne hodnotenie: %.2lf P\n", score);
		printf("Priemerny cas: %.2lf s\n", cas);
	}

	else
	{
		printf("Nemate ziadne dokoncene testy.");
	}

	getchar();
}
//
void zacit_novy_test(int a)
{
	int poradi = 1, poradie = 1;
	int i = 0;
	int spravnespatne[MaX_UZI] = { 0 };
	double velkost = 0;

	printf("Testy na vyber:\n");

	for (int x = 1; x < of.loc2; x++) printf("%d. %s \n", x, of.testy[x - 1]);

	printf("Zadaj cislo testu: ");
	scanf_s("%d", &i);
	getchar();
	i -= 1;

	printf("\n* = Chci se vratit k jine otazce.\n");
	printf("/ = Chci si ulozit test a ukoncit program.\n\n");

	time_t zaciatok_c, koniec_c;
	time(&zaciatok_c);

	int j = 0;
	while(of.otazky[i][j][0] != '\0')
	{
		int t = j;
		j = prejst_otazku(i, j, poradie, spravnespatne, a, zaciatok_c);

		if (t == j)
		{
			poradie++;
			velkost++;
		}
		j++;
	}

	time(&koniec_c);
	double cas = difftime(koniec_c, zaciatok_c);
	printf("Trvalo to: %.2lf s\n", cas);
	printf("\n");

	int x = sizeof(moje.testy[a]) / sizeof(moje.testy[a][0]) + 1;
	strcpy(moje.testy[a][x], of.testy[i]);

	double spravne_odpovede = 0;
	for (int z = 0; z <= velkost; z++) if (spravnespatne[z] == 1) spravne_odpovede++;

	if (spravne_odpovede == 0) moje.score[a][x] = 0;
	else moje.score[a][x] = spravne_odpovede / velkost * 100;

	printf("Tvoje hodnotenie: %.2lf P", moje.score[a][x]);
	printf("\n");

	FILE* fp;
	fp = fopen("..\\..\\..\\d_testy.txt", "a");

	fprintf(fp, "%d %s %.2lf %.2lf\n", a, moje.testy[a][x], moje.score[a][x], cas);
	fclose(fp);
	while (getchar() != '\n');
}
//
int prejst_otazku(int i, int j, int poradie, int* spravnespatne, int a, long zaciatok_c)
{
	int poradi = 1;
	int t = 0;
	char spravna_odpoved, typ;
	char spravna_text_odpoved[MaX_STR_T], text_typ[MaX_STR_T];

	int c = 0;
	while (of.otazky[i][j][c] != '\0')
	{
		if (of.otazky[i][j][c] == '_') of.otazky[i][j][c] = ' ';
		c++;
	}

	if (of.otazky[i][j][strlen(of.otazky[i][j]) - 1] == '*')
	{
		of.otazky[i][j][strlen(of.otazky[i][j]) - 1] = ' ';
		t = 1;
	}

	printf("\n%d. Otazka: %s\n\n", poradie, of.otazky[i][j]);

	c = 0;
	while (of.otazky[i][j][c] != '\0')
	{
		if (of.otazky[i][j][c] == ' ') of.otazky[i][j][c] = '_';
		c++;
	}

	if (t == 1)
	{
		strcpy(spravna_text_odpoved, of.odpovedi[i][j][0]);
		strcat(of.otazky[i][j], "*");

		printf("Zadej svoji textovou odpoved: ");
		scanf("%79s", text_typ);
		while (getchar() != '\n');

		if (strcmp(spravna_text_odpoved, text_typ) == 0) spravnespatne[j] = 1;

		else if (strcmp("*", text_typ) == 0)
		{
			printf("\nZadej cislo otazky: ");
			scanf("%d", &poradie);
			int g = poradie - 1;
			g = prejst_otazku(i, g, poradie, spravnespatne, a, zaciatok_c);
			j--;
		}

		else if (strcmp("/", text_typ) == 0)
		{
			time_t koniec_c;

			time(&koniec_c);
			double cas = difftime(koniec_c, zaciatok_c);

			FILE* fp;

			fp = fopen("..\\..\\..\\n_testy.txt", "a");

			fprintf(fp, "%d %s %d %.2lf ", a, of.testy[i], j, cas);
			int x = 0;
			while (spravnespatne[x])
			{
				fprintf(fp, "%d ", spravnespatne[x]);
				x++;
			}
			fprintf(fp, "\n");

			fclose(fp);
			exit(1);
		}

		else spravnespatne[j] = 2;
	}

	else if (t == 0)
	{
		int k = 0;
		while (of.odpovedi[i][j][k][0] != '\0')
		{
			if (of.odpovedi[i][j][k][strlen(of.odpovedi[i][j][k]) - 1] == '*')
			{
				of.odpovedi[i][j][k][strlen(of.odpovedi[i][j][k]) - 1] = ' ';
				spravna_odpoved = (char)(poradi + '0');

				int c = 0;
				while (of.odpovedi[i][j][k][c] != '\0')
				{
					if (of.odpovedi[i][j][k][c] == '_') of.odpovedi[i][j][k][c] = ' ';
					c++;
				}

				printf("%d. Odpoved: %s\n", poradi, of.odpovedi[i][j][k]);

				strcat(of.odpovedi[i][j][k], "*");

				c = 0;
				while (of.odpovedi[i][j][k][c] != '\0')
				{
					if (of.odpovedi[i][j][k][c] == ' ') of.odpovedi[i][j][k][c] = '_';
					c++;
				}
			}

			else
			{
				int c = 0;
				while (of.odpovedi[i][j][k][c] != '\0')
				{
					if (of.odpovedi[i][j][k][c] == '_') of.odpovedi[i][j][k][c] = ' ';
					c++;
				}

				printf("%d. Odpoved: %s\n", poradi, of.odpovedi[i][j][k]);

				c = 0;
				while (of.odpovedi[i][j][k][c] != '\0')
				{
					if (of.odpovedi[i][j][k][c] == ' ') of.odpovedi[i][j][k][c] = '_';
					c++;
				}
			}
			k++;
			poradi++;
		}

		printf("Zadej svoji odpoved: ");
		scanf(" %c", &typ);
		while (getchar() != '\n');
		printf("%c/\n", typ);

		if (typ == spravna_odpoved) spravnespatne[j] = 1;

		else if (typ == '*')
		{
			printf("\nZadej cislo otazky: ");
			scanf("%d", &poradie);
			int g = poradie - 1;
			g = prejst_otazku(i, g, poradie, spravnespatne, a, zaciatok_c);
			j--;
		}

		else if (typ == '/')
		{
			time_t koniec_c;

			time(&koniec_c);
			double cas = difftime(koniec_c, zaciatok_c);

			FILE* fp;

			fp = fopen("..\\..\\..\\n_testy.txt", "a");

			fprintf(fp, "%d %s %d %.2lf ", a, of.testy[i], j, cas);

			int x = 0;
			while (spravnespatne[x])
			{
				fprintf(fp, "%d ", spravnespatne[x]);
				x++;
			}
			fprintf(fp, "\n");

			fclose(fp);
			exit(1);
		}

		else spravnespatne[j] = 2;
		printf("\n");
	}
	return j;
}
//
void pokracovat_v_nedokoncenom_teste(int a)
{
	FILE* fp, *tfp;

	if ((fp = fopen("..\\..\\..\\n_testy.txt", "r")) == NULL)
	{
		printf("Soubor n_testy.txt nelze otevrit.\n");
		exit(1);
	}

	int x = 0, index = 0;
	char test[MaX_STR_T];
	int pocet_odp_otazok[10] = { 0 };
	int sprspa[10][10] = { 0 };
	double cas[10] = { 0 };

	while (fscanf(fp, "%d %s %d %lf", &x, test, &pocet_odp_otazok[index], &cas[index]) == 4)
	{
		for (int y = 0; y < pocet_odp_otazok[index]; y++) fscanf(fp, "%d ", &sprspa[index][y]);
		if (a == x)
		{
			strcpy(moje.n_testy[a][index], test);
			index++;
		}
	}

	fclose(fp);

	if (index == 0)
	{
		printf("Nemate ziadne nedokoncene testy.\n");
		getchar();
		return;
	}

	printf("Vase nedokoncene testy na vyber:\n");
	for (int x = 1; x <= index; x++) printf("%d. %s\n", x, moje.n_testy[a][x - 1]);

	printf("Zadaj cislo testu: ");
	scanf("%d", &index);
	getchar();
	index -= 1;

	int i = 0;
	while (of.testy[i][0] != '\0')
	{
		if (strcmp(moje.n_testy[a][index], of.testy[i]) == 0) break;
		i++;
	}

	fp = fopen("..\\..\\..\\n_testy.txt", "r");
	tfp = fopen("temp.txt", "w");

	char temp[80] = {};
	int tem = 0, te[10] = {}, t = 0;
	double tempo = 0;
	while (fscanf(fp, "%d %s %d %lf", &t, temp, &tem, &tempo) == 4)
	{
		for (int y = 0; y < tem; y++) fscanf(fp, "%d ", &te[y]);

		if (a != t && strcmp(temp, of.testy[i]) != 0)
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

	int poradie = pocet_odp_otazok[index] + 1;
	int spravnespatne[10] = { 0 };
	double velkost = 0;
	for (int y = 0; y < poradie; ++y)
	{
		spravnespatne[y] = sprspa[index][y];
		velkost++;
	}

	int j = poradie - 1;

	printf("* = Chci se vratit k jine otazce.\n");
	printf("/ = Chci si ulozit test a ukoncit program.\n\n");

	time_t zaciatok_c, koniec_c;
	time(&zaciatok_c);

	while(of.otazky[i][j][0] != '\0')
	{
		int t = j;
		j = prejst_otazku(i, j, poradie, spravnespatne, a, zaciatok_c);

		j++;
		if (t == j)
		{
			poradie++;
			velkost++;
		}
	}

	time(&koniec_c);
	cas[index] += difftime(koniec_c, zaciatok_c);
	printf("Trvalo to: %.0f\n", cas[index]);
	printf("\n");

	x = sizeof(moje.testy[a]) / sizeof(moje.testy[a][0]) + 1;
	strcpy(moje.testy[a][x], of.testy[i]);

	double spravne_odpovede = 0;
	for (int x = 0; x <= velkost; x++) if (spravnespatne[x] == 1) spravne_odpovede++;
	moje.score[a][x] = spravne_odpovede / velkost * 100;

	printf("Tvoje hodnotenie: %.2lf percent", moje.score[a][x]);
	printf("\n");

	fp = fopen("..\\..\\..\\d_testy.txt", "a");

	fprintf(fp, "%d %s %.2lf %.2lf\n", a, moje.testy[a][x], moje.score[a][x], cas[index]);

	fclose(fp);
	while (getchar() != '\n');
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
	while (of.testy[i][0] != '\0')
	{
		printf("%d. %s\n", i + 1, of.testy[i]);
		i++;
	}
	while (getchar() != '\n');
}
//
struct h_testy* prvni = NULL;
void vsechny_hodnoceni(void)
{
	FILE* fp;

	if ((fp = fopen("..\\..\\..\\d_testy.txt", "r")) == NULL)
	{
		printf("Soubor d_testy.txt nelze otevrit.\n");
		exit(1);
	}
	 
	int my_uzivatel = 0;
	char my_test[MaX_STR_T] = {};
	double  my_cas = 0;
	double my_score = 0;

	while (fscanf(fp, "%d %s %lf %lf", &my_uzivatel, my_test, &my_score, &my_cas) == 4)
	{
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
//
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
		scanf("%79s", of.testy[of.loc2]);
		for (int x = 0; x < 100 && of.testy[of.loc2][0] != '\0'; x++) if (of.testy[of.loc2][x] == ' ') of.testy[of.loc2][x] = '_';
		for (int x = 0; x < of.loc2; x++)
		{
			if (!strcmp(of.testy[of.loc2], of.testy[x]))
			{
				printf("Test so zadanym menom uz existuje, skuste znova.\n");
				w = 1;
				break;
			}
			else w = 0;
		}
	} while (w);

	fprintf(fp, "%s ", of.testy[of.loc2]);

	printf("Zadajte pocet otazok: ");
	scanf("%d", &MAX_OT);;
	fprintf(fp, "%d ", MAX_OT);

	for (int j = 0; j < MAX_OT; j++)
	{
		printf("Zadejte otazku: ");
		scanf("%79s", of.otazky[of.loc2][j]);
		while (getchar() != '\n');

		for (int x = 0; x < 100 && of.otazky[of.loc2][j][0] != '\0'; x++) if (of.otazky[of.loc2][j][x] == ' ') of.otazky[of.loc2][j][x] = '_';

		printf("Zadajte typ of.otazky (1 = dane of.otazky, 2 = uzivatel musi zadat): ");
		scanf("%d", &typ);

		if (typ == 1)
		{
			fprintf(fp, "%s ", of.otazky[of.loc2][j]);
			fprintf(fp, "%d ", typ);
			printf("Zadajte pocet of.odpovedi: ");
			scanf("%d", &MAX_OD);
			fprintf(fp, "%d ", MAX_OD);

			for (int k = 0; k < MAX_OD; k++)
			{
				printf("Zadejte odpoved (pri spravnej zadajte *): ");
				scanf("%79s", of.odpovedi[of.loc2][j][k]);
				while (getchar() != '\n');
				fprintf(fp, "%s ", of.odpovedi[of.loc2][j][k]);

			}
		}
		else if (typ == 2)
		{
			strcat(of.otazky[of.loc2][j],"*");
			fprintf(fp, "%s ", of.otazky[of.loc2][j]);
			fprintf(fp, "%d ", typ);
			printf("Zadejte spravnu odpoved: ");
			scanf("%79s", of.odpovedi[of.loc2][j][0]);
			fprintf(fp, "%s ", of.odpovedi[of.loc2][j][0]);
		}
	}
	of.loc2++;

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
		fscanf(fp, "%s %d", of.testy[of.loc2], &pocet_otazok);

		for (int j = 0; j < pocet_otazok; j++)
		{
			int typ = 0;
			fscanf(fp, "%s %d", of.otazky[of.loc2][j], &typ);
			if (typ == 1)
			{
				int pocet_odpovedi = 0;
				fscanf(fp, "%d", &pocet_odpovedi);
				for (int k = 0; k < pocet_odpovedi; k++)
				{
					fscanf(fp, "%s", of.odpovedi[of.loc2][j][k]);
				}
			}
			else if (typ == 2)
			{
				fscanf(fp, "%s", &of.odpovedi[of.loc2][j][0]);
			}
		}
		of.loc2++;
	}

	fclose(fp);
	return of.loc2;
}
//

void vypisat(void)
{
	struct h_testy* aktTest = prvni;
	printf("\n");
	while (aktTest)
	{
		printf("%s: %s %.2lf P %.2lf s\n", uzi.jmena[aktTest->uzivatel], aktTest->test, aktTest->score, aktTest->cas);
		aktTest = aktTest->dalsi;
	}
	getchar();
}
//
void vypisat_pohl(void)
{
	struct h_testy* aktTest = prvni;
	char pohlavi[MAX_STR];
	int i = 0;
	double score = 0;
	do
	{
		printf("Zadejte pohlavi (muz/zena): ");
		scanf("%s", pohlavi);
		while (getchar() != '\n');
	} while (strcmp(pohlavi, "muz") && strcmp(pohlavi, "zena"));

	printf("\n");
	while (aktTest)
	{
		if (strcmp(pohlavi, uzi.pohlavia[aktTest->uzivatel]) == 0)
		{
			printf("%s: %s %.2lf P %.2lf s\n", uzi.jmena[aktTest->uzivatel], aktTest->test, aktTest->score, aktTest->cas);
			i++;
			score += aktTest->score;
		}
		aktTest = aktTest->dalsi;
	}
	if (i == 0) printf("\nDane pohlavie nedokoncilo ani 1 test.\n");
	else
	{
		score /= i;
		printf("\nPriemerne skore pohlavia %s: %.2lf P", pohlavi, score);
	}
	getchar();
}
//
void vypisat_vek(void)
{
	struct h_testy* aktTest = prvni;
	int z_vek, k_vek;
	int i = 0;
	double score = 0;

	printf("Zadejte vek od, do: ");
	scanf_s("%d, %d", &z_vek, &k_vek);
	while (getchar() != '\n');
	while (aktTest)
	{
		if (z_vek <= uzi.veky[aktTest->uzivatel] && uzi.veky[aktTest->uzivatel] <= k_vek)
		{
			printf("%s: %s %.2lf P %.2lf s\n", uzi.jmena[aktTest->uzivatel], aktTest->test, aktTest->score, aktTest->cas);
			i++;
			score += aktTest->score;
		}
		aktTest = aktTest->dalsi;
	}
	if (i == 0) printf("\nDane rocniky nedokoncily ani 1 test.\n");
	else
	{
		score /= i;
		printf("\nPriemerne skore rocnikov od %d do %d: %.2lf", z_vek, k_vek, score);
	}
	getchar();
}
//
void vypisat_test(void)
{
	struct h_testy* aktTest = prvni;
	char test[MaX_STR_P];
	int i = 0;
	double score = 0;

	printf("Zadejte nazev testu: ");
	scanf("%s", test);
	while (getchar() != '\n');
	while (aktTest)
	{
		if (strcmp(test, aktTest->test) == 0)
		{
			printf("%s: %s %.2lf %.2lf\n", uzi.jmena[aktTest->uzivatel], aktTest->test, aktTest->score, aktTest->cas);
			i++;
			score += aktTest->score;
		}
		aktTest = aktTest->dalsi;
	}
	if (i == 0) printf("\nDany test nedokoncil ani 1 uzivatel.\n");
	else
	{
		score /= i;
		printf("\nPriemerne skore v teste %s: %.2lf", test, score);
	}
	getchar();
}
//