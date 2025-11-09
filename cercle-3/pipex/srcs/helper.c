#include "pipex.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_putstr_fd(int fd, char *str, int error_code)
{
	write(fd, str, ft_strlen(str));
	return (error_code);
}

int	close_all_pipes(int (*pipes)[2], int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		close(pipes[i][WRITE_END]);
		close(pipes[i][READ_END]);
		i++;
	}
	return (0);
}
