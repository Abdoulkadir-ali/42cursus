#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

char *const commands[][4] = {
    {"find", ".", NULL, NULL},
    {"grep", "pipe", NULL, NULL},
    {"wc", "-l", NULL, NULL}
};

#define NUM_COMMANDS 3
#define READ_END 0
#define WRITE_END 1

void execute_command(char *const cmd_args[])
{
    execvp(cmd_args[0], cmd_args);
    perror(cmd_args[0]);
    exit(EXIT_FAILURE);
}

int main(void)
{
    int current_pipe[2];
    int prev_read_end;
    pid_t pids[NUM_COMMANDS];
    int i;
    
    prev_read_end = STDIN_FILENO;
    i = 0;
    while (i < NUM_COMMANDS)
    {
        if (i < NUM_COMMANDS - 1)
        {
            if (pipe(current_pipe) == -1)
            {
                perror("pipe failed");
                return (1);
            }
        }
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork failed");
            return (2);
        }
        if (pid == 0)
        {
            if (prev_read_end != STDIN_FILENO)
            {
                dup2(prev_read_end, STDIN_FILENO);
                close(prev_read_end);
            }
            if (i < NUM_COMMANDS - 1)
            {
                close(current_pipe[READ_END]);
                dup2(current_pipe[WRITE_END], STDOUT_FILENO);
                close(current_pipe[WRITE_END]);
            }
            execute_command(commands[i]);
        }
        pids[i] = pid;
        if (prev_read_end != STDIN_FILENO)
            close(prev_read_end);
        if (i < NUM_COMMANDS - 1)
        {
            prev_read_end = current_pipe[READ_END];
            close(current_pipe[WRITE_END]);
        }
        i++;
    }
    if (prev_read_end != STDIN_FILENO)
        close(prev_read_end);
    i = 0;
    while (i < NUM_COMMANDS)
        waitpid(pids[i++], NULL, 0);
    return (0);
}