/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 01:02:38 by bgohan            #+#    #+#             */
/*   Updated: 2022/02/22 22:23:58 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

int	write_usage(void)
{
	printf("usage: philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	return (0);
}

void	*destroy_mutexes(pthread_mutex_t *mutexes, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		pthread_mutex_destroy(&mutexes[i++]);
	free(mutexes);
	return (NULL);
}

void	*free_phils(t_phil **phils, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		free(phils[i++]);
	free(phils);
	return (NULL);
}

void	join_threads(pthread_t *threads, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		pthread_join(threads[i++], NULL);
	free(threads);
}
