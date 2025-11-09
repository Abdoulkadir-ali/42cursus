#include "pipex.h"

int	premature_exit(char *error_msg, int (*pipes)[2], int error_code)
{
	if (error_msg)
		ft_putstr_fd(2, error_msg, -1);
	if (pipes)
		free(pipes);
	return (error_code);
}

int	exit_process(char *error)
{
	perror(error);
	exit(EXIT_FAILURE);
}
