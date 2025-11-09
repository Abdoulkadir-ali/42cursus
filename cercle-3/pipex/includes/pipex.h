/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 00:00:00 by abdali            #+#    #+#             */
/*   Updated: 2025/11/09 14:36:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define WRITE_END 1
# define READ_END 0

/* Helper functions */
int		ft_strlen(char *str);
int		ft_putstr_fd(int fd, char *str, int error_code);
int		close_all_pipes(int (*pipes)[2], int nb);

/* Error handling */
int		premature_exit(char *error_msg, int (*pipes)[2], int error_code);
int		exit_process(char *error);

/* Pipex core functions */
int		execute_command(const char *cmd);
int		read_from_infile(char *infile, int (*pipes)[2]);
int		write_to_outfile(char *outfile, int (*pipes)[2], int i);
int		run_process(int i, int nb, int (*pipes)[2], char **argv);
int		(*create_pipes(int nb))[2];
int		check_file_access(char *infile, char *outfile);
int		pipex(char **argv, int argc);

#endif
