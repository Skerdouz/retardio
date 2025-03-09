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
	
}