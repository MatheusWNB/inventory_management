#ifndef UTILS_H
#define UTILS_H

//Função para limpar o buffer da entrada padrão
void clearstdin(void);

//Limpa a quebra de linha do fgets
void limpar_quebra_linha(char *nome);

//Função simples para validação rápida dentro de um intervalo de números inteiros
int validar_resposta(int min, int max, int *resposta_usuario);

//Essa função obtém o nome que o usuário digitar de maneira mais segura
void getname(char *nome, int max_len);

void getname2();

#endif