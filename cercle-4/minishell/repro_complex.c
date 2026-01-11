#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

void run_test(char *desc, char *cmd_str) {
    printf("--- Running: %s ---\n", desc);
    int pid = fork();
    if (pid == 0) {
        char *args[] = {"./minishell", "-c", cmd_str, NULL};
        execv("./minishell", args);
        perror("execv failed");
        exit(1);
    } else {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            printf("Exit Code: %d\n", WEXITSTATUS(status));
    }
}

int main() {
    // Test 1: cd /////
    run_test("cd /////", "cd /////; pwd");
    
    // Test 2: export complex
    run_test("export HELLO42=T=\"\"", "export HELLO42=T=\"\"; env | grep HELLO42");
    
    // Test 3: unset valid
    run_test("unset valid", "export FOO=bar; unset FOO; env | grep FOO");

    // Test 4: unset invalid option
    run_test("unset invalid option", "unset -TEST");

    // Test 5: export append
    run_test("export append", "export APP=100; export APP+=200; echo $APP");

    return 0;
}
