#include "includes/exec.h"
#include "includes/parsing.h"
#include <stdio.h>

void print_ast(t_ast *node, int depth)
{
	if (!node)
		return;
	for (int i = 0; i < depth; i++) printf("  ");
	printf("TYPE: %d", node->type);
	if (node->args && node->args[0])
	{
		for (int i=0; node->args[i]; i++)
			printf(" | ARG[%d]: '%s'", i, node->args[i]);
	}
	printf("\n");
	if (node->left) {
		for (int i = 0; i < depth; i++) printf("  ");
		printf("LEFT:\n");
		print_ast(node->left, depth + 1);
	}
	if (node->right) {
		for (int i = 0; i < depth; i++) printf("  ");
		printf("RIGHT:\n");
		print_ast(node->right, depth + 1);
	}
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	t_shell_state state;
	ft_bzero(&state, sizeof(state));
	state.envp = envp;
	state.exit_code = 0;

	char *input = argv[1];
	printf("INPUT: %s\n", input);
	t_nodes *tokens = tokenize(input, &state);
	if (!tokens) {
		printf("Tokenizer failed\n");
		return 1;
	}
	expand_tokens(&tokens, state.envp, 0);
	t_ast *ast = ast_builder(tokens);
	if (!ast) {
		printf("AST failed\n");
		return 1;
	}
	print_ast(ast, 0);
	return 0;
}
