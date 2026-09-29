
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const char *escolha();
void abrir_arquivo(const char *arquivo);

int main()
{
    const char *arquivo_escolhido = escolha();
    if (arquivo_escolhido == NULL)
        return 1;
    printf("Arquivo escolhido: %s\n", arquivo_escolhido);
    abrir_arquivo(arquivo_escolhido);

    return 0;
}

const char *escolha()
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
    switch (alternativa) {
        case 1: return "pacientes.txt";
        case 2: return "leitos.txt";
        case 3: return "medicos.txt";
        case 4: return "medicamentos.txt";
    }
    return NULL;
}

void abrir_arquivo(const char *arquivo_escolhido)
{   
    FILE *arquivo;
    arquivo = fopen(arquivo_escolhido, "r");
    if(arquivo == NULL)
    {
        printf("erro ao abrir arquivo\n");
        return;
    }
    char linha[256]; //tamanho maximo da linha 
    int numero_linha = 1;
    //ler o arquivo ate chegar o fim, depois podemos modificar para o usuario escolher a qntd de colunas ou linhas
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("Linha %d: %s", numero_linha, linha);
        numero_linha++;
    }


}