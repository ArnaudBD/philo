/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <abiju-du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 23:54:44 by abiju-du          #+#    #+#             */
/*   Updated: 2022/02/03 23:54:47 by abiju-du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	parsing(int argc, char *argv[], t_config *c)
{
	pthread_t	t;

	if (argc != 5 && argc != 6)
		return (terminator(c, ERR_PARS));
	if (ft_atoi(argv[1]) < 0 || ft_atoi(argv[2]) < 0 \
	|| ft_atoi(argv[3]) < 0 || ft_atoi(argv[4]) < 0)
		return (terminator(c, ERR_PARS));
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) < 0)
			return (terminator(c, ERR_PARS));
	}
	if (ft_atoi(argv[1]) == 1)
	{
		pthread_create(&t, NULL, routine_solo, argv[2]);
		pthread_join(t, NULL);
		return (FAILURE);
	}
	return (SUCCESS);
}

void	set_values(t_config *c, int i)
{
	c->philos[i].id = i + 1;
	c->philos[i].ms_start = c->ms_start;
	c->philos[i].start_time = c->start_time;
	c->philos[i].lfork = &c->forklist[i];
	c->philos[i].dead_body = c->dead_body;
	c->philos[i].time_to_die = c->time_to_die;
	c->philos[i].time_to_eat = c->time_to_eat;
	c->philos[i].time_to_sleep = c->time_to_sleep;
	c->philos[i].num_of_t_e_p_m_eat = c->num_of_t_e_p_m_eat;
	c->philos[i].last_meal = c->ms_start;
	c->philos[i].casket = c->casket;
	c->philos[i].stomach = c->stomach;
	c->philos[i].full = 0;
	pthread_mutex_init(&c->forklist[i], NULL);
	if (i + 1 == c->number_of_philosophers)
	{
		pthread_mutex_init(&c->forklist[0], NULL);
		c->philos[i].rfork = &c->forklist[0];
	}
	else
	{
		pthread_mutex_init(&c->forklist[i + 1], NULL);
		c->philos[i].rfork = &c->forklist[i + 1];
	}
}

t_config	*init_philosophers(t_config *c)
{
	int	i;

	i = 0;
	while (i < c->number_of_philosophers)
	{
		set_values(c, i);
		i++;
	}
	return (c);
}

int	init_malloc(t_config *c)
{
	c->philos = malloc(sizeof(t_philo) * c->number_of_philosophers);
	if (!c->philos)
		return (FAILURE);
	c->forklist = malloc(sizeof(pthread_mutex_t) * c->number_of_philosophers);
	if (!c->forklist)
		return (FAILURE);
	c->casket = malloc(sizeof(pthread_mutex_t));
	if (!c->casket)
		return (FAILURE);
	c->stomach = malloc(sizeof(pthread_mutex_t));
	if (!c->stomach)
		return (FAILURE);
	return (SUCCESS);
}

int	init(t_config *c, int argc, char *argv[])
{
	gettimeofday(&c->start_time, NULL);
	c->ms_start = 1000 + (c->start_time.tv_sec * 1000) \
	+ (c->start_time.tv_usec / 1000);
	c->number_of_philosophers = ft_atoi(argv[1]);
	c->time_to_die = ft_atoi(argv[2]);
	c->time_to_eat = ft_atoi(argv[3]);
	c->time_to_sleep = ft_atoi(argv[4]);
	c->dead_body = 0;
	if (argc == 6)
		c->num_of_t_e_p_m_eat = ft_atoi(argv[5]);
	else
		c->num_of_t_e_p_m_eat = -1;
	if (init_malloc(c) == FAILURE)
		return (FAILURE);
	pthread_mutex_init(c->casket, NULL);
	pthread_mutex_init(c->stomach, NULL);
	c = init_philosophers(c);
	return (SUCCESS);
}
