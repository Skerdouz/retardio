#include "retardio.h"

int	isnumber(char *str)
{
	if (!*str)
		return (0);

	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int	check_args(char **args)
{
	int	i = 1;
	int	n = 0;

	while (i != 7)
	{
		if (!isnumber(args[i]))
			return (1);

		n = atoi(args[i]);

		if (i == 1)
			if (n < 1 || n > 200)
				return (1);
		else
			if (n < 1)
				return (1);
		i++;
	}
	return (0);
}

int	error(char *str, t_data *data)
{
	printf("%s\n", str);
	if (data)
		ft_exit(data);
	return (1);
}