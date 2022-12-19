/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 23:20:56 by miahmadi          #+#    #+#             */
/*   Updated: 2022/12/19 14:32:39 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if ((c > 47 && c < 58))
		return (1);
	return (0);
}

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	output;

	sign = 1;
	output = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr)
	{
		if (ft_isdigit(*nptr))
			output = output * 10 + (*nptr - 48);
		else
			return (sign * output);
		nptr++;
	}
	return (sign * output);
}

void	free_it(t_data	*data, t_philo *philos)
{
	int		i;
	int		n;

	n = data->num_philos;
	pthread_mutex_destroy(&(data->general_mutex));
	pthread_mutex_destroy(&(data->msg_mutex));
	i = -1;
	while (++i < n)
		pthread_mutex_destroy(&(data->forks[i].fork));
	free(data->forks);
	free(philos);
}
