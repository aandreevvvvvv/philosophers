/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simul.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 02:10:34 by bgohan            #+#    #+#             */
/*   Updated: 2022/02/23 20:20:25 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <sys/time.h>

static pthread_mutex_t	*init_mutexes(size_t n)
{
	pthread_mutex_t	*mutexes;
	size_t			i;

	mutexes = malloc(n * sizeof(pthread_mutex_t));
	if (!mutexes)
		return (NULL);
	i = 0;
	while (i < n)
	{
		if (pthread_mutex_init(&mutexes[i++], NULL))
			return (destroy_mutexes(mutexes, i));
	}
	return (mutexes);
}

static void	init_phils(t_phil **phils, t_args *args, time_t *start, \
									pthread_mutex_t *mutexes)
{
	size_t	i;

	i = 0;
	while (i < args->n)
	{
		phils[i]->state = THINK;
		phils[i]->last_meal = 0;
		phils[i]->change_time = 0;
		phils[i]->start = start;
		phils[i]->left_fork = &mutexes[(args->n + i - 1) % args->n];
		phils[i]->right_fork = &mutexes[(i + 1) % args->n];
		phils[i]->n = i;
		phils[i]->args = args;
		++i;
	}
}

static t_phil	**init(t_args *args, time_t *start, pthread_mutex_t **mutexes)
{
	t_phil	**phils;
	size_t	i;

	*mutexes = init_mutexes(args->n);
	if (!*mutexes)
		return (NULL);
	phils = malloc(args->n * sizeof(t_phil *));
	if (!phils)
		return (NULL);
	i = 0;
	while (i < args->n)
	{
		phils[i] = malloc(sizeof(t_phil));
		if (!phils[i])
			return (free_phils(phils, i));
		++i;
	}
	init_phils(phils, args, start, *mutexes);
	return (phils);
}

static int	create_threads(pthread_t *threads, t_phil **phils, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (pthread_create(&threads[i], NULL, philos, phils[i]))
		{
			join_threads(threads, i);
			return (0);
		}
		++i;
	}
	return (1);
}

int	simulation(t_args *args)
{
	t_phil			**phils;
	pthread_t		*threads;
	pthread_mutex_t	*mutexes;
	struct timeval	timeval;
	time_t			start;

	phils = init(args, &start, &mutexes);
	if (!phils)
		return (0);
	threads = malloc(args->n * sizeof(pthread_t));
	if (!threads)
		return (0);
	gettimeofday(&timeval, NULL);
	start = timeval.tv_sec * 1000 + timeval.tv_usec / 1000;
	if (create_threads(threads, phils, args->n))
		join_threads(threads, args->n);
	destroy_mutexes(mutexes, args->n);
	free_phils(phils, args->n);
	return (1);
}
