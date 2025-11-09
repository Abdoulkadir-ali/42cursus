#include "pipex.h"

int	execute_command(const char *cmd)
{
	extern char	**environ;
	char		*argv[2];

	argv[0] = (char *)cmd;
	argv[1] = NULL;
	execve(cmd, argv, environ);
	perror(cmd);
	exit(EXIT_FAILURE);
}

int	read_from_infile(char *infile, int (*pipes)[2])
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
		exit_process(infile);
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(pipes[0][WRITE_END], STDOUT_FILENO);
	return (0);
}

int	write_to_outfile(char *outfile, int (*pipes)[2], int i)
{
	int	fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit_process(outfile);
	dup2(pipes[i - 1][READ_END], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	run_process(int i, int nb, int (*pipes)[2], char **argv)
{
	if (i == 0)
		read_from_infile(argv[0], pipes);
	else if (i == nb - 1)
		write_to_outfile(argv[nb + 1], pipes, i);
	else
	{
		dup2(pipes[i - 1][READ_END], STDIN_FILENO);
		dup2(pipes[i][WRITE_END], STDOUT_FILENO);
	}
	close_all_pipes(pipes, nb - 1);
	execute_command(argv[i + 1]);
	exit(EXIT_FAILURE);
}

int (*create_pipes(int nb))[2]
{
	int(*pipes)[2];
	int i;

	pipes = malloc(sizeof(int[2]) * (nb - 1));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < nb - 1)
	{
		if (pipe(pipes[i++]) == -1)
		{
			premature_exit("Failed to create pipes\n", pipes, 0);
			return NULL;
		}
	}
	return (pipes);
}

int	check_file_access(char *infile, char *outfile)
{
	if (access(infile, R_OK) == -1)
	{
		perror(infile);
		return (-1);
	}
	if (access(outfile, W_OK) == -1 && access(outfile, F_OK) == 0)
	{
		perror(outfile);
		return (-1);
	}
	return (0);
}

int	pipex(char **argv, int argc)
{
	int	i;
	int	pid;
	int	nb_cmds;
	int(*pipes)[2];

	if (check_file_access(argv[0], argv[argc - 1]) == -1)
		return (1);
	nb_cmds = argc - 2;
	pipes = create_pipes(nb_cmds);
	if (!pipes)
		return (premature_exit("Couldn't create pipes\n", NULL, -1));
	i = 0;
	while (i < nb_cmds)
	{
		pid = fork();
		if (pid < 0)
			return (premature_exit("Couldn't fork\n", pipes, -1));
		if (!pid)
			run_process(i, nb_cmds, pipes, argv);
		i++;
	}
	close_all_pipes(pipes, nb_cmds - 1);
	while (wait(NULL) > 0)
		;
	free(pipes);
	return (0);
}
