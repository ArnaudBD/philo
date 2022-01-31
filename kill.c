#include "includes/philo.h"

int	terminator(t_config *c, int code)
{
	int	i;

	while (i < c->number_of_philosophers)
	{
		pthread_mutex_destroy(&c->forklist[i]);
		i++;
	}	
	if (code != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
