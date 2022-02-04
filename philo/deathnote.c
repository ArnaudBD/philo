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
		pthread_mutex_lock(c->casket);
		printf("%lld %d died\n", t_aft_start(c->start_time), *i + 1);
		j = 0;
		while (j < c->number_of_philosophers)
		{
			c->philos[j].dead_body = j + 1;
			j++;
		}
		pthread_mutex_unlock(c->stomach);
		return (FAILURE);
	}
	pthread_mutex_unlock(c->stomach);
	// pthread_mutex_lock(c->casket);
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
	// starting_block(c->start_time);
	while (1)
	{
		// usleep(500);
		ms_tv = t_aft_start(c->start_time);
// printf("%lld %")
		if (see_the_stomach(c, &full, ms_tv, &i) == FAILURE)
			break ;
		if (++i == c->number_of_philosophers)
			i = 0;
	}
		pthread_mutex_unlock(c->casket);
	// pthread_mutex_lock(c->casket);
	// pthread_mutex_unlock(c->casket);
	return (SUCCESS);
}
