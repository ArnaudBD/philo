#include "includes/philo.h"

int	terminator(t_config *c, int code)
{
	int	i;

	i = 0;
	if (c->philos && code != ERR_INIT && code != ERR_PARS)
		free(c->philos);
	if (c->forklist && code != ERR_INIT && code != ERR_PARS)
		free(c->forklist);
	while (i < c->number_of_philosophers && code != ERR_INIT && code != ERR_PARS)
	{
		pthread_mutex_destroy(&c->forklist[i]);
		i++;
	}	
	if (code != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
