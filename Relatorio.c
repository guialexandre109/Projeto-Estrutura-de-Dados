
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        printf("Relatorio escolhido: Pacientes-Atendimentos\n");
        relatorio_pacientes();
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

void relatorio_pacientes()
{
    //cruza os dados de atendimentos e pacientes
    // o id do paciente e uma chave primaria e esta presente em atendimentos.txt
    // para cada atendimentos extraimos o id e percorremos o arquivo ate achar id do paciente 
    FILE *arquivo;
    arquivo = fopen("arquivos_txt/pacientes.txt", "r");
    if(arquivo == NULL)
    {
        printf("erro ao abrir o arquivo\n");
        return;
    }
    
    char linha[256]; //tamanho maximo de cada linha
    lista_pacientes *inicio_pacientes = NULL;
    lista_pacientes *ultimo_pac = NULL;

    // o loop percore o arquivo e coloca as informaçoes na lista_pacientes;
    while(fgets(linha,sizeof(linha), arquivo) != NULL) //inicialmente o relatorio ira ler todo o arquivo
    {
        linha[strcspn(linha, "\r\n")] = 0;
        // strtok divide a linha em tokens pela marcaçao ";"
        char *id   = strtok(linha, ";");
        char *nom  = strtok(NULL, ";");
        char *idat = strtok(NULL, ";");
        char *sex  = strtok(NULL, ";");
        char *cpf  = strtok(NULL, ";");
        char *conv = strtok(NULL, ";");

        if (id && nom) {
            
            lista_pacientes *novo = (lista_pacientes*) malloc(sizeof(lista_pacientes));
            //strdup copia a string alocando dinamicamente
            // o operador ternario serve para evitar erro caso algum dos campos sejam vazios
            novo->id_paciente = strdup(id);
            novo->nome        = strdup(nom);
            novo->idade       = idat ? strdup(idat) : strdup("N/A");
            novo->sexo        = sex  ? strdup(sex)  : strdup("N/A");
            novo->cpf         = cpf  ? strdup(cpf)  : strdup("N/A");
            novo->convenio    = conv ? strdup(conv) : strdup("N/A");
            novo->proximo     = NULL;

            if(inicio_pacientes == NULL) inicio_pacientes = novo;
            else ultimo_pac->proximo = novo;
            ultimo_pac = novo;
        }
    }
    fclose(arquivo);

    arquivo = fopen("arquivos_txt/atendimentos.txt", "r");
    if(arquivo == NULL) 
    {
        printf("erro ao abrir o arquivo\n");
        liberar_lista_pacientes(inicio_pacientes);
        return;
    }
    printf("\n========================================================================================\n");
    printf("                  RELATORIO DE ATENDIMENTOS X PACIENTES                                 \n");
    printf("========================================================================================\n");
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        linha[strcspn(linha, "\r\n")] = 0;
        if (strlen(linha) == 0) continue;

        char *id_atd = strtok(linha, ";");
        char *id_pac = strtok(NULL, ";");
        char *crm    = strtok(NULL, ";");
        char *data   = strtok(NULL, ";");
        char *diag   = strtok(NULL, ";");

        if (id_atd && id_pac) {
            // busca o paciente  na lista que carregamos anteriormente pelo id dele
            lista_pacientes *paciente_encontrado = buscar_paciente_por_id(inicio_pacientes, id_pac);

            char *nome_paciente = (paciente_encontrado != NULL) ? paciente_encontrado->nome : "Paciente Desconhecido";
            char *convenio      = (paciente_encontrado != NULL) ? paciente_encontrado->convenio : "N/A";

            printf("Atendimento: %s | Paciente: %s | Convenio: %s | Data: %s | Diagnostico: %s\n",
                   id_atd, nome_paciente, convenio, data, diag);
        }
        
    }
    fclose(arquivo);
    lista_pacientes *atual = inicio_pacientes;
    liberar_lista_pacientes(inicio_pacientes);

}

lista_pacientes* buscar_paciente_por_id(lista_pacientes *inicio, const char *id_procurado) {
    lista_pacientes *atual = inicio;
    while (atual != NULL) {
        if (strcmp(atual->id_paciente, id_procurado) == 0) {
            return atual; // Encontrou o paciente correspondente
        }
        atual = atual->proximo;
    }
    return NULL; // Não encontrado
}
void liberar_lista_pacientes(lista_pacientes *inicio) {
    lista_pacientes *atual = inicio;
    while (atual != NULL) {
        lista_pacientes *temp = atual;
        atual = atual->proximo;
        free(temp->id_paciente);
        free(temp->nome);
        free(temp->idade);
        free(temp->sexo);
        free(temp->cpf);
        free(temp->convenio);
        free(temp);
    }
}