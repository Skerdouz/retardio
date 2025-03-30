#include "retardio.h"

static int	case_one(t_data *data)
{
	data->start_time = get_time();
	if (pthread_create(&data->tid[0], NULL, &routine, &data->retards[0]))
		return (error(TH_ERR_CREATE, data));
	pthread_detach(data->tid[0]);
	while (data->dead == 0)
		usleep(0);
	ft_exit(data);
	return (0);
}

void	free_data(t_data *data)
{
	if (data->tid)
		free(data->tid);
	if (data->forks)
		free(data->forks);
	if (data->retards)
		free(data->retards);
}

void	ft_exit(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->retard_num)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->retards[i].lock);
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->lock);
	free_data(data);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 6 || check_args(av))
		return (printf("invalid args: {retard_amount} {time_to_die} {time_to_eat} {time_to_sleep} {eat_amount_to_end}\n"), 0);
	if (init(&data, av))
		return (1);
	if (data.retard_num == 1)
		return (case_one(&data));
	if (thread_init(&data))
		return (1);
	ft_exit(&data);
	return (0);
}
