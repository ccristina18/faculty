#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 100


int A[MAXN];
int chei[MAXN];
unsigned int contor;
unsigned long a;

//functia insereaza un nod cu cheieN ca fiu la nodul cu cheieT
//functia retureneaza < 0 in caz de eroare
int insereaza(int cheieN, int cheieT)
{
	int i;
	for (i = 0; i < MAXN; i++)
	{
		if (chei[i] == cheieT) // i index pt T
			break;
	}
	if (chei[i] != cheieT)
	{
		printf("Insereaza(): Nu am gasit cheia pentru T nodul tata\n");
		return -1;
	}
	if (contor == MAXN)
	{
		printf("insereaza(): Arborele A este plin. contor == MAXN!\n");
		return -1;
	}
	A[contor] = i; // i este indexul pentru T 
	chei[contor] = cheieN;
	contor++;
	return 0; // totul e ok
}
//functia returneaza parintele nodului N din arborele A 
int tata(int cheieN)
{
	int i;
	for (i = 0; i < contor; i++)
	{
		if (chei[i] == cheieN)
			break;
	}
	if (chei[i] != cheieN)
	{
		printf("tata(): Nu am gasit nodul N in arborele A");
		return -1;
	}
	return chei[A[i]]; //returneaza cheia parintelui pt nodul N
}

int suprima(int cheieN) //functia suprima nodul cu cheieN si toti descendentii sai
{
	int i,j;
	for (i = 0; i < contor;i++)
	{
		if (chei[i] == cheieN) break;
	}
	if (chei[i] != cheieN)
	{
		printf("Suprima(): nu exista cheia pe care doriti sa o stergeti!\n");
		return -1;
	}
	chei[i] = 0;
	A[i] = 0; //radacina are si ea parinte pe 0,dar e mereu pe pozitia i=0
	for (j = 0; j < contor; j++)
	{
		if (A[j] == i) suprima(chei[j]);
	}
}
//functia returneaza primul fiu al nodului cu cheia cheieN din A
int primulfiu(int cheieN)
{
	int i,j;
	for (i = 0; i < contor; i++)
	{
		if (chei[i] == cheieN)
			break;
	}
	if (chei[i] != cheieN)
	{
		printf("primul fiu(): Nu am gasit nodul cu cheia cheieN\n");
		return -1;
	}
	for (j = 0; j < contor; j++)
	{
		if (A[j] == i)
			break;
	}
	if (A[j] != i)
	{
		printf("primulfiu(): Nodul cu cheia cheieN nu are fii.\n");
		return -1;
	}
	return chei[j]; //cheia primului fiu al nodului cu cheia cheieN
}

int fratedreapta(int cheieN, int cheieT) //returneaza nodul care este fratele din din dreapta
{
	int i = 0;
	int j = 0;
	for (j = 2; j < contor; j++) //parcurgem primul fiu 
	{
		if (chei[j] == cheieN)
		{
			break;
		}
	}
	for (i = cheieN + 1; i < contor; i++) //parcurgem partea dreapta a arborelui, cu valori mai mari decat cheieN
	{
		if (cheieT == cheieN)
			return i;
	}
	return NULL;

}

int cheie(int cheieN, int i)
{
	return  chei[A[i]];
}

int radacina(void)
{
	if (contor == 0)
	{
		printf("Arborele este vid!\n");
		return -1;
	}
	else return chei[0];
}
void initializeaza(void)
{
	int i;
	for (i = 0; i < contor; i++)
	{
		chei[i] = 0;
		A[i] = 0;
	}
	contor = 0;
	return;
}

