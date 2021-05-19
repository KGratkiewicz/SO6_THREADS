#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

void *engine(void* a)
{
    int b = 0;
    int i;
    if(*(int*)a < 0)
    {
        *(int*)a = -1;
        return a;
    }

    for (i = *(int*)a-1; i>b ; i--)
    {
         *(int*)a *= i;
    }
    return a;
}

int main(int argc, char* argv[])
{
    pthread_t* threads = (pthread_t*) malloc (sizeof(pthread_t)*(argc-1));
    int *numbers = (int*) malloc (sizeof(int)*(argc-1));;
    int i, suma = 0;
    void* output = NULL;
    pthread_t* ptr_thread;
    int* ptr_num;

    for(i=0,ptr_thread = threads, ptr_num = numbers; i<argc-1; i++, ptr_thread++, ptr_num++)
    {
        numbers[i] = atoi(argv[i+1]);
        pthread_create(ptr_thread, NULL, engine, (void*)ptr_num);
    }

    for(i=0,ptr_thread = threads, ptr_num = numbers; i<argc-1; i++, ptr_thread++, ptr_num++)
    {
        output = NULL;
        pthread_join(*ptr_thread, &output);
        if( *(int*)output != -1)
        {
            printf("Thread: %ld; returns: %d \n", *ptr_thread, *(int*)output);    
            if( (*(int*) output % 2) == 0)
            {
                suma += *(int*)output;
            }
            else
            {
                suma -= *(int*)output;
            }  
        }
        else
        {
            printf("Thread: %ld; returns: %d , Invalid value of argument for factorial %d\n", *ptr_thread, *(int*)output, *numbers); 
        }        
        
    }

    printf("Sumarry of even resoults - Summary of odd resoults: %d \n", suma);

    free(threads);
    free(numbers);
    return 0;
}