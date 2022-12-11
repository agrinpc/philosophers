/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:19:26 by miahmadi          #+#    #+#             */
/*   Updated: 2022/12/11 20:19:43 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

pthread_mutex_t	mutex;

void	*eat(void *data)
{
	t_data 			*d;
	struct timeval	t;
	long long		dt;
	int				id;

	d = data;
	pthread_mutex_lock(&mutex);
	id = d->curPhilo;
	gettimeofday(&t, NULL);
	dt = t.tv_sec * 1000 + t.tv_usec / 1000 - d->philos[id].last_meal;
	if ( dt > 6000)
		d->dead = 1;
	printf("Philo Number %d ==> ID: %d, Status: %d, dt = %lld, Thread : %ld\n", id, d->philos[id].id, d->dead, dt, pthread_self());
	sleep(1);
	pthread_mutex_unlock(&mutex);
	return (d);
}

int	main(int argc, char **argv)
{
	t_data		data;
	int			i;
	t_philo		*philos;
	pthread_mutex_t *forks;
	struct timeval t1;

	if (argc !=5 && argc != 6)
	{
		printf("Error: Number of arguments is not correct - <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> <[number_of_times_each_philosopher_must_eat]>\n");
		return (0);
	}
	data.num_philos = atoi(argv[1]);
	data.ttd = atoi(argv[2]);
	data.tte = atoi(argv[3]);
	data.tts = atoi(argv[4]);
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_init(&(data.general), NULL);
	data.dead = 0;
	if (argc == 6)
		data.num_eat = atoi(argv[5]);
	philos = malloc(sizeof(t_philo) * data.num_philos);
	forks = malloc(sizeof(pthread_mutex_t) * data.num_philos);
	i = -1;
	while (++i < data.num_philos)
		pthread_mutex_init(&forks[i], NULL);
	i = -1;
	while (++i < data.num_philos)
	{
		gettimeofday(&t1, NULL);
		philos[i].id = i + 1;
		philos[i].last_meal = t1.tv_sec * 1000 + t1.tv_usec / 1000;
		philos[i].right_fork = forks[i];
		if (i == data.num_philos - 1)
			philos[i].left_fork = forks[0];
		else
			philos[i].left_fork = forks[i + 1];
	}
	data.philos = philos;
	while (!data.dead)
	{
		i = -1;
		while (++i < data.num_philos)
		{
			data.curPhilo = i;
			printf("%d\n",data.curPhilo);
			pthread_create(&(philos[i].thread), NULL, &eat, &data);
		}
		i = -1;
		while (++i < data.num_philos)
		{
			pthread_join(philos[i].thread, NULL);
		}
		
	}
	return (0);
}