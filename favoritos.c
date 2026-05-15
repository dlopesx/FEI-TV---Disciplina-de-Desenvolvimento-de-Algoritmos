#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include <locale.h>
#include "funcoes.h"
#include <unistd.h>

int verificar_existencia(char *arquivo_playlists, char *lista_desejada, char *usernamecpy){

    char verificar_temp[50], linha_atual[1024], username_temp[50];

    FILE *file = fopen(arquivo_playlists, "r");

    while(fgets(linha_atual, sizeof(linha_atual), file)){

        sscanf(linha_atual, "%[^;];%[^;]", username_temp, verificar_temp);

        if (strcmp(lista_desejada, verificar_temp) == 0 && strcmp(username_temp, usernamecpy) == 0){
            fclose(file);
            return 1; // se existir retorna 1
            }
        }
    fclose(file);
    return 0; // se nao existir retorna 0
}

void criar_lista(char *usernamecpy){
    
    char nome_lista[50], linha_atual[] = {0};

    printf("\nInsira um nome para a sua lista de reprodução (máx. 50 caracteres): ");

    while (1){

        fgets(nome_lista, sizeof(nome_lista), stdin);
        nome_lista[strcspn(nome_lista, "\n")] = '\0';

        if (strcmp(nome_lista, "0") == 0){
            return;
        }

        if (verificar_existencia("playlists.txt", nome_lista, usernamecpy) == 1){
            printf("Essa lista já existe. Digite novamente ou 0 para voltar: \n ");
        }
        else{
            break;
        }
    };

    FILE *playlists = fopen("playlists.txt", "a");

    fprintf(playlists, "%s;%s;\n", usernamecpy, nome_lista);

    fclose(playlists);

    printf("\nA lista '%s' foi criada com sucesso! Voltando ao menu...\n", nome_lista);
    Sleep(3000);
    system("cls");
}

void excluir_lista(char *usernamecpy){

    char nome_lista[50], nome_lista_temp[50], linha_atual[1024] = {0}, username_temp[50];

    printf("\n");
    printf("Nome da lista a deletar: ");
    
    while (1){

        fgets(nome_lista, sizeof(nome_lista), stdin);
        nome_lista[strcspn(nome_lista, "\n")] = '\0';

        if (verificar_existencia("playlists.txt", nome_lista, usernamecpy) == 0){
            if (strcmp(nome_lista, "0") == 0){
                return;
            }
            printf("\nEssa lista não existe. Digite novamente ou 0 para voltar: \n ");
        }
        else{
            break;
        }
    };

    FILE *playlists = fopen("playlists.txt", "r");
    FILE *playlists_nova = fopen("playlists_nova.txt", "w");

    while (fgets(linha_atual, sizeof(linha_atual), playlists)){ // pega cada linha e transforma numa string

        linha_atual[strcspn(linha_atual, "\n")] = '\0'; // tirando o \n da linha atual

        sscanf(linha_atual, "%[^;];%[^;]", username_temp, nome_lista_temp); // compara a primeira variavel da linha atual com oq foi digitado
        if (strcmp(nome_lista, nome_lista_temp) != 0 || strcmp(usernamecpy, username_temp) != 0){
            fprintf(playlists_nova, "%s\n", linha_atual);
        }
    } 
    fclose(playlists);
    fclose(playlists_nova);
    
    printf("\nLista deletada com sucesso! Voltando ao menu...\n");
    Sleep(3000);
    system("cls");

    remove("playlists.txt");
    rename("playlists_nova.txt", "playlists.txt");
}

void adicionar_filme(char *filme, char*usernamecpy){

    char nome_lista[50], nome_lista_temp[50], linha_atual[1024] = {0}, username[50];

    printf("\nAdicionar em qual lista de reproducao: ");

    while (1){

        fgets(nome_lista, sizeof(nome_lista), stdin);
        nome_lista[strcspn(nome_lista, "\n")] = '\0';

        if (strcmp(nome_lista, "0") == 0){
            system("cls");
            printf("Voltando...");

            return;
        }

        if (verificar_existencia("playlists.txt", nome_lista, usernamecpy) == 1){ // verificando se o filme ja existe na playlist

            FILE *playlists = fopen("playlists.txt", "r");

            while (fgets(linha_atual, sizeof(linha_atual), playlists)){
                
                sscanf(linha_atual, "%[^;]", username); // guarda o nome do usuario na variavel diferente de strtok q sempre vai mudar

                char *filme_atual = strtok(linha_atual, ";"); // pega o nome do usuario
                char *nome_lista_atual = strtok(NULL, ";"); // pega o nome da lista
                
                if (strcmp(nome_lista, nome_lista_atual) != 0 || strcmp(usernamecpy, username) != 0) continue; // se a lista que eu estiver nao for a lista que eu quero, pula pra proxima iteração do loop pq senao ele vai dar erro msm quando n tiver nada na lista!!

                filme_atual = strtok(NULL, ";"); // pega o filme!!
                
                while (filme_atual != NULL){

                    if (strcmp(filme, filme_atual) == 0){
                        printf("\nEste filme já está nessa lista. Voltando em 4s...\n");
                        Sleep(4000);
                        system("cls");
                        fclose(playlists);  
                        return;
                    
                    };
                    filme_atual = strtok(NULL, ";");
                }
            }
            fclose(playlists);
            break;
            
        }
        else{
            printf("Lista não encontrada. Digite novamente ou 0 para voltar: ");
        };
    };

    FILE *playlists = fopen("playlists.txt", "r");
    FILE *playlists_nova = fopen("playlists_nova.txt", "w");

    while (fgets(linha_atual, sizeof(linha_atual), playlists)){ // pega cada linha e transforma numa string
    
        linha_atual[strcspn(linha_atual, "\n")] = '\0'; // tirando o \n da linha atual

        sscanf(linha_atual, "%[^;];%[^;]", username, nome_lista_temp);

        if (strcmp(nome_lista, nome_lista_temp) == 0 && strcmp(username, usernamecpy) == 0){
            fprintf(playlists_nova, "%s;%s\n", linha_atual, filme);
        }
        else{
            fprintf(playlists_nova, "%s\n", linha_atual);
        }
        
    }
    fclose(playlists);
    fclose(playlists_nova);
    
    printf("\nFilme adicionado com sucesso! Voltando ao menu...\n");
    Sleep(3000);
    system("cls");


    remove("playlists.txt");
    rename("playlists_nova.txt", "playlists.txt");
}


