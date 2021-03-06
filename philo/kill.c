/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <abiju-du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 23:54:57 by abiju-du          #+#    #+#             */
/*   Updated: 2022/02/03 23:55:02 by abiju-du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	printerror(int code)
{
	if (code == ERR_PARS)
		printf("Parsing error\n");
}

int	terminator(t_config *c, int code)
{
	int	i;

	i = 0;
	while (i < c->number_of_philosophers && code != ERR_INIT \
	&& code != ERR_PARS)
	{
		pthread_mutex_destroy(&c->forklist[i]);
		i++;
	}	
	if (c->philos && code != ERR_INIT && code != ERR_PARS)
	{
		pthread_mutex_destroy(c->stomach);
		free(c->stomach);
		free(c->philos);
		free(c->forklist);
	}
	if (code != ERR_INIT && code != ERR_PARS)
	{
		pthread_mutex_destroy(c->casket);
		free(c->casket);
	}
	printerror(code);
	if (code != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}	
