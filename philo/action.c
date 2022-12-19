/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 03:33:46 by miahmadi          #+#    #+#             */
/*   Updated: 2022/12/18 03:35:06 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_philo *philo)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	if (get_time() - philo->last_meal > philo->data->ttd)
	{
		philo->state = 0;
		return (0);
	}
	return (1);
}

void	check_all(t_philo *philos, t_data *data)
{
	int				i;

	while (!data->dead)
	{
		i = -1;
		while (++i < data->num_philos)
		{
			pthread_mutex_lock(&(data->general_mutex));
			pthread_mutex_lock(&(data->msg_mutex));
			if (get_time() - philos[i].last_meal > data->ttd)
			{
				data->dead = 1;
				if (philos[i].num_ate < data->num_eat)
					printf("%s%-8lldms%s philo %-3d %sdied\n%s", KCYN, get_time()
						- data->start, KNRM, philos[i].id, KRED, KNRM);
				pthread_mutex_unlock(&(data->general_mutex));
				pthread_mutex_unlock(&(data->msg_mutex));
				break ;
			}
			pthread_mutex_unlock(&(data->general_mutex));
			pthread_mutex_unlock(&(data->msg_mutex));
			mod_sleep(1);
		}
	}
}

void	grab_forks(pthread_mutex_t *m, t_philo *d)
{
	pthread_mutex_lock(m);
	print_msg("grab a fork", d, 0, KMAG);
}

int	eat(t_philo	*d)
{
	grab_forks(&(d->right_fork->fork), d);
	if (d->left_fork)
	{
		grab_forks(&(d->left_fork->fork), d);
		pthread_mutex_lock(&(d->data->general_mutex));
		if (d->data->dead)
		{
			pthread_mutex_unlock(&(d->data->general_mutex));
			pthread_mutex_unlock(&(d->right_fork->fork));
			pthread_mutex_unlock(&(d->left_fork->fork));
			return (0);
		}
		print_msg("is eating", d, 1, KGRN);
		d->num_ate++;
		pthread_mutex_unlock(&(d->data->general_mutex));
		mod_sleep(d->data->tte);
	}
	pthread_mutex_unlock(&(d->right_fork->fork));
	if (d->left_fork)
		pthread_mutex_unlock(&(d->left_fork->fork));
	return (1);
}

void	*philo_act(void	*philo)
{
	t_philo			*d;

	d = philo;
	if (d->id % 2 == 0)
		mod_sleep(d->data->tte / 11);
	while (check_dead(d) && d->state && d->num_ate < d->data->num_eat)
	{
		if (!eat(d))
			return (NULL);
		if (d->num_ate == d->data->num_eat)
			return (NULL);
		print_msg("is sleeping", d, 0, KBLU);
		mod_sleep(d->data->tts);
		print_msg("is thinking", d, 0, KYEL);
	}
	return (NULL);
}
