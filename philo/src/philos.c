/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 22:36:41 by bgohan            #+#    #+#             */
/*   Updated: 2022/02/23 20:20:31 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <stdio.h>

static time_t	curtime(time_t start_time)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return (timeval.tv_sec * 1000 + timeval.tv_usec / 1000 - start_time);
}

void	*philos(void *arg)
{
	t_phil			*phil;

	phil = arg;
	while (1)
	{
		if (curtime(*phil->start) < phil->change_time)
			continue ;
		phil->state = (phil->state + 1) % 3;
		if (phil->state == EAT)
		{
			if (phil->n == 0)
			{
				pthread_mutex_lock(phil->right_fork);
				printf("%lu %zu has taken a fork\n", curtime(*phil->start), phil->n);
				pthread_mutex_lock(phil->left_fork);
				printf("%lu %zu has taken a fork\n", curtime(*phil->start), phil->n);
			}
			else
			{
				pthread_mutex_lock(phil->left_fork);
				printf("%lu %zu has taken a fork\n", curtime(*phil->start), phil->n);
				pthread_mutex_lock(phil->right_fork);
				printf("%lu %zu has taken a fork\n", curtime(*phil->start), phil->n);
			}
			phil->change_time = curtime(*phil->start) + phil->args->eat_time;
			printf("%lu %zu is eating\n", curtime(*phil->start), phil->n);
		}
		else if (phil->state == SLEEP)
		{
			pthread_mutex_unlock(phil->left_fork);
			pthread_mutex_unlock(phil->right_fork);
			phil->change_time = curtime(*phil->start) + phil->args->sleep_time;
			printf("%lu %zu is sleeping\n", curtime(*phil->start), phil->n);
		}
		else
		{
			phil->change_time = phil->last_meal + phil->args->die_time - phil->args->eat_time;
			printf("%lu %zu is thinking\n", curtime(*phil->start), phil->n);
		}
	}
	return (NULL);
}
