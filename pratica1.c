#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int dia, mes;
} Data;

typedef struct {
    char nome[40];
    char telefone[15];
    char celular[15];
    char email[40];
    Data aniversario;
} Contato;

typedef struct elemento {
    Contato info;
    struct elemento* prox;
} Elemento;

typedef Elemento* Lista;

Lista cria_agenda() {
    return NULL;
}

Contato ler_contato() {
    Contato c;
    printf("Nome: "); fgets(c.nome, 40, stdin); strtok(c.nome, "\n");
    printf("Telefone: "); fgets(c.telefone, 15, stdin); strtok(c.telefone, "\n");
    printf("Celular: "); fgets(c.celular, 15, stdin); strtok(c.celular, "\n");
    printf("Email: "); fgets(c.email, 40, stdin); strtok(c.email, "\n");
    printf("Data de Aniversário (dia mes): ");
    scanf("%d %d", &c.aniversario.dia, &c.aniversario.mes);
    getchar();
    return c;
}

Lista insere_contato(Lista lista, Contato c) {
    Elemento* novo = (Elemento*) malloc(sizeof(Elemento));
    novo->info = c;
    novo->prox = NULL;

    if (lista == NULL) return novo;

    Elemento* p = lista;
    while (p->prox != NULL) p = p->prox;
    p->prox = novo;
    return lista;
}

void lista_contatos(Lista lista) {
    Elemento* p = lista;
    if (!p) { printf("Agenda vazia!\n"); return; }
    while (p != NULL) {
        printf("\nNome: %s\nTelefone: %s\nCelular: %s\nEmail: %s\nAniversário: %02d/%02d\n",
               p->info.nome, p->info.telefone, p->info.celular,
               p->info.email, p->info.aniversario.dia, p->info.aniversario.mes);
        p = p->prox;
    }
}

Elemento* busca_contato(Lista lista, char* nome) {
    Elemento* p = lista;
    while (p != NULL) {
        if (strcmp(p->info.nome, nome) == 0)
            return p;
        p = p->prox;
    }
    return NULL;
}

Lista remove_contato(Lista lista, char* nome) {
    Elemento *ant = NULL, *p = lista;
    while (p != NULL && strcmp(p->info.nome, nome) != 0) {
        ant = p;
        p = p->prox;
    }
    if (p == NULL) {
        printf("Contato não encontrado!\n");
        return lista;
    }
    if (ant == NULL) lista = p->prox;
    else ant->prox = p->prox;
    free(p);
    printf("Contato removido!\n");
    return lista;
}

void atualiza_contato(Lista lista, char* nome) {
    Elemento* p = busca_contato(lista, nome);
    if (p == NULL) {
        printf("Contato não encontrado!\n");
        return;
    }
    printf("=== Atualizar contato ===\n");
    p->info = ler_contato();
    printf("Contato atualizado!\n");
}

int main() {
    Lista agenda = cria_agenda();
    int opc;
    char nome[40];

    do {
        printf("\n=== MENU ===\n");
        printf("1. Inserir Contato\n2. Listar Contatos\n3. Buscar Contato\n4. Editar Contato\n5. Remover Contato\n6. Sair\nEscolha: ");
        scanf("%d", &opc);
        getchar();

        switch (opc) {
            case 1:
                agenda = insere_contato(agenda, ler_contato());
                break;
            case 2:
                lista_contatos(agenda);
                break;
            case 3:
                printf("Nome para buscar: ");
                fgets(nome, 40, stdin); strtok(nome, "\n");
                Elemento* e = busca_contato(agenda, nome);
                if (e)
                    printf("Encontrado: %s - %s\n", e->info.nome, e->info.celular);
                else
                    printf("Contato não encontrado.\n");
                break;
            case 4:
                printf("Nome para editar: ");
                fgets(nome, 40, stdin); strtok(nome, "\n");
                atualiza_contato(agenda, nome);
                break;
            case 5:
                printf("Nome para remover: ");
                fgets(nome, 40, stdin); strtok(nome, "\n");
                agenda = remove_contato(agenda, nome);
                break;
        }
    } while (opc != 6);

    return 0;
}
