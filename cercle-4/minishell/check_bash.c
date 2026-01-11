#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int ac, char **av) {
    if (ac < 2) return 0;
    char cmd[1024];
    sprintf(cmd, "bash -c '%s'", av[1]);
    int ret = system(cmd);
    printf("Command: [%s] -> Exit Code: %d\n", av[1], WEXITSTATUS(ret));
    return 0;
}
