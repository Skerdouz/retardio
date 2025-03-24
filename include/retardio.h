#ifndef RETARDIO_H
# define RETARDIO_H

# include <stdio.h> // printf
# include <stdlib.h> // atoi, malloc
# include <string.h> // strcmp
# include <pthread.h> // pthread stuff
# include <stdint.h> // uint64_t type
# include <sys/types.h> // u_int64_t type (fuck this)
# include <sys/time.h> // timeval type (fuck this too)
# include <unistd.h> // usleep

// error macros
# define ALLOC_ERR_TID "ALLOCATION ERROR FOR THREAD ID"
# define ALLOC_ERR_FORK "ALLOCATION ERROR FOR FORKS"
# define ALLOC_ERR_RETARD "ALLOCATION ERROR FOR RETARDS"

# define TH_ERR_CREATE "ERROR WHILE CREATING THREAD"
# define TH_ERR_JOIN "ERROR WHILE JOINING THREAD"

# define RTD_THINKING "is thinking"
# define RTD_SLEEPING "is sleeping"
# define RTD_EATING "is eating"
# define RTD_TAKE_FORK "has taken a fork"
# define RTD_DIED "has died"

typedef struct s_retard
{
	struct s_data	*data;
	pthread_t		t1;
	int				id;
	int				eat_count;
	int				status;
	int				eating;
	uint64_t		time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
} t_retard;

typedef struct s_data
{
	pthread_t		*tid;
	int				retard_num;
	int				meals_nb;
	int				dead;
	int				finished;
	t_retard		*retards;
	uint64_t		death_time;
	uint64_t		eat_time;
	uint64_t		sleep_time;
	uint64_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
} t_data;

// utils
int			check_args(char **args);
int			isnumber(char *str);
int			error(char *str, t_data *data);

// init
int			init(t_data *data, char **args);

// actions
u_int64_t	get_time(void);
void		messages(char *str, t_retard *retard);
void		eat(t_retard *retard);

// threads
void		*routine(void *retard_pointer);
int			thread_init(t_data *data);

// main
void		ft_exit(t_data *data);

#endif