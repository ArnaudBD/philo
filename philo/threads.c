/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <abiju-du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 23:55:25 by abiju-du          #+#    #+#             */
/*   Updated: 2022/02/03 23:55:33 by abiju-du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	starting_block(struct timeval start_time)
{
	long long int	ms_time;

	ms_time = t_aft_start(start_time);
	while (ms_time < 0)
	{
		usleep(100);
		ms_time = t_aft_start(start_time);
	}
}

void	*routine(void *arg)
{
	t_philo			*p;
	int				i;

	p = (t_philo *)arg;
	pthread_mutex_lock(p->casket);
	// starting_block(p->start_time);
	pthread_mutex_unlock(p->casket);

	i = 0;
	while (1)
	{
		if (grabing_forks(p, &i) == FAILURE)
			break ;
		if (eating(p) == FAILURE)
			break ;
		if (++i >= p->num_of_t_e_p_m_eat && p->num_of_t_e_p_m_eat > 0)
		{
			pthread_mutex_lock(p->stomach);
			p->full = 1;
			pthread_mutex_unlock(p->stomach);
			break ;
		}	
		if (sleeping_and_thinking(p) == FAILURE)
			break ;
	}
	return (SUCCESS);
}

void	*routine_solo(void *arg)
{
	char	*s;

	s = (char *)arg;
	printf("0 1 has taken a fork\n");
	usleep(1000 * ft_atoi(s));
	printf("%d %d 1 died\n", ft_atoi(s), ft_atoi(s));
	return (NULL);
}
