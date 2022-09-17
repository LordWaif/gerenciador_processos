#define _GNU_SOURCE  
#define _POSIX_SOURCE
#include <linux/sched.h>    
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>

void handlerkill(int num){
    write(STDOUT_FILENO,"O GRANDE COLAPSO!!!",19);
    exit(0);
}

void handlercold(int num){
    write(STDOUT_FILENO,"O GRANDE CONGELAMENTO!!!",24);
    exit(0);
}

void handlerplanet(int num){
    for(;;){
        printf("Criando planetas...\n");
        sleep(1);
    }
}

void handlerBackinTime(int num){
    sleep(2);
    printf("Universo2 - Ah não!!! Um vortice temporal está me cobrindo!!! ó_ò\n");
    sleep(4);
    printf("Universo2 - O que aconteceu?\n");
    sleep(2);
    printf("Universo2 - Foi você?\n");
    sleep(2);
    printf("Olhando diretamente para você... ಠ_ಠ\n");
    sleep(3);
    printf("Reset existêncial\n");
    char *path = "./universo";
    execl(path,path, NULL);
}

int main(){
    sleep(2);
    printf("Universo2 - Eu nasci PID - %d\n",getpid());
    sleep(3);
    printf("Universo2 - Agora as coisas vão dá certo\n");
    sleep(4);
    printf("Universo2 - Agora vou passar um tempo criando estrelas\n");

    struct sigaction sa;
    sa.sa_handler = handlerkill;
    sigaction(SIGINT,&sa,NULL);

    struct sigaction sa2;
    sa2.sa_handler = handlercold;
    sigaction(SIGTSTP,&sa2,NULL);

    struct sigaction sa3;
    sa3.sa_handler = handlerplanet;
    sigaction(SIGQUIT,&sa3,NULL);

    struct sigaction sa4;
    sa4.sa_handler = handlerBackinTime;
    sigaction(SIGALRM,&sa4,NULL);

    sleep(1);
    for(;;){
        printf("Criando estrelas...\n");
        sleep(1);
    }
    return 0;
}