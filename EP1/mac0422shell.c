#include <signal.h>
#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>




 char **parser(char *input) {
    char **command;
    char *tokenized;
    int i;

    command = malloc(32 * sizeof(char *));

    tokenized = strtok(input, " ");
    i = 0;

    while(tokenized != NULL) {
        command[i] = tokenized;
        i = i + 1;
        tokenized = strtok(NULL, " ");
    }

    command[i] = NULL;  
    
    return command;

}

char **isolateCommand(char **command) {

    char **isolated;
    int i;

    i = 1;
    isolated = malloc(32 * sizeof(char *));
    while (command[i] != NULL) {
        isolated[i-1] = command[i];
        i++;
    }

    isolated[i] = NULL;

    return isolated;
}


int main() {

    char *input;
    char **command;
    int result;
    pid_t pidDoFilho;
    int status;
    
    while(1) {
        input = malloc(32 * sizeof(char));
        printf("mac422shell> ");
        scanf("%[^\n]", input); 
        /*
        input = readline("mac422shell> ") 
        */
        command = parser(input);        


        pidDoFilho = fork();
        if(pidDoFilho == 0){

            if (strcmp(command[0], "protegepracaramba") == 0) {
                result = chmod(command[1], 0000);
                exit(result);
            }

            else if (strcmp(command[0], "liberageral") == 0)  {
                result = chmod(command[1], 0777);
                exit(result);
            }

            else{
                execve(command[0], command);
                printf("execvp nao funcionou!\n");
                exit(0);
            }
        }
        else{
            waitpid(pidDoFilho, &status, WUNTRACED);
        }

        free(command);
        free(input);
    }
    
    return 0;
}