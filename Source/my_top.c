#include "my_top.h"

/*
 * Verifica se o nome do diretório é um número
 */

int is_number(char input[]) {

     for (int i = 0; i < strlen(input); i++) {

          if (isdigit(input[i]) != 0) { return 0; }
     }

     return 1;
}

/*
 * Ordena os processos pela % CPU
 */

void sort_proc(t_my_top my_top[], int n) {
    
    t_my_top aux;
    int i = 0;
    int j;

    while (i < n) {

          j = 0;

          while (j < i) {

               if (my_top[j].cpu_usage < my_top[i].cpu_usage) {

                    aux = my_top[j];
                    my_top[j] = my_top[i];
                    my_top[i] = aux;
               }
            
               j = j + 1;
          }
        
          i = i + 1;
     }
}

void print_all_proc(t_my_top my_top[], int n) {

     int hour, minute, second;

     for (int i = 1; i < 70; i ++) { mvprintw(0, i, "=");  }

     mvprintw(1, 1, "     PID |");
     mvprintw(1, 11, "  PR |");
     mvprintw(1, 17, "   S |");
     mvprintw(1, 27, "    %%CPU |");
     mvprintw(1, 42, "    TIME |");
     mvprintw(1, 53, "COMMAND");

     for (int i = 1; i < 70; i ++) { mvprintw(2, i, "=");  }

     for (int i = 0; i < n; i ++) {

          hour = my_top[i].time / 3600;
          minute = (my_top[i].time - (3600 * hour)) / 60;
          second = (my_top[i].time - (3600 * hour) - (minute * 60));

          mvprintw(i + 3, 1, "%8d |\t", my_top[i].pid);
          mvprintw(i + 3, 11, "%4ld |\t", my_top[i].priority);
          mvprintw(i + 3, 17, "%4c |\t", my_top[i].state);
          mvprintw(i + 3, 27, "%6.2f %% |\t", my_top[i].cpu_usage);
          mvprintw(i + 3, 42, "%02d:%02d:%02d |\t", hour, minute, second);
          mvprintw(i + 3, 53, "%s\t\n", my_top[i].command);
     }
}

/*
 * Calcula o tempo de execução do processo
 */

double get_seconds(unsigned long long starttime) {

     long int uptime;
     long int hertz;
     double seconds;

     FILE * uptimeFile = fopen("/proc/uptime", "r");

     if (!uptimeFile) { return 0; }

     fscanf(uptimeFile, "%ld", &uptime);
     fclose(uptimeFile);
     
     hertz = sysconf(_SC_CLK_TCK);

     if (hertz == 0) { return 0; }

     seconds = (double) (uptime - starttime / hertz);

     return seconds;
}

/*
 * Calcula a porcentagem de uso da cpu
 */

double get_cpu_usage(unsigned long int utime, unsigned long int stime, long int cutime, long int cstime, unsigned long long starttime) {

     double cpu_usage, seconds;
     long int total_time, hertz;
     
     hertz = sysconf(_SC_CLK_TCK);
     total_time = utime + stime;
     total_time = total_time + cstime + cutime;

     if (hertz == 0) { return 0; }

     seconds = get_seconds(starttime);

     if (seconds == 0) { return 0; }

     cpu_usage = 100 * ((total_time / hertz) / seconds);

     return cpu_usage;
}

/*
 * Recebe o diretório do processo
 * Faz a leitura do arquivo stat
 * Imprimi na tela os valore exigidos
 */

void read_stat(char * path, int position, t_my_top my_top[]) {
     
     char * pth = malloc(sizeof(char) * 90);

     int null_int;
     unsigned int null_uns_int;
     unsigned long int utime, stime, null_uns_long_int;
     long int cutime, cstime, null_long_int;
     unsigned long long starttime;

     strcpy(pth, path);
     strcat(pth, "stat");

     FILE * file = fopen(pth, "r");

     if(!file) { return; }
     
     fscanf(file, "%d %s %c %d %d %d %d %d %u %lu %lu %lu %lu %lu %lu %ld %ld %ld %ld %ld %ld %llu", 
          &my_top[position].pid, 
          my_top[position].command, 
          &my_top[position].state, 
          &null_int,
          &null_int,
          &null_int,
          &null_int,
          &null_int,
          &null_uns_int,
          &null_uns_long_int,
          &null_uns_long_int,
          &null_uns_long_int,
          &null_uns_long_int,
          &utime,
          &stime,
          &cutime,
          &cstime,
          &my_top[position].priority,
          &null_long_int,
          &null_long_int,
          &null_long_int,
          &starttime
     );

     fclose(file);

     my_top[position].cpu_usage = get_cpu_usage(utime, stime, cutime, cstime, starttime);
     my_top[position].time = get_seconds(starttime);

     free(pth);
}

/*
 * Busca no diretório /proc
 * Verifica os diretórios com números na nomenclatura
 * Chama a função read_stat passando o diretório encontrado
 */

void read_all_proc(int row, int col) {

     int i = 0;
     DIR * directory;
     struct dirent * dir;
     t_my_top my_top[300];
     char * directory_name_buffer, * current_path;
     
     directory = opendir("/proc");
     current_path = malloc(sizeof(char) * 10);

     if (directory == NULL) { return; }

     while ((dir = readdir(directory)) != NULL && i < 300) {

          directory_name_buffer = dir -> d_name;

          if(is_number(directory_name_buffer) != 0) { continue; }

          strcpy(current_path, "/proc/");
          strcat(current_path, directory_name_buffer);
          strcat(current_path, "/");

          read_stat(current_path, i, my_top);
          i = i + 1;
     }

     sort_proc(my_top, i - 1);
     print_all_proc(my_top, 15);

     free(current_path);
}
