/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 14:44:32 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/09 21:41:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
