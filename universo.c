#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MSGSIZE 64

int main(){
    pid_t pidVL;
    pid_t pidA;
    int p1[2],p2[2];
    char inbuf[75];
    
    int status;
    if (pipe(p1) < 0){printf("pipe não foi");exit(1);}
    if (pipe(p2) < 0){printf("pipe não foi");exit(1);}

    printf("Olá eu sou o universo PID %d\n",getpid());
    printf("Eu acho que vou criar a via lactea\n");
    if ((pidVL = fork()) < 0){
        //Erro
        printf("Eita big bang veio cedo\n");
        exit(1);
    }
    if (pidVL == 0){
        //Via Lactea executa aqui
        printf("Opa sou a via lactea PID %d\n",getpid());
        printf("Acho que vou conversar com a minha vizinha a Andromeda\n");        
        char* msg1 = "Iai Andromeda, chegou né. Quer que eu te passo alguns meteoros?";
        write(p1[1], msg1, MSGSIZE+1);

        read(p2[0], inbuf, MSGSIZE+1);
        printf("%s\n",inbuf);

        exit(0);
    }else{
        //waitpid(pidVL, &status, 0);
        //Universo Executa aqui
        printf("Beleza via lactea foi criado, vou criar uma vizinha. O nome vai ser Andromeda\n");
        if ((pidA = fork()) < 0){
            //Erro
            printf("Cabo pra mim\n");
            exit(1);
        }
        if (pidA == 0){
            //Andromeda executa aqui
            printf("Opa sou a andromeda PID %d\n",getpid());
            read(p1[0], inbuf, MSGSIZE+1);
            printf("%s\n",inbuf);
            char* msg1 = "Ah oi via lactea.Alguns meteoros seriam bons pro meu crescimento";
            write(p2[1], msg1, MSGSIZE+1);
        }else{
            //waitpid(pidA, &status, 0);
            //Universo Executa aqui
            printf("Andromeda ok, acho que vou para por aqui por hoje\n");
        }
    }
    return 0;
}