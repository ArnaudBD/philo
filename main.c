#include "includes/philo.h"

int	main(int argc, char *argv[])
{
	t_config	c;
	// t_philo		p;
	int			i;
	// pthread_t	chronos;

	if (parsing(argc, argv, &c) == FAILURE)
		return (terminator(&c, ERR_PARS));
	if (init(&c, argc, argv) == FAILURE)
		return (terminator(&c, ERR_INIT));

// Creating threads
	i = 0;
	while (i < c.number_of_philosophers)
	{
		pthread_create(&c.philos[i].t, NULL, routine, &c.philos[i]);
		i++;
	}
// Chronos thread
	// pthread_create(&chronos, NULL, timekeeper, NULL);
	// pthread_detach(chronos);

// Join threads
	while (i >= 0)
	{
		pthread_join(c.philos[i].t, NULL);
		i--;
	}

// // Show the mutex\'s addresses 
// 	i = 0;
// 	while (i < c.number_of_philosophers)
// 	{
// 		printf("&c.forklist[%d] == %p\n", i, &c.forklist[i]);
// 		printf("Philo%d\n", c.philos[i].id);
// 		printf("lfork == %p\n", c.philos[i].lfork);
// 		printf("rfork == %p\n\n",c.philos[i].rfork);
// 		i++;
// 	}
	printf("Time of start is %20lld\n", c.ms_start + 1000);
	return (terminator(&c, SUCCESS));
}