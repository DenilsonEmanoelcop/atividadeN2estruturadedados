#include <stdio.h>
#include <stdlib.h>

int* cria_vetor(int n) {
    return (int*) malloc(n * sizeof(int));
}

void imprime_vetor(int* v, int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}

void libera_vetor(int* v) {
    free(v);
}

int main() {
    int n;
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &n);

    int* vetor = cria_vetor(n);
    for (int i = 0; i < n; i++) {
        printf("Elemento %d: ", i + 1);
        scanf("%d", &vetor[i]);
    }

    printf("Vetor: ");
    imprime_vetor(vetor, n);

    libera_vetor(vetor);
    return 0;
}
