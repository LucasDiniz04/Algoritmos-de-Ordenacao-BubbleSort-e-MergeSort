#include <stdio.h>
#include <stdlib.h> //biblioteca para alocação de memória
#include <time.h> //biblioteca para manipulação de tempo

void bubbleSort(int arr[], int n) { //função de bubblesort
    int i, j, temp;
    for(i = 0; i < n-1; i++){ //ordena o array de tamanho n, e os dois 'for' sao executados repetidamente, trocando os elementos que estão na ordem errada
        for (j = 0; j < n-i-1; j++){
            if (arr[j] > arr[j+1]){

                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void merge(int arr[], int esq, int meio, int dir){ //função do merge, onde vai mesclar dois subarrays ordenados em um único subarray ordenado
    int i, j, k;
    int n1 = meio - esq + 1;
    int n2 = dir - meio;

    int Esq[n1], Dir[n2];

    for (i = 0; i < n1; i++)
        Esq[i] = arr[esq + i];
    for (j = 0; j < n2; j++)
        Dir[j] = arr[meio + 1 + j];

    i = 0;
    j = 0;
    k = esq;
    while (i < n1 && j < n2) {
        if (Esq[i] <= Dir[j]) {
            arr[k] = Esq[i];
            i++;
        } else {
            arr[k] = Dir[j];
            j++;
        }
        k++;
    }

    while (i < n1){
        arr[k] = Esq[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = Dir[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int esq, int dir){ //função que ordena o array 'arr' usando o mergesort
    if (esq < dir) {
        int meio = esq + (dir - esq) / 2; //divide o array em duas metades

        //chama de forma recursiva a função mergesort para cada metade e depois mescla as duas metades ordenadas
        mergeSort(arr, esq, meio);
        mergeSort(arr, meio + 1, dir);

        merge(arr, esq, meio, dir);
    }
}

void gerarArrayAleatorio(int arr[], int n){ //função que gera numero aleatorio
    for (int i = 0; i < n; i++) {
        arr[i] = rand();
    }
}

void copiarArray(int inicio[], int dest[], int n){  //função que copia um array pro outro
    for (int i = 0; i < n; i++) {
        dest[i] = inicio[i];
    }
}

int main(){ //função principal do programa
    srand(time(NULL)); // começa o gerador de numeros aleatórios, comando da biblioteca time

    int tamanho[] = {1000, 10000, 100000, 1000000}; //define o tamanho dos vetores
    int tamanNum = sizeof(tamanho) / sizeof(tamanho[0]); //alocação de memoria

    for (int i = 0; i < tamanNum; i++){
        int n = tamanho[i];
        int *arr1 = (int *)malloc(n * sizeof(int));
        int *arr2 = (int *)malloc(n * sizeof(int));

        gerarArrayAleatorio(arr1, n); //Para cada tamanho, aloca memória para dois arrays, gera um array aleatório e faz uma cópia dele.
        copiarArray(arr1, arr2, n);

        //trecho que vai medir o tempo do bubblesort
        clock_t start = clock();
        bubbleSort(arr1, n);
        clock_t end = clock();
        double bubbleSortTime = ((double)(end - start)) / CLOCKS_PER_SEC;

        //trecho que vai medir o tempo do mergesort
        start = clock();
        mergeSort(arr2, 0, n - 1);
        end = clock();
        double mergeSortTime = ((double)(end - start)) / CLOCKS_PER_SEC;

        //mostra os resultados na tela
        printf("Tamanho do vetor: %d\n", n); //1000, 10.000, 100.000, 1.000.000
        printf("Bubble Sort: %f segundos\n", bubbleSortTime);
        printf("Merge Sort: %f segundos\n\n", mergeSortTime);

        free(arr1); //libera a memoria
        free(arr2); // libera a memoria
    }

    return 0;
}