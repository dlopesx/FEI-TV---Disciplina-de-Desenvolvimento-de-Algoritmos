# FEI-TV---

O projeto foi desenvolvido para a disciplina de desenvolvimento de algoritmos do curso de ciência da computação. Consiste em simular uma plataforma em que o usuário possa pesquisar por filmes e realizar ações como curtir, criar listas de reprodução e adicionar filmes a elas.

### Tecnologias utilizadas: Linguagem C, .txt, Dev-C++

## Funcionalidades:
- Cadastro e login de usuários
- Pesquisa de filmes por título (literal e case sensitive)
- Curtir/descurtir filmes
- Criar/excluir listas de reprodução
- Adicionar/remover filmes nas listas de reprodução

## Estrutura de arquivos: 

───fei-tv
    ├───codigo
    │       📄 favoritos.c/.h -> sistema de curtidas e listas de reprodução
    │       📄 funcoes.h -> inicialização de funções externas
    │       📄 main.c -> ponto de partida para o início do código; armazena os menus
    │       📄 usuario.c/.h -> lógica de cadastro e login do usuário
    │       📄 videos.c/.h -> gerenciamento de curtidas e pesquisa de filmes
    │
    └───dados
            🎬filmes.txt
            👍likes.txt
            🎵playlists.txt
            👤usuarios.txt
            
## Como rodar

1 - Baixe ou clone o repositório
2 - Utilize a IDE de preferência (com GCC ou utilize o Dev-C++)
3 - Compilando e executando: caso use VSCode, compile os arquivos no terminal com o comando "gcc codigo/main.c codigo/usuario.c codigo/favoritos.c codigo/videos.c -o fei-tv" e execute com "./fei-tv". Caso use Dev-C++, aperte F9 para compilar e executar.

### Funcionamento

Realize seu cadastro e login no menu inicial do usuário:
<img width="583" height="203" alt="image" src="https://github.com/user-attachments/assets/7deac5e5-e10c-4000-baa4-000aa34a5ec6" />

Após o login, selecione a sua opção no menu principal:
<img width="870" height="242" alt="image" src="https://github.com/user-attachments/assets/6aa13422-18cd-4ae1-a4eb-0365fab251b2" />

## Possíveis melhorias

- Adaptar para diferentes SOs: o código foi desenvolvido somente para Windows - utiliza funções como Sleep() e system("cls")
- Implementar busca inteligente e case insensitive
- Verificar erros na abertura de arquivos com if NULL
- Verificar erros de input no terminal
- Formatação de caracteres da lingua portuguesa
- Otimizar funções com menos repetições




