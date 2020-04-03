#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <fnmatch.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void processdir(const struct dirent *dir)
{
     puts(dir->d_name);
}

int filter(const struct dirent *dir)
{
     uid_t user;
     struct stat dirinfo;
     int len = strlen(dir->d_name) + 7; 
     char path[len];

     strcpy(path, "/proc/");
     strcat(path, dir->d_name);
     user = getuid();
     if (stat(path, &dirinfo) < 0) {
	  perror("processdir() ==> stat()");
	  exit(EXIT_FAILURE);
     }
     return !fnmatch("[1-9]*", dir->d_name, 0) && user == dirinfo.st_uid;
}

int main() 
{
     /* Based on example in "man scandir" */

     struct dirent **namelist;
     int n;

     n = scandir("/proc", &namelist, filter, 0);
     if (n < 0)
	  perror("Not enough memory.");
     else {
	  while(n--) {
	       processdir(namelist[n]);
	       free(namelist[n]);
	  }
	  free(namelist);
     }
     return 0;
}