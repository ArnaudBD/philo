/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <abiju-du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 23:55:12 by abiju-du          #+#    #+#             */
/*   Updated: 2022/02/03 23:55:14 by abiju-du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	main(int argc, char *argv[])
{
	t_config	c;
	int			i;
	pthread_t	chronos;

	if (parsing(argc, argv, &c) == FAILURE)
		return (0);
	if (init(&c, argc, argv) == FAILURE)
		return (terminator(&c, ERR_INIT));
	pthread_mutex_lock(c.casket);	
	i = 0;
	while (i < c.number_of_philosophers)
	{
		pthread_create(&c.philos[i].t, NULL, routine, &c.philos[i]);
		i++;
	}
	gettimeofday(&c.start_time, NULL);
	pthread_mutex_unlock(c.casket);
	pthread_create(&chronos, NULL, timekeeper, &c);
	while (--i >= 0)
		pthread_join(c.philos[i].t, NULL);
	pthread_join(chronos, NULL);
	return (terminator(&c, SUCCESS));
}
