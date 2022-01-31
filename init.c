#include "includes/philo.h"

int	parsing(int argc, char *argv[], t_config *c)
{
	(void)argv;
	if (argc != 5 && argc != 6)
		return (terminator(c, ERR_PARS));
	return (0);
}

int	init_philosophers(t_config *c)
{
	int	i;

	i = 0;
	while (i < c->number_of_philosophers)
	{
		c->philos[i].id = i + 1;
		c->philos[i].ms_start = c->ms_start;
		c->philos[i].lfork = &c->forklist[i];
		c->philos[i].time_to_die = c->time_to_die;
		c->philos[i].time_to_eat = c->time_to_eat;
		c->philos[i].time_to_sleep = c->time_to_sleep;
		pthread_mutex_init(&c->forklist[i], NULL);
		if (i + 1 == c->number_of_philosophers)
		{
			pthread_mutex_init(&c->forklist[0], NULL);
			c->philos[i].rfork = &c->forklist[0];
		}
		else
		{
			pthread_mutex_init(&c->forklist[i + 1], NULL);
			c->philos[i].rfork = &c->forklist[i + 1];
		}
		i++;
	}
	return (SUCCESS);
}

int	init(t_config *c, int argc, char *argv[])
{
	gettimeofday(&c->start_time, NULL);
	c->ms_start = 1000 + (c->start_time.tv_sec * 1000) \
	+ (c->start_time.tv_usec / 1000);
	c->number_of_philosophers = ft_atoi(argv[1]);
	c->time_to_die = ft_atoi(argv[2]);
	c->time_to_eat = ft_atoi(argv[3]);
	c->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		c->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	c->philos = malloc(sizeof(t_philo) * c->number_of_philosophers);
	if (!c->philos)
		return (FAILURE);
	c->forklist = malloc(sizeof(pthread_mutex_t) * c->number_of_philosophers);
	init_philosophers(c);
	return (SUCCESS);
}
