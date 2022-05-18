/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 00:27:08 by bgohan            #+#    #+#             */
/*   Updated: 2022/02/23 17:03:35 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/types.h>

typedef struct s_args
{
	unsigned int	n;
	unsigned int	die_time;
	unsigned int	eat_time;
	unsigned int	sleep_time;
	unsigned int	eat_number;
}	t_args;

# define EAT 0
# define SLEEP 1
# define THINK 2

typedef struct s_phil
{
	size_t			n;
	int				state;
	time_t			last_meal;
	time_t			change_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	time_t			*start;
	t_args			*args;
}	t_phil;

t_args	*parse(int argc, char **argv);
int		simulation(t_args *args);
void	*philos(void *arg);

int		write_usage(void);
void	*free_phils(t_phil **phils, size_t n);
void	*destroy_mutexes(pthread_mutex_t *mutexes, size_t n);
void	join_threads(pthread_t *threads, size_t n);

#endif