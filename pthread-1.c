#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_T 2

struct targs{
	int id;
	int usecs;
};

typedef struct targs targs_t;

void *func_thread(void *args){
	int i=0;
	targs_t ta = *(targs_t*)args; 
	int *ret = NULL;

	ret = calloc(1,sizeof(int));
	*ret = 10;

	while (1)
	{
		printf("thread %d executando %d\n", ta.id, i++);
		usleep(ta.usecs);

		if (i == 100)
		{
			pthread_exit(ret);
		}
		  
	}
	pthread_exit(ret);
		
}

int main(int argc,char **argv){
	int i;
	pthread_t tid[MAX_T];
	int *ret_val[MAX_T];
	targs_t ta [MAX_T];
	
	for (i = 0; i < MAX_T; i++)
	{
		ta[i].id = i;
		if (i%2){
			ta[i].usecs = 100000;
		}
		else{
			ta[i].usecs = 10000;
		}

		pthread_create(&tid[i], NULL, func_thread, (void*)&ta[i]);
	}
	for( i = 0; i < MAX_T; i++)
	{
		pthread_join(tid[i], (void **)&ret_val[i]);
		printf("ret_val[%d] = %d\n",i , *ret_val[i]);
	}

	//pthread_exit

	return 0;
}
