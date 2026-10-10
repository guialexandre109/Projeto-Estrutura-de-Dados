#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "relatorios_medicos.h"

typedef struct medicos{
    char *crm;
    char *nome;
    char *especialidade;
    char *valorconsulta;
    char *atendimentos;
    float faturamento;
    struct medicos *proximo;
}medicos;


void gerar()
{
    FILE *arquivo;
    arquivo = fopen("arquivos_txt/medicos.txt", "r");
    
    char linha[256];
    medicos *inicio = NULL;
    medicos *ultimo = NULL;

    while(fgets(linha,sizeof(linha),arquivo)!=NULL)
    {
        //remove  a quebra  de linha 
        linha[strcspn(linha, "\r\n")] = 0;

        char *aux_crm = strtok(linha,";");
        char *aux_nome = strtok(NULL,";");
        char *aux_especialidade = strtok(NULL,";");
        char *aux_valorconsulta = strtok(NULL,";");
        char *aux_atendimentos = strtok(NULL,";");


        medicos *novo = (medicos*) malloc(sizeof(medicos));
        
        novo->crm = strdup(aux_crm);
        novo->nome = strdup(aux_nome);
        novo->especialidade = strdup(aux_especialidade);
        novo->valorconsulta = strdup(aux_valorconsulta);
        novo->atendimentos = strdup(aux_atendimentos);
        
        novo->faturamento = atof(aux_valorconsulta) * atoi(aux_atendimentos);

        novo->proximo = NULL;

        if(inicio == NULL) inicio = novo;
        else ultimo->proximo = novo;
        ultimo = novo;
    }
    fclose(arquivo);
    
    printf("\n========================================================================================\n");
    printf("                  RELATORIO DE FATURAMENTO/MEDICOS                                        \n");
    printf("==========================================================================================\n");

    medicos *atual = inicio;
    while (atual != NULL)
    {
        printf("CRM: %s | Nome: %s | Especialidade: %s | Valor Consulta: R$ %s | Atendimentos: %s | Faturamento: R$ %.2f\n",
               atual->crm, 
               atual->nome, 
               atual->especialidade, 
               atual->valorconsulta, 
               atual->atendimentos, 
               atual->faturamento);

        atual = atual->proximo;
    }
    
    atual = inicio;
    while (atual != NULL)
    {
        medicos *temp = atual;
        atual = atual->proximo;

        free(temp->crm);
        free(temp->nome);
        free(temp->especialidade);
        free(temp->valorconsulta);
        free(temp->atendimentos);
        free(temp);
    }

}


