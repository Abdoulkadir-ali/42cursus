/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 15:10:38 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/09 15:45:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_file_access(char *infile, char *outfile)
{
	(void)outfile;
	if (access(infile, R_OK) == -1)
	{
		perror(infile);
		return (-1);
	}
	return (0);
}
