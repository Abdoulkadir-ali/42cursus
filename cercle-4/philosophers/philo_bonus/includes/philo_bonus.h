/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 09:53:13 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/02 11:08:28 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define MAX_PHILOS 200

typedef struct s_rules
{
	int		nb_philo;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	int		nb_meals;
	sem_t	*forks;
	sem_t	*print;
	sem_t	*stop;
	sem_t	*meal_check;
	sem_t	*waiter;
}			t_rules;

typedef struct s_philo
{
	int		id;
	int		meals_eaten;
	long	last_meal;
	long	sim_start;
	pid_t	pid;
	t_rules	*rules;
	sem_t	meal_lock;
}			t_philo;

/* --- Helper --- */
long		now(void);
void		precise_usleep(long ms);
int			ft_atoi(const char *str);
size_t		ft_strlen(const char *s);
void		parse_rules(t_rules *rules, char **av);
void		init_semaphores(t_rules *r);
void		philo(t_rules *rules);

/* --- Print --- */
void		print_status(t_philo *p, char *msg);
void		ft_putstr_fd(char *s, int fd);

/* --- Routine --- */
void		*meal_monitor(void *arg);
void		philo_routine(t_philo *p);
void		philo_eat(t_philo *p);
void		philo_sleep(t_philo *p);
void		philo_think(t_philo *p);

/* --- Death --- */
void		*death_monitor(void *arg);

#endif
