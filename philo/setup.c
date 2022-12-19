/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 03:30:18 by miahmadi          #+#    #+#             */
/*   Updated: 2022/12/19 14:22:43 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_data(t_data *data, char **argv, int argc)
{
	struct timeval	t1;

	data->num_philos = atoi(argv[1]);
	data->ttd = atoi(argv[2]);
	data->tte = atoi(argv[3]);
	data->tts = atoi(argv[4]);
	pthread_mutex_init(&data->general_mutex, NULL);
	pthread_mutex_init(&(data->msg_mutex), NULL);
	gettimeofday(&t1, NULL);
	data->start = t1.tv_sec * 1000 + t1.tv_usec / 1000;
	data->dead = 0;
	if (argc == 6)
		data->num_eat = atoi(argv[5]);
	else
		data->num_eat = INT_MAX;
}

t_fork	*set_forks(int num)
{
	int		i;
	t_fork	*forks;

	forks = malloc(sizeof(t_fork) * num);
	if (!forks)
		return (NULL);
	i = -1;
	while (++i < num)
	{
		pthread_mutex_init(&(forks[i].fork), NULL);
		forks[i].is_available = 1;
	}
	return (forks);
}

t_fork	*get_fork(int i, t_data *data, int mod)
{
	if (mod == 0)
	{
		if (i == data->num_philos - 1)
			return (&(data->forks[0]));
		else
			return (&(data->forks[i]));
	}
	else
	{
		if (i == data->num_philos - 1)
		{
			if (data->num_philos == 1)
				return (NULL);
			else
				return (&(data->forks[i]));
		}
		else
			return (&(data->forks[i + 1]));
	}
	return (NULL);
}

t_philo	*set_philos(t_data *data)
{
	int		i;
	t_philo	*philos;

	philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!philos)
		return (NULL);
	i = -1;
	while (++i < data->num_philos)
	{
		philos[i].id = i + 1;
		philos[i].state = 1;
		philos[i].num_ate = 0;
		philos[i].last_meal = data->start;
		philos[i].right_fork = get_fork(i, data, 0);
		philos[i].left_fork = get_fork(i, data, 1);
		philos[i].data = data;
	}
	return (philos);
}

int	check_data(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("Error: Number of arguments is not correct - <number_of_philosophers> \
			<time_to_die> <time_to_eat> <time_to_sleep> \
			<[number_of_times_each_philosopher_must_eat]>\n");
		return (0);
	}
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[2]) < 1 \
		|| ft_atoi(argv[3]) < 1 || ft_atoi(argv[4]) < 1)
	{
		printf("Error: There is no philosophor\n");
		return (0);
	}
	if (ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0 || ft_atoi(argv[4]) < 0)
	{
		printf("Error: Arguments should be non-negative\n");
		return (0);
	}
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) < 0)
		{
			printf("Error: Arguments should be non-negative\n");
			return (0);
		}
	}
	return (1);
}
