
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "relatorios_pacientes.h"
#include "relatorio_ocupaçao.h"
typedef struct lista_atendimentos{
        char *id_atedimento;
        char *id_paciente; //chave estrangeira
        char *CRM;
        char *data;
        char *diagnostico;
        struct lista_atendimentos *proximo;
    } lista_atendimentos;

typedef struct lista_pacientes {
    char *id_paciente;    // chave primaria
    char *nome;
    char *idade;
    char *sexo;
    char *cpf;
    char *convenio;
    struct lista_pacientes *proximo;
} lista_pacientes;

void liberar_lista_pacientes(lista_pacientes *inicio);
lista_pacientes* buscar_paciente_por_id(lista_pacientes *inicio, const char *id_procurado);
int escolha();
void abrir_arquivo(const char *arquivo);
void relatorio_pacientes();

int main()
{
    int relatorio = escolha();
    switch (relatorio)
    {
    case 1:
        printf("Relatorio Escolhido: Pacientes-Atendimentos\n");
        relatorio_pacientes();
        break;
    case 2:
        printf("Relatorio Escolhido: Ocupacao de Quartos/Leitos\n");
        
        break;
    default:
        break;
    }
    return 0;
}

int escolha()
{
    int alternativa;
    do {
        printf("==================================================\n");
        printf("        GERADOR DE RELATORIOS HOSPITALARES        \n");
        printf("==================================================\n");
        printf("Selecione o modelo de relatorio desejado:\n");
        printf("[1] Relatorio de Prontuario do Paciente (pacientes.txt)\n");
        printf("[2] Relatorio de Ocupacao de Quartos/Leitos (leitos.txt)\n");
        printf("[3] Relatorio de Faturamento por Medico (medicos.txt)\n");
        printf("[4] Relatorio de Estoque e Validade de Remedios (medicamentos.txt)\n");
        printf("> Opcao: ");
        scanf("%d", &alternativa);
        getchar(); //limpa o buffer
        if (alternativa < 1 || alternativa > 4) {
            printf("Opcao invalida! Tente novamente.\n\n");
        }
    } while (alternativa < 1 || alternativa > 4);
    return alternativa;
}

