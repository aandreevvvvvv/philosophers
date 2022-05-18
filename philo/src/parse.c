/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 00:38:13 by bgohan            #+#    #+#             */
/*   Updated: 2022/02/23 17:12:48 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <limits.h>

static unsigned int	ft_atoui(const char *str)
{
	unsigned int	ans;
	int				i;

	ans = 0;
	i = 0;
	while (str[i])
		ans = ans * 10 + str[i++] - '0';
	return (ans);
}

static int	check(const char *str)
{
	size_t		i;
	long long	ans;

	i = 0;
	ans = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		ans = ans * 10 + str[i] - '0';
		if (ans > UINT_MAX)
			return (0);
		++i;
	}
	return (1);
}

t_args	*parse(int argc, char **argv)
{
	t_args	*args;
	size_t	i;

	if (argc < 5 || argc > 6)
		return (NULL);
	i = 1;
	while (i < (size_t)argc)
		if (!check(argv[i++]))
			return (NULL);
	args = malloc(sizeof(t_args));
	if (!args)
		return (NULL);
	args->n = ft_atoui(argv[1]);
	args->die_time = ft_atoui(argv[2]);
	args->eat_time = ft_atoui(argv[3]);
	args->sleep_time = ft_atoui(argv[4]);
	if (argc == 6)
		args->eat_number = ft_atoui(argv[5]);
	else
		args->eat_number = UINT_MAX;
	return (args);
}