FILE *output;
void inordine(int cheieN) //cautare pe principiul: stanga->radacina->dreapta
{
	int aux1, aux2;
	if (cheieN > 0)
	{
		inordine(A, primulfiu(A, contor));
		if (!cheieN && cheie(A, cheieN) != -1) //citire din fisier
		{
			fprintf(output, "%d ", cheie(A, cheieN));
			cheieN = 1;
		}

		aux1 = fratedreapta(A, cheie(A, primulfiu(A, cheieN)));
		aux2 = fratedreapta(A, cheie(A, aux1));

		while (aux1 || aux2)
		{
			if (aux1)
				inordine(A, aux1);  //daca aux1 este primul fiu,se parcurge inordinea de la primul fiu

			if (aux2)
				inordine(A, aux2);

			aux1 = primulfiu(A, aux1);
			aux2 = fratedreapta(A, cheie(A, aux2));
		}

	}
}

void preordine(int cheieN) //radacina->stanga->dreapta
{
	int aux1, aux2;
	if (cheieN > 0)  //cautam radacina
	{
		if (!cheieN && cheie(A, cheieN));
		cheieN = 1;
	}
	preordine(A, primulfiu(A, cheieN));

	aux1 = fratedreapta(A, cheie(A, primulfiu(A, cheieN)));
	aux2 = fratedreapta(A, cheie(A, aux1));

	while (aux1 || aux2)  //in functie de radacina parcurgem arborele
	{
		if (aux1)
			preordine(A, aux1);

		if (aux2)
			preordine(A, aux2);

		aux1 = primulfiu(A, aux1);
		aux2 = fratedreapta(A, cheie(A, aux2));
	}

}

