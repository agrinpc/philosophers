/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 03:33:34 by miahmadi          #+#    #+#             */
/*   Updated: 2022/12/21 16:17:21 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	t;
	long			dt;

	gettimeofday(&t, NULL);
	dt = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (dt);
}

void	mod_sleep(int ms)
{
	long			dt;

	dt = get_time();
	while (get_time() - dt < ms)
		usleep(ms);
}

void	print_msg(char *msg, t_philo *philo, int mod, char *color)
{
	struct timeval	t;
	long long		dt;

	pthread_mutex_lock(&(philo->data->msg_mutex));
	gettimeofday(&t, NULL);
	dt = get_time() - philo->data->start;
	if (mod == 1)
		philo->last_meal = get_time();
	if (!philo->data->dead)
		printf("%s%-8lldms%s philo %-3d %s%s\n",
			KCYN, dt, KNRM, philo->id, color, msg);
	pthread_mutex_unlock(&(philo->data->msg_mutex));
}
