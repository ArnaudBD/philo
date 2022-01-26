#include "includes/philo.h"

// void	*routine(void* args)
// {

// }

int	main(int argc, char *argv[])
{
	t_config	c;

	if (init(&c, argc, argv) != 0)
		terminator(&c, ERR_INIT);
	if (parsing(argc, argv) != 0)
		terminator(&c, ERR_PARS);
// Show the mutex\'s addresses 
	int i = 0;
	while (i < c.number_of_philosophers)
	{
		printf("&c.forklist[%d] == %p\n", i, &c.forklist[i]);
		printf("Philo%d\n", c.philos[i].id);
		printf("lfork == %p\n", c.philos[i].lfork);
		printf("rfork == %p\n\n",c.philos[i].rfork);
		i++;
	}
	return (terminator(&c, 0));
}