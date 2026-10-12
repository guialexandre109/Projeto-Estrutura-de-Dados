#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "relatorios_remedios.h"

typedef struct medicamentos{
    char *codigo;
    char *nome;
    int qntd_estoque;
    char *validade;
    float preço;
    struct medicamentos *proximo;
}medicamentos;

void gerar_medicamentos(){
    FILE *arquivo;
    arquivo = fopen("arquivos_txt/medicamentos.txt", "r");

    char linha[256];

    medicamentos *inicio = NULL;
    medicamentos *ultimo = NULL;

    while(fgets(linha,sizeof(linha),arquivo))
    {
        linha[strcspn(linha, "\r\n")] = 0;
        
        char *aux_codigo = strtok(linha,";");
        char *aux_nome = strtok(NULL,";");
        char *aux_estoque = strtok(NULL,";");
        char *aux_validade = strtok(NULL,";");
        char *aux_preço = strtok(NULL,";");

        medicamentos *novo = (medicamentos*) malloc(sizeof(medicamentos));

        novo->codigo = strdup(aux_codigo);
        novo->nome = strdup(aux_nome);
        novo->validade = strdup(aux_validade);
        novo->qntd_estoque = atoi(aux_estoque);
        novo->preço = atof(aux_preço);

        novo->proximo = NULL;

        if(inicio == NULL) inicio = novo;
        else ultimo->proximo = novo;
        ultimo = novo;
    }
    fclose(arquivo);
    
    printf("\n========================================================================================\n");
    printf("                  RELATÓRIO DE MEDICAMENTOS EM ESTOQUE                                  \n");
    printf("========================================================================================\n");

    medicamentos *atual = inicio;
    while (atual != NULL) {
        printf("Código: %s | Nome: %s | Estoque: %d | Validade: %s | Preço: R$ %.2f\n",
               atual->codigo,
               atual->nome,
               atual->qntd_estoque,
               atual->validade,
               atual->preço);

        atual = atual->proximo;
    }

    atual = inicio;
    while (atual != NULL) {
        medicamentos *temp = atual;
        atual = atual->proximo;

        free(temp->codigo);
        free(temp->nome);
        free(temp->validade);
        free(temp);
    }
}


