#include "includes/philo.h"

int	ft_isdead(t_philo *p)
{
	pthread_mutex_lock(&p->casket);
	if (p->dead_body != 0)
	{
		pthread_mutex_unlock(&p->casket);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	grabing_forks(long long int ms_time, t_philo *p, int *i)
{
(void)ms_time;
	if (p->id % 2 == 0)
	{
		if (*i == 0)
		{
			usleep(p->time_to_eat / 2);
		}
		*i = 1;
		pthread_mutex_lock(p->rfork);
		// ms_time = time_after_start(p);
		if (ft_isdead(p) == SUCCESS)
		{
			printf("%lld %d has taken a fork\n", time_after_start(p), p->id);
			pthread_mutex_unlock(&p->casket);
		}
		pthread_mutex_lock(p->lfork);
		// ms_time = time_after_start(p);
		if (ft_isdead(p) == SUCCESS)
		{
			printf("%lld %d has taken a fork\n", time_after_start(p), p->id);
			pthread_mutex_unlock(&p->casket);
		}
	}
	else 
	{
		pthread_mutex_lock(p->lfork);
		ms_time = time_after_start(p);
		if (ft_isdead(p) == SUCCESS)
		{
			printf("%lld %d has taken a fork\n", time_after_start(p), p->id);
			pthread_mutex_unlock(&p->casket);
		}
		pthread_mutex_lock(p->rfork);
		ms_time = time_after_start(p);
		if (ft_isdead(p) == SUCCESS)
		{
			printf("%lld %d has taken a fork\n", time_after_start(p), p->id);
			pthread_mutex_unlock(&p->casket);
		}
	}
	return (SUCCESS);
}

int	eating(t_philo *p)
{
	long long int begining;
	long long int now;

	gettimeofday(&p->tv, NULL);
	begining = time_after_start(p);
	now = begining;
	if (ft_isdead(p) == SUCCESS)
	{
		printf("%lld %d is eating\n", time_after_start(p), p->id);
		pthread_mutex_unlock(&p->casket);
	}
	pthread_mutex_lock(&p->stomach);
	p->last_meal = begining;
	pthread_mutex_unlock(&p->stomach);
	while (now - begining < p->time_to_eat)
	{
		now = time_after_start(p);
		usleep(100);
	}
	pthread_mutex_unlock(p->lfork);
	pthread_mutex_unlock(p->rfork);
	return (SUCCESS);
}

int	sleeping_and_thinking(t_philo *p)
{
	long long int	begining;
	long long int	now;

	begining = time_after_start(p);
	now = begining;
	if (ft_isdead(p) == SUCCESS)
	{
		printf("%lld %d is sleeping\n", time_after_start(p), p->id);
		pthread_mutex_unlock(&p->casket);
	}
	else
		return (FAILURE);
	while (now - begining < p->time_to_sleep)
	{
		now = time_after_start(p);
		usleep(100);
	}
	// thinking
	begining = time_after_start(p);
	if (ft_isdead(p) == SUCCESS)
	{
		printf("%lld %d is thinking\n", time_after_start(p), p->id);
		pthread_mutex_unlock(&p->casket);
	}
	else
		return (FAILURE);
	// usleep(100);
	return (SUCCESS);
}















void *routine(void * arg)
{
	t_philo			*p;
	long long int	ms_time;
	int				i;
	
	p = (t_philo *)arg;
	ms_time = time_after_start(p);
	while (ms_time < 0)
	{
		usleep(100);
		ms_time = time_after_start(p);
	}
	if (ft_isdead(p) == FAILURE)
		return (NULL);
	i = 0;
	while (1)
	{
		if (grabing_forks(ms_time, p, &i) == FAILURE)
				break ;
		if (eating(p) == FAILURE)
			break ;
		if (sleeping_and_thinking(p) == FAILURE)
			break ;
	}
	return (SUCCESS);
}

void	*routine_solo(void *arg)
{
	char	*s;
	s = (char *)arg;
	printf("0 1 has taken a fork\n%d 1 Died\n", ft_atoi(s));
	return (NULL);
}