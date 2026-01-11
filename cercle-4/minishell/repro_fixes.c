#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int ac, char **av) {
    char cmd[1024];
    if (ac > 1) {
        sprintf(cmd, "./minishell -c \"%s\"", av[1]);
        int ret = system(cmd);
        printf("\nMinishell Exit Code: %d\n", WEXITSTATUS(ret));
    }
    return 0;
}
