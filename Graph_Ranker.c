#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#define MAX 3000000
typedef struct {
    int valsomma;
    int indi;
}ind;

void max_heapify(ind A[],int indice,int grandezzaheap){
    int largest;
    int tmp;
    int left = 2*indice;                   //left child
    int right = (2*indice) +1;           //right child

    if(left <= grandezzaheap && right <=grandezzaheap){
        if(A[left].valsomma>A[indice].valsomma) {
            if (A[left].valsomma > A[right].valsomma)
                largest = left;
            else {
                if (A[left].valsomma == A[right].valsomma)
                    if (A[left].indi > A[right].indi)
                        largest = left;
                    else
                        largest = right;
                else
                    largest = right;
            }
        }
        else{
            if(A[left].valsomma==A[indice].valsomma){
                if(A[right].valsomma>A[left].valsomma)
                    largest=right;
                else{
                    if(A[right].valsomma==A[left].valsomma){
                        if(A[right].indi>A[left].indi) {
                            if (A[right].indi > A[indice].indi)
                                largest = right;
                            else
                                largest = right;
                        }
                        else {
                            if (A[left].indi > A[indice].indi)
                                largest = left;
                            else
                                largest = indice;
                        }
                    }
                    else{
                        if(A[left].indi>A[indice].indi)
                            largest=left;
                        else
                            largest=indice;
                    }
                }
            }
            else{
                if(A[right].valsomma>A[indice].valsomma)
                    largest=right;
                else
                if(A[right].valsomma==A[indice].valsomma) {
                    if (A[right].indi > A[indice].indi)
                        largest = right;
                    else
                        largest = indice;
                }
                else
                    largest=indice;
            }
        }
    }
    else
    if(left<=grandezzaheap){  //allora right >grandezzaheap
        if(A[left].valsomma>A[indice].valsomma)
            largest=left;
        else
        if(A[left].valsomma==A[indice].valsomma)
            if(A[left].indi>A[indice].indi)
                largest=left;
            else
                largest=indice;
        else
            largest=indice;
    }
    else
    if(right <= grandezzaheap){  //allora left > grandezzaheap
        if(A[right].valsomma>A[indice].valsomma)
            largest=right;
        else
        if(A[right].valsomma==A[indice].valsomma)
            if(A[right].indi>A[indice].indi)
                largest=right;
            else
                largest=indice;
        else
            largest=indice;
    }
    else  //entrambi > grandezzaheap
        largest=indice;

    if(largest != indice )
    {
        tmp=A[indice].valsomma;
        A[indice].valsomma=A[largest].valsomma;
        A[largest].valsomma=tmp;
        tmp=A[indice].indi;
        A[indice].indi=A[largest].indi;
        A[largest].indi=tmp;
        max_heapify (A, largest,grandezzaheap);
    }
}

void crea_max_heap(ind A[],int grandezzaheap) {
    int i;
    if(grandezzaheap!=1)
        for(i = grandezzaheap/2 ; i >=1 ; i-- )
        {
            max_heapify (A, i,grandezzaheap) ;
        }
}

void sostmax(ind A[], int val,int ind,int grandezzaheap)
{
    A[1].valsomma=val;
    A[1].indi=ind;
    max_heapify(A,1,grandezzaheap);
}

int mindist(unsigned long int V[],int vis[],unsigned long int n)
{

    int min,i,j,c,k;
    j=1;
    min=INT_MAX;
    c=0;
    k=1;
    for(i=1;i<n;i++){
        if(V[i]<min && vis[i]==0)
        {min=V[i];
            j=i;
            c=1;
        }
        else
            if(V[i]==INT_MAX){
                k=i;
            }
    }
    if(c==1)
    return j;
    else
        return k;
}

int Dijkstra(unsigned long int n,unsigned long int m[][n])
{
    int i,vis[n],somma,g,k,c;
    unsigned long int lung,dist[n];
    for(i=0;i<n;i++) {
        dist[i] = INT_MAX;
        vis[i]=0;
    }
    dist[0]=0;
//Parte per il nodo sorgente
    g =0;
    c=0;
    k=1;
    for(k=1;k<n;k++) {
        if (m[g][k] != 0) {
            c = 1;
            lung = dist[g] + m[g][k];
            if (lung < dist[k]) {
                dist[k] = lung;
            }
        }
    }
    //Parte per il nodo sorgente
    somma=0;
    if(c==1) {
        for (i = 1; i < n; i++) {
            g = mindist(dist, vis, n); //Trova la posizione del minimo in dist
            if (dist[g] == INT_MAX)
                break;
            vis[g] = 1;
            for (k = 1; k < n; k++)
                if (m[g][k] != 0 && g != k) {
                    lung = dist[g] + m[g][k];
                    if (lung < dist[k]) {
                        dist[k] = lung;
                    }
                }
        }
        for (i = 1; i < n; i++)
            if (dist[i] != INT_MAX)
                somma = somma + dist[i];
    }
    return somma;
}


int main() {
    char stringain[20];
    char top[6] = {'T', 'o', 'p', 'K', '\n', '\0'};
    char *ptr;
    char *c;
    int i, j, s, cont, grandezzaheap;
    unsigned long int n, k;
    c = fgets(stringain, 19, stdin);
    n = strtoul(stringain, &ptr, 10);
    k = strtoul(ptr + 1, &ptr, 10);
    char stringa[n * 10 + n + 10];
    unsigned long int m[n][n];
    ind A[k+1];
    grandezzaheap = 0;
    cont = 0;
    while (!feof(stdin)) {
        c = fgets(stringa, MAX, stdin);   //AggiungiGrafo
        if (feof(stdin))
            break;
        while (strcmp(stringa, top) != 0) {
            for (i = 0; i < n; i++) {
                j = 0;
                c = fgets(stringa, MAX, stdin);
                m[i][j] = strtoul(stringa, &ptr, 10);
                for (j = 1; j < n; j++) {
                    m[i][j] = strtoul(ptr + 1, &ptr, 10);
                }
            }

            s = Dijkstra(n, m);     //aggiustare dijkstra
            if (cont < k) {     //se cont==k faccio crea_maxheap, cont>k faccio sostmax
                grandezzaheap++;
                A[cont + 1].valsomma = s;
                A[cont + 1].indi = cont;
            }
            else {
                if (cont == k) {
                    crea_max_heap(A, grandezzaheap);
                }
                if (s < A[1].valsomma)
                    sostmax(A, s, cont, grandezzaheap);
            }
            cont++;
            c = fgets(stringa, MAX, stdin);
            //Ci arriva stampando giusto
        }
        //E' arrivato un Topk e devo stampare i k indici
        if (grandezzaheap == 0)
            printf("\n");
        else {
            for (i = 1; i < grandezzaheap; i++)
                printf("%d ", A[i].indi);
            printf("%d\n", A[grandezzaheap].indi);
        }
        //c=fgets(stringa,MAX,stdin);
    }
}
