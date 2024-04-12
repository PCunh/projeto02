#include "tarefas.h"
#include <stdio.h>
#include <string.h>
#define TOTAL 100

void extermina_linha(char *str) {
  int len = strlen(str);
  if (len > 0 && str[len - 1] == '\n') {
    str[len - 1] = '\0';
  }
}

ERROS criar(Tarefa tarefas[], int *pos) {
  if (*pos >= TOTAL)
    return MAX_TAREFA;

  printf("Entre com a prioridade (entre 1 a 10): ");
  scanf("%d", &tarefas[*pos].prioridade);
  if (tarefas[*pos].prioridade < 1 ||       tarefas[*pos].prioridade > 10)
    printf("Prioridade inválida , o limite é entre 1 e 10 tente novamente!\n"); 
  //return MAX_TAREFA;
  clearBuffer();

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

  for (int i = 0; i < pos; i++) {
    printTarefas(tarefas[i], pos);
  }

  return OK;
}

ERROS salvar(Tarefa tarefas[], int *pos) {
  FILE *f = fopen("tarefas.bin", "wb");
  if (f == NULL)
    return ABRIR;

  int qtd = fwrite(tarefas, *pos, sizeof(Tarefa), f);
  if (qtd != *pos)
    return ESCREVER;

  qtd = fwrite(&pos, sizeof(int), 1, f);
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

  int qtd = fread(tarefas, TOTAL, sizeof(Tarefa), f);
  if (qtd == 0)
    return LER;

  qtd = fwrite(pos, 1, sizeof(int), f);
  if (qtd != sizeof(int))
    return LER;

  if (fclose(f) != 0)
    return FECHAR;

  return OK;
}

void printTarefas(Tarefa t, int pos) {
  printf("Posição da tarefa: %d\n", pos);
  printf("Prioridade: %d\n", t.prioridade);
  printf("Categoria: %s\n", t.categoria);
  printf("Descrição: %s\n", t.descricao);
}

void clearBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}
