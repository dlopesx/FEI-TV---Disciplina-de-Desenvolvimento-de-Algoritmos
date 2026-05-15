#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <unistd.h>
#include <windows.h>
#include "funcoes.h"
#include "favoritos.h"
#include "videos.h"
#include "usuario.h"

void menu_pesquisar_filme(char *titulo, char *ano, char *duracao, char *descricao, char *nota_letterboxd, char *usernamecpy){

    char comando[8];

    printf("Escolha uma opção: ");

    if (verificar_se_curtido(titulo, usernamecpy) == 1){ // só exibe a opcao de curtir se o usuario nao tiver curtido
        printf(
        "\n[ 1 ] - Curtir filme\n"
        );
        strcpy(comando, "like");
    }
    else if (verificar_se_curtido(titulo, usernamecpy) == 0){ // só exibe a opcao de descurtir se o usuario ja curtiu
        printf(
        "\n[ 1 ] - Descurtir filme\n"
        );
        strcpy(comando, "deslike");
    }

   printf(
        "[ 2 ] - Adicionar filme na playlist\n"
        "[ 3 ] - Voltar\n"
        "\nOpção: ");

    while (1){

        char opcao;
            scanf(" %c", &opcao);
            getchar();
    
        switch (opcao)
            {
            case '1':
                curtir_video(titulo, usernamecpy, comando);
                return;
            case '2': 
                if (mostrar_playlists(usernamecpy) != 1){
                    adicionar_filme(titulo, usernamecpy);
                    return;
                }
                return;
            case '3':
                printf("\n");
                printf("Voltando...\n");
                Sleep(2000);
                system("cls");
                return;
            default:
                printf("\nPor favor, selecione uma opção válida: ");
                break;
            }
    }
    }

void menu_playlists(char *usernamecpy){

    char titulo[102], ano[6], duracao[7], descricao[502], nota_letterboxd[5], opcao;

    printf(
        "\nSelecione uma opção:\n"
        "\n[ 1 ] - Adicionar filme em lista de reprodução\n"
        "[ 2 ] - Remover filme de lista de reprodução\n"
        "[ 3 ] - Voltar\n"
        "Sua opção: "
    );
    while (1){

        
        scanf(" %c", &opcao);
        getchar();

        switch(opcao){
            case '1':
                if (pesquisar_filme(titulo, ano,duracao,descricao,nota_letterboxd) != 2){
                adicionar_filme(titulo, usernamecpy);
                return;
            }
                return;
            case '2':
                if (pesquisar_filme(titulo, ano,duracao,descricao,nota_letterboxd) != 2){
                remover_filme(titulo, usernamecpy);
                return;
                }
            case '3':

                return;
            default:
                printf("\nPor favor, selecione uma opção válida: ");
                break;
        }
    }

}

void menu_principal(char *usernamecpy){

    char titulo[102], ano[6], duracao[7], descricao[502], nota_letterboxd[5];
    
    while (1){

        printf(
        "\n================ PÁGINA INICIAL ================\n"
        "[ 1 ] - Pesquisar filme\n"
        "[ 2 ] - Criar lista de reprodução de filmes\n"
        "[ 3 ] - Deletar lista de reprodução\n"
        "[ 4 ] - Acessar listas de reprodução\n"
        "[ 5 ] - Voltar ao login\n"
        "\nOpção: ");
        
        char opcao;
            
        scanf(" %c", &opcao);
        getchar();
        system("cls");

        switch (opcao)
        {
        case '1':
            printf("Você selecionou: [ 1 ] - Pesquisar filme\n");
            if (pesquisar_filme(titulo, ano,duracao,descricao,nota_letterboxd) != 2){
                menu_pesquisar_filme(titulo, ano, duracao, descricao, nota_letterboxd, usernamecpy);
                break;
            };
            break;
        case '2': 
            printf("Você selecionou: [ 2 ] - Criar lista de reprodução de filmes\n");
            printf("\n");
            criar_lista(usernamecpy);
            break;
        case '3':
            printf("Você selecionou: [ 3 ] - Deletar lista de reprodução\n");
            printf("\n");
            if (mostrar_playlists(usernamecpy) == 1){
                break;
            }
            else{
                excluir_lista(usernamecpy);
            }
            break;
        case '4':
            printf("Você selecionou: [ 4 ] - Acessar listas de reprodução\n");
            printf("\n");
            if (mostrar_playlists(usernamecpy) == 1){
                break;
            }
            else{
                menu_playlists(usernamecpy);
            }
            break;
        case '5':
            printf("Você selecionou: [ 5 ] - Voltar ao login\n");
            printf("\n");
            return;
            break;
        default:
            printf("\nPor favor, selecione uma opção válida: ");

        }
    }
}


void menu_login(){

    char usernamecpy[50]; 

    while (1){

        printf(
        "\n=======================================================\n"
        "                       FEI TV                          \n"
        "=======================================================\n"
        "[ 1 ] - Cadastrar novo usuário\n"
        "[ 2 ] - Efetuar login\n"
        "[ 0 ] - Sair\n"
        "\nOpção: ");

        char opcao;
            
        scanf(" %c", &opcao);
        getchar();

        switch (opcao)
        {
        case '0':
             printf("Saindo do programa...");
             Sleep(3000);
            exit(0);
        case '1': 
            cadastrar_usuario();
            break;
        case '2':
            logar_usuario(usernamecpy);
            break;
        default:
            printf("\nPor favor, selecione uma opção                válida: ");
        }
    }
}

int main(){
    setlocale(LC_ALL, "Portuguese");
   menu_login();
   system("pause");
   return 0;
};
