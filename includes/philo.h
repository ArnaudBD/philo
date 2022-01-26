#ifndef PHILO_H

# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

enum
{
	ERR_ARGC = 1,
	ERR_INIT,
	ERR_PARS
};

typedef struct	s_philo
{
	int				id;
	pthread_mutex_t	*rfork;
	pthread_mutex_t *lfork;
}	t_philo;

typedef	struct	s_config
{
	t_philo	*philos;
	pthread_mutex_t	*forklist;
	int number_of_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_times_each_philosopher_must_eat;
}	t_config;

// INIT
int	parsing(int argc, char *argv[]);
int	init(t_config *c, int argc, char *argv[]);

// UTILS
int		ft_atoi(const char *str);

// KILL
int	terminator(t_config *c, int code);

#endif