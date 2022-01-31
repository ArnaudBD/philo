#include "includes/philo.h"

void	grabing_forks(long long int ms_time, t_philo *p)
{
	int	i;

	i = 0;
	if (i == 0 && p->id % 2 == 0)
	{
		i = 1;
		usleep(p->time_to_eat);
		pthread_mutex_lock(p->lfork);
		gettimeofday(&p->tv, NULL);
		ms_time = (p->tv.tv_sec * 1000) + (p->tv.tv_usec / 1000) - p->ms_start;
		printf("%lld %d has taken a fork\n", ms_time, p->id);
	}
	else 
	{
		pthread_mutex_lock(p->lfork);
		gettimeofday(&p->tv, NULL);
		ms_time = (p->tv.tv_sec * 1000) + (p->tv.tv_usec / 1000) - p->ms_start;
		printf("%lld %d has taken a fork\n", ms_time, p->id);
	}
	pthread_mutex_lock(p->rfork);
	gettimeofday(&p->tv, NULL);
	ms_time = (p->tv.tv_sec * 1000) + (p->tv.tv_usec / 1000) - p->ms_start;
	printf("%lld %d has taken a fork\n", ms_time, p->id);
}

void	eating(long long int ms_time, t_philo *p)
{
	long long int begining;

	gettimeofday(&p->tv, NULL);
	begining = (p->tv.tv_sec * 1000) + (p->tv.tv_usec / 1000) - p->ms_start;
	printf("%lld %d is eating\n", begining, p->id);
	while (ms_time - begining < p->time_to_eat)
	{
		gettimeofday(&p->tv, NULL);
		ms_time = (p->tv.tv_sec * 1000) + (p->tv.tv_usec / 1000) - p->ms_start;
		usleep(p->time_to_eat / 100);
	}
	pthread_mutex_unlock(p->lfork);
	pthread_mutex_unlock(p->rfork);
}

void	sleeping_and_thinking(long long int ms_time, t_philo *p)
{
	long long int	begining;

	begining = (p->tv.tv_sec * 1000) + (p->tv.tv_usec / 1000) - p->ms_start;
	printf("%lld %d is sleeping\n", begining, p->id);
	while (ms_time - begining < p->time_to_sleep)
	{
		gettimeofday(&p->tv, NULL);
		ms_time = (p->tv.tv_sec * 1000) + (p->tv.tv_usec / 1000) - p->ms_start;
		usleep(p->time_to_sleep / 100);
	}
	// thinking
	begining = (p->tv.tv_sec * 1000) + (p->tv.tv_usec / 1000) - p->ms_start;
	printf("%lld %d is thinking\n", ms_time, p->id);
}

void *routine(void * arg)
{
	t_philo			*p;
	long long int	ms_time;
	
	p = (t_philo *)arg;
	gettimeofday(&p->tv, NULL);
	ms_time = (p->tv.tv_sec * 1000) + (p->tv.tv_usec / 1000) - p->ms_start;
	while (ms_time < 0)
	{
		usleep(100);
		gettimeofday(&p->tv, NULL);
		ms_time = (p->tv.tv_sec * 1000) + (p->tv.tv_usec / 1000) - p->ms_start;

	}
	// grabing forks
	while (1)
	{
		grabing_forks(ms_time, p);
		// if (i == 0 && p->id % 2 == 0)
		// {
		// 	i = 1;
		// 	usleep(p->time_to_eat);
		// 	pthread_mutex_lock(p->lfork);
		// 	gettimeofday(&p->tv, NULL);
		// 	ms_time = (p->tv.tv_sec * 1000) + (p->tv.tv_usec / 1000) - p->ms_start;
		// 	printf("%lld %d has taken a fork\n", ms_time, p->id);
		// }
		// else 
		// {
		// 	pthread_mutex_lock(p->lfork);
		// 	gettimeofday(&p->tv, NULL);
		// 	ms_time = (p->tv.tv_sec * 1000) + (p->tv.tv_usec / 1000) - p->ms_start;
		// 	printf("%lld %d has taken a fork\n", ms_time, p->id);
		// }
		// pthread_mutex_lock(p->rfork);
		// gettimeofday(&p->tv, NULL);
		// ms_time = (p->tv.tv_sec * 1000) + (p->tv.tv_usec / 1000) - p->ms_start;
		// printf("%lld %d has taken a fork\n", ms_time, p->id);

		eating(ms_time, p);
		sleeping_and_thinking(ms_time, p);		
	}
	return (SUCCESS);
}
