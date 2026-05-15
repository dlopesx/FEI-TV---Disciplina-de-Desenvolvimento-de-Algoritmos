#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <stdbool.h>
#include <unistd.h>
#include "funcoes.h"

typedef struct{ // struct que armazena usuarios

    char nome[50];
    char username[256];
    char senha[20];

}Usuario;

// FUNCAO DE CADASTRAR USUARIO

void cadastrar_usuario(){ 

    Usuario usuario = {0}; // struct base pra cadastrar um por vez na funçao

    printf("\nInsira um apelido: ");
    fgets(usuario.nome, sizeof(usuario.nome), stdin); 
    usuario.nome[strlen(usuario.nome) - 1] = '\0';

    printf("Insira um username: ");
    fgets(usuario.username, sizeof(usuario.username), stdin);
    usuario.username[strlen(usuario.username) - 1] = '\0';

    // VERIRICANDO SE username EXISTE
    
    char nome_temp[50], username_temp[256], senha_temp[20]; // variaveis de teste
    
    while (1){

        FILE *usuarios_verificacao = fopen("usuarios.txt", "r");

        bool username_invalido = false;

        while (fscanf(usuarios_verificacao, "%[^,],%[^,],%[^,\n]\n", nome_temp, username_temp, senha_temp) == 3){

            if (strcmp(username_temp, usuario.username) == 0){
                username_invalido = true;
                break; // para de ler o arquivo pq deu erro
            };
        };
        fclose(usuarios_verificacao);

        // validando pra ver se o username digitado é válido 
        if (username_invalido == true){
            printf("Esse username já está cadastrado. Digite um válido: ");
            fgets(usuario.username, sizeof(usuario.username), stdin);
            usuario.username[strlen(usuario.username) - 1] = '\0';
        }
        else{
            break;
        }
    };

    printf("Crie uma senha: ");
    fgets(usuario.senha, sizeof(usuario.senha), stdin);
    usuario.senha[strlen(usuario.senha) - 1] = '\0';

    // abrindo arquivo e cadastrando usuario
 
    FILE *usuarios = fopen("usuarios.txt", "a");
    FILE *likes = fopen("likes.txt", "a"); // inicia uma linha de curtidas para cada usuario

    fprintf(usuarios, "%s,%s,%s\n", usuario.nome, usuario.username, usuario.senha);
    fprintf(likes, "%s\n", usuario.username);

    fclose(usuarios);
    fclose(likes);

    printf("\nUsuário cadastrado com sucesso! Voltando ao menu de login...\n");
    Sleep(2000);
    system("cls");
}

// funcao de verificar se o username existe
int verificar_username(char* nome_user, char *username, char *senha){

    char nome[50], username_temp[256], senha_temp[50];

    FILE *usuarios = fopen("usuarios.txt", "r");

    while(fscanf(usuarios, "%[^,],%[^,],%[^,\n]\n", nome, username_temp, senha_temp) == 3){
        if (strcmp(username, username_temp) == 0){
            strcpy(nome_user, nome);
            strcpy(username, username_temp);
            strcpy(senha, senha_temp);
            fclose(usuarios);
            return 1;
            }
        }
    fclose(usuarios);
    return 0;
    
}

// FUNCAO DE LOGIN 

void logar_usuario(char *usernamecpy){

    char nome_usuario[256], senha[20], username[50], senha_digitada[50];

    printf("\nDigite o username cadastrado ou 0 para voltar: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    if (strcmp(username, "0") == 0){
        printf("Voltando...");
        Sleep(1000);
        system("cls");
        return;
    }

    while(1){

        if (verificar_username(nome_usuario, username, senha) == 1){
            printf("Digite sua senha: ");
            fgets(senha_digitada, sizeof(senha_digitada), stdin);
            senha_digitada[strcspn(senha_digitada, "\n")] = '\0';

            while (1){
                if (strcmp(senha, senha_digitada) == 0){
                    system("cls");
                    printf("\nBem-vindo(a), %s!\n", username);
                    strcpy(usernamecpy, username);
                    break;
                }
                else{
                    printf("Senha inválida. Tente novamente: ");
                    fgets(senha_digitada, sizeof(senha_digitada), stdin);
                    senha_digitada[strcspn(senha_digitada, "\n")] = '\0';
                }
            }

            break;
        }
        else{
            printf("Esse username não existe. Tente novamente ou 0 para voltar: ");
            fgets(username, sizeof(username), stdin);
            username[strcspn(username, "\n")] = '\0';
            if (strcmp(username, "0") == 0){
               printf("Voltando...");
               Sleep(2000);
               system("cls");
               return;
            }
        }
    }
    
    menu_principal(username);
}
