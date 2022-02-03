/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <abiju-du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 23:56:09 by abiju-du          #+#    #+#             */
/*   Updated: 2022/02/03 23:56:12 by abiju-du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H
# define SUCCESS 0
# define FAILURE 1

# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

enum
{
	ERR_ARGC = 1,
	ERR_INIT,
	ERR_PARS
};

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*casket;
	pthread_mutex_t	*stomach;
	int				dead_body;
	pthread_t		t;
	struct timeval	tv;
	struct timeval	start_time;
	long long int	ms_start;
	long long int	last_meal;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_t_e_p_m_eat;
	int				full;
}	t_philo;

typedef struct s_config
{
	t_philo			*philos;
	pthread_mutex_t	*forklist;
	pthread_mutex_t	*casket;
	pthread_mutex_t	*stomach;
	int				dead_body;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_t_e_p_m_eat;
	struct timeval	start_time;
	long long int	ms_start;
}	t_config;

// INIT
int				parsing(int argc, char *argv[], t_config *c);
int				init(t_config *c, int argc, char *argv[]);

// UTILS
int				ft_atoi(const char *str);
long long int	t_aft_start(struct timeval start_time);
int				ft_isdead(t_philo *p);

// KILL
int				terminator(t_config *c, int code);

// THREADS
void			starting_block(struct timeval start_time);
void			*routine(void *arg);
void			*routine_solo(void *arg);

// DEATHNOTE
void			*timekeeper(void *arg);

// ACTIONS
int				grabing_forks(t_philo *p, int *i);
int				eating(t_philo *p);
int				sleeping_and_thinking(t_philo *p);

#endif
