#include "includes/philo.h"

int	ft_isdead(t_philo *p)
{
	pthread_mutex_lock(&p->casket);
	if (p->dead_body != 0)
	{
		pthread_mutex_unlock(&p->casket);
		return (FAILURE);
	}
	else
		pthread_mutex_unlock(&p->casket);
	return (SUCCESS);
}

int	grabing_forks(long long int ms_time, t_philo *p, int *i)
{
	if (*i == 0 && p->id % 2 == 0)
	{
		*i = 1;
		usleep(p->time_to_eat);
		pthread_mutex_lock(p->lfork);
		gettimeofday(&p->tv, NULL);
		ms_time = (p->tv.tv_sec * 1000) + (p->tv.tv_usec / 1000) - p->ms_start;
		if (ft_isdead(p) == SUCCESS)
			printf("%lld %d has taken a fork\n", ms_time, p->id);
	}
	else 
	{
		pthread_mutex_lock(p->lfork);
		gettimeofday(&p->tv, NULL);
		ms_time = (p->tv.tv_sec * 1000) + (p->tv.tv_usec / 1000) - p->ms_start;
		if (ft_isdead(p) == SUCCESS)
			printf("%lld %d has taken a fork\n", ms_time, p->id);
	}
	pthread_mutex_lock(p->rfork);
	// if (ft_isdead(p) == FAILURE)
	// 	return (FAILURE);
	gettimeofday(&p->tv, NULL);
	ms_time = (p->tv.tv_sec * 1000) + (p->tv.tv_usec / 1000) - p->ms_start;
	if (ft_isdead(p) == SUCCESS)
		printf("%lld %d has taken a fork\n", ms_time, p->id);
	return (SUCCESS);
}

int	eating(long long int ms_time, t_philo *p)
{
	long long int begining;

	gettimeofday(&p->tv, NULL);
	begining = (p->tv.tv_sec * 1000) + (p->tv.tv_usec / 1000) - p->ms_start;
	if (ft_isdead(p) == SUCCESS)
		printf("%lld %d is eating\n", begining, p->id);
	pthread_mutex_lock(&p->stomach);
	p->last_meal = begining;
	pthread_mutex_unlock(&p->stomach);
	while (ms_time - begining < p->time_to_eat)
	{
		gettimeofday(&p->tv, NULL);
		ms_time = (p->tv.tv_sec * 1000) + (p->tv.tv_usec / 1000) - p->ms_start;
		usleep(p->time_to_eat / 100);
		// if (ft_isdead(p) == FAILURE)
		// 	return (FAILURE);
	}
	pthread_mutex_unlock(p->lfork);
	pthread_mutex_unlock(p->rfork);
	return (SUCCESS);
}

int	sleeping_and_thinking(long long int ms_time, t_philo *p)
{
	long long int	begining;

	if (ft_isdead(p) == FAILURE)
		return (FAILURE);
	begining = (p->tv.tv_sec * 1000) + (p->tv.tv_usec / 1000) - p->ms_start;
	if (ft_isdead(p) == SUCCESS)
		printf("%lld %d is sleeping\n", begining, p->id);
	while (ms_time - begining < p->time_to_sleep)
	{
		gettimeofday(&p->tv, NULL);
		ms_time = (p->tv.tv_sec * 1000) + (p->tv.tv_usec / 1000) - p->ms_start;
		usleep(p->time_to_sleep / 100);
		if (ft_isdead(p) == FAILURE)
			return (FAILURE);
	}
	// thinking
	if (ft_isdead(p) == FAILURE)
		return (FAILURE);
	begining = (p->tv.tv_sec * 1000) + (p->tv.tv_usec / 1000) - p->ms_start;
	if (ft_isdead(p) == SUCCESS)
		printf("%lld %d is thinking\n", begining, p->id);
	return (SUCCESS);
}

void *routine(void * arg)
{
	t_philo			*p;
	long long int	ms_time;
	int				i;
	
	p = (t_philo *)arg;
	gettimeofday(&p->tv, NULL);
	ms_time = (p->tv.tv_sec * 1000) + (p->tv.tv_usec / 1000) - p->ms_start;
	while (ms_time < 0)
	{
		usleep(100);
		gettimeofday(&p->tv, NULL);
		ms_time = (p->tv.tv_sec * 1000) + (p->tv.tv_usec / 1000) - p->ms_start;

	}
	if (ft_isdead(p) == FAILURE)
		return (NULL);
	i = 0;
	while (1)
	{
		if (grabing_forks(ms_time, p, &i) == FAILURE)
			{

				break ;
			}
		// if (ft_isdead(p) == FAILURE)
		// 	return (NULL);
		if (eating(ms_time, p) == FAILURE)
			break ;
		if (ft_isdead(p) == FAILURE)
			break ;
		if (sleeping_and_thinking(ms_time, p) == FAILURE)
			break ;
		if (ft_isdead(p) == FAILURE)
			break ;
	}
	//---------------//
// gettimeofday(&p->tv, NULL);
// ms_time = (p->tv.tv_sec * 1000) + (p->tv.tv_usec / 1000) - p->ms_start;
// printf("%lld for %d, hello im here%d\n", ms_time, p->id, i++);
//------------//
	return (SUCCESS);
}

void	*routine_solo(void *arg)
{
	char	*s;
	s = (char *)arg;
	printf("0 1 has taken a fork\n%d 1 Died\n", ft_atoi(s));
	return (NULL);
}