/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:19:26 by miahmadi          #+#    #+#             */
/*   Updated: 2022/12/13 01:58:46 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	print_forks(t_data data)
{
	int	i;

	i = -1;
	printf("\n");
	while (++i < data.num_philos)
		printf("Fork number %d : %d\n", i, data.forks[i].is_available);
}

void	*eat(void *philo)
{
	t_philo 		*d;
	struct timeval	t;
	long long		dt;

	d = philo;
	while (d->state < 4 && !d->data->dead)
	{
		pthread_mutex_lock(&d->data->general);
		// print_forks(*(d->data));
		gettimeofday(&t, NULL);
		dt = t.tv_sec * 1000 + t.tv_usec / 1000;
		if ( dt - d->last_meal > d->data->ttd)
		{
			d->data->dead = 1;
			d->state = 4;
			printf("%lld %d is dead\n", dt - d->data->start, d->id);
			pthread_mutex_unlock(&d->data->general);
			return (d);
		}
		if (d->left_fork->is_available && d->right_fork->is_available && d->state == 2)
		{
			d->state = 0;
			d->right_fork->is_available = 0;
			d->left_fork->is_available = 0;
			pthread_mutex_lock(&(d->right_fork->fork));
			pthread_mutex_lock(&(d->left_fork->fork));
			pthread_mutex_unlock(&d->data->general);
			gettimeofday(&t, NULL);
			printf("%lld %d is eating\n", dt - d->data->start, d->id);
			d->last_meal = dt;
			usleep(d->data->tte * 1000);
			d->right_fork->is_available = 1;
			d->left_fork->is_available = 1;
			pthread_mutex_unlock(&(d->right_fork->fork));
			pthread_mutex_unlock(&(d->left_fork->fork));
		}
		else if (d->state < 4)
		{
			pthread_mutex_unlock(&d->data->general);
			if (d->state == 0)
			{
				printf("%lld %d is sleeping\n", dt - d->data->start, d->id);
				usleep(d->data->tts * 1000);
				d->state = 1;
			}
			else if (d->state == 1)
			{
				printf("%lld %d is thinking\n", dt - d->data->start, d->id);
				d->state = 2;
			}
		}
	}
	return (d);
}

int	main(int argc, char **argv)
{
	t_data		data;
	int			i;
	t_philo		*philos;
	t_fork		*forks;
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
	pthread_mutex_init(&data.general, NULL);
	pthread_mutex_init(&(data.general), NULL);
	gettimeofday(&t1, NULL);
	data.start = t1.tv_sec * 1000 + t1.tv_usec / 1000;
	data.dead = 0;
	if (argc == 6)
		data.num_eat = atoi(argv[5]);
	philos = malloc(sizeof(t_philo) * data.num_philos);
	forks = malloc(sizeof(t_fork) * data.num_philos);
	i = -1;
	while (++i < data.num_philos)
	{
		pthread_mutex_init(&(forks[i].fork), NULL);
		forks[i].is_available = 1;
	}
	data.forks = forks;
	i = -1;
	while (++i < data.num_philos)
	{
		philos[i].id = i + 1;
		philos[i].state = 2;
		philos[i].last_meal = data.start;
		philos[i].right_fork = &forks[i];
		philos[i].data = &data;
		if (i == data.num_philos - 1)
			philos[i].left_fork = &forks[0];
		else
			philos[i].left_fork = &forks[i + 1];
	}
	i = -1;
	while (++i < data.num_philos)
	{
		pthread_create(&(philos[i].thread), NULL, &eat, &philos[i]);
	}
	i = -1;
	while (++i < data.num_philos)
	{
		pthread_join(philos[i].thread, NULL);
	}
	return (0);
}