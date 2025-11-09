/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 14:44:32 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/09 16:13:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	handle_heredoc_mode(int argc, char **argv)
{
	if (argc < 6)
	{
		ft_putstr_fd("Usage: ./pipex here_doc LIMITER cmd cmd file\n", 2);
		return (-1);
	}
	if (handle_here_doc(argv[2]) == -1)
		return (-1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	(void)envp;
	if (argc >= 2 && ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		if (handle_heredoc_mode(argc, argv) == -1)
			return (1);
		argv += 2;
		argc -= 2;
	}
	else
	{
		if (argc < 5)
		{
			ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 ... outfile\n", 2);
			return (1);
		}
	}
	argv++;
	argc--;
	return (pipex(argv, argc));
}
