/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 01:10:00 by copilot           #+#    #+#             */
/*   Updated: 2026/01/11 05:38:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_ast(t_nodes *ast_node, int depth)
{
	int		i;
	t_ast	*node;

	if (!ast_node)
		return ;
	node = (t_ast *)ast_node->content;
	i = 0;
	while (i < depth)
	{
		printf("  ");
		i++;
	}
	if (node->type == TOKEN_PIPE)
	{
		printf("PIPE\n");
		print_ast(node->left, depth + 1);
		print_ast(node->right, depth + 1);
	}
	else if (node->type == TOKEN_WORD)
	{
		printf("CMD: ");
		i = 0;
		while (node->args && node->args[i])
		{
			printf("[%s] ", node->args[i]);
			i++;
		}
		printf("\n");
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_nodes	*tokens;
	t_nodes	*ast;

	(void)ac;
	(void)av;
	while (1)
	{
		line = get_command_line();
		if (!line)
		{
			if (isatty(STDIN_FILENO))
				printf("exit\n");
			break ;
		}
		if (*line)
		{
			add_history(line);
			tokens = tokenizer(line);
			if (tokens)
			{
				expand_tokens(tokens, envp);
				ast = ast_builder(tokens);
				// print_ast(ast, 0);
				exec_tree(ast, &envp);
				free_ast(ast);
			}
		}
		free(line);
	}
	rl_clear_history();
	return (0);
}
