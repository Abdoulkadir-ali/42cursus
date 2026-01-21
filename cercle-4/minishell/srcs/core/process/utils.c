/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 22:41:27 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/21 05:26:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include <fcntl.h>

int	is_whitespace_only(char *str)
{
	while (str && *str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}

int	expand_and_check_error(t_nodes **segment, char **envp, int exit_code,
		int *new_exit_code)
{
	expand_tokens(segment, envp, exit_code);
	if (g_state.expansion_error)
	{
		*new_exit_code = g_state.exit_code;
		ft_lstclear(segment, del_token);
		g_state.expansion_error = 0;
		return (1);
	}
	return (0);
}

void	execute_ast(t_nodes *segment, char ***envp, int *exit_code)
{
    t_nodes	*ast;
    int     dbg_fd;

    dbg_fd = open("/tmp/minishell_dbg.log", O_WRONLY | O_CREAT | O_APPEND, 0600);
    if (dbg_fd != -1)
    {
        dprintf(dbg_fd, "[execute_ast] start segment=%p pid=%d\n", (void *)segment, getpid());
        close(dbg_fd);
    }

    ast = ast_builder(segment);

    dbg_fd = open("/tmp/minishell_dbg.log", O_WRONLY | O_CREAT | O_APPEND, 0600);
    if (dbg_fd != -1)
    {
        dprintf(dbg_fd, "[execute_ast] ast=%p pid=%d\n", (void *)ast, getpid());
        close(dbg_fd);
    }

    if (!scan_heredocs(ast))
    {
        dbg_fd = open("/tmp/minishell_dbg.log", O_WRONLY | O_CREAT | O_APPEND, 0600);
        if (dbg_fd != -1)
        {
            dprintf(dbg_fd, "[execute_ast] calling exec_tree pid=%d\n", getpid());
            close(dbg_fd);
        }
        *exit_code = exec_tree(ast, envp);
        dbg_fd = open("/tmp/minishell_dbg.log", O_WRONLY | O_CREAT | O_APPEND, 0600);
        if (dbg_fd != -1)
        {
            dprintf(dbg_fd, "[execute_ast] exec_tree returned %d pid=%d\n", *exit_code, getpid());
            close(dbg_fd);
        }
    }
    else
    {
        if (g_state.last_signal == 130)
            *exit_code = 130;
        else
            *exit_code = 1;
    }
    free_ast(ast);
}

void	build_segment_until_semicolon(t_nodes **segment, t_nodes **seg_tail,
		t_nodes **it)
{
	t_nodes	*next;

	while (*it && ((t_token *)(*it)->content)->type != TOKEN_SEMICOLON)
	{
		next = (*it)->next;
		(*it)->next = NULL;
		if (!*segment)
			*segment = *it;
		else
			(*seg_tail)->next = *it;
		*seg_tail = *it;
		*it = next;
	}
}

void	consume_semicolon_if_present(t_nodes *it, t_nodes **pnext)
{
	if (it && ((t_token *)it->content)->type == TOKEN_SEMICOLON)
	{
		*pnext = it->next;
		del_token(it->content);
		free(it);
	}
	else
		*pnext = it;
}
