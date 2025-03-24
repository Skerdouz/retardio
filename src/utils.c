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
	int	val = 0;

	val = atoi(args[i++]);
	if (val < 1 || val > 200)
		return (1);
	while (i != 6)
	{
		val = atoi(args[i++]);
		if (!val)
			return (1);
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