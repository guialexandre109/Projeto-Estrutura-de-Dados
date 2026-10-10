
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "relatorios_pacientes.h"
#include "relatorios_ocupaçao.h"
#include "relatorios_medicos.h"

int escolha();


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
        relatorio_ocupaçao();
        break;
    case 3:
        printf("Relatorio Escolhido: Faturamento Medicos\n");
        gerar();
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

