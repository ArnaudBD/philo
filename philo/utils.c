/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <abiju-du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 23:55:43 by abiju-du          #+#    #+#             */
/*   Updated: 2022/02/03 23:55:46 by abiju-du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	n;
	int	resultat;

	i = 0;
	n = 1;
	resultat = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			n = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		resultat = 10 * resultat + str[i] - '0';
		i++;
	}
	return (resultat * n);
}

long long int	t_aft_start(struct timeval start_time)
{
	long long int	time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000) \
	- ((start_time.tv_sec * 1000) + (start_time.tv_usec / 1000));
	return (time);
}

int	ft_isdead(t_philo *p)
{
	pthread_mutex_lock(p->casket);
	if (p->dead_body != 0)
	{
		pthread_mutex_unlock(p->casket);
		return (FAILURE);
	}
	return (SUCCESS);
}
