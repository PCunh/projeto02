#include <stdio.h>
#include "tarefas.h"




int main(){  
    funcao fs[] = {criar, deletar, listar, salvar, carregar};
  
    Tarefa tarefas[TOTAL];
    int pos = 0;
    ERROS erro = carregar(tarefas, &pos);
    if(erro != ABRIR){
      pos = 0;
      printf("Arquivo não encontrado\n");
    }
    else if (pos == LER || pos == FECHAR){
      printf("Arquivo vazio\n");
    }  
  
      int opcao;
    do{
        printf("\nMenu principal\n");
        printf("1 - Criar tarefa\n");
        printf("2 - Deletar tarefa\n");
        printf("3 - Listar tarefas\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        

        if(opcao == 1){
          criar(tarefas, &pos); 
        }else if(opcao == 2){
          deletar(tarefas, &pos);
        }else if (opcao == 3){
          listar(tarefas, pos);
        }else if (opcao == 0){
          printf("Sair...\n");
          break;
        }else {
          printf("opção inválida\n");
        }
    } while(opcao != 0);
}
