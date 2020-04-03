#include <stdio.h>
#include <stdlib.h>

struct cpust {

	unsigned long utime;
	unsigned long stime;
	unsigned long um;
	unsigned long nm;
	unsigned long sm;
} typedef cpust;


struct cpusg {

	float u;
	float s;
};

void gcpusg(struct cpusg *usg,struct cpust *st1,struct cpust *st2) {
    
	if(st1->utime == st2->utime)
		usg->u = 0;
	else{
		if(st2->um == st1->um)
			usg->u = (st2->utime - st1->utime) / 100;
		else{
			printf("st2->utime: %ld st1->utime: %ld st2->um: %ld st1->um: %ld\n",
				st2->utime,st1->utime,st2->um,st1->um);
			usg->u = (st2->utime - st1->utime) / (float)((st2->um - st1->um) * 100);
		}
	}
	if(st1->stime == st2->stime)
		usg->s = 0;
	else{
		if(st2->sm == st1->sm)
			usg->s = (st2->stime - st1->stime) / 100;
		else
			usg->s = (st2->stime - st1->stime) / (float)((st2->sm - st1->sm) * 100);
	}
}

void clear_cpust(struct cpust *st)
{
	st->utime = 0;
	st->stime = 0;
	st->um = 0;
	st->nm = 0;
	st->sm = 0;
}

void read_st(struct cpust *st)
{
	char cpun[255];
	FILE *fp = fopen("/proc/stat","r");
	if(fscanf(fp,"%s %ld %ld %ld",cpun,&(st->um),&(st->nm),&(st->sm)) == EOF)
		perror("fscanf");
	printf("cpu: %s user mode: %ld nice mode: %ld system mode: %ld\n",
		cpun,st->um,st->nm,st->sm);
	fclose(fp);
}

int main()
{
    cpust * st;
    st = (cpust *) malloc(sizeof(cpust));
	read_st(st);
    return 0;
}