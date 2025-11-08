#include <unistd.h>

void	ft_strlen(char *str)
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

int	close_all_pipes(int *pipes[2], nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		close(pipes[i][WRITE_END]);
		close(pipes[i][READ_END]);
		i++;
	}
}

int	execute_command(const char **argv)
{
	extern char	**env;

	execve(argv[0], argv, env);
	perror(argv[0]);
	exit(EXIT_FAILURE);
}

int	handle_process(int *pipes[2], char **argv)
{
	close(pipe[WRITE_END]);
	close(pipe[READ_END]);
	execute_command(argv);
}

int	handle_here_doc(int pipe[2], char **argv)
{
	close(pipe[WRITE_END]);
	close(pipe[READ_END]);
	execute_command(argv);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((int)s1[i] - s2[i]);
}

int	run_process(int i, int pipe[2], char **argv)
{
	if (!i)
    {
		dup2(pipe[READ_END], STDIN_FILENO);
        *argv++;
    }
	if (i == nb - 1)
		dup2(pipe[WRITE_END], STDIN_FILENO);
	if (ft_strcmp(*argv, "here_doc"))
		return (handle_here_doc(pipe, argv));
	else
		return (handle_process(pipe, argv));
}

int	pipex(char ***argv)
{
	int nb;
	int i;
	int *pipes[2];
	int pid;

	pipes = malloc(sizeof(int[2]) * (nb - 1));
	if (!pipes)
		return (ft_putstr_fd(2, "Couldn't create pipes", -1));
	i = 0;
	while (i < nb)
	{
		if (pipe(pipes[i]) == -1)
			return (ft_putstr_fd(2, "Couldn't create pipes", -1));
		pid = fork();
		if (pid < 0)
			return (ft_putstr_fd(2, "Couldn't fork", -1));
		if (!pid)
			run_process(i, pipes[i], argv);
        advance_argvs(&argv);
		i++;
	}
	close_all_pipes(pipes, nb);
}