#include "retardio.h"

static void	init_data(t_data *data, char **args)
{
	data->retard_num = (int) atoi(args[1]);
	data->death_time = (uint64_t) atoi(args[2]);
	data->eat_time = (uint64_t) atoi(args[3]);
	data->sleep_time = (uint64_t) atoi(args[4]);
	data->meals_nb = (int) atoi(args[5]);
	data->dead = 0;
	data->finished = 0;
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->lock, NULL);
}

static void	init_retards(t_data *data)
{
	int	i = 0;
	
	while (i < data->retard_num)
	{
		data->retards[i].data = data;
		data->retards[i].id = i + 1;
		data->retards[i].time_to_die = data->death_time;
		data->retards[i].eat_count = 0;
		data->retards[i].eating = 0;
		data->retards[i].status = 0;
		pthread_mutex_init(&data->retards[i].lock, NULL);
		i++;
	}
}

static int	init_forks(t_data *data)
{
	int	i = -1;

	while (++i < data->retard_num)
		pthread_mutex_init(&data->forks[i], NULL);
	data->retards[0].l_fork = &data->forks[0];
	data->retards[0].r_fork = &data->forks[data->retard_num - 1];
	i = 1;
	while (i < data->retard_num)
	{
		data->retards[i].l_fork = &data->forks[i];
		data->retards[i].r_fork = &data->forks[i - 1];
		i++;
	}
	return (0);
}

static int	alloc(t_data *data)
{
	data->tid = malloc(sizeof(pthread_t) * data->retard_num);
	if(!data->tid)
		return (error(ALLOC_ERR_TID, data));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->retard_num);
	if(!data->forks)
		return (error(ALLOC_ERR_FORK, data));
	data->retards = malloc(sizeof(t_retard) * data->retard_num);
	if(!data->retards)
		return (error(ALLOC_ERR_RETARD, data));
	return (0);
}

int	init(t_data *data, char **args)
{
	init_data(data, args);
	if (alloc(data))
		return (1);
	if (init_forks(data))
		return (1);
	init_retards(data);
	return (0);
}