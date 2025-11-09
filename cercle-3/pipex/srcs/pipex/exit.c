/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 15:08:02 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/09 15:15:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	exit_statement(char *error_msg, void *ptr, int error_code)
{
	if (error_msg)
		perror(error_msg);
	if (ptr)
		free(ptr);
	return (error_code);
}

int	exit_process(char *error)
{
	perror(error);
	exit(EXIT_FAILURE);
}
