/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 00:00:00 by abdali            #+#    #+#             */
/*   Updated: 2026/03/10 04:07:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
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

typedef struct s_pipex_config
{
	int		append_mode;
	int		nb_cmds;
	char	**argv;
}			t_config;

/* Helper functions */
int			close_all_pipes(t_pipe *pipes, int nb);

/* Error handling */
int			exit_statement(char *error_msg, void *ptr, int error_code);
int			exit_process(char *error);

/* Parser functions */
char		**parse_command(char *cmd);
void		free_args(char **args);

/* Pipex core functions */
int			execute_command(char *cmd);
int			read_from_infile(char *infile, t_pipe *pipes, int nb);
int			write_to_outfile(char *outfile, t_pipe *pipes, int i, int nb);
int			write_to_outfile_append(char *outfile, t_pipe *pipes, int i,
				int nb);
int			run_process(t_config *cfg, int i, t_pipe *pipes);
t_pipe		*create_pipes(int nb);
int			check_file_access(char *infile, char *outfile);
int			pipex(char **argv, int argc, int append_mode);

/* Here_doc bonus functions */
char		*create_here_doc(char *limiter);
int			handle_heredoc_mode(int argc, char **argv);

#endif
