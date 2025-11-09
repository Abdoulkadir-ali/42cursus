#include "pipex.h"

int	main(int argc, char **argv)
{
	if (argc < 5)
		return (ft_putstr_fd(2, "Usage: ./pipex infile cmd1 cmd2 ... outfile\n",
				1));
	argv++;
	argc--;
	pipex(argv, argc);
	return (0);
}
