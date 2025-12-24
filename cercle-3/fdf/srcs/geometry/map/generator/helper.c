#include "generator.h"

static int	ft_atoi_safe(const char *str)
{
	if (!str)
		return (0);
	return (ft_atoi(str));
}

static float	ft_atof(const char *str)
{
	float	res;
	float	sign;
	int		i;
	float	div;

	res = 0.0;
	sign = 1.0;
	i = 0;
	div = 1.0;
	if (str[i] == '-')
	{
		sign = -1.0;
		i++;
	}
	while (str[i] && str[i] != '.')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		while (str[i])
		{
			res = res * 10 + (str[i] - '0');
			div *= 10;
			i++;
		}
	}
	return (res / div * sign);
}