void postordine(int cheieN)//stanga->dreapta->radacina
{
	int aux1, aux2;
	if (cheieN > 0)  //cautam cel mai din stanga nod(frunza)
	{
		postordine(A, primulfiu(A, cheieN));

		aux1 = fratedreapta(A, cheie(A, primulfiu(A, cheieN)));
		aux2 = fratedreapta(A, cheie(A, aux1));

		while (aux1 || aux2)
		{
			if (aux1)
				postordine(A, aux1);

			if (aux2)
				postordine(A, aux2);

			aux1 = primulfiu(A, aux1);
			aux2 = fratedreapta(A, cheie(A, aux2));
		}

		if (!cheieN && cheie(A, cheieN) != -1) //inregisteaza info in fisierul de iesire 
		{
			fprintf(output, "%d ", cheie(A, cheieN));
			cheieN = 1;
		}

	}
}
int main(void)
{
	int auxx = 0;
	int i = 0;
	unsigned long t = 1;
	char fis[20];
	int opt = 1;
	int radacina1;


	FILE*fp;
	/*printf("Numele fisierului:");  //dam informatiile pentru fisierul de intrare
	if (scanf("%s", fis) != 1)
	{
		perror("scanf");
	}
	if ((input = fopen(fis, "rb")) == NULL)
	{
		perror("fopen");
		return -1;
	}*/
	fp = fopen("INPUT.BIN", "wb");
	if (fp == NULL) {
		perror("fopen()");
		return -1;
	}

	if ((output = fopen("DATA.OUT", "w")) == NULL) //info pentru fisierul de iesire
	{
		perror("fopen");
		exit(-1);
	}

	fseek(fp, 0, SEEK_END); //fisier binar
	contor = ftell(fp) / sizeof(unsigned);
	fseek(fp, 0, SEEK_SET);

	while (opt)
	{
		printf("1.Afisarea tatalui unui nod.\n");
		printf("2.Afisare primul fiu.\n");
		printf("3.Afisare frate dreapta.\n");
		printf("4.Afisare cheie.\n");
		printf("5.Afisare radacina.\n");
		printf("6.Parcurgere in inordine.\n");
		printf("7.Parcurgere in preordine.\n");
		printf("8.Parcurgere in postordine.\n");
		printf("9.Stergerea unui nod.\n");
		printf("0.Iesire.\n");
		printf("Alegeti o optiune:");

		if (scanf("%d", &opt) != 1) //se alege o optiune 
		{
			perror("scanf");
		}

		switch (opt)
		{

		case 1: printf("\nDati cheia nodul dorit: "); //returneaza tatal nodului 

			if (scanf("%d", &i) != 1)
			{
				perror("scanf");
			}

			if (i > contor)
			{
				printf("Nodul nu apartine arborelui cautat!\n\n");
			}

			i = tata(A, cheie(A, i)); //functia ''Tata '' 
			if (i > 0)
			{
				printf("Tatal nodului cu cheia %d este nodul %d cu cheia %d.\n\n", auxx, i, cheie(A, i));
			}

			else if (i == -1)
			{
				printf("Nodul a fost sters din arbore!\n\n");
			}

			else
			{
				printf("Nodul este radacina sau arborele nu a fost initializat!\n");
			}
			break;

		case 2: printf("\nDati nodul: "); // returneaza PrimulFiu

			if (scanf("%d", &i) != 1)
			{
				perror("scanf");
			}

			if (i > contor)
			{
				printf("Nodul nu apartine arborelui!\n\n");
			}

			i = primulfiu(A, auxx);

			if (i > 0)
			{
				printf("Primul fiu al nodului %d este  nodul %d cu cheia %d.\n", auxx, i, cheie(A, i));
			}

			else if (i == -1)
			{
				printf("Nodul a fost sters din arbore.\n");
			}

			else
			{
				printf("Nodul este o frunza.\n");
			}
			break;
		case 3: printf("Dati nodul: "); //returneaza frate dreapta 

			if (scanf("%d", &i) != 1)
			{
				perror("scanf");
			}

			if (i > contor)
			{
				printf("Nodul nu apartine arborelui!\n\n");
			}

			i = fratedreapta(A, cheie(A, auxx));

			if (i > 0)
			{
				printf("Fratele de drapta al nodului %lu este  nodul %lu cu cheia %lu.\n\n", auxx, i, cheie(A, i));
			}

			else if (i == -1)
			{
				printf("Nodul a fost sters din arbore!\n\n");
			}

			else
			{
				printf("Nodul nu are un frate de dreapta!\n\n");
			}
			break;
		case 4: //cheia-criteriu de cautare dintr-un arbore
			printf("\nDati nodul: ");
			if (scanf("%d", &auxx) != 1)
			{
				perror("scanf");
			}

			if (auxx > contor)
			{
				printf("Nodul nu apartine arborelui!\n\n");
			}

			else if (cheie(A, auxx) == -1)
			{
				printf("Nodul a fost sters din arbore!\n\n");
			}

			else
			{
				printf("Cheia nodului %lu este %lu.\n\n", auxx, cheie(A, auxx));
			}

			break;
		case 5: //initializeaza radacina arborelui 
			if ((radacina1 = radacina(A)) == -1)
			{
				printf("\nArborele nu a fost initializat!\n");
			}

			else
			{
				printf("\nRdacina arborelul este: %d\n", radacina1);
			}
			break;
		case 6:
			printf("Parcurgerea in inordine:");

			inordine(A, 1);
			fprintf(output, "\n");
			break;
		case 7:
			printf("Parcurgere prin preodine:");

			preordine(A, 1);
			fprintf(output, "\n");
			break;
		case 8:
			printf("Parcurgere in postordine:");

			postordine(A, 1);
			fprintf(output, "\n");
			break;
		case 9:
			printf("Nodul este: ");
			if (scanf("%d", &a) != 1)
			{
				perror("scanf");
			}

			if (a > contor)
			{
				printf("Nodul nu apartine arborelui!\n");
			}

			else
			{
				suprima(A, a);
			}
			break;

		case 0: break;

		default: printf("Optiune gresita!");
		}
	}

	for (i = 1; i < contor; i++)
	{
		printf("%d  %d   %d    %d\n", i, chei[i], A[i]); //afisam elementele structurii arbore 
	}

	fclose(fp); //inchidem fisierul de intrare
	fclose(output); //inchidem fisierul de iesire

	getch();
	return 0;
}
