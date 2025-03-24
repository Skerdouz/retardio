#include "retardio.h"

void	*monitor(void *data_pointer)
{
	t_retard	*retard;

	retard = (t_retard *) data_pointer;
	pthread_mutex_lock(&retard->data->write);
	printf("data val: %d", retard->data->dead);
	pthread_mutex_unlock(&retard->data->write);
	while (!retard->data->dead)
	{
		pthread_mutex_lock(&retard->lock);
		if (retard->data->finished >= retard->data->retard_num)
			retard->data->dead = 1;
		pthread_mutex_unlock(&retard->lock);
	}
	return ((void *) 0);
}

void	*supervisor(void *retard_pointer)
{
	t_retard	*retard;

	retard = (t_retard *) retard_pointer;
	while (!retard->data->dead)
	{
		pthread_mutex_lock(&retard->lock);
		if (get_time() >= retard->time_to_die && !retard->eating)
			messages(RTD_DIED, retard);
		if (retard->eat_count == retard->data->meals_nb)
		{
			pthread_mutex_lock(&retard->data->lock);
			retard->data->finished++;
			retard->eat_count++;
			pthread_mutex_unlock(&retard->data->lock);
		}
		pthread_mutex_unlock(&retard->lock);
	}
	return ((void *) 0);
}

void	*routine(void *retard_pointer)
{
	t_retard	*retard;

	retard = (t_retard *) retard_pointer;
	retard->time_to_die = retard->data->death_time + get_time();
	if (pthread_create(&retard->t1, NULL, &supervisor, (void *)retard))
		return ((void *)1);
	while (!retard->data->dead)
	{
		eat(retard);
		messages(RTD_THINKING, retard);
	}
	if (pthread_join(retard->t1, NULL))
		return ((void *)1);
	return ((void *)0);
}

int	thread_init(t_data *data)
{
	int			i;
	pthread_t	t0;

	i = -1;
	data->start_time = get_time();
	if (data->meals_nb > 0)
	{
		if (pthread_create(&t0, NULL, &monitor, &data->retards[0]))
			return (error(TH_ERR_CREATE, data));
		while (++i < data->retard_num)
		{
			if (pthread_create(&data->tid[i], NULL, &routine, &data->retards[i]))
				return (error(TH_ERR_CREATE, data));
			usleep(1);
		}
		i = -1;
		while (++i < data->retard_num)
		{
			if (pthread_join(data->tid[i], NULL))
				return (error(TH_ERR_JOIN, data));
		}
		return (0);
	}
}
