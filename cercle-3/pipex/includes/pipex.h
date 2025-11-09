/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 00:00:00 by abdali            #+#    #+#             */
/*   Updated: 2025/11/09 16:13:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define WRITE_END 1
# define READ_END 0

typedef int	t_pipe[2];

/* Helper functions */
int		close_all_pipes(t_pipe *pipes, int nb);

/* Error handling */
int		exit_statement(char *error_msg, void *ptr, int error_code);
int		exit_process(char *error);

/* Parser functions */
char	**parse_command(char *cmd);
void	free_args(char **args);

/* Pipex core functions */
int		execute_command(char *cmd);
int		read_from_infile(char *infile, t_pipe *pipes, int nb);
int		write_to_outfile(char *outfile, t_pipe *pipes, int i, int nb);
int		run_process(int i, int nb, t_pipe *pipes, char **argv);
t_pipe	*create_pipes(int nb);
int		check_file_access(char *infile, char *outfile);
int		pipex(char **argv, int argc);

/* Here_doc bonus functions */
int		handle_here_doc(char *limiter);
int		write_to_outfile_append(char *outfile);
void	read_here_doc(char *limiter, int write_fd);

#endif
