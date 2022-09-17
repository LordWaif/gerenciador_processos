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

#define MSGSIZE 25

/*
fork ok
kill ok
exit ok
pipe ok
waitpid ok
clone ok
sigaction ok
exec ok
*/
static int init_planet(void *arg){
    int ret;
    char* nome = (char*)arg;
    printf("Criando %s PID - %d\n",nome,getpid());
    ret = strcmp(nome,"plutão");
    sleep(4);
    if(ret == 0){
        printf("Plutão não é mais planeta, eliminado\n");
        kill(getpid(),SIGKILL);
    }else{
        printf("Planeta %s de PID - %d morreu\n",nome,getpid());
        kill(getpid(),SIGKILL);
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
    sleep(1);
    printf("Universo - Vou tentar criar a via lactea\n");
    sleep(1);
    printf("Criando ...\n");
    sleep(1);

    if ((pidVL = fork()) < 0){printf("Eita big bang veio cedo\n");exit(1);}
    
    if (pidVL == 0){
        char* msg1 = "Via Lactea - Quem sou eu?\n";
        sleep(1);

        //escrevendo pipe
        write(p1[1], msg1, MSGSIZE+1);
        close(p1[1]);

        //lendo pipe
        read(p2[0], inbuf, 32+1);
        printf("%s",inbuf);
        close(p2[0]);

        sleep(3);
        printf("Via lactea - Sim é verdade eu sou a via lactea PID - %d\n",getpid());
        sleep(2);
        printf("Via lactea - Vou criar o sistema solar\n");
        sleep(2);

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
            sleep(2);
            printf("\n");
            waitpid(pid, &status, 0);
        }
        sleep(2);
        printf("\nVia lactea - Todos os meu planetas morreram, eu não fiz um bom trabalho\n");
        sleep(4);

        exit(0);
    }else{
        //lendo pipe
        read(p1[0], inbuf, MSGSIZE+1);
        sleep(1);
        printf("%s",inbuf);
        sleep(1);
        close(p1[0]);

        char* msg2 = "Universo - Você é a via lactea\n";
        //escrevendo pipe
        write(p2[1], msg2, 32+1);
        close(p2[1]);

        waitpid(pidVL, &status, 0);

        sleep(3);
        printf("Universo - Deu tudo errado\n");
        sleep(3);
        printf("Universo - Acho que vou dar a vez a outro\n");
        sleep(4);
        printf("BIGCRUNCH");
        sleep(2);
        printf("Vazio absoluto ...");
        sleep(2);
        printf("BIGBANG");

        char *path = "./universo2";
        execl(path,path, NULL);

        exit(0);
    }
    exit(0);
    return 0;
}