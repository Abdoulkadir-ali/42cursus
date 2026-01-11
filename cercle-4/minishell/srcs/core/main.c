/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 01:10:00 by copilot           #+#    #+#             */
/*   Updated: 2026/01/11 13:20:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

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
		ft_printf("  ");
		i++;
	}
	if (node->type == TOKEN_PIPE)
	{
		ft_printf("PIPE\n");
		print_ast(node->left, depth + 1);
		print_ast(node->right, depth + 1);
	}
	else if (node->type == TOKEN_WORD)
	{
		ft_printf("CMD: ");
		i = 0;
		while (node->args && node->args[i])
		{
			ft_printf("[%s] ", node->args[i]);
			i++;
		}
		ft_printf("\n");
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_nodes	*tokens;
	t_nodes	*ast;

	(void)ac;
	(void)av;
	setup_signals(SIGNAL_INTERACTIVE);
	// Helper for env duplication - inline for now
	int env_count = 0;
	while (envp[env_count]) env_count++;
	char **heap_env = malloc(sizeof(char *) * (env_count + 1));
	int k = 0;
	while (k < env_count) { heap_env[k] = ft_strdup(envp[k]); k++; }
	heap_env[k] = NULL;
	envp = heap_env;

	while (1)
	{
		line = get_command_line();
		if (!line)
		{
			if (isatty(STDIN_FILENO))
				ft_printf("exit\n");
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
				if (!scan_heredocs(ast))
					exec_tree(ast, &envp);
				free_ast(ast);
			}
		}
		free(line);
	}
	rl_clear_history();
	return (0);
}
