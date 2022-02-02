#include "includes/philo.h"

void *timekeeper(void *arg)
{
	t_config		*c;
	// struct timeval	tv;
	int				i;
	int				id;
	long long int	ms_tv;

	c = (t_config *)arg;
	i = 0;
	// gettimeofday(&c->philos->tv, NULL);
	// ms_tv = time_after_start(c->start_time);
	// while (ms_tv < 0)
	// {
	// 	usleep(100);
	// 	gettimeofday(&c->philos->tv, NULL);
	// 	ms_tv = time_after_start(c->start_time);
	// }

	while (1)
	{
			id = c->philos[i].id;
			// gettimeofday(&tv, NULL);
			ms_tv = time_after_start(c->start_time);
			pthread_mutex_lock(&c->philos[i].stomach);
			if ((ms_tv - c->philos[i].last_meal) > c->time_to_die)
			{
				pthread_mutex_unlock(&c->philos[i].stomach);
				pthread_mutex_lock(c->philos[i].casket);
				printf("%lld %d died\n", ms_tv, id);
				pthread_mutex_unlock(c->philos[i].casket);
				break ;
			}
			pthread_mutex_unlock(&c->philos[i].stomach);
			i++;
			if (i == c->number_of_philosophers)
				i = 0;
	}
	i = 0;
	while (i < c->number_of_philosophers)
	{
		pthread_mutex_lock(c->philos[i].casket);
		c->philos[i].dead_body = id;
		pthread_mutex_unlock(c->philos[i].casket);
		i++;
	}

	return (SUCCESS);
}