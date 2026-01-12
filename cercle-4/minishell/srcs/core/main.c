
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
	{
		*exit_code = 2;
		return;
	}
	if (check_syntax(tokens))
	{
		consume_heredocs(tokens);
		*exit_code = 2;
		ft_lstclear(&tokens, del_token);
		return;
	}

	/* Execute each top-level command segment separately so expansions occur
	   with the environment state after previous commands (e.g. export). */
	t_nodes *cursor = tokens;
	while (cursor)
	{
		t_nodes *segment = NULL;
		t_nodes *seg_tail = NULL;
		t_nodes *it = cursor;

		while (it && ((t_token *)it->content)->type != TOKEN_SEMICOLON)
		{
			t_nodes *next = it->next;
			it->next = NULL;
			if (!segment)
				segment = it;
			else
				seg_tail->next = it;
			seg_tail = it;
			it = next;
		}

		t_nodes *next_cursor = NULL;
		if (it && ((t_token *)it->content)->type == TOKEN_SEMICOLON)
		{
			next_cursor = it->next;
			del_token(it->content);
			free(it);
		}
		else
			next_cursor = it;

		if (segment)
		{
			expand_tokens(&segment, *envp, *exit_code);
			execute_command(segment, envp, exit_code);
		}

		cursor = next_cursor;
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
	heap_env = duplicate_env(envp);
	g_envp = heap_env;
	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
	{
		setup_signals(SIGNAL_HEREDOC); // Use non-interactive signals or heredoc signals which might be safer
		process_input(av[2], &heap_env, &last_exit_code);
		rl_clear_history();
		return (last_exit_code);
	}
	setup_signals(SIGNAL_INTERACTIVE);
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
