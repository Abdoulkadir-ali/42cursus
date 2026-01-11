#include "core.h"
#include "parsing.h"
#include <stdio.h>

// Mocking required externs/funcs
char **g_envp = NULL;
int g_exit_code = 0;
int g_last_signal = 0;
void setup_signals(int mode) {}
void rl_replace_line(const char *text, int clear_undo) {}

int main(int ac, char **av)
{
    if (ac < 2) return 1;
    char *line = av[1];
    printf("Testing: [%s]\n", line);
    t_nodes *tokens = tokenizer(line);
    if (!tokens) {
        printf("Tokenizer returned NULL\n");
        return 1;
    }
    
    t_nodes *curr = tokens;
    while(curr) {
        t_token *t = (t_token*)curr->content;
        printf("Token: Type=%d, Value=[%s]\n", t->type, t->value);
        curr = curr->next;
    }

    int syn = check_syntax(tokens);
    printf("Syntax Check Result: %d\n", syn);
    
    return 0;
}
