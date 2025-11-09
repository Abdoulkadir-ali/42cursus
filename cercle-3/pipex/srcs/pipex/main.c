/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 14:44:32 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/09 16:40:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	handle_heredoc_mode(int argc, char **argv)
{
	char	*heredoc_file;
	int		exit_code;

	if (argc < 6)
	{
		ft_putstr_fd("Usage: ./pipex here_doc LIMITER cmd cmd file\n", 2);
		return (1);
	}
	heredoc_file = create_here_doc(argv[2]);
	if (!heredoc_file)
		return (1);
	argv[2] = heredoc_file;
	exit_code = pipex(argv + 2, argc - 2, 1);
	unlink(heredoc_file);
	free(heredoc_file);
	return (exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	(void)envp;
	if (argc >= 2 && ft_strncmp(argv[1], "here_doc", 9) == 0)
		return (handle_heredoc_mode(argc, argv));
	if (argc < 5)
	{
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 ... outfile\n", 2);
		return (1);
	}
	argv++;
	argc--;
	return (pipex(argv, argc, 0));
}
