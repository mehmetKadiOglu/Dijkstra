#include <stdio.h>
#include "stdafx.h"
#include <stdlib.h>
#include<conio.h>
#define INFINITY 9999
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct dijkstra {

	int **G;
	int **cost;
	int *yol_maliyeti;
	int *yol;
	int *ziyaret;
	int n;
	int startnode;

};
void graf_gir(struct dijkstra *v);
void yer_ayir(struct dijkstra *v);
void dijkstraa(struct dijkstra *v);
void geri_ver(struct dijkstra *v);

int main(int argc, char *argv[]) {

	struct	dijkstra a;
	int eleman;


	do {

		printf("Graf Sayisini giriniz ");
		scanf_s("%d", &(a.n));
		graf_gir(&a);
		dijkstraa(&a);
		do 
		{
			printf("\nGitmek istediginiz graf  numarasini %d ile %d degerler arasinda giriniz.\nBaslangici degismek icin -1 \nYeni Graf Girmek icin -2  \nCikmak icin -3 ",0,a.n-1);
			scanf_s("%d",&eleman);
			if (eleman >= 0 && eleman < a.n)
			{
				printf("\nGraf uzakligi %d = %d", eleman, a.yol_maliyeti[eleman]);
				printf("  Yol=%d", eleman);
				do
				{
					eleman = a.yol[eleman];
					printf("<-%d", eleman);
				} while (eleman != a.startnode);
			}
			else if (eleman >= a.n)
			{
				printf("Lutfen Dogru Aralikda Deger Giriniz");
			}
			else if (eleman == -1)
			{
				printf("Baslangic degeri giriniz ");
				scanf_s("%d", &(a.startnode));
				dijkstraa(&a);
			}

		} while (eleman > -2);
		
		geri_ver(&a);

	} while (eleman>-3);

	return 0;
}

void dijkstraa(struct dijkstra *v)
{
	int count, mindistance, nextnode, i, j;


	for (i = 0; i<(v->n); i++)
		for (j = 0; j<(v->n); j++)
			if (v->G[i][j] == 0)
				v->cost[i][j] = INFINITY;
		else
		v->cost[i][j] = v->G[i][j];
	
	for(i=0;i<(v->n);i++)
	{
	v->yol_maliyeti[i]=v->cost[v->startnode][i];
	v->yol[i]=v->startnode; 
	v->ziyaret[i]=0;
	}

	v->yol_maliyeti[v->startnode]=0;
	v->ziyaret[v->startnode]=1;
	count=1;

	while(count<(v->n)-1)
	{
		mindistance=INFINITY;

		for(i=0;i<(v->n);i++)
			if(v->yol_maliyeti[i]<mindistance&&!v->ziyaret[i])
			{
				mindistance=v->yol_maliyeti[i];
				nextnode=i;
			}

		v->ziyaret[nextnode]=1;

		for(i=0;i<(v->n);i++)
		if(!v->ziyaret[i])
			if(mindistance+v->cost[nextnode][i]<v->yol_maliyeti[i])
			{
				v->yol_maliyeti[i]=mindistance+v->cost[nextnode][i];
				v->yol[i]=nextnode;
			}
	count++;
	}


}


void graf_gir(struct dijkstra *v) {
	int i, j;
	yer_ayir(v);
	printf("iliskileri giriniz \n");
	
	for (i = 0; i<(v->n); i++)
	{
		for (j = i; j<(v->n); j++)
		{
			scanf_s("%d", &(v->startnode));
			v->G[i][j] = v->startnode;
			v->G[j][i] = v->startnode;

		}
	}
	printf("Baslangic grafini giriniz ");
	scanf_s("%d", &(v->startnode));

	system("CLS");

	printf("Graflar \n");

	for (i = 0; i<(v->n); i++)
	{
		for (j = 0; j<(v->n); j++)
		{
			printf("%d ", v->G[i][j]);
		}
		printf("\n");
	}

	printf("Baslangic grafi= %d\n", v->startnode);


}
void yer_ayir(struct dijkstra *v) {
	int i;
	v->G = (int **)malloc((v->n) * sizeof(int));
	v->cost = (int **)malloc((v->n) * sizeof(int));
	for (i = 0; i<(v->n); i++)
	{
		v->G[i] = (int *)malloc((v->n) * sizeof(int));
		v->cost[i] = (int *)malloc((v->n) * sizeof(int));
	}

	v->yol = (int *)malloc((v->n) * sizeof(int));
	v->yol_maliyeti = (int *)malloc((v->n) * sizeof(int));
	v->ziyaret = (int *)malloc((v->n) * sizeof(int));

}
void geri_ver(struct dijkstra *v) {

	system("cls");
	free(v->cost);
	free(v->ziyaret);
	free(v->G);
	free(v->yol);
	free(v->yol_maliyeti);
}

