/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:19:22 by miahmadi          #+#    #+#             */
/*   Updated: 2022/12/11 20:10:03 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>


typedef struct s_philo
{
	int				id;
	int				state;
	long long		last_meal;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
	pthread_t		thread;
}	t_philo;


typedef struct s_data
{
	int		tte;
	int		ttd;
	int		tts;
	int		num_philos;
	int		num_eat;
	int		dead;
	t_philo	*philos;
	int		curPhilo;
	pthread_mutex_t	general;
} 	t_data;

#endif