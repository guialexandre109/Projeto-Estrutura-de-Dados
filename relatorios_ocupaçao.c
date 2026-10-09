#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "relatorios_ocupaçao.h"

typedef  struct quartos{
    char *numero_quarto;
    char *ala;
    char *tipo;
    char *status;
    char *id_pacientes; // = 0 quarto livre
    struct quartos  *proximo;
} quartos;

void liberar(quartos *atual)
{
    while(atual != NULL)
    {
        quartos *temp = atual;
        atual = atual->proximo;

        free(temp->numero_quarto);
        free(temp->ala);
        free(temp->tipo);
        free(temp->status);
        free(temp->id_pacientes);
        free(temp);
    }
}

void relatorio_ocupaçao()
{
    FILE *arquivo;
    arquivo = fopen("arquivos_txt/leitos.txt", "r");
    if(arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    char linha[256];
    quartos *inicio = NULL;
    quartos *ultimo = NULL;
    
    int livres = 0, ocupados = 0;
    while(fgets(linha,sizeof(linha),arquivo) != NULL)
    {
        //remove  a quebra  de linha 
        linha[strcspn(linha, "\r\n")] = 0;
        // strtok divide a linha em tokens pela marcaçao ";"
        char *aux_numero_quarto =  strtok(linha,";");
        char *aux_ala = strtok(NULL,";");
        char *aux_tipo = strtok(NULL,";");
        char *aux_status = strtok(NULL,";");
        char *aux_id_pacientes = strtok(NULL,";");

        quartos *novo = (quartos*) malloc(sizeof(quartos));
        //strdup copia a string alocando dinamicamente
        // o operador ternario serve para evitar erro caso algum dos campos sejam vazios
        novo->numero_quarto = strdup(aux_numero_quarto);
        novo->ala = strdup(aux_ala);
        novo->tipo  = strdup(aux_tipo);
        novo->status = strdup(aux_status);
        novo->id_pacientes = strdup(aux_id_pacientes);
        novo->proximo = NULL;
        if(inicio == NULL) inicio = novo;
        else ultimo->proximo = novo;
        ultimo = novo;
        if(atoi(aux_id_pacientes) == 0) livres++;
        else ocupados++;
    }
    fclose(arquivo);
    printf("\n========================================================================================\n");
    printf("                  RELATORIO DE OCUPAÇAO DE LEITOS                                         \n");
    printf("==========================================================================================\n");
    quartos *atual = inicio;
    while(atual != NULL)
    {
        printf("Numero do quarto: %s | Ala: %s | Tipo: %s | Status: %s | Id Pacientes: %s\n",
               atual->numero_quarto, atual->ala, atual->tipo, atual->status, atual->id_pacientes);
        atual = atual->proximo;
    }
    
    atual = inicio;
    liberar(atual);
}
