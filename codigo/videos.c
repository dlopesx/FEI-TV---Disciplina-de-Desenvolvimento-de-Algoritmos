#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include "funcoes.h"

int pesquisar_filme(char *titulo, char *ano, char *duracao, char *descricao, char *nota_letterboxd){

    char titulo_inserido[102], titulo_t[102], ano_t[5], duracao_t[7], descricao_t[502], nota_letterboxd_t[5];

    printf("\nDigite o título do filme: ");
    fgets(titulo_inserido, sizeof(titulo_inserido), stdin);
    titulo_inserido[strcspn(titulo_inserido, "\n")] = '\0';

    FILE *filmes = fopen("filmes.txt", "r");

    if (filmes == NULL){
        printf("Erro ao abrir o arquivo filmes.txt. Reinicie o programa.\n");
        return 0;
    }

    while (fscanf(filmes, "%[^;];%[^;];%[^;];%[^;];%[^;];\n", titulo_t, ano_t, duracao_t, descricao_t, nota_letterboxd_t) == 5){
        if (strcmp(titulo_inserido, titulo_t) == 0){
            strcpy(titulo, titulo_t);
            strcpy(ano, ano_t);
            strcpy(duracao, duracao_t);
            strcpy(descricao, descricao_t);
            strcpy(nota_letterboxd, nota_letterboxd_t);

            printf("\n==============================================================================================\n");
            printf("Título: %s\n", titulo);
            printf("Ano: %s\n", ano);
            printf("Duração: %s\n", duracao);
            printf("Sinopse: %s\n", descricao);
            printf("Avaliação no Letterboxd: %s\n", nota_letterboxd);
            printf("\n==============================================================================================\n");
            fclose(filmes);
            return 1;
        }
    };
    printf("\nOps, não encontramos nenhum título com esse nome.\n");
    fclose(filmes);
    return 2;
}

int verificar_se_curtido(char *titulo, char *usernamecpy){
    char linhaAtual[1024], username_temp[50];
    
    FILE *likes = fopen("likes.txt", "r");

    while (fgets(linhaAtual, sizeof(linhaAtual), likes)){

        linhaAtual[strcspn(linhaAtual, "\n")] = '\0';

        sscanf(linhaAtual, "%[^;]", username_temp);

        char *filme = strtok(linhaAtual, ";"); // pega nome do usuario
        filme = strtok(NULL, ";"); // pega o filme

        if (strcmp(username_temp, usernamecpy) == 0){ // verifica se é o usuario

            while (filme != NULL){ // verificando filme a filme

                if (strcmp(filme, titulo) == 0){ 
                    fclose(likes);
                    return 0; // usuario já curtiu o filme
                }
                filme = strtok(NULL, ";");
            }
            fclose(likes);
            return 1; // se passou pelo loop todo, usuario nao curtiu o filme
        };
        
    }
    fclose(likes);
}

void curtir_video(char *titulo, char *usernamecpy, char* comando){
    
    // char titulo_inserido[102], titulo_t[102], ano_t[5], duracao_t[7], descricao_t[502], nota_letterboxd_t[5], 
    char linhaAtual[1024], nova_linha[1024] = {0}, linha_atual_temporaria[1024] = {0}, username_temp[50];
    char like[] = "like";
    char deslike[] = "deslike";
    
    FILE *likes = fopen("likes.txt", "r");
    FILE *likes_novo = fopen("likes_novo.txt", "w");

    while (fgets(linhaAtual, sizeof(linhaAtual), likes)){

        linhaAtual[strcspn(linhaAtual, "\n")] = '\0';

        sscanf(linhaAtual, "%[^;]", username_temp);
        strcpy(linha_atual_temporaria, linhaAtual);

        char *filme = strtok(linhaAtual, ";"); // pega nome do usuario
        filme = strtok(NULL, ";"); // pega o filme

        if (strcmp(username_temp, usernamecpy) == 0){ // curte/descurte só se for a linha do usuario

            if (strcmp(comando, like) == 0){ // executa se o comando foi para curtir
                fprintf(likes_novo, "%s;%s\n", linha_atual_temporaria, titulo);
                printf("\nFilme curtido. Voltando...\n");
                Sleep(3000);
                system("cls");
            }
            else if (strcmp(comando, deslike) == 0){ // executa se o comando foi para descurtir

                strcat(nova_linha, usernamecpy); // reescrevendo a nova linha
                strcat(nova_linha, ";");

                while (filme != NULL){ // inicia a logica de remover o filme da linha enquanto percorre a linha atual

                    if (strcmp(filme, titulo) != 0){ // reescreve somente quando não é o filme a descurtir
                        strcat(nova_linha, filme);
                    }
                    filme = strtok(NULL, ";");
                }
                fprintf(likes_novo, "%s\n", nova_linha);
                nova_linha[0] = '\0';

                printf("\nVocê descurtiu esse filme. Voltando...\n");
                Sleep(3000);
                system("cls");
            };
        }
        else{
            fprintf(likes_novo, "%s\n", linha_atual_temporaria); // se nao for a linha do usuario, só escreve sem modificar
        };
    };

    fclose(likes);
    fclose(likes_novo);

    remove("likes.txt");
    rename("likes_novo.txt", "likes.txt");
}
