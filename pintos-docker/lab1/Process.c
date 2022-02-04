#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

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

int main(int argc , char * argv []){
    //Number of prime numbers stored in memmory
    int* n_number = (int*) malloc(sizeof(int));
    //Ask for an integer number
    printf("Ingrese numero de primos: ");
    scanf("%d", n_number);
    //Create a new process
    pid_t pid;
    //Creating new process
    pid = fork();
    int cont = 0;
    int x = 2;
    while(cont < *n_number){
        if(isPrimeNumber(x) == 1){
            printf("Proceso %d: El numero %d es primo\n", getpid() , x);
            cont++;
            x++;
        } else {
            x++;
        }
    }
    free(n_number);
    return 0;
}