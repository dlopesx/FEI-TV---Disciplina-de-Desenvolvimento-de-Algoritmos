#ifndef VIDEOS_H
#define VIDEOS_H

void curtir_video(char *titulo, char *usernamecpy, char* comando);
int pesquisar_filme(char *titulo, char *ano, char *duracao, char *descricao, char *nota_letterboxd);
int verificar_se_curtido(char *titulo, char *usernamecpy);

#endif
