/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/11 05:26:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "parser.h"
# include <sys/wait.h>
# include <fcntl.h>

int		exec_tree(t_nodes *ast_node, char ***envp);
int		exec_simple_command(t_ast *node, char **envp);
int		exec_pipe(t_ast *node, char ***envp);

char	*find_path(char *cmd, char **envp);

#endif
