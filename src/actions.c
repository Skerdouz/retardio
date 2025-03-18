#include "retardio.h"

u_int64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (error("gettimeofday() FAILURE\n", NULL));
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

void	messages(char *str, t_retard *retard)
{
	u_int64_t	time;

	pthread_mutex_lock(&retard->data->write);
	time = get_time() - retard->data->start_time;
	if (!strcmp("DIED", str) && !retard->data->dead)
	{
		printf("%llu %d %s\n", time, retard->id, str);
		retard->data->dead = 1;
	}
	if (!retard->data->dead)
		printf("%llu %d %s\n", time, retard->id, str);
	pthread_mutex_unlock(&retard->data->write);
}

void	take_forks(t_retard *retard)
{
	pthread_mutex_lock(retard->l_fork);
	messages("TAKE_FORKS", retard);
	pthread_mutex_lock(retard->r_fork);
	messages("TAKE_FORKS", retard);
}

void	drop_forks(t_retard *retard)
{
	pthread_mutex_unlock(retard->l_fork);
	pthread_mutex_unlock(retard->r_fork);
	messages("SLEEPING", retard);
	usleep(retard->data->sleep_time);
}

void	eat(t_retard *retard)
{
	take_forks(retard);
	pthread_mutex_lock(&retard->lock);
	retard->eating = 1;
	retard->time_to_die = get_time() + retard->data->death_time;
	messages("EATING", retard);
	retard->eat_count++;
	usleep(retard->data->eat_time);
	retard->eating = 0;
	pthread_mutex_unlock(&retard->lock);
	drop_forks(retard);
}
