/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <abiju-du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 23:54:13 by abiju-du          #+#    #+#             */
/*   Updated: 2022/02/03 23:54:25 by abiju-du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	even_philos(t_philo *p, int *i)
{
	if (*i == 0)
		usleep(p->time_to_eat * 500);
	pthread_mutex_lock(p->lfork);
	if (ft_isdead(p) == SUCCESS)
	{
		printf("%lld %d has taken a fork\n", t_aft_start(p->start_time), p->id);
		pthread_mutex_unlock(p->casket);
	}
	pthread_mutex_lock(p->rfork);
}

int	grabing_forks(t_philo *p, int *i)
{
	if (p->id % 2 == 0)
		even_philos(p, i);
	else
	{
		pthread_mutex_lock(p->rfork);
		if (ft_isdead(p) == SUCCESS)
		{
			printf("%lld %d has taken a fork\n", \
			t_aft_start(p->start_time), p->id);
			pthread_mutex_unlock(p->casket);
		}
		pthread_mutex_lock(p->lfork);
	}
	if (ft_isdead(p) == SUCCESS)
	{
		printf("%lld %d has taken a fork\n", t_aft_start(p->start_time), p->id);
		pthread_mutex_unlock(p->casket);
	}
	return (SUCCESS);
}

int	eating(t_philo *p)
{
	long long int	begining;
	long long int	now;

	// gettimeofday(&p->tv, NULL);
	begining = t_aft_start(p->start_time);
	now = begining;
	if (ft_isdead(p) == SUCCESS)
	{
		printf("%lld %d is eating\n", t_aft_start(p->start_time), p->id);
		pthread_mutex_unlock(p->casket);
	}
	else
	{
		pthread_mutex_unlock(p->rfork);
		pthread_mutex_unlock(p->lfork);
		return (FAILURE);
	}
	pthread_mutex_lock(p->stomach);
	p->last_meal = begining;
	pthread_mutex_unlock(p->stomach);
	while (now - begining < p->time_to_eat)
	{
		now = t_aft_start(p->start_time);
		usleep(100);
	}
	pthread_mutex_unlock(p->rfork);
	pthread_mutex_unlock(p->lfork);

	return (SUCCESS);
}

int	thinking(t_philo *p)
{
	if (ft_isdead(p) == SUCCESS)
	{
		printf("%lld %d is thinking\n", t_aft_start(p->start_time), p->id);
		pthread_mutex_unlock(p->casket);
	}
	else
		return (FAILURE);
	return (SUCCESS);
}

int	sleeping_and_thinking(t_philo *p)
{
	long long int	begining;
	long long int	now;

	begining = t_aft_start(p->start_time);
	now = begining;
	if (ft_isdead(p) == SUCCESS)
	{
		printf("%lld %d is sleeping\n", t_aft_start(p->start_time), p->id);
		pthread_mutex_unlock(p->casket);
	}
	else
		return (FAILURE);
	while (now - begining < p->time_to_sleep)
	{
		now = t_aft_start(p->start_time);
		usleep(100);
	}
	if (thinking(p) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
