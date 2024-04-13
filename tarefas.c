#include "tarefas.h"
#include <stdio.h>
#include <string.h>

void extermina_linha(char *str) {
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        continue;
    }
}

ERROS criar(Tarefa tarefas[], int *pos) {
    if (*pos >= TOTAL)
        return MAX_TAREFA;

    printf("Entre com a prioridade(entre 1 a 10): ");
    scanf("%d", &tarefas[*pos].prioridade);
    if (tarefas[*pos].prioridade < 1 || tarefas[*pos].prioridade > 10) {
        printf("O limite da prioridade é 1 a 10! Tente Novamente\n");
        return OK; // Retorna OK aqui para indicar que a tarefa não foi criada devido à prioridade inválida
    }

    clearBuffer(); // Limpa o buffer do teclado para evitar problemas de entrada

    printf("Entre com a categoria: ");
    fgets(tarefas[*pos].categoria, 100, stdin);
    extermina_linha(tarefas[*pos].categoria);

    printf("Entre com a descricao: ");
    fgets(tarefas[*pos].descricao, 300, stdin);
    extermina_linha(tarefas[*pos].descricao);

    *pos = *pos + 1;

    return OK;
}

ERROS deletar(Tarefa tarefas[], int *pos) {
    // teste se existem tarefas
    if (*pos == 0)
        return SEM_TAREFAS;

    // verifica se a tarefa escolhida existe
    int pos_deletar;
    printf("Entre com a posicao da tarefa a ser deletada: ");
    scanf("%d", &pos_deletar);
    pos_deletar--; // garantir posicao certa no array
    if (pos_deletar >= *pos || pos_deletar < 0)
        return NAO_ENCONTRADO;

    for (int i = pos_deletar; i < *pos - 1; i++) {
        tarefas[i].prioridade = tarefas[i + 1].prioridade;
        strcpy(tarefas[i].categoria, tarefas[i + 1].categoria);
        strcpy(tarefas[i].descricao, tarefas[i + 1].descricao);
    }

    *pos = *pos - 1;

    return OK;
}

ERROS listar(Tarefa tarefas[], int pos) {
    if (pos == 0)
        return SEM_TAREFAS;

    char categoria[100];
   

    printf("Entre com a categoria das tarefas que deseja listar: ");

    fgets(categoria, 100, stdin);
    extermina_linha(categoria);

    int encontradas = 0;
    for (int i = 0; i < pos; i++) {
        if (categoria[0] == '\0' || strcmp(tarefas[i].categoria, categoria) == 0) {
            printf("--------------------------------------------------------\n");
            printf("Posição da tarefa: %d\n", i + 1); 
            printf("Prioridade: %d\n", tarefas[i].prioridade);
            printf("Categoria: %s\n", tarefas[i].categoria);
            printf("Descrição: %s\n", tarefas[i].descricao);
            encontradas++;
        }
    }

    if (encontradas == 0)
        printf("Nenhuma tarefa encontrada com a categoria especificada.\n");

    return OK;
}

ERROS salvar(Tarefa tarefas[], int *pos) {
    FILE *f = fopen("tarefas.bin", "wb");
    if (f == NULL)
        return ABRIR;

    int qtd = fwrite(tarefas, *pos, sizeof(Tarefa), f);
    if (qtd != *pos)
        return ESCREVER;

    qtd = fwrite(pos, sizeof(int), 1, f);
    if (qtd != 1)
        return ESCREVER;

    if (fclose(f) != 0)
        return FECHAR;

    return OK;
}

ERROS carregar(Tarefa tarefas[], int *pos) {
    FILE *f = fopen("tarefas.bin", "rb");
    if (f == NULL)
        return ABRIR;

    int qtd = fread(tarefas, *pos, sizeof(Tarefa), f); // Corrigido para ler a quantidade correta de tarefas
    if (qtd == 0)
        return LER;

    qtd = fread(pos, sizeof(int), 1, f); // Corrigido para ler a posição correta
    if (qtd != 1)
        return LER;

    if (fclose(f) != 0)
        return FECHAR;

    return OK;
}

ERROS exportarTarefas(Tarefa tarefas[], int *pos) {
  printf("Entre com o nome do arquivo para exportacao: ");
  char nomeArquivo[100];
  scanf("%s", nomeArquivo);
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return ABRIR;
    }

    for (int i = 0; i < pos; i++) {
        fprintf(arquivo, "Posição da tarefa: %d\n", i + 1); // Corrigido para imprimir a posição correta
        fprintf(arquivo, "Prioridade: %d\n", tarefas[i].prioridade);
        fprintf(arquivo, "Categoria: %s\n", tarefas[i].categoria);
        fprintf(arquivo, "Descrição: %s\n\n", tarefas[i].descricao);
    }

    fclose(arquivo);
    printf("Tarefas exportadas com sucesso para o arquivo: %s\n", nomeArquivo);
    return OK;
}