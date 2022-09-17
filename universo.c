#define _GNU_SOURCE  
#include <linux/sched.h>    
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>

#define MSGSIZE 25

/*
fork ok
kill ok
exit ok
pipe ok
waitpid ok
clone ok
sigaction
exec
*/
static int init_planet(void *arg){
    int ret;
    char* nome = (char*)arg;
    printf("Criando %s PID - %d\n",nome,getpid());
    ret = strcmp(nome,"plutão");
    sleep(2);
    if(ret == 0){
        printf("Plutão não é mais planeta, eliminado\n");
        kill(getpid(),9);
    }else{
        printf("Planeta %s de PID - %d morreu\n",nome,getpid());
        kill(getpid(),9);
    return 0;
    }
}

int main(){
    pid_t pidVL;
    int p1[2],p2[2];
    char inbuf[150];
    int status;

    //Pipe
    if (pipe(p1) < 0){printf("pipe não foi");exit(1);}
    if (pipe(p2) < 0){printf("pipe não foi");exit(1);}

    printf("Universo - Olá eu sou o universo PID %d\n",getpid());

    printf("Universo - Vou tentar criar a via lactea\n");

    printf("Criando ...\n");
    //sleep(2);

    if ((pidVL = fork()) < 0){printf("Eita big bang veio cedo\n");exit(1);}
    
    if (pidVL == 0){
        char* msg1 = "Via Lactea - Quem sou eu?\n";

        //escrevendo pipe
        write(p1[1], msg1, MSGSIZE+1);
        close(p1[1]);

        //lendo pipe
        read(p2[0], inbuf, 32+1);
        printf("%s",inbuf);
        close(p2[0]);

        printf("Via lactea - Sim é verdade eu sou a via lactea PID - %d\n",getpid());
        printf("Via lactea - Vou criar o sistema solar\n");

        int i;
        printf("Via lactea - Vou criar todos os planetas do sistema solar.\n\n");
        char nomes[9][9] = {"mercurio","venus","terra","marte","jupiter","saturno","urano","netuno","plutão"};
        pid_t pid;
        for (i = 0; i < 9; i++)
        {
            void *stack = malloc(1024 * 1024);
            if (!stack) {
                    printf("Planeta sem espaço de fala.\n");;
                    exit(1);
            }
            pid = clone(&init_planet, (char *)stack + (1024 * 1024), SIGCHLD, nomes[i]);  
            if (pid < 0){
                    printf("Sem humanidade hoje");
                    exit(1);
            }
            printf("\n");
            waitpid(pid, &status, 0);
        }
        printf("\nTodos os meu planetas morrerão, eu não fiz um bom trabalho\n");
        printf("Acho que vou dar a vez a outro\n");
        exit(0);
    }else{
        //lendo pipe
        read(p1[0], inbuf, MSGSIZE+1);
        printf("%s",inbuf);
        close(p1[0]);

        char* msg2 = "Universo - Você é a via lactea\n";
        //escrevendo pipe
        write(p2[1], msg2, 32+1);
        close(p2[1]);

        waitpid(pidVL, &status, 0);

        exit(0);
    }
    exit(0);
    return 0;
}