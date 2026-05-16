#ifndef FAVORITOS_H
#define FAVORITOS_H

void criar_lista(char *usernamecpy);
void excluir_lista(char *usernamecpy);
int verificar_existencia(char *arquivo_playlists, char *lista_desejada, char *usernamecpy);
void adicionar_filme(char *titulo, char *usernamecpy);
void remover_filme(char *filme, char *usernamecpy);
int mostrar_playlists(char *usernamecpy);

#endif
