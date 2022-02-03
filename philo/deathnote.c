/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deathnote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <abiju-du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 23:54:34 by abiju-du          #+#    #+#             */
/*   Updated: 2022/02/03 23:54:37 by abiju-du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	see_the_stomach(t_config *c, int *full, long long int ms_tv, int *i)
{
	pthread_mutex_lock(c->stomach);
	*full = c->philos[*i].full;
	if ((ms_tv - c->philos[*i].last_meal) > c->time_to_die)
	{
		pthread_mutex_lock(c->philos[*i].casket);
		printf("%lld %d died\n", ms_tv, *i + 1);
		pthread_mutex_unlock(c->stomach);
		pthread_mutex_unlock(c->philos[*i].casket);
		return (FAILURE);
	}
	pthread_mutex_unlock(c->stomach);
	if (*full == 1)
		return (FAILURE);
	return (SUCCESS);
}

void	*timekeeper(void *arg)
{
	t_config		*c;
	int				i;
	long long int	ms_tv;
	int				full;

	c = (t_config *)arg;
	i = 0;
	starting_block(c->start_time);
	while (1)
	{
		ms_tv = t_aft_start(c->start_time);
		if (see_the_stomach(c, &full, ms_tv, &i) == FAILURE)
			break ;
		if (++i == c->number_of_philosophers)
			i = 0;
	}
	i = 0;
	pthread_mutex_lock(c->casket);
	while (i < c->number_of_philosophers && full != 1)
	{
		c->philos[i].dead_body = i + 1;
		i++;
	}
	pthread_mutex_unlock(c->casket);
	return (SUCCESS);
}
