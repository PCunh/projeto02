#include <stdio.h>
#include "tarefas.h"

int main() {  
    funcao *fs[] = {criar, deletar, listar, salvar, carregar, exportarTarefas};

    Tarefa tarefas[TOTAL];
    int pos = 0;
    ERROS erro = carregar(tarefas, &pos);
    if (erro == ABRIR) {
        pos = 0;
        printf("Arquivo não encontrado\n");
    } else if (erro == LER || erro == FECHAR) {
        printf("Arquivo vazio\n");
    }

    int opcao;
    do {
        printf("\nMenu principal\n");
        printf("1 - Criar tarefa\n");
        printf("2 - Deletar tarefa\n");
        printf("3 - Listar tarefas\n");
        printf("4 - Exportar tarefas para arquivo\n");
        printf("5 - Carregar tarefas do arquivo\n"); // Opção adicionada
        printf("6 - Salvar tarefas em arquivo binário\n"); // Opção adicionada
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        clearBuffer(); 

        if (opcao == 1) {
            fs[0](tarefas, &pos); 
        } else if (opcao == 2) {
            fs[1](tarefas, &pos);
        } else if (opcao == 3) {
            fs[2](tarefas, pos); 
        } else if (opcao == 4) {
            fs[5](tarefas, &pos); // Chama a função de exportar tarefas

        } else if (opcao == 5) {
            erro = carregar(tarefas, &pos); // Chama a função de carregar tarefas
            if (erro == ABRIR)
                printf("Erro ao abrir o arquivo para leitura.\n");
            else if (erro == LER)
                printf("Erro ao ler o arquivo.\n");
            else if (erro == FECHAR)
                printf("Erro ao fechar o arquivo.\n");
            else
                printf("Tarefas carregadas com sucesso do arquivo.\n");
        } else if (opcao == 6) {
            erro = salvar(tarefas, &pos); // Chama a função de salvar tarefas
            if (erro == ABRIR)
                printf("Erro ao abrir o arquivo para escrita.\n");
            else if (erro == ESCREVER)
                printf("Erro ao escrever no arquivo.\n");
            else if (erro == FECHAR)
                printf("Erro ao fechar o arquivo.\n");
            else
                printf("Tarefas salvas com sucesso no arquivo.\n");
        } else if (opcao == 0) {
            printf("Sair...\n");
            break;
        } else {
            printf("opção inválida\n");
        }
    } while (opcao != 0);

    return 0;
}