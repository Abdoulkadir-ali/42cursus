/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 22:01:06 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/02 11:10:01 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_PHILOS 200

typedef struct s_rules
{
	int				nb_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
}					t_rules;

typedef struct s_philo
{
	size_t			id;
	size_t			sim_start;
	size_t			last_meal;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
	t_rules			*rules;
}					t_philo;

/* --- Utilities --- */
int					ft_putnbr_base(long long int n, const char *base);
int					ft_atoi(const char *str);
long				now(void);
void				precise_usleep(long ms);
void				print_status(t_philo *philo, char *msg);

/* --- Core --- */
void				parse_rules(t_rules *rules, char **av);
void				philo(t_rules *rules);

/* --- Helper --- */
void				init_mutexes(t_rules *rules, pthread_mutex_t *forks);
void				create_philos(t_rules *rules, t_philo *data,
						pthread_mutex_t *forks, pthread_t *philos);
void				join_threads(t_rules *rules, pthread_t *philos,
						pthread_t monitor);
void				destroy_mutexes(t_rules *rules, pthread_mutex_t *forks);

/* --- Routine --- */
void				*monitor_routine(void *arg);
void				*philo_routine(void *arg);
int					philo_eat(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				philo_think(t_philo *philo);
int					check_dead_flag(t_philo *philo);

#endif