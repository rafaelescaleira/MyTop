#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <ncurses.h>
#include <time.h>

#ifndef _MYTOP_H
#define _MYTOP_H

#define BUFFER_LENGTH 30

struct my_top {

     int pid;
     long int priority;
     char state;
     double cpu_usage;
     double time;
     char command[BUFFER_LENGTH];

} typedef t_my_top;

/*
 * Calcula o tempo de execução do processo
 */

double get_seconds(unsigned long long starttime);

/*
 * Calcula a porcentagem de uso da cpu
 */

double get_cpu_usage(unsigned long int utime, unsigned long int stime, long int cutime, long int cstime, unsigned long long starttime);

/*
 * Verifica se o nome do diretório é um número
 */

int is_number(char input[]);

/*
 * Recebe o diretório do processo
 * Faz a leitura do arquivo stat
 * Imprimi na tela os valore exigidos
 */

void read_stat(char * path, int position, t_my_top my_top[]);

/*
 * Busca no diretório /proc
 * Verifica os diretórios com números na nomenclatura
 * Chama a função read_print_stat passando o diretório encontrado
 */

void read_all_proc(int row, int col);

#endif
