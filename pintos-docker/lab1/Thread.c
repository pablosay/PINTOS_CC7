#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//Structure to pass arguments to threads
struct args_threads{
    void *vargp;
    int number;
};

//Checks if it is a prime number
// 0: Not a prime number.
// 1: It is a prime number.
int isPrimeNumber(int number){
    int i;
    if(number > 1){
        for(i=2; i < (number - 1); i++){
            if(number%i == 0){
                return 0;
            } 
        }
    } else {
        return 0;
    }
    return 1;
}

//Function to find n prime numbers
void* nPrimeNumbers(void* ptr_strct){
    struct args_threads *args = (struct args_threads *) ptr_strct;
    int *myid = (int *) args->vargp;
    int number_of_primes = args -> number;
    int cont = 0;
    int x = 2;
    while(cont < number_of_primes){
        if(isPrimeNumber(x) == 1){
            printf("Thread %d: El numero %d es primo\n", *myid , x);
            cont++;
            x++;
        } else {
            x++;
        }
    }
    return NULL;
}

int main(int argc , char * argv []){
    //Number of prime numbers stored in memmory
    int* n_number = (int*) malloc(sizeof(int));
    //Ask for an integer number
    printf("Ingrese numero de primos: ");
    scanf("%d", n_number);
    //Create threads
    pthread_t t1id;
    pthread_t t2id;
    //structure for parameters
    struct args_threads params_thread1;
    struct args_threads params_thread2;
    //Params for the thread 1
    params_thread1.vargp = (void *)&t1id;
    params_thread1.number = *n_number;
    //Params for thread 2
    params_thread2.vargp = (void *)&t2id;
    params_thread2.number = *n_number;
    //Create threads
    pthread_create(&t1id, NULL, nPrimeNumbers, (void *)&params_thread1);
    pthread_create(&t2id, NULL, nPrimeNumbers, (void *)&params_thread2);
    //Join threads
    pthread_join(t1id, NULL);
    pthread_join(t2id, NULL);
    //free space
    free(n_number);
    return 0;
}

