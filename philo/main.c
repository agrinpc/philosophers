/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:19:26 by miahmadi          #+#    #+#             */
/*   Updated: 2022/12/17 08:39:29 by miahmadi         ###   ########.fr       */
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

void	mod_sleep(int ms)
{
	struct timeval	t;
	long			dt;

	gettimeofday(&t, NULL);
	dt = t.tv_sec * 1000 + t.tv_usec / 1000;
	while (t.tv_sec * 1000 + t.tv_usec / 1000 - dt < ms)
	{
		usleep(ms);
		gettimeofday(&t, NULL);
	}
}

void	print_msg(char *msg, t_philo *philo, int mod)
{
	struct timeval	t;
	long long		dt;

	pthread_mutex_lock(&(philo->data->msg_mutex));
	gettimeofday(&t, NULL);
	dt = t.tv_sec * 1000 + t.tv_usec / 1000 - philo->data->start;
	if (mod == 1)
		philo->last_meal = t.tv_sec * 1000 + t.tv_usec / 1000;
	if (!philo->data->dead)
		printf("%lld philo %d %s\n", dt, philo->id, msg);
	pthread_mutex_unlock(&(philo->data->msg_mutex));
}

int	check_dead(t_philo *philo)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	if (t.tv_sec * 1000 + t.tv_usec / 1000 - philo->last_meal > philo->data->ttd)
	{
		philo->state = 0;
		return (0);
	}
	return (1);
}

int	check_all(t_philo *philos, t_data *data)
{
	int				i;
	struct timeval	t;

	while (!data->dead)
	{
		i = -1;
		while (++i < data->num_philos)
		{
			
			pthread_mutex_lock(&(data->general_mutex));
			pthread_mutex_lock(&(data->msg_mutex));
			gettimeofday(&t, NULL);
			if (t.tv_sec * 1000 + t.tv_usec / 1000 - philos[i].last_meal > data->ttd)
			{
				data->dead = 1;
				printf("%lld philo %d died\n", t.tv_sec * 1000 + t.tv_usec / 1000 - data->start, philos[i].id);
				pthread_mutex_unlock(&(data->general_mutex));
				pthread_mutex_unlock(&(data->msg_mutex));
				break ;
			}
			pthread_mutex_unlock(&(data->general_mutex));
			pthread_mutex_unlock(&(data->msg_mutex));
			mod_sleep(1);
		}
	}
	return (1);
}

void	*philo_act(void	*philo)
{
	t_philo			*d;

	d = philo;
	if (d->id % 2 == 0)
		mod_sleep(d->data->tte / 11);
	while (check_dead(d) && d->state)
	{
		pthread_mutex_lock(&(d->right_fork->fork));
		if (d->left_fork)
		{
			pthread_mutex_lock(&(d->left_fork->fork));
			pthread_mutex_lock(&(d->data->general_mutex));
			if (d->data->dead)
			{
				pthread_mutex_unlock(&(d->data->general_mutex));
				pthread_mutex_unlock(&(d->right_fork->fork));
				pthread_mutex_unlock(&(d->left_fork->fork));
				return (d);
			}
			print_msg("is eating", d, 1);
			pthread_mutex_unlock(&(d->data->general_mutex));
			mod_sleep(d->data->tte);
		}
		pthread_mutex_unlock(&(d->right_fork->fork));
		if (d->left_fork)
			pthread_mutex_unlock(&(d->left_fork->fork));
		print_msg("is sleeping", d, 0);
		mod_sleep(d->data->tts);
		print_msg("is thinking", d, 0);
	}
	return (d);
}

void free_it(t_data	data, t_fork *forks, t_philo *philos)
{
	int		i;
	int		n;

	n = data.num_philos;
	pthread_mutex_destroy(&(data.general_mutex));
	pthread_mutex_destroy(&(data.msg_mutex));
	i = -1;
	while (++i < n)
	{
		pthread_mutex_destroy(&(forks[i].fork));
		free(&forks[i]);
		free(&philos[i]);
	}
	free(forks);
	free(philos);
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
	if (data.num_philos < 1)
	{
		printf("Minimum number of philosophers is 1\n");
		return (0);
	}	
	data.ttd = atoi(argv[2]);
	data.tte = atoi(argv[3]);
	data.tts = atoi(argv[4]);
	pthread_mutex_init(&data.general_mutex, NULL);
	pthread_mutex_init(&(data.msg_mutex), NULL);
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
		philos[i].state = 1;
		philos[i].last_meal = data.start;
		if (i == data.num_philos - 1)
			philos[i].right_fork = &forks[0];
		else
			philos[i].right_fork = &forks[i];
		if (i == data.num_philos - 1)
		{
			if (data.num_philos == 1)
				philos[i].left_fork = NULL;
			else
				philos[i].left_fork = &forks[i];
		}
		else
			philos[i].left_fork = &forks[i + 1];
		philos[i].data = &data;
	}
	data.philos = (void *)philos;
	i = -1;
	while (++i < data.num_philos)
	{
		pthread_create(&(philos[i].thread), NULL, &philo_act, &philos[i]);
	}
	check_all(philos, &data);
	i = -1;
	while (++i < data.num_philos)
	{
		pthread_join(philos[i].thread, NULL);
	}
	// i = -1;
	// pthread_mutex_destroy(&(data.general_mutex));
	// pthread_mutex_destroy(&(data.msg_mutex));
	// while (++i < data.num_philos)
	// {
	// 	pthread_mutex_destroy(&(forks[i].fork));
	// 	free(&forks[i]);
	// 	free(&philos[i]);
	// }
	// free(philos);
	// free(forks);
	free_it(data, forks, philos);
	return (0);
}