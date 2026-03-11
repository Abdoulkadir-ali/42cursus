#include <cctype>
#include <iostream>

int	main(int argc, char **argv)
{
	unsigned long	i = 0;
	int j = 0;
	std::string str;

	if (argc < 2)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
		return (0);
	}
	argv++;
	while (*argv)
	{
		str = *argv++;
		i = 0;
		while (i < str.length())
			std::cout << (char)toupper(str.at(i++));
		if (j++ < argc - 1)
			std::cout << ' ';

	}
	return (0);
}
