#include "includes/philo.h"

void *timekeeper(void *arg)
{
	t_config		*c;
	int				i;
	int				id;
	long long int	ms_tv;
	int				full;

	c = (t_config *)arg;
	i = 0;
	gettimeofday(&c->philos->tv, NULL);
	ms_tv = time_after_start(c->start_time);
	while (ms_tv < 0)
	{
		usleep(100);
		gettimeofday(&c->philos->tv, NULL);
		ms_tv = time_after_start(c->start_time);
	}

	while (1)
	{
			pthread_mutex_lock(c->stomach);
			id = c->philos[i].id;
			pthread_mutex_unlock(c->stomach);
			ms_tv = time_after_start(c->start_time);
			pthread_mutex_lock(c->stomach);
			full = c->philos[i].full;
			if ((ms_tv - c->philos[i].last_meal) > c->time_to_die)
			{
				pthread_mutex_unlock(c->stomach);
				pthread_mutex_lock(c->philos[i].casket);
				printf("%lld %d died\n", ms_tv, id);
				pthread_mutex_unlock(c->philos[i].casket);
				break ;
			}
			pthread_mutex_unlock(c->stomach);
			if (full == 1)
				break ;
			i++;
			if (i == c->number_of_philosophers)
				i = 0;
	}
	i = 0;
	pthread_mutex_lock(c->casket);
	while (i < c->number_of_philosophers && full !=1)
	{
		c->philos[i].dead_body = id;
		i++;
	}
	pthread_mutex_unlock(c->casket);

	return (SUCCESS);
}