int mostrar_playlists(char *usernamecpy){

    char linha_atual[1024] = {0}, usuario[50], nome_playlist[600];
    int contador = 0;
    
    FILE *arq_filmes = fopen("playlists.txt", "r");

    while (fgets(linha_atual, sizeof(linha_atual), arq_filmes)){

        linha_atual[strcspn(linha_atual, "\n")] = '\0';
        sscanf(linha_atual, "%[^;]", usuario);

        if (strcmp(usuario, usernamecpy) == 0){
            contador++;
        }
    }

    if (contador == 0){
        printf("\nN�o existe nenhuma lista de reprodu��o. Voltando...\n");
        fclose(arq_filmes);
        Sleep(3000);
        system("cls");
        return 1;
    };
    
    rewind(arq_filmes); // metodo para voltar o ponteiro pro começo do arquivo!

    printf(
    "------------------------------------------------------\n"
    "               PLAYLISTS DO USUÁRIO              "
    );
    
    while(fgets(linha_atual, sizeof(linha_atual), arq_filmes)){
        
        linha_atual[strcspn(linha_atual, "\n")] = '\0';

        sscanf(linha_atual, "%[^;];%[^;]", usuario, nome_playlist);

        char *filme = strtok(linha_atual, ";"); // pega usuario no comeco
        
        if (strcmp(usernamecpy, usuario) != 0) continue;

        char *nome_playlist_temp = strtok(NULL, ";"); // pega nome da lista
        filme = strtok(NULL, ";"); // pega nome do filme

        printf("\n------------------------------------------------------\n");
        printf("Playlist: %s\n", nome_playlist);
        printf("Filmes: ");


        while (filme != NULL){

            printf("%s, ", filme);
            filme = strtok(NULL, ";");

        };
        
    };
    printf("\n------------------------------------------------------\n");
    fclose(arq_filmes);
    return 0;
};

void remover_filme(char *filme, char* usernamecpy){

    char nome_lista[50], nome_lista_temp[50], linha_atual[1024] = {0}, nova_linha[1024] = {0}, username[50],  linha_atual_temporaria[1024] = {0};

    while (1){

        printf("\n Remover da lista: ");
        fgets(nome_lista, sizeof(nome_lista), stdin);
        nome_lista[strcspn(nome_lista, "\n")] = '\0';

        if (verificar_existencia("playlists.txt", nome_lista, usernamecpy) == 1){
            break;
        }
        else{
            printf("Lista não encontrada. Digite novamente: ");
        }
    };

    FILE *playlists = fopen("playlists.txt", "r");
    FILE *playlists_nova = fopen("playlists_nova.txt", "w");

    while (fgets(linha_atual, sizeof(linha_atual), playlists)){ // pega cada linha e transforma numa string
    
        linha_atual[strcspn(linha_atual, "\n")] = '\0'; // tirando o \n da linha atual

        sscanf(linha_atual, "%[^;];%[^;]", username, nome_lista_temp);
        strcpy(linha_atual_temporaria, linha_atual);

        char *titulo_filme = strtok(linha_atual_temporaria, ";"); // pega nome do usuario
        char *nome_lista_atual = strtok(NULL, ";"); // pega o nome da lista

        titulo_filme = strtok(NULL, ";"); // pega o filme!!

        if (strcmp(nome_lista, nome_lista_temp) == 0 && strcmp(username, usernamecpy) == 0){

            strcat(nova_linha, usernamecpy); // reescrevendo a nova linha
            strcat(nova_linha, ";");
            strcat(nova_linha, nome_lista_temp);
            strcat(nova_linha, ";");

            while (titulo_filme != NULL){
            
                if (strcmp(titulo_filme, filme) != 0){
                    strcat(nova_linha, titulo_filme);
                    strcat(nova_linha, ";");
                }    
                titulo_filme = strtok(NULL, ";");
            }   
            fprintf(playlists_nova, "%s\n", nova_linha);
            nova_linha[0] = '\0';
        }
        else{
            fprintf(playlists_nova, "%s\n", linha_atual);
        }
        }

    printf("\nFilme removido com sucesso! Voltando ao menu...\n");
    fclose(playlists);
    fclose(playlists_nova);
    Sleep(3000);
    system("cls");

    remove("playlists.txt");
    rename("playlists_nova.txt", "playlists.txt");
}
