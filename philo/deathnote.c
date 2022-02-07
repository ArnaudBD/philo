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
	int	j;

	pthread_mutex_lock(c->stomach);
	*full = c->philos[*i].full;
	if ((ms_tv - c->philos[*i].last_meal) > c->time_to_die)
	{
		pthread_mutex_lock(c->philos[*i].casket);
		j = 0;
		while (j < c->number_of_philosophers)
		{
			c->philos[j].dead_body = j + 1;
			j++;
		}
		printf("%lld %d died\n", ms_tv, *i + 1);
		pthread_mutex_unlock(c->philos[*i].casket);
		pthread_mutex_unlock(c->stomach);
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
	while (1)
	{
		ms_tv = t_aft_start(c->start_time);
		if (see_the_stomach(c, &full, ms_tv, &i) == FAILURE)
			break ;
		if (++i == c->number_of_philosophers)
			i = 0;
	}
	return (SUCCESS);
}
