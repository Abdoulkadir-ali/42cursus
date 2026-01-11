
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 01:10:00 by copilot           #+#    #+#             */
/*   Updated: 2026/01/11 14:19:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include <dirent.h>
#include "minishell.h"

char **g_envp = NULL;
int g_exit_code = 0;


void print_ast(t_nodes *ast_node, int depth)
{
	int i;
	t_ast *node;
	if (!ast_node)
		return;
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

char **duplicate_env(char **envp)
{
	int env_count = 0;
	char **heap_env;
	int k;
	while (envp[env_count])
		env_count++;
	heap_env = malloc(sizeof(char *) * (env_count + 1));
	if (!heap_env)
		return NULL;
	k = 0;
	while (k < env_count)
	{
		heap_env[k] = ft_strdup(envp[k]);
		k++;
	}
	heap_env[k] = NULL;
	return heap_env;
}

void execute_command(t_nodes *tokens, char ***envp, int *exit_code)
{
	t_nodes	*ast;

	ast = ast_builder(tokens);
	if (!scan_heredocs(ast))
		*exit_code = exec_tree(ast, envp);
	else
	{
		if (g_last_signal == 130)
			*exit_code = 130;
		else
			*exit_code = 1;
	}
	free_ast(ast);
}

int is_whitespace_only(char *str)
{
	while (str && *str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}

	void process_input(char *line, char ***envp, int *exit_code)
	{
		t_nodes *tokens;
		if (!*line || is_whitespace_only(line))
			return;
	add_history(line);
	tokens = tokenizer(line);
	if (!tokens)
		return;
	if (check_syntax(tokens))
	{
		*exit_code = 2;
		ft_lstclear(&tokens, del_token);
		return;
	}
	expand_tokens(&tokens, *envp, *exit_code);
	if (tokens)
	{
		execute_command(tokens, envp, exit_code);
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	int		last_exit_code;
	char	**heap_env;

	(void)ac;
	(void)av;
	last_exit_code = 0;
	setup_signals(SIGNAL_INTERACTIVE);
	heap_env = duplicate_env(envp);
	g_envp = heap_env;
	while (1)
	{
		line = get_command_line();
		if (!line)
		{
			if (isatty(STDIN_FILENO))
				ft_printf_fd(2, "exit\n");
			break ;
		}
		process_input(line, &heap_env, &last_exit_code);
		g_exit_code = last_exit_code;
		free(line);
	}
	rl_clear_history();
	return (last_exit_code);
}
