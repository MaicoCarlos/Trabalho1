#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct
{
  int topo;
  int  el[200];
} Pilha;


typedef struct
{
  int fim;
  int  el[200];
} Visitados;

typedef struct
{
    int  el[200];
} Status;

typedef struct
{
    int adj[200][200];
    int indice_inc;
    int max;
} Vetor;

void cria_vetores(Vetor *mVetor, Visitados *mvis, Status *mstatus, Pilha *mpilha, int maximo){
    for (int i=0; i<maximo;i++)
       for (int j=0; j<maximo;j++)
          mVetor->adj[i][j] = 0;

     mVetor->indice_inc=0;
     mVetor->max=maximo;

   for (int i=0; i<maximo; i++){
      mvis->el[i]=0;
   }
    mvis->fim=0;

    for (int i=0; i<maximo;i++){
      mstatus->el[i]=0;
   }
    for (int i=0; i<maximo;i++){
      mpilha->el[i]=0;
   }
    mpilha->topo=0;

}

void cria_aresta(Vetor *mVetor){

    mVetor->adj[0][1] = 1;
	mVetor->adj[0][3] = 1;
	mVetor->adj[1][2] = 1;
	mVetor->adj[1][4] = 1;
	mVetor->adj[2][3] = 1;
	mVetor->adj[2][5] = 1;
	mVetor->adj[3][7] = 1;
	mVetor->adj[4][5] = 1;
	mVetor->adj[5][6] = 1;
	mVetor->adj[5][8] = 1;
	mVetor->adj[5][9] = 1;
	mVetor->adj[6][3] = 1;
	mVetor->adj[6][7] = 1;
	mVetor->adj[6][9] = 1;

}

void zerabusca(Vetor *mVetor, Visitados *mvis, Status *mstatus, Pilha *mpilha){
    int maximo = mVetor->max;
    for (int i=0; i<maximo;i++){
      mvis->el[i]=0;
	}
    mvis->fim=0;

    for (int i=0; i<maximo;i++){
      mstatus->el[i]=0;
    }

    for (int i=0; i<maximo;i++){
      mpilha->el[i]=0;
    }
    mpilha->topo=0;
}

void imprime_adj(Vetor *mVetor){
    printf("\n				 Matriz 								\n");
    printf("							\n");

    for(int i=0; i<mVetor->max;i++)
           if(i==0){
               printf("|\tV0");
            }else if(i!=(mVetor->max-1)){
               printf("\tV%d",i);
           }else{
              printf("\tV%d\t|",i);
          }
    for(int i=0; i<mVetor->max;i++){
             printf("\n|V%d\t",i);
       for (int j=0;j<mVetor->max;j++){
        printf("%d\t",mVetor->adj[i][j]);
        }
        printf("|");
        }
     printf("\n------------------\n\n");
    }

void busca_profundidade (Vetor *mvetor, Visitados *mVis, Status *mstatus, Pilha *mpilha, int inicio){

      int novoinicio =99;
     
     
      if(mstatus->el[inicio]!=1){
          mVis->el[mVis->fim]= inicio;
          mVis->fim++;
          mstatus->el[inicio]=1;
      }


	  for (int i=0; i<mvetor->max; i++)
          if(mvetor->adj[i][inicio]==1){
                      if(novoinicio==99){
                          if(mstatus->el[i]==0){
                               novoinicio=i;
                           }
                       }else if(mstatus->el[i]!=1){
                           mpilha->el[mpilha->topo]=i;
                           mpilha->topo++;
                           mstatus->el[i]=2;
                       }
            }


            if(novoinicio!=99){
              busca_profundidade(mvetor, mVis, mstatus, mpilha, novoinicio);
            }else if(mpilha->topo!=0){
			                 mpilha->topo--;

                 busca_profundidade(mvetor, mVis, mstatus, mpilha, mpilha->el[mpilha->topo]);
              
            }else{
                printf("\n			 Resultado da Busca \n");
                  printf("			\n");


                for (int i=0;i<mVis->fim;i++){
                     printf("%d\t",mVis->el[i]);
                }
                 printf("\n------------\n");
                }
}

int main(){
	int op,vp,vu,valor,novo;
    Vetor mVetor;
    Pilha mPilha;
    Visitados mVisitados;
    Status mStatus;

    printf("\n		---------Matriz de 8 x 8-----------\n\n ");
    novo = 8;
    cria_vetores(&mVetor,&mVisitados, &mStatus, &mPilha, novo);
	printf("\n");

    do	{
	    cria_aresta(&mVetor);
        imprime_adj(&mVetor);

        printf ("1|- Realizar Busca\n");
        printf ("2|- Sair\n");

        printf("\n===============================================================================\n");
        printf("\n");
        scanf("%d", &op);
		switch(op)
		{
			case 1:{ zerabusca(&mVetor,&mVisitados, &mStatus, &mPilha);	// usado para limpar qualquer busca feita antes.
              printf("Digite o vertice inicial da Busca: ");
                        scanf("%d",&vp);	// digita o número para encontrar o caminho
                        busca_profundidade(&mVetor, &mVisitados, &mStatus, &mPilha, vp); // busca os caminhos para chegar até o número fornecido no "vp"
                        system ("pause");
                        break; }
		}
	}
	while (op!=2);
		return 1;
